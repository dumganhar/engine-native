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

#include "jsb_scene_manual.h"
#include "bindings/auto/jsb_scene_auto.h"
#include "core/event/EventTypesToJS.h"
#include "core/scene-graph/Node.h"
#include "core/scene-graph/NodeEvent.h"
#include "scene/Model.h"

#ifndef JSB_ALLOC
    #define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
    #define JSB_FREE(ptr) delete ptr
#endif

static se::Object *nodeVec3CacheObj{nullptr};
static se::Object *nodeQuatCacheObj{nullptr};
static se::Object *nodeMat4CacheObj{nullptr};
static float *     _tempFloatArray = nullptr;

class NodeUserData : public cc::Node::UserData {
public:
    NodeUserData(uint32_t size) {
        setArrayLength(size);
        _arrayObject = se::Object::createArrayObject(size);
        _arrayObject->root();
    }

    ~NodeUserData() override {
        if (_arrayObject) {
            _arrayObject->unroot();
            _arrayObject->decRef();
            _arrayObject = nullptr;
        }
    }

    inline se::Object *getArrayObject() {
        return _arrayObject;
    }

    inline void setArrayLength(uint32_t length) {
        _arrayLength = length;
    }

    inline uint32_t getArrayLength() {
        return _arrayLength;
    }

private:
    se::Object *_arrayObject{nullptr};
    uint32_t    _arrayLength{0};
};

static bool js_root_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_root_registerListeners : Invalid Native Object");

#define DISPATCH_EVENT_TO_JS_ARGS_0(eventType, jsFuncName)                                              \
    cobj->getEventProcessor()->on(eventType, [](cc::Root *rootObj) {                                    \
        se::AutoHandleScope hs;                                                                         \
        se::Value           rootVal;                                                                    \
        bool                ok = nativevalue_to_se(rootObj, rootVal);                                   \
        SE_PRECONDITION2_VOID(ok, "js_root_registerListeners : Error processing arguments");            \
        if (rootVal.isObject()) {                                                                       \
            se::ScriptEngine::getInstance()->callFunction(rootVal.toObject(), #jsFuncName, 0, nullptr); \
        }                                                                                               \
    })

    DISPATCH_EVENT_TO_JS_ARGS_0(cc::EventTypesToJS::ROOT_BATCH2D_INIT, _onBatch2DInit);
    DISPATCH_EVENT_TO_JS_ARGS_0(cc::EventTypesToJS::ROOT_BATCH2D_UPDATE, _onBatch2DUpdate);
    DISPATCH_EVENT_TO_JS_ARGS_0(cc::EventTypesToJS::ROOT_BATCH2D_UPLOAD_BUFFERS, _onBatch2DUploadBuffers);
    DISPATCH_EVENT_TO_JS_ARGS_0(cc::EventTypesToJS::ROOT_BATCH2D_RESET, _onBatch2DReset);
    DISPATCH_EVENT_TO_JS_ARGS_0(cc::EventTypesToJS::DIRECTOR_BEFORE_COMMIT, _onDirectorBeforeCommit);

    return true;
}
SE_BIND_FUNC(js_root_registerListeners) // NOLINT(readability-identifier-naming)

static void registerOnTransformChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::TRANSFORM_CHANGED,
        [jsObject](cc::TransformBit transformBit) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(transformBit, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onTransformChanged", 1, &arg0);
        });
}

static void registerOnParentChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::PARENT_CHANGED,
        [jsObject](cc::Node *oldParent) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(oldParent, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onParentChanged", 1, &arg0);
        });
}

static void registerOnLayerChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::LAYER_CHANGED,
        [jsObject](uint32_t layer) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(layer, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onLayerChanged", 1, &arg0);
        });
}

static void registerOnChildRemoved(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::CHILD_REMOVED,
        [jsObject](cc::Node *child) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(child, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onChildRemoved", 1, &arg0);
        });
}

static void registerOnChildAdded(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->on(
        cc::NodeEventType::CHILD_ADDED,
        [jsObject](cc::Node *child) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(child, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onChildAdded", 1, &arg0);
        },
        skip);
}

