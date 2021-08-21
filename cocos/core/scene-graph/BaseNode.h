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
#include <vector>
#include "core/components/Component.h"
#include "core/data/Object.h"
#include "core/event/Event.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "NodeEvent.h"
#include "NodeEventProcessor.h"

namespace cc {
namespace scenegraph {
class Scene;
class BaseNode : public CCObject {
public:
    using CCObject::CCObject;
    BaseNode()                 = default;
    BaseNode(const BaseNode &) = delete;
    BaseNode(BaseNode &&)      = delete;
    virtual ~BaseNode()        = default;
    BaseNode &operator=(const BaseNode &) = delete;
    BaseNode &operator=(const BaseNode &&) = delete;

    virtual inline void updateWorldTransform() {}
    virtual inline void updateWorldRTMatrix() {}

    virtual inline void setWorldPosition(float x, float y, float z) {}
    virtual inline void setWorldRotation(float x, float y, float z, float w) {}
    void                setParent(BaseNode *parent);
    Scene *             getScene() const;
    void                walk(std::function<void(BaseNode *)>, std::function<void(BaseNode *)>);
    inline void         addComponent(const std::string &className) {}
    inline void         removeComponent(const std::string &className) {}
    inline void         removeComponent(components::Component *cmp) {}
    inline void         on(NodeEventType type, const std::function<void(BaseNode *)> &callback) {}
    inline void         off(NodeEventType type, const std::function<void(BaseNode *)> &callback) {}
    inline void         once(NodeEventType type, const std::function<void(BaseNode *)> &callback) {}
    template <class... T>
    inline void emit(NodeEventType type, T... args) {}
    inline void dispatchEvent(event::Event eve) {}
    inline void hasEventListener(const std::string &type) {}
    inline void targetOff(const std::string &target) {}
    inline bool destroy() override { return false; }
    inline void destroyAllChildren() {}
    inline void updateSiblingIndex() {}

    inline void addChild(BaseNode *node) { _children.emplace_back(node); }
    inline void removeChild(BaseNode *node) {
        auto iter = std::find(_children.begin(), _children.end(), node);
        if (iter != _children.end()) {
            _children.erase(iter);
        }
    }
    inline void removeFromParent() {}
    inline void removeAllChildren() {}
    inline bool isChildOf(BaseNode *parent) { return parent != nullptr; }

    inline void setPersistNode(bool val) {
        val ? _objFlags |= DONT_DESTROY : _objFlags &= ~DONT_DESTROY;
    };
    inline void setName(const std::string &name) {
        _name = name;
    }
    inline void         setActive(bool isActive) {}
    inline void         setSiblingIndex(uint32_t idx) {}
    virtual inline void setFlagsChanged(uint32_t value) {}
    virtual inline void setDirtyFlag(uint32_t value) {}
    virtual inline void setLayer(uint32_t layer) {}
    virtual inline void setWorldMatrix(const Mat4 &matrix) {}
    virtual inline void setWorldPosition(const Vec3 &pos) {}
    virtual inline void setWorldRotation(const Quaternion &rotation) {}
    virtual inline void setWorldScale(const Vec3 &scale) {}
    virtual inline void setLocalPosition(const Vec3 &pos) {}
    virtual inline void setLocalPosition(float x, float y, float z) {}
    virtual inline void setLocalRotation(const Quaternion &rotation) {}
    virtual inline void setLocalRotation(float x, float y, float z, float w) {}
    virtual inline void setLocalScale(const Vec3 &scale) {}

    inline bool getPersistNode() const {
        return (_objFlags & DONT_DESTROY) > 0;
    }
    inline std::string getName() const {
        return _name;
    }
    inline std::string getUUid() const {
        return _id;
    }
    inline bool getActive() const { return _active; }
    inline bool getActiveInHierarchy() const { return _activeInHierarchy; }

    inline components::Component *              getComponent(const std::string &name) { return nullptr; }
    inline components::Component *              getComponentInChildren(const std::string &name) { return nullptr; }
    inline std::vector<components::Component *> getComponentsInChildren(const std::string &name) {}

