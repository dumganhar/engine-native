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

#include "2d/framework/UITransform.h"

namespace cc {

std::unordered_map<std::string, Node *> UITransform::priorityChangeNodeMap;

void UITransform::setContentSize(const Size &size) {}

void     UITransform::setWidth(float width) {}
void     UITransform::setHeight() {}
void     UITransform::setAnchorPoint(const Vec2 &value) {}
void     UITransform::setAnchorX(float value) {}
void     UITransform::setAnchorY(float value) {}
void     UITransform::setPriority(int32_t priority) {}
uint32_t UITransform::getVisibility() const { return 0; }
int32_t  UITransform::getCameraPriority() const { return 0; }

void UITransform::__preload() {}
void UITransform::onLoad() {}
void UITransform::onEnable() {}
void UITransform::onDisable() {}
void UITransform::onDestroy() {}

bool UITransform::isHit(const Vec2 &point, event::EventListener *listener) const { return false; } //cjh TODO:

Vec3 UITransform::convertToNodeSpaceAR(const Vec3 &worldPoint) const { return Vec3::ZERO; }

Vec3 UITransform::convertToWorldSpaceAR(const Vec3 &nodePoint) const { return Vec3::ZERO; }

Rect UITransform::getBoundingBox() const { return Rect{}; }

Rect UITransform::getBoundingBoxToWorld() const { return Rect{}; }

Rect UITransform::getBoundingBoxTo(const Mat4 &parentMat) const { return Rect{}; }

geometry::AABB UITransform::getComputeAABB() const { return geometry::AABB{}; }

void UITransform::onParentChanged(Node *node) {}
void UITransform::markRenderDataDirty() {}

/* static */
void UITransform::insertChangeMap(Node *node) {}
/* static */
void UITransform::sortChildrenSibling(Node *node) {}
/* static */
void UITransform::sortSiblings(Node *node) {}
/* static */
void UITransform::cleanChangeMap() {}

} // namespace cc