static void registerOnActiveNode(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->on(
        cc::EventTypesToJS::NODE_ACTIVE_NODE,
        [jsObject](bool shouldActiveNow) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(shouldActiveNow, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onActiveNode", 1, &arg0);
        },
        skip);
}

static void registerOnBatchCreated(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->on(
        cc::EventTypesToJS::NODE_ON_BATCH_CREATED,
        [jsObject](bool dontChildPrefab) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(dontChildPrefab, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onBatchCreated", 1, &arg0);
        },
        skip);
}

static void registerOnUiTransformDirty(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->setUIPropsTransformDirtyCallback(
        [jsObject](uint32_t **uiTransformDirty) {
            if (!*uiTransformDirty) {
                se::AutoHandleScope hs;
                se::Value           uiPropsVal;
                jsObject->getProperty("_uiProps", &uiPropsVal, true);
                SE_PRECONDITION2_VOID(uiPropsVal.isObject(), "Not property named _uiProps.");
                se::Value uiTransformDirtyVal;
                uiPropsVal.toObject()->getProperty("_uiTransformDirty", &uiTransformDirtyVal, true);
                SE_PRECONDITION2_VOID(uiTransformDirtyVal.isObject() && uiTransformDirtyVal.toObject()->isTypedArray(), "_uiTransformDirtyVal is not a TypedArray");
                sevalue_to_native(uiTransformDirtyVal, uiTransformDirty);
            }

            **uiTransformDirty = 1;
        });
}

static bool js_scene_Node_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerListeners : Invalid Native Object");

    auto *jsObject = s.thisObject();

#define NODE_DISPATCH_EVENT_TO_JS(eventType, jsFuncName)                                      \
    cobj->on(                                                                                 \
        eventType, [jsObject]() {                                                             \
            se::AutoHandleScope hs;                                                           \
            se::ScriptEngine::getInstance()->callFunction(jsObject, #jsFuncName, 0, nullptr); \
        });

    registerOnActiveNode(cobj, jsObject);
    registerOnBatchCreated(cobj, jsObject);

    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_REATTACH, _onReAttach);
    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_REMOVE_PERSIST_ROOT_NODE, _onRemovePersistRootNode);
    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_DESTROY_COMPONENTS, _onDestroyComponents);
    //    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_UI_TRANSFORM_DIRTY, _onUiTransformDirty);
    NODE_DISPATCH_EVENT_TO_JS(cc::NodeEventType::SIBLING_ORDER_CHANGED, _onSiblingOrderChanged);
    registerOnUiTransformDirty(cobj, jsObject);

    cobj->on(
        cc::NodeEventType::NODE_DESTROYED,
        [](cc::Node *node) {
            se::AutoHandleScope hs;
            se::Value           nodeVal;
            nativevalue_to_se(node, nodeVal);
            se::ScriptEngine::getInstance()->callFunction(nodeVal.toObject(), "_onNodeDestroyed", 1, &nodeVal);
        });

    return true;
}
SE_BIND_FUNC(js_scene_Node_registerListeners) // NOLINT(readability-identifier-naming)

static bool js_scene_Node_registerOnTransformChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerOnTransformChanged : Invalid Native Object");

    auto *jsObject = s.thisObject();

    registerOnTransformChanged(cobj, jsObject);
    return true;
}
SE_BIND_FUNC(js_scene_Node_registerOnTransformChanged) // NOLINT(readability-identifier-naming)

static bool js_scene_Node_registerOnParentChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerOnParentChanged : Invalid Native Object");

    auto *jsObject = s.thisObject();

    registerOnParentChanged(cobj, jsObject);
    return true;
}
SE_BIND_FUNC(js_scene_Node_registerOnParentChanged) // NOLINT(readability-identifier-naming)

