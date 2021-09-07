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

#include "core/assets/RenderTexture.h"
#include "core/Root.h"
#include "core/utils/IDGenerator.h"
#include "renderer/gfx-base/GFXDef-common.h"

namespace {
// TODO(xwx): ts is to define a global value in sampler-lib.ts
uint64_t getDefaultSamlerHash() {
    auto defaultInfo            = cc::gfx::SamplerInfo();
    defaultInfo.cmpFunc         = cc::gfx::ComparisonFunc::NEVER; //defaultInfo.cmpFunc seems diffent between ts and cpp
    uint64_t defaultSamplerHash = cc::pipeline::SamplerLib::genSamplerHash(defaultInfo);
    return defaultSamplerHash;
}

cc::gfx::RenderPassInfo getPassInfo() {
    auto passInfo = cc::gfx::RenderPassInfo();
    for (auto &colorAttachment : passInfo.colorAttachments) {
        colorAttachment.endAccesses = std::vector<cc::gfx::AccessType>{cc::gfx::AccessType::COLOR_ATTACHMENT_WRITE};
    }
    return passInfo;
}

cc::scene::IRenderWindowInfo windowInfo{
    .width          = 1,
    .height         = 1,
    .renderPassInfo = getPassInfo()};
} // namespace
namespace cc {

static IDGenerator idGenerator("RenderTex");

void RenderTexture::initialize(const IRenderTextureCreateInfo &info) {
    _name   = info.name.value();
    _width  = info.width;
    _height = info.height;
    initWindow(info);
}

void RenderTexture::reset(const IRenderTextureCreateInfo &info) {
    initialize(info);
}

bool RenderTexture::destroy() {
    if (_window != nullptr) {
        Root::getInstance()->destroyWindow(_window);
        _window = nullptr;
    }
    return Super::destroy();
}

void RenderTexture::resize(uint32_t width, uint32_t height) {
    _width  = width;
    _height = height;
    if (_window != nullptr) {
        _window->resize(_width, _height);
    }
    // emit(std::string("resize"), _window); //TODO(xwx): not inherit form Eventify in Asset base class
}

gfx::Texture *RenderTexture::getGFXTexture() {
    return _window ? _window->getFramebuffer()->getColorTextures()[0] : nullptr;
}

gfx::Sampler *RenderTexture::getGFXSampler() {
    return pipeline::SamplerLib::getSampler(getDefaultSamlerHash());
}

uint64_t RenderTexture::getSamplerHash() const {
    return getDefaultSamlerHash();
}

void RenderTexture::onLoaded() {
    initWindow();
}

void RenderTexture::initWindow() {
    windowInfo.title          = _name;
    windowInfo.width          = _width;
    windowInfo.height         = _height;
    windowInfo.renderPassInfo = getPassInfo();

    if (_window != nullptr) {
        _window->destroy();
        _window->initialize(Root::getInstance()->getDevice(), windowInfo);
    } else {
        _window = Root::getInstance()->createWindow(windowInfo);
    }
}

void RenderTexture::initWindow(const IRenderTextureCreateInfo &info) {
    windowInfo.title  = _name;
    windowInfo.width  = _width;
    windowInfo.height = _height;
    if (info.passInfo.has_value()) {
        windowInfo.renderPassInfo = info.passInfo.value();
    } else {
        windowInfo.renderPassInfo = getPassInfo();
    }
    if (_window != nullptr) {
        _window->destroy();
        _window->initialize(Root::getInstance()->getDevice(), windowInfo);
    } else {
        _window = Root::getInstance()->createWindow(windowInfo);
    }
}

void RenderTexture::initDefault(const std::optional<std::string> &uuid) {
    Super::initDefault(uuid);
    _width  = 1;
    _height = 1;
    initWindow();
}

bool RenderTexture::validate() const {
    return _width >= 1 && _width <= 2048 && _height >= 1 && _height <= 2048;
}

} // namespace cc
