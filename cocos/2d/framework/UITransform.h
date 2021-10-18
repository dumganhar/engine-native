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
#pragma once

#include "core/components/Component.h"
#include "core/geometry/AABB.h"
#include "core/scene-graph/NodeEvent.h"
#include "math/Geometry.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

namespace cc {

namespace event {
class EventListener;
}

class UITransform final : public Component {
public:
    UITransform()           = default;
    ~UITransform() override = default;

    const Size &getContentSize() const { return _contentSize; }
    void        setContentSize(const Size &size);

    float       getWidth() const { return _contentSize.width; }
    void        setWidth(float width);
    float       getHeight() const { return _contentSize.height; }
    void        setHeight();
    const Vec2 &getAnchorPoint() const { return _anchorPoint; }
    void        setAnchorPoint(const Vec2 &value);
    float       getAnchorX() const { return _anchorPoint.x; }
    void        setAnchorX(float value);
    float       getAnchorY() const { return _anchorPoint.y; }
    void        setAnchorY(float value);
    int32_t     getPriority() const { return _priority; }
    void        setPriority(int32_t priority);
    uint32_t    getVisibility() const;
    int32_t     getCameraPriority() const;

    using EventType = NodeEventType;

    void __preload() override;
    void onLoad() override;
    void onEnable() override;
    void onDisable() override;
    void onDestroy() override;

    /**
     * @zh
     * 当前节点的点击计算。
     *
     * @param point - 屏幕点。
     * @param listener - 事件监听器。
     */
    bool isHit(const Vec2 &point, event::EventListener *listener) const;

    /**
     * @en
     * Converts a Point to node (local) space coordinates.
     *
     * @zh
     * 将一个 UI 节点世界坐标系下点转换到另一个 UI 节点 (局部) 空间坐标系，这个坐标系以锚点为原点。
     * 非 UI 节点转换到 UI 节点(局部) 空间坐标系，请走 Camera 的 `convertToUINode`。
     *
     * @param worldPoint - 世界坐标点。
     * @param out - 转换后坐标。
     * @returns - 返回与目标节点的相对位置。
     * @example
     * ```ts
     * const newVec3 = uiTransform.convertToNodeSpaceAR(cc.v3(100, 100, 0));
     * ```
     */
    Vec3 convertToNodeSpaceAR(const Vec3 &worldPoint) const;

    /**
     * @en
     * Converts a Point in node coordinates to world space coordinates.
     *
     * @zh
     * 将距当前节点坐标系下的一个点转换到世界坐标系。
     *
     * @param nodePoint - 节点坐标。
     * @param out - 转换后坐标。
     * @returns - 返回 UI 世界坐标系。
     * @example
     * ```ts
     * const newVec3 = uiTransform.convertToWorldSpaceAR(3(100, 100, 0));
     * ```
     */
    Vec3 convertToWorldSpaceAR(const Vec3 &nodePoint) const;

    /**
     * @en
     * Returns a "local" axis aligned bounding box of the node. <br/>
     * The returned box is relative only to its parent.
     *
     * @zh
     * 返回父节坐标系下的轴向对齐的包围盒。
     *
     * @return - 节点大小的包围盒
     * @example
     * ```ts
     * const boundingBox = uiTransform.getBoundingBox();
     * ```
     */
    Rect getBoundingBox() const;

    /**
     * @en
     * Returns a "world" axis aligned bounding box of the node.<br/>
     * The bounding box contains self and active children's world bounding box.
     *
     * @zh
     * 返回节点在世界坐标系下的对齐轴向的包围盒（AABB）。
     * 该边框包含自身和已激活的子节点的世界边框。
     *
     * @returns - 返回世界坐标系下包围盒。
     * @example
     * ```ts
     * const newRect = uiTransform.getBoundingBoxToWorld();
     * ```
     */
    Rect getBoundingBoxToWorld() const;

    /**
     * @en
     * Returns the minimum bounding box containing the current bounding box and its child nodes.
     *
     * @zh
     * 返回包含当前包围盒及其子节点包围盒的最小包围盒。
     *
     * @param parentMat - 父节点矩阵。
     * @returns
     */
    Rect getBoundingBoxTo(const Mat4 &parentMat) const;

    /**
     * @en
     * Compute the corresponding aabb in world space for raycast.
     *
     * @zh
     * 计算出此 UI_2D 节点在世界空间下的 aabb 包围盒
     */
    geometry::AABB getComputeAABB() const;

protected:
    void onParentChanged(Node *node);
    void markRenderDataDirty();

    static void insertChangeMap(Node *node);
    static void sortChildrenSibling(Node *node);
    static void sortSiblings(Node *node);
    static void cleanChangeMap();

private:
    static std::unordered_map<std::string, Node *> priorityChangeNodeMap;

    Size    _contentSize{100.F, 100.F};
    Vec2    _anchorPoint{0.5F, 0.5F};
    int32_t _priority{0};
};

// HACK
//cjh TODO: director.on(Director.EVENT_AFTER_UPDATE, UITransform._sortSiblings);
//director.on(Director.EVENT_BEFORE_SCENE_LAUNCH, UITransform._cleanChangeMap);

} // namespace cc