static bool js_scene_Node_registerOnLayerChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerOnLayerChanged : Invalid Native Object");

    auto *jsObject = s.thisObject();

    registerOnLayerChanged(cobj, jsObject);
    return true;
}
SE_BIND_FUNC(js_scene_Node_registerOnLayerChanged) // NOLINT(readability-identifier-naming)

static bool js_scene_Node_registerOnChildRemoved(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerOnChildRemoved : Invalid Native Object");

    auto *jsObject = s.thisObject();

    registerOnChildRemoved(cobj, jsObject);
    return true;
}
SE_BIND_FUNC(js_scene_Node_registerOnChildRemoved) // NOLINT(readability-identifier-naming)

static bool js_scene_Node_registerOnChildAdded(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerOnChildAdded : Invalid Native Object");

    auto *jsObject = s.thisObject();

    registerOnChildAdded(cobj, jsObject);
    return true;
}
SE_BIND_FUNC(js_scene_Node_registerOnChildAdded) // NOLINT(readability-identifier-naming)

static bool js_scene_Node_isActiveInHierarchy(void *s) // NOLINT(readability-identifier-naming)
{
    auto *cobj         = reinterpret_cast<cc::Node *>(s);
    bool  result       = cobj->isActiveInHierarchy();
    _tempFloatArray[0] = result ? 1 : 0;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_isActiveInHierarchy)

static bool scene_Vec3_to_seval(const cc::Vec3 &v, se::Value *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    if (!nodeVec3CacheObj) {
        nodeVec3CacheObj = se::Object::createPlainObject();
        nodeVec3CacheObj->root();
    }
    se::Object *obj(nodeVec3CacheObj);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    ret->setObject(obj);

    return true;
}

static bool scene_Quaternion_to_seval(const cc::Quaternion &v, se::Value *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    if (!nodeQuatCacheObj) {
        nodeQuatCacheObj = se::Object::createPlainObject();
        nodeQuatCacheObj->root();
    }
    se::Object *obj(nodeQuatCacheObj);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    obj->setProperty("w", se::Value(v.w));
    ret->setObject(obj);

    return true;
}

static bool scene_Mat4_to_seval(const cc::Mat4 &v, se::Value *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    if (!nodeMat4CacheObj) {
        nodeMat4CacheObj = se::Object::createPlainObject();
        nodeMat4CacheObj->root();
    }
    se::Object *obj(nodeMat4CacheObj);

    char keybuf[8] = {0};
    for (auto i = 0; i < 16; i++) {
        snprintf(keybuf, sizeof(keybuf), "m%02d", i);
        obj->setProperty(keybuf, se::Value(v.m[i]));
    }
    ret->setObject(obj);

    return true;
}

static bool scene_Vector_to_seval(cc::Node *node, const std::vector<cc::Node *> &from, se::Value &to) { // NOLINT(readability-identifier-naming)
    assert(node != nullptr);
    uint32_t      size     = from.size();
    NodeUserData *userData = nullptr;
    if (!node->getUserData()) {
        userData = new NodeUserData(size);
        node->setUserData(userData);
    } else {
        userData = static_cast<NodeUserData *>(node->getUserData());
    }
    se::Object *array(userData->getArrayObject());

    se::Value tmp;
    for (size_t i = 0; i < size; i++) {
        nativevalue_to_se(from[i], tmp, nullptr);
        array->setArrayElement(static_cast<uint32_t>(i), tmp);
    }
    if (userData->getArrayLength() != size) {
        userData->setArrayLength(size);
        array->setProperty("length", se::Value(size));
    }
    to.setObject(array);

    return true;
}

static bool js_scene_Camera_screenPointToRay(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_screenPointToRay : Invalid Native Object");

    cc::geometry::Ray ray;
    cobj->screenPointToRay(&ray, _tempFloatArray[0], _tempFloatArray[1]);
    _tempFloatArray[0] = ray.o.x;
    _tempFloatArray[1] = ray.o.y;
    _tempFloatArray[2] = ray.o.z;
    _tempFloatArray[3] = ray.d.x;
    _tempFloatArray[4] = ray.d.y;
    _tempFloatArray[5] = ray.d.z;
    return true;
}
SE_BIND_FUNC(js_scene_Camera_screenPointToRay)

