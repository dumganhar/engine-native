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
#include <any>
#include <string>
#include <variant>
#include <vector>
#include "base/Log.h"
#include "base/TypeDef.h"
#include "core/components/Component.h"
#include "core/data/Object.h"
#include "core/event/Event.h"
#include "core/scene-graph/NodeEvent.h"
#include "core/utils/IDGenerator.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace cc {
namespace scenegraph {
class Scene;
class NodeEventProcessor;
class BaseNode : public CCObject {
public:
    using CCObject::CCObject;
    explicit BaseNode(const std::string &name);
    BaseNode(const BaseNode &) = delete;
    BaseNode(BaseNode &&)      = delete;
    virtual ~BaseNode()        = default;
    BaseNode &operator=(const BaseNode &) = delete;
    BaseNode &operator=(const BaseNode &&) = delete;

    static const uint TRANSFORM_ON;
    static const uint DESTROYING;
    static const uint DEACTIVATING;
    static const uint DONT_DESTROY;
    virtual void      updateWorldTransform() {}
    virtual void      updateWorldRTMatrix() {}

    virtual void setWorldPosition(float x, float y, float z) {}
    virtual void setWorldRotation(float x, float y, float z, float w) {}
    virtual void setParent(BaseNode *parent, bool isKeepWorld = false);

