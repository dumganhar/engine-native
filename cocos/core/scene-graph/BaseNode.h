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

class Scene;
class NodeEventProcessor;
class BaseNode : public CCObject {
public:
    friend class NodeActivator;

    static const uint TRANSFORM_ON;
    static const uint DESTROYING;
    static const uint DEACTIVATING;
    static const uint DONT_DESTROY;

    using CCObject::CCObject;

    static BaseNode *instantiate(BaseNode *cloned, bool isSyncedNode);
    // for walk
    static std::vector<std::vector<BaseNode *>> stacks;
    static index_t                              stackId;

    static void    setScene(BaseNode *);
    static index_t getIdxOfChild(const std::vector<BaseNode *> &, BaseNode *);
    // TODO(Lenovo):
    static Component *findComponent(BaseNode *, const std::string &);
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static Component *findComponent(BaseNode *, const T &);
    static Component *findComponents(BaseNode *, const std::string &, const std::vector<Component *> &);
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static Component *findComponents(BaseNode *, const T &, const std::vector<Component *> &);
    static Component *findChildComponent(const std::vector<BaseNode *> &, const std::string &);
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static Component *              findChildComponent(const std::vector<BaseNode *> &, const T &);
    static std::vector<Component *> findChildComponents(const std::vector<BaseNode *> &, const std::string &, std::vector<Component *>);
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static std::vector<Component *> findChildComponents(const std::vector<BaseNode *> &, const T &, std::vector<Component *>);

    BaseNode() = default;
    explicit BaseNode(const std::string &name);
    virtual ~BaseNode() = default;

    virtual void setParent(BaseNode *parent, bool isKeepWorld = false);

    Scene *getScene() const;
    void   walk();
    void   walk(const std::function<void(BaseNode *)> &);
    void   walk(const std::function<void(BaseNode *)> &, const std::function<void(BaseNode *)> &);

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
    void setActive(bool isActive);
    void setSiblingIndex(index_t idx);

    inline bool getPersistNode() const {
        return static_cast<FlagBits>(_objFlags & Flags::DONT_DESTROY) > 0;
    }
    inline std::string getName() const {
        return _name;
    }
    inline std::string getUUid() const {
        return _id;
    }
    inline bool isActive() const { return _active; }
    inline bool isActiveInHierarchy() const { return _activeInHierarchy; }

    template <typename T, typename Enabled = std::enable_if_t<std::is_base_of_v<Component, T>, T>>
    T *addComponent() {
        T *comp = new T();
        return static_cast<T *>(addComponent(comp));
    }

    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    void removeComponent() {
        for (auto iter = _components.begin(); iter != _components.end(); ++iter) {
            if (dynamic_cast<T *>(*iter) != nullptr) {
                _components.erase(iter);
            }
        }
    }

    Component *addComponent(Component *comp);
    void       removeComponent(Component *comp);

    Component *addComponent(const std::string &className);
    void       removeComponent(const std::string &className);

    Component *getComponent(const std::string &name) const;

    template <typename T, typename Enabled = std::enable_if_t<std::is_base_of<Component, T>::value>>
    Component *getComponent() const {
        for (auto iter = _components.begin(); iter != _components.end(); ++iter) {
            if (dynamic_cast<T *>(*iter) != nullptr) {
                return *iter;
            }
        }
        return nullptr;
    }

    // TODO(Lenovo):
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    inline std::vector<Component *> getComponents(const T & /*unused*/) const {};
    inline std::vector<Component *> getComponents(const std::string & /*unused*/) const {
        // TODO: validate return value
        return _components;
    };
    Component *getComponentInChildren(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    Component *              getComponentInChildren(const T &comp) const {}
    std::vector<Component *> getComponentsInChildren(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    std::vector<Component *> getComponentsInChildren(const T &comp) const {}

    inline std::vector<Component *> getComponents() const { return _components; }

    virtual void                          onPostActivated(bool active) {}
    inline const std::vector<BaseNode *> &getChildren() { return _children; }
    inline BaseNode *                     getParent() const { return _parent; }
    inline NodeEventProcessor *           getEventProcessor() const { return _eventProcessor; }

    BaseNode *  getChildByUuid(const std::string &) const;
    BaseNode *  getChildByName(const std::string &) const;
    BaseNode *  getChildByPath(const std::string &) const;
    inline uint getSiblingIndex() const { return _siblingIndex; }
    inline void insertChild(BaseNode *child, uint32_t siblingIndex) {
        child->_parent = this;
        child->setSiblingIndex(siblingIndex);
    }

    // For SubClass Node compilation
    virtual void              updateWorldTransform() {}
    virtual const Mat4 &      getWorldMatrix() { return Mat4::IDENTITY; }
    virtual const Quaternion &getWorldRotation() { return Quaternion::identity(); }
    virtual uint              getChangedFlags() const { return 0; } //cjh TODO: return 0?
    virtual void              setChangedFlags(uint value) {}
    virtual void              setDirtyFlag(uint value) {}
    virtual uint              getDirtyFlag() const { return 0; }
    virtual void              setLayer(uint layer) {}
    virtual const Vec3 &      getPosition() const { return Vec3::ZERO; }
    virtual const Quaternion &getRotation() const { return Quaternion::identity(); }
    virtual const Vec3 &      getScale() const { return Vec3::ONE; }
    //

protected:
    std::vector<BaseNode *>  _children;
    std::vector<Component *> _components;
    BaseNode *               _parent{nullptr};

    bool _persistNode{false};

    std::string         _id{IDGenerator("Node").getNewId()};
    bool                _active{true};
    bool                _activeInHierarchy{true};
    Scene *             _scene{nullptr};
    NodeEventProcessor *_eventProcessor{nullptr};
    index_t             _siblingIndex{0};
    uint                _eventMask{0};

    //cjh TODO: remove BaseNode
    cc::Vec3       _worldPosition{Vec3::ZERO};
    cc::Quaternion _worldRotation{Quaternion::identity()};
    cc::Vec3       _worldScale{Vec3::ONE};

    Mat4     _rtMat{Mat4::IDENTITY};
    cc::Mat4 _worldMatrix{Mat4::IDENTITY};

    // local transform
    cc::Vec3       _localPosition{Vec3::ZERO};
    cc::Quaternion _localRotation{Quaternion::identity()};
    cc::Vec3       _localScale{Vec3::ONE};
    //

    inline void updateScene() {
        if (_parent == nullptr) {
            return;
        }
        _scene = _parent->_scene;
    }
    void onHierarchyChanged(BaseNode *);
    void onHierarchyChangedBase(BaseNode *oldParent);

    virtual void onSetParent(BaseNode *oldParent, bool keepWorldTransform = false);
    void         walkInternal(std::function<void(BaseNode *)>, std::function<void(BaseNode *)>);
    virtual void onBatchCreated(bool dontChildPrefab);
    bool         onPreDestroy() override;

    bool onPreDestroyBase();
    void onSiblingIndexChanged(uint siblingIndex) {}
    void checkMultipleComp(Component *comp) {}

    friend class Scene;
    friend class Node;

    CC_DISALLOW_COPY_MOVE_ASSIGN(BaseNode);
};

} // namespace cc