static bool js_scene_Node_getPosition(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getPosition : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getPosition();
        _tempFloatArray[0]     = result.x;
        _tempFloatArray[1]     = result.y;
        _tempFloatArray[2]     = result.z;
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getPosition)

static bool js_scene_Node__setTempFloatArray(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        uint8_t *buffer = nullptr;
        args[0].toObject()->getArrayBufferData(&buffer, nullptr);
        _tempFloatArray = reinterpret_cast<float *>(buffer);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Node__setTempFloatArray)

static bool js_scene_Node_getRight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getRight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Vec3 result = cobj->getRight();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getRight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getRight)

static bool js_scene_Node_getRotation(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getRotation : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Quaternion &result = cobj->getRotation();
        ok &= scene_Quaternion_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getRotation : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getRotation)

static bool js_scene_Node_getScale(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getScale : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getScale();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getScale : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getScale)

static bool js_scene_Node_setPosition(void *s) // NOLINT(readability-identifier-naming)
{
    auto * cobj = reinterpret_cast<cc::Node *>(s);
    size_t argc = _tempFloatArray[0];
    if (argc == 2) {
        cobj->setPosition(_tempFloatArray[1], _tempFloatArray[2]);

    } else {
        cobj->setPosition(_tempFloatArray[1], _tempFloatArray[2], _tempFloatArray[3]);
    }
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_setPosition)

static bool js_scene_Node_setRotation(void *s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node *>(s);
    cobj->setRotation(_tempFloatArray[0], _tempFloatArray[1], _tempFloatArray[2], _tempFloatArray[3]);
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_setRotation)

static bool js_scene_Node_setRotationFromEuler(void *s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node *>(s);
    cobj->setRotationFromEuler(_tempFloatArray[0], _tempFloatArray[1], _tempFloatArray[2]);
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_setRotationFromEuler)

static bool js_scene_Node_setScale(void *s) // NOLINT(readability-identifier-naming)
{
    auto * cobj = reinterpret_cast<cc::Node *>(s);
    size_t argc = _tempFloatArray[0];
    if (argc == 2) {
        cobj->setScale(_tempFloatArray[1], _tempFloatArray[2]);

    } else {
        cobj->setScale(_tempFloatArray[1], _tempFloatArray[2], _tempFloatArray[3]);
    }
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_setScale)

static bool js_scene_Node_setRTS(void *s) // NOLINT(readability-identifier-naming)
{
    auto *         cobj = reinterpret_cast<cc::Node *>(s);
    cc::Quaternion qt;
    int            rotSize = _tempFloatArray[0];
    if (rotSize > 0) {
        qt.set(_tempFloatArray[1], _tempFloatArray[2], _tempFloatArray[3], _tempFloatArray[4]);
    }

    int      posSize = _tempFloatArray[5];
    cc::Vec3 pos;
    if (posSize > 0) {
        pos.set(_tempFloatArray[6], _tempFloatArray[7], _tempFloatArray[8]);
    }

    int      scaleSize = _tempFloatArray[9];
    cc::Vec3 scale;
    if (scaleSize > 0) {
        scale.set(_tempFloatArray[10], _tempFloatArray[11], _tempFloatArray[12]);
    }
    cobj->setRTS(rotSize > 0 ? &qt : nullptr, posSize > 0 ? &pos : nullptr, scaleSize > 0 ? &scale : nullptr);
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_setRTS)

static bool js_scene_Node_rotateForJS(void *s) // NOLINT(readability-identifier-naming)
{
    auto * cobj = reinterpret_cast<cc::Node *>(s);
    size_t argc = _tempFloatArray[0];
    if (argc == 4) {
        cobj->rotateForJS(_tempFloatArray[1], _tempFloatArray[2], _tempFloatArray[3], _tempFloatArray[4]);
    } else {
        int size = _tempFloatArray[5];
        cobj->rotateForJS(_tempFloatArray[1], _tempFloatArray[2], _tempFloatArray[3], _tempFloatArray[4], size == 0 ? cc::NodeSpace::LOCAL : cc::NodeSpace::LOCAL);
    }
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_rotateForJS)