    Scene *                       getScene() const;
    void                          walk();
    void                          walk(const std::function<void(BaseNode *)> &);
    void                          walk(const std::function<void(BaseNode *)> &, const std::function<void(BaseNode *)> &);
    static components::Component *addComponent(const std::string &className);
    components::Component *       addComponent(components::Component *comp);
    void                          removeComponent(const std::string &className);
    void                          removeComponent(components::Component *comp);
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    void removeComponent(const T &comp){};
    void on(const std::string &, const std::function<void(BaseNode *)> &);
    void on(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    void off(const std::string &, const std::function<void(BaseNode *)> &);
    void off(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    void once(const std::string &, const std::function<void(BaseNode *)> &);
    void once(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    void emit(const std::string &, const std::any &);
    void emit(const std::string &, const std::any &, const std::any &, const std::any &, const std::any &);

    void        dispatchEvent(const event::Event &);
    bool        hasEventListener(const std::string &);
    bool        hasEventListener(const std::string &, const std::function<void(BaseNode *)> &);
    bool        hasEventListener(const std::string &, const std::function<void(BaseNode *)> &, const std::any &);
    void        targetOff(const std::string &);
    inline bool destroy() override {
        if (CCObject::destroy()) {
            _active = false;
            return true;
        }
        return false;
    }
    inline void destroyAllChildren() {
        for (auto *child : _children) {
            child->destroy();
        }
    }
    inline void updateSiblingIndex() {
        uint i = 0;
        for (auto *child : _children) {
            child->_siblingIndex = i++;
        }
        emit(NodeEventType::SIBLING_ORDER_CHANGED, NodeEventType::SIBLING_ORDER_CHANGED);
    }

    inline void addChild(BaseNode *node) { node->setParent(this); }
    inline void removeChild(BaseNode *node) {
        auto idx = getIdxOfChild(_children, node);
        if (idx != -1) {
            node->setParent(nullptr);
        }
    }
    inline void removeFromParent() {
        if (_parent) {
            _parent->removeChild(this);
        }
    }
    void removeAllChildren();
    bool isChildOf(BaseNode *parent);

    inline void setPersistNode(bool val) {
        val ? _objFlags |= Flags::DONT_DESTROY : _objFlags &= ~Flags::DONT_DESTROY;
    };
    inline void setName(const std::string &name) {
        _name = name;
    }
    void         setActive(bool isActive);
    void         setSiblingIndex(index_t idx);
    virtual void setFlagsChanged(uint value) {}
    virtual void setDirtyFlag(uint value) {}
    virtual void setLayer(uint layer) {}
    virtual void setWorldMatrix(const Mat4 &matrix) {}
    virtual void setWorldPosition(const Vec3 &pos) {}
    virtual void setWorldRotation(const Quaternion &rotation) {}
    virtual void setWorldScale(const Vec3 &scale) {}
    virtual void setLocalPosition(const Vec3 &pos) {}
    virtual void setLocalPosition(float x, float y, float z) {}
    virtual void setLocalRotation(const Quaternion &rotation) {}
    virtual void setLocalRotation(float x, float y, float z, float w) {}
    virtual void setLocalScale(const Vec3 &scale) {}

    inline bool getPersistNode() const {
        return static_cast<FlagBits>(_objFlags & Flags::DONT_DESTROY) > 0;
    }
    inline std::string getName() const {
        return _name;
    }
    inline std::string getUUid() const {
        return _id;
    }
    inline bool getActive() const { return _active; }
    inline bool getActiveInHierarchy() const { return _activeInHierarchy; }

    components::Component *getComponent(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    components::Component *getComponent(const T &type) const {}
    // TODO(Lenovo):
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    inline std::vector<components::Component *> getComponents(const T & /*unused*/) const {};
    inline std::vector<components::Component *> getComponents(const std::string & /*unused*/) const {
        // TODO: validate return value
        return _components;
    };
    components::Component *getComponentInChildren(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    components::Component *              getComponentInChildren(const T &comp) const {}
    std::vector<components::Component *> getComponentsInChildren(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    std::vector<components::Component *> getComponentsInChildren(const T &comp) const {}

    virtual void                                onPostActivated(bool active) {}
    inline const std::vector<BaseNode *> &      getChildren() { return _children; }
    inline BaseNode *                           getParent() const { return _parent; }
    inline std::vector<components::Component *> getComponents() const { return _components; }
    inline NodeEventProcessor *                 getEventProcessor() const { return _eventProcessor; }
    virtual uint                                getFlagsChanged() const { return _flagChange; }
    virtual uint                                getLayer() const { return _layer; }
    virtual uint                                getDirtyFlag() const { return _dirtyFlag; }
    virtual const Vec3 &                        getPosition() const { return _localPosition; }
    virtual const Vec3 &                        getScale() const { return _localScale; }
    virtual const Quaternion &                  getRotation() const { return _localRotation; }
    virtual const Mat4 &                        getWorldMatrix() const { return _worldMatrix; }
    virtual const Vec3 &                        getWorldPosition() const { return _worldPosition; }
    virtual const Quaternion &                  getWorldRotation() const { return _worldRotation; }
    virtual const Vec3 &                        getWorldScale() const { return _worldScale; }
    virtual const Mat4 &                        getWorldRTMatrix() const { return _rtMat; }
    BaseNode *                                  getChildByUuid(const std::string &) const;
    BaseNode *                                  getChildByName(const std::string &) const;
    BaseNode *                                  getChildByPath(const std::string &) const;
    inline uint                                 getSiblingIndex() const { return _siblingIndex; }
    inline void                                 insertChild(BaseNode *child, uint32_t siblingIndex) {
        child->_parent = this;
        child->setSiblingIndex(siblingIndex);
    }

protected:
    std::vector<BaseNode *>              _children;
    std::vector<components::Component *> _components;
    BaseNode *                           _parent{nullptr};
    uint                                 _flagChange{0};
    uint                                 _dirtyFlag{0};
    Flags                                _objFlags{Flags::ZERO};
    bool                                 _persistNode{false};
    uint                                 _layer{0};
    cc::Vec3                             _worldScale{Vec3::ONE};
    cc::Vec3                             _worldPosition{Vec3::ZERO};
    cc::Quaternion                       _worldRotation{Quaternion::identity()};
    Mat4                                 _rtMat{Mat4::IDENTITY};
    cc::Mat4                             _worldMatrix{Mat4::IDENTITY};
    cc::Vec3                             _localScale{Vec3::ONE};
    cc::Vec3                             _localPosition{Vec3::ZERO};
    cc::Quaternion                       _localRotation{Quaternion::identity()};
    std::string                          _id{IDGenerator("Node").getNewId()};
    bool                                 _active{true};
    bool                                 _activeInHierarchy{true};
    Scene *                              _scene{nullptr};
    NodeEventProcessor *                 _eventProcessor{nullptr};
    index_t                              _siblingIndex{0};
    uint                                 _eventMask{0};
    inline void                          updateScene() {
        if (_parent == nullptr) {
            return;
        }
        _scene = _parent->_scene;
    }
    void onHierarchyChanged(BaseNode *);
    void onHierarchyChangedBase(BaseNode *oldParent);

    virtual void     onSetParent(BaseNode *oldParent, bool keepWorldTransform = false);
    void             walkInternal(std::function<void(BaseNode *)>, std::function<void(BaseNode *)>);
    virtual void     onBatchCreated(bool dontChildPrefab);
    virtual bool     onPreDestroy() override;
    static BaseNode *instantiate(BaseNode *cloned, bool isSyncedNode);
    bool             onPreDestroyBase();
    inline void      onSiblingIndexChanged(uint siblingIndex) {}
    inline void      checkMultipleComp(components::Component *comp) {}
    // for walk
    static std::vector<std::vector<BaseNode *>> stacks;
    static index_t                              stackId;

    static void    setScene(BaseNode *);
    static index_t getIdxOfChild(const std::vector<BaseNode *> &, BaseNode *);
    // TODO(Lenovo):
    static components::Component *findComponent(BaseNode *, const std::string &);
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    static components::Component *findComponent(BaseNode *, const T &);
    static components::Component *findComponents(BaseNode *, const std::string &, const std::vector<components::Component *> &);
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    static components::Component *findComponents(BaseNode *, const T &, const std::vector<components::Component *> &);
    static components::Component *findChildComponent(const std::vector<BaseNode *> &, const std::string &);
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    static components::Component *              findChildComponent(const std::vector<BaseNode *> &, const T &);
    static std::vector<components::Component *> findChildComponents(const std::vector<BaseNode *> &, const std::string &, std::vector<components::Component *>);
    template <typename T, typename std::enable_if_t<std::is_base_of<components::Component, T>::value>>
    static std::vector<components::Component *> findChildComponents(const std::vector<BaseNode *> &, const T &, std::vector<components::Component *>);
};
} // namespace scenegraph
} // namespace cc