    inline const std::vector<BaseNode *> &getChilds() { return _children; }
    inline BaseNode *                     getParent() const { return _parent; }
    inline std::vector<components::Component *>       getComponents() const { return _components; }
    inline NodeEventProcessor *           getEventProcessor() const { return _eventProcessor; }
    virtual inline uint32_t               getFlagsChanged() const { return _flagChange; }
    virtual inline uint32_t               getLayer() const { return _layer; }
    virtual inline uint32_t               getDirtyFlag() const { return _dirtyFlag; }
    virtual inline const Vec3 &           getPosition() const { return _localPosition; }
    virtual inline const Vec3 &           getScale() const { return _localScale; }
    virtual inline const Quaternion &     getRotation() const { return _localRotation; }
    virtual inline const Mat4 &           getWorldMatrix() const { return _worldMatrix; }
    virtual inline const Vec3 &           getWorldPosition() const { return _worldPosition; }
    virtual inline const Quaternion &     getWorldRotation() const { return _worldRotation; }
    virtual inline const Vec3 &           getWorldScale() const { return _worldScale; }
    virtual inline const Mat4 &           getWorldRTMatrix() const { return _rtMat; }
    inline BaseNode *                     getChildByUuid(const std::string &uid) const {
        if (!uid.empty()) {
            return nullptr;
        }
        return nullptr;
    }
    inline BaseNode *getChildByName(const std::string &name) const {
        if (!name.empty()) {
            return nullptr;
        }
        return nullptr;
    }
    inline BaseNode *getChildByPath(const std::string &path) const { return nullptr; }
    inline uint32_t  getSiblingIndex() const { return _siblingIndex; }
    inline void      insertChild(BaseNode *child, uint32_t siblingIndex) {}

protected:
    std::vector<BaseNode *>  _children;
    std::vector<components::Component *> _components;
    BaseNode *               _parent{nullptr};
    uint32_t                 _flagChange{0};
    uint32_t                 _dirtyFlag{0};
    uint32_t                 _objFlags{0};
    bool                     _persistNode{false};
    uint32_t                 _layer{0};
    cc::Vec3                 _worldScale{Vec3::ONE};
    cc::Vec3                 _worldPosition{Vec3::ZERO};
    cc::Quaternion           _worldRotation{Quaternion::identity()};
    Mat4                     _rtMat{Mat4::IDENTITY};
    cc::Mat4                 _worldMatrix{Mat4::IDENTITY};
    cc::Vec3                 _localScale{Vec3::ONE};
    cc::Vec3                 _localPosition{Vec3::ZERO};
    cc::Quaternion           _localRotation{Quaternion::identity()};
    std::string              _id{"Node"};
    bool                     _active{true};
    bool                     _activeInHierarchy{true};
    Scene *                  _scene{nullptr};
    NodeEventProcessor *     _eventProcessor{nullptr};
    uint32_t                 _siblingIndex{0};
    inline void              updateScene() {}
    inline void              onSetParent(BaseNode *oldParent, bool keepWorldTransform = false) {}
    inline void              onPostActivated(bool active) {}
    inline void              onBatchCreated(bool dontChildPrefab) {}
    inline void              onPreDestroy() {}
    inline void              instantiate(BaseNode *cloned, bool isSyncedNode) {}
    inline void              onPreDestroyBase() {}
    inline void              onSiblingIndexChanged(uint32_t siblingIndex) {}

    // for walk
    static std::vector<std::vector<BaseNode *>> stacks;
    static uint32_t                             stackId;

    static void       setScene(BaseNode *);
    static components::Component *findComponent(BaseNode *, components::Component *);
    static components::Component *findComponents(BaseNode *, components::Component *, std::vector<components::Component *>);
    static components::Component *findChildComponent(std::vector<BaseNode *>, components::Component *);
    static components::Component *findChildComponents(std::vector<BaseNode *>, components::Component *, std::vector<components::Component *>);
};
} // namespace scenegraph
} // namespace cc