static bool js_scene_Node_getUp(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getUp : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Vec3 result = cobj->getUp();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getUp : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getUp)

static bool js_scene_Node_getWorldMatrix(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldMatrix : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getWorldMatrix();
        memcpy(_tempFloatArray, result.m, sizeof(result.m));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC_AS_PROP_GET(js_scene_Node_getWorldMatrix)
SE_BIND_FUNC(js_scene_Node_getWorldMatrix)

static bool js_scene_Node_getWorldPosition(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldPosition : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getWorldPosition();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldPosition : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldPosition)

static bool js_scene_Node_getWorldRS(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldRS : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Mat4 result = cobj->getWorldRS();
        ok &= scene_Mat4_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldRS : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldRS)

static bool js_scene_Node_getWorldRT(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldRT : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Mat4 result = cobj->getWorldRT();
        ok &= scene_Mat4_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldRT : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldRT)

static bool js_scene_Node_getWorldRotation(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldRotation : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Quaternion &result = cobj->getWorldRotation();
        ok &= scene_Quaternion_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldRotation : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldRotation)

static bool js_scene_Node_getWorldScale(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldScale : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getWorldScale();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldScale : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldScale)

static bool js_scene_Node_getEulerAngles(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getEulerAngles : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getEulerAngles();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getEulerAngles : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getEulerAngles)

static bool js_scene_Node_getForward(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getForward : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Vec3 result = cobj->getForward();
        ok &= scene_Vec3_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_scene_Node_getForward : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getForward)

static bool js_scene_Node_getChildren(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getChildren : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::Node *> &result = cobj->getChildren();
        ok &= scene_Vector_to_seval(cobj, result, s.rval());
        //ok &= nativevalue_to_se(result, s.rval(), nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getChildren : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getChildren)

static bool js_scene_Pass_blocks_getter(se::State &s) {
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerListeners : Invalid Native Object");
    auto *thiz = s.thisObject();

    se::Value blocksVal;
    if (thiz->getProperty("_blocks", &blocksVal, true) && blocksVal.isObject() && blocksVal.toObject()->isArray()) {
        s.rval() = blocksVal;
        return true;
    }

    const auto &   blocks        = cobj->getBlocks();
    const uint8_t *blockDataBase = cobj->getRootBlock()->getData();

    se::HandleObject jsBlocks{se::Object::createArrayObject(blocks.size())};
    int32_t          i = 0;
    for (const auto &block : blocks) {
        se::HandleObject jsBlock{
            se::Object::createTypedArrayWithBuffer(
                se::Object::TypedArrayType::FLOAT32,
                cobj->getRootBlock()->getJSArrayBuffer(),
                reinterpret_cast<const uint8_t *>(block.data) - blockDataBase,
                block.count * 4)};
        jsBlocks->setArrayElement(i, se::Value(jsBlock));
        ++i;
    }
    thiz->setProperty("_blocks", se::Value(jsBlocks));
    s.rval().setObject(jsBlocks);
    return true;
}
SE_BIND_PROP_GET(js_scene_Pass_blocks_getter)

static bool js_scene_RenderScene_root_getter(se::State &s) {
    nativevalue_to_se(cc::Root::getInstance(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_RenderScene_root_getter)

static bool js_Model_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_Model_registerListeners : Invalid Native Object");
    auto *thiz = s.thisObject();

#define MODEL_DISPATCH_EVENT_TO_JS(eventType, jsFuncName)                               \
    cobj->getEventProcessor().on(eventType, [=](uint32_t stamp) {                       \
        cobj->setCalledFromJS(true);                                                    \
        se::AutoHandleScope hs;                                                         \
        se::Value           stampVal{stamp};                                            \
        se::ScriptEngine::getInstance()->callFunction(thiz, #jsFuncName, 1, &stampVal); \
    })

    MODEL_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::MODEL_UPDATE_TRANSFORM, updateTransform);
    MODEL_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::MODEL_UPDATE_UBO, updateUBOs);

#undef MODEL_DISPATCH_EVENT_TO_JS

    cobj->getEventProcessor().on(cc::EventTypesToJS::MODEL_UPDATE_LOCAL_DESCRIPTORS, [=](index_t subModelIndex, cc::gfx::DescriptorSet *descriptorSet) {
        cobj->setCalledFromJS(true);
        se::AutoHandleScope hs;

        std::array<se::Value, 2> args;
        nativevalue_to_se(subModelIndex, args[0]);
        nativevalue_to_se(descriptorSet, args[1]);
        se::ScriptEngine::getInstance()->callFunction(thiz, "_updateLocalDescriptors", args.size(), args.data());
    });

    cobj->getEventProcessor().on(cc::EventTypesToJS::MODEL_UPDATE_INSTANCED_ATTRIBUTES, [=](const std::vector<cc::gfx::Attribute> &attributes, cc::scene::Pass *pass) {
        cobj->setCalledFromJS(true);
        se::AutoHandleScope hs;

        std::array<se::Value, 2> args;
        nativevalue_to_se(attributes, args[0]);
        nativevalue_to_se(pass, args[1]);
        se::ScriptEngine::getInstance()->callFunction(thiz, "_updateInstancedAttributes", args.size(), args.data());
    });

    cobj->getEventProcessor().on(cc::EventTypesToJS::MODEL_GET_MACRO_PATCHES, [=](index_t subModelIndex, std::vector<cc::scene::IMacroPatch> *pPatches) {
        cobj->setCalledFromJS(true);
        se::AutoHandleScope hs;

        se::Value                rval;
        std::array<se::Value, 1> args;
        nativevalue_to_se(subModelIndex, args[0]);
        bool ok = se::ScriptEngine::getInstance()->callFunction(thiz, "getMacroPatches", args.size(), args.data(), &rval);

        if (ok) {
            sevalue_to_native(rval, pPatches);
        }
    });

    return true;
}
SE_BIND_FUNC(js_Model_registerListeners) // NOLINT(readability-identifier-naming)

static bool js_assets_MaterialInstance_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::MaterialInstance>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_MaterialInstance_registerListeners : Invalid Native Object");
    cobj->setRebuildPSOCallback([](index_t index, cc::Material *material) {
        se::AutoHandleScope hs;
        se::Value           matVal;
        bool                ok = nativevalue_to_se(material, matVal);
        if (!ok) {
            return;
        }
        se::ScriptEngine::getInstance()->callFunction(matVal.toObject(), "_onRebuildPSO", 0, nullptr);
    });

    return true;
}
SE_BIND_FUNC(js_assets_MaterialInstance_registerListeners) // NOLINT(readability-identifier-naming)

bool register_all_scene_manual(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("ns", &nsVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("ns", nsVal);
    }
    se::ScriptEngine::getInstance()->addBeforeCleanupHook([]() {
#define _SAFE_UNROOT_AND_DEC(obj) \
    if ((obj) != nullptr) {       \
        (obj)->unroot();          \
        (obj)->decRef();          \
        (obj) = nullptr;          \
    }
        _SAFE_UNROOT_AND_DEC(nodeVec3CacheObj);
        _SAFE_UNROOT_AND_DEC(nodeQuatCacheObj);
        _SAFE_UNROOT_AND_DEC(nodeMat4CacheObj);

#undef _SAFE_UNROOT_AND_DEC
    });

    __jsb_cc_Root_proto->defineFunction("_registerListeners", _SE(js_root_registerListeners));

    __jsb_cc_scene_Camera_proto->defineFunction("screenPointToRay", _SE(js_scene_Camera_screenPointToRay));

    // Node TS wrapper will invoke this function to let native object listen some events.
    __jsb_cc_Node_proto->defineFunction("_registerListeners", _SE(js_scene_Node_registerListeners));

    __jsb_cc_Node_proto->defineFunction("_registerOnTransformChanged", _SE(js_scene_Node_registerOnTransformChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnParentChanged", _SE(js_scene_Node_registerOnParentChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnLayerChanged", _SE(js_scene_Node_registerOnLayerChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnChildRemoved", _SE(js_scene_Node_registerOnChildRemoved));
    __jsb_cc_Node_proto->defineFunction("_registerOnChildAdded", _SE(js_scene_Node_registerOnChildAdded));

    se::Value jsbVal;
    obj->getProperty("jsb", &jsbVal);
    se::Value nodeVal;
    jsbVal.toObject()->getProperty("Node", &nodeVal);

    nodeVal.toObject()->defineFunction("_setTempFloatArray", _SE(js_scene_Node__setTempFloatArray));

    __jsb_cc_Node_proto->defineFunction("getChildren", _SE(js_scene_Node_getChildren));
    __jsb_cc_Node_proto->defineFunction("getPosition", _SE(js_scene_Node_getPosition));
    __jsb_cc_Node_proto->defineFunction("getRotation", _SE(js_scene_Node_getRotation));
    __jsb_cc_Node_proto->defineFunction("setRotation", _SE(js_scene_Node_setRotation));
    __jsb_cc_Node_proto->defineFunction("setRotationFromEuler", _SE(js_scene_Node_setRotationFromEuler));
    __jsb_cc_Node_proto->defineFunction("getScale", _SE(js_scene_Node_getScale));
    __jsb_cc_Node_proto->defineFunction("getEulerAngles", _SE(js_scene_Node_getEulerAngles));
    __jsb_cc_Node_proto->defineFunction("getForward", _SE(js_scene_Node_getForward));
    __jsb_cc_Node_proto->defineFunction("getUp", _SE(js_scene_Node_getUp));
    __jsb_cc_Node_proto->defineFunction("getRight", _SE(js_scene_Node_getRight));
    __jsb_cc_Node_proto->defineFunction("getWorldMatrix", _SE(js_scene_Node_getWorldMatrix));
    __jsb_cc_Node_proto->defineFunction("getWorldPosition", _SE(js_scene_Node_getWorldPosition));
    __jsb_cc_Node_proto->defineFunction("getWorldRS", _SE(js_scene_Node_getWorldRS));
    __jsb_cc_Node_proto->defineFunction("getWorldRT", _SE(js_scene_Node_getWorldRT));
    __jsb_cc_Node_proto->defineFunction("getWorldRotation", _SE(js_scene_Node_getWorldRotation));
    __jsb_cc_Node_proto->defineFunction("getWorldScale", _SE(js_scene_Node_getWorldScale));
    __jsb_cc_Node_proto->defineProperty("worldMatrix", _SE(js_scene_Node_getWorldMatrix_asGetter), nullptr);
    __jsb_cc_Node_proto->defineFunction("isActiveInHierarchy", _SE(js_scene_Node_isActiveInHierarchy));
    __jsb_cc_Node_proto->defineFunction("setPosition", _SE(js_scene_Node_setPosition));
    __jsb_cc_Node_proto->defineFunction("setScale", _SE(js_scene_Node_setScale));
    __jsb_cc_Node_proto->defineFunction("rotateForJS", _SE(js_scene_Node_rotateForJS));
    __jsb_cc_Node_proto->defineFunction("setRTS", _SE(js_scene_Node_setRTS));

    __jsb_cc_scene_Pass_proto->defineProperty("blocks", _SE(js_scene_Pass_blocks_getter), nullptr);

    __jsb_cc_scene_RenderScene_proto->defineProperty("root", _SE(js_scene_RenderScene_root_getter), nullptr);

    __jsb_cc_scene_Model_proto->defineFunction("_registerListeners", _SE(js_Model_registerListeners));
    __jsb_cc_MaterialInstance_proto->defineFunction("_registerListeners", _SE(js_assets_MaterialInstance_registerListeners));

    return true;
}
