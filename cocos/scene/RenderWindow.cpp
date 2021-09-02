/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.
 
 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "scene/RenderWindow.h"
#include "scene/Camera.h"

namespace cc {
namespace scene {
bool RenderWindow::initialize(gfx::Device *device, const IRenderWindowInfo &info) {
    if (info.title.has_value() && !info.title.value().empty()) {
        _title = info.title.value();
    }
    if (info.swapchainBufferIndices.has_value()) {
        _swapchainBufferIndices = info.swapchainBufferIndices.value();
    }

    if (info.shouldSyncSizeWithSwapchain.has_value()) {
        _swapchainBufferIndices = info.swapchainBufferIndices.value();
    }
    _width  = info.width;
    _height = info.height;

    gfx::ColorAttachmentList    colorAttachments       = info.renderPassInfo.colorAttachments;
    gfx::DepthStencilAttachment depthStencilAttachment = info.renderPassInfo.depthStencilAttachment;
    for (auto &colorAttachment : colorAttachments) {
        if (colorAttachment.format == gfx::Format::UNKNOWN) {
            colorAttachment.format = device->getColorFormat();
        }
    }
    if (depthStencilAttachment.format == gfx::Format::UNKNOWN) {
        depthStencilAttachment.format = device->getDepthStencilFormat();
    }

    _renderPass = device->createRenderPass(info.renderPassInfo);

    for (uint32_t i = 0; i < colorAttachments.size(); ++i) {
        gfx::Texture *colorTex = nullptr;
        if (!(_swapchainBufferIndices & (1 << i))) {
            colorTex                 = device->createTexture({gfx::TextureType::TEX2D,
                                              gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED,
                                              colorAttachments[i].format,
                                              _width,
                                              _height});
            _hasOffScreenAttachments = true;
        } else {
            _hasOnScreenAttachments = true;
        }
        _colorTextures.emplace_back(colorTex);
    }

    // Use the sign bit to indicate depth attachment
    if (depthStencilAttachment.format != gfx::Format::UNKNOWN) {
        if (_swapchainBufferIndices >= 0) {
            _depthStencilTexture     = device->createTexture({gfx::TextureType::TEX2D,
                                                          gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT | gfx::TextureUsageBit::SAMPLED,
                                                          depthStencilAttachment.format,
                                                          _width,
                                                          _height});
            _hasOffScreenAttachments = true;
        } else {
            _hasOnScreenAttachments = true;
        }
    }

    _frameBuffer = device->createFramebuffer({_renderPass, _colorTextures, _depthStencilTexture});
    return true;
}

void RenderWindow::destroy() {
    clearCameras();
    if (_depthStencilTexture != nullptr) {
        CC_SAFE_DESTROY(_depthStencilTexture);
    }
    for (auto *colorTexture : _colorTextures) {
        CC_SAFE_DESTROY(colorTexture);
    }
    _colorTextures.clear();
    CC_SAFE_DESTROY(_frameBuffer);
}

void RenderWindow::resize(uint32_t width, uint32_t height) {
    _width  = width;
    _height = height;

    bool needRebuild = false;

    if (_depthStencilTexture != nullptr) {
        _depthStencilTexture->resize(width, height);
        needRebuild = true;
    }

    for (gfx::Texture *colorTexture : _colorTextures) {
        if (colorTexture != nullptr) {
            colorTexture->resize(width, height);
            needRebuild = true;
        }
    }

    if (needRebuild && _frameBuffer != nullptr) {
        _frameBuffer->destroy();
        _frameBuffer->initialize({
            _renderPass,
            _colorTextures,
            _depthStencilTexture,
        });
    }

    for (Camera *camera : _cameras) {
        if (camera->isWindowSize) {
            camera->resize(width, height);
        }
    }
}

void RenderWindow::extractRenderCameras(std::vector<Camera *> &cameras) {
    for (Camera *camera : cameras) {
        if (camera->isEnabled()) {
            camera->update();
            cameras.push_back(camera);
        }
    }
}

void RenderWindow::attachCamera(Camera *camera) {
    for (Camera *cam : _cameras) {
        if (cam == camera) return;
    }
    _cameras.emplace_back(camera);
    sortCameras();
}

void RenderWindow::detachCamera(Camera *camera) {
    for (auto it = _cameras.begin(); it != _cameras.end(); ++it) {
        if (*it == camera) {
            _cameras.erase(it);
            return;
        }
    }
}

void RenderWindow::clearCameras() {
    for (Camera *camera : _cameras) {
        CC_SAFE_DESTROY(camera);
    }
    _cameras.clear();
}

void RenderWindow::sortCameras() {
    std::sort(_cameras.begin(), _cameras.end(), [](Camera *a, Camera *b) { return a->getPriority() - b->getPriority(); });
}

} // namespace scene

} // namespace cc