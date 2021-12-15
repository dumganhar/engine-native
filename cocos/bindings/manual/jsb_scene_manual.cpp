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
#include "core/Root.h"
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


static float *_tempFloatArray{nullptr};
static void *nodeCommandArrayBuffers[]{nullptr, nullptr}; //cjh HOW TO RESET?

#define REGISTER_NODE_TYPED_ARRAY(jsPropertyName, cppFuncName, cppPtrType, typedArrayType, dataBytes) \
do { \
    se::Value val; \
    bool ok = jsObject->getProperty(jsPropertyName, &val); \
    CC_ASSERT(ok && val.isObject() && val.toObject()->isTypedArray() && val.toObject()->getTypedArrayType() == typedArrayType); \
    uint8_t *ptr{nullptr}; \
    size_t bytes{0}; \
    ok = val.toObject()->getTypedArrayData(&ptr, &bytes); \
    CC_ASSERT(ok && bytes == (dataBytes)); \
    cobj->cppFuncName(reinterpret_cast<cppPtrType>(ptr)); \
} while(false)

static void registerOnUiTransformDirty(cc::Node *node, se::Object *jsObject) {
    se::Value           uiPropsVal;
    jsObject->getProperty("_uiProps", &uiPropsVal, true);
    SE_PRECONDITION2_VOID(uiPropsVal.isObject(), "Not property named _uiProps.");
    se::Value uiTransformDirtyVal;
    uiPropsVal.toObject()->getProperty("_uiTransformDirty", &uiTransformDirtyVal, true);
    SE_PRECONDITION2_VOID(uiTransformDirtyVal.isObject() && uiTransformDirtyVal.toObject()->isTypedArray()
                          && uiTransformDirtyVal.toObject()->getTypedArrayType() == se::Object::TypedArrayType::UINT32,
                          "_uiTransformDirtyVal is not a TypedArray");
    uint8_t* pDirty{nullptr};
    size_t dirtyArrBytes{0};
    bool ok = uiTransformDirtyVal.toObject()->getTypedArrayData(&pDirty, &dirtyArrBytes);
    CC_ASSERT(ok && pDirty != nullptr && dirtyArrBytes == 4);
    node->setUIPropsTransformDirtyPtr(reinterpret_cast<uint32_t*>(pDirty));
}

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
    node->on(
        cc::NodeEventType::CHILD_ADDED,
        [jsObject](cc::Node *child) {
            se::AutoHandleScope hs;
            se::Value           arg0;
            nativevalue_to_se(child, arg0);
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onChildAdded", 1, &arg0);
        });
}

static void registerOnSiblingOrderChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::SIBLING_ORDER_CHANGED,
        [jsObject]() {
            se::AutoHandleScope hs;
            se::ScriptEngine::getInstance()->callFunction(jsObject, "_onSiblingOrderChanged", 0, nullptr);
        });
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

static void registerLocalPositionRotationScaleUpdated(cc::Node *node, se::Object *jsObject) {
    node->on(cc::EventTypesToJS::NODE_LOCAL_POSITION_UPDATED, [jsObject](float x, float y, float z) {
        se::AutoHandleScope      hs;
        std::array<se::Value, 3> args;
        nativevalue_to_se(x, args[0]);
        nativevalue_to_se(y, args[1]);
        nativevalue_to_se(z, args[2]);
        se::ScriptEngine::getInstance()->callFunction(jsObject, "_onLocalPositionUpdated", args.size(), args.data());
    });

    node->on(cc::EventTypesToJS::NODE_LOCAL_ROTATION_UPDATED, [jsObject](float x, float y, float z, float w) {
        se::AutoHandleScope      hs;
        std::array<se::Value, 4> args;
        nativevalue_to_se(x, args[0]);
        nativevalue_to_se(y, args[1]);
        nativevalue_to_se(z, args[2]);
        nativevalue_to_se(z, args[3]);
        se::ScriptEngine::getInstance()->callFunction(jsObject, "_onLocalRotationUpdated", args.size(), args.data());
    });

    node->on(cc::EventTypesToJS::NODE_LOCAL_SCALE_UPDATED, [jsObject](float x, float y, float z) {
        se::AutoHandleScope      hs;
        std::array<se::Value, 3> args;
        nativevalue_to_se(x, args[0]);
        nativevalue_to_se(y, args[1]);
        nativevalue_to_se(z, args[2]);
        se::ScriptEngine::getInstance()->callFunction(jsObject, "_onLocalScaleUpdated", args.size(), args.data());
    });

    node->on(cc::EventTypesToJS::NODE_LOCAL_POSITION_ROTATION_SCALE_UPDATED, [jsObject](float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz) {
        se::AutoHandleScope       hs;
        std::array<se::Value, 10> args;
        nativevalue_to_se(px, args[0]);
        nativevalue_to_se(py, args[1]);
        nativevalue_to_se(pz, args[2]);

        nativevalue_to_se(rx, args[3]);
        nativevalue_to_se(ry, args[4]);
        nativevalue_to_se(rz, args[5]);
        nativevalue_to_se(rw, args[6]);

        nativevalue_to_se(sx, args[7]);
        nativevalue_to_se(sy, args[8]);
        nativevalue_to_se(sz, args[9]);

        se::ScriptEngine::getInstance()->callFunction(jsObject, "_onLocalPositionRotationScaleUpdated", args.size(), args.data());
    });
}

static bool js_scene_Node_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerListeners : Invalid Native Object");

    auto *jsObject = s.thisObject();

    registerOnUiTransformDirty(cobj, jsObject);
    REGISTER_NODE_TYPED_ARRAY("_activeInHierarchyArr", setActiveInHierarchyPtr, uint8_t*, se::Object::TypedArrayType::UINT8, 1);
    REGISTER_NODE_TYPED_ARRAY("_layerArr", setLayerPtr, uint32_t*, se::Object::TypedArrayType::UINT32, 4);
    REGISTER_NODE_TYPED_ARRAY("_worldMatrixArr", setWorldMatrixPtr, float*, se::Object::TypedArrayType::FLOAT32, 4 * 16);
    REGISTER_NODE_TYPED_ARRAY("_worldPositionArr", setWorldPositionPtr, float*, se::Object::TypedArrayType::FLOAT32, 4 * 3);
    REGISTER_NODE_TYPED_ARRAY("_worldRotationArr", setWorldRotationPtr, float*, se::Object::TypedArrayType::FLOAT32, 4 * 4);
    REGISTER_NODE_TYPED_ARRAY("_worldScaleArr", setWorldScalePtr, float*, se::Object::TypedArrayType::FLOAT32, 4 * 3);

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
    //    NODE_DISPATCH_EVENT_TO_JS(cc::NodeEventType::SIBLING_ORDER_CHANGED, _onSiblingOrderChanged);

    cobj->on(
        cc::NodeEventType::NODE_DESTROYED,
        [](cc::Node *node) {
            se::AutoHandleScope hs;
            se::Value           nodeVal;
            nativevalue_to_se(node, nodeVal);
            se::ScriptEngine::getInstance()->callFunction(nodeVal.toObject(), "_onNodeDestroyed", 1, &nodeVal);
        });

    cobj->onSiblingIndexChanged = [jsObject](index_t newIndex) {
        se::AutoHandleScope hs;
        se::Value           arg0;
        nativevalue_to_se(newIndex, arg0);
        se::ScriptEngine::getInstance()->callFunction(jsObject, "_onSiblingIndexChanged", 1, &arg0);
    };

    cobj->on(cc::EventTypesToJS::NODE_SCENE_UPDATED, [jsObject](cc::Scene *scene) {
        se::AutoHandleScope hs;
        se::Value           arg0;
        nativevalue_to_se(scene, arg0);
        se::ScriptEngine::getInstance()->callFunction(jsObject, "_onSceneUpdated", 1, &arg0);
    });

    registerLocalPositionRotationScaleUpdated(cobj, jsObject);

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

static bool js_scene_Node_registerOnSiblingOrderChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerOnSiblingOrderChanged : Invalid Native Object");

    auto *jsObject = s.thisObject();
    registerOnSiblingOrderChanged(cobj, jsObject);
    return true;
}
SE_BIND_FUNC(js_scene_Node_registerOnSiblingOrderChanged) // NOLINT(readability-identifier-naming)

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

static bool js_scene_Node__setCommandArrayBuffer(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        uint8_t *buffer = nullptr;
        args[0].toObject()->getArrayBufferData(&buffer, nullptr);
        nodeCommandArrayBuffers[0] = buffer;
        buffer = nullptr;
        args[1].toObject()->getArrayBufferData(&buffer, nullptr);
        nodeCommandArrayBuffers[1] = buffer;
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Node__setCommandArrayBuffer)

static bool js_scene_Node_getRight(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    cc::Vec3 result = cobj->getRight();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getRight)

static bool js_scene_Node_getUp(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    cc::Vec3 result = cobj->getUp();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getUp)

static bool js_scene_Node_getWorldMatrix(void *nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj   = reinterpret_cast<cc::Node *>(nativeObject);
    const cc::Mat4 &result = cobj->getWorldMatrix();
    memcpy(_tempFloatArray, result.m, sizeof(result.m));
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getWorldMatrix)

static bool js_scene_Node_getWorldPosition(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    const cc::Vec3 &result = cobj->getWorldPosition();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getWorldPosition)

static bool js_scene_Node_getAngle(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    const float result = cobj->getAngle();
    _tempFloatArray[0] = result;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getAngle)

static bool js_scene_Node_getWorldRS(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj   = reinterpret_cast<cc::Node *>(nativeObject);
    const cc::Mat4 &result = cobj->getWorldRS();
    memcpy(_tempFloatArray, result.m, sizeof(result.m));
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getWorldRS)

static bool js_scene_Node_getWorldRT(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj   = reinterpret_cast<cc::Node *>(nativeObject);
    const cc::Mat4 &result = cobj->getWorldRT();
    memcpy(_tempFloatArray, result.m, sizeof(result.m));
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getWorldRT)

static bool js_scene_Node_getWorldRotation(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    const cc::Quaternion &result = cobj->getWorldRotation();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    _tempFloatArray[3] = result.w;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getWorldRotation)

static bool js_scene_Node_getWorldScale(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    const cc::Vec3 &result = cobj->getWorldScale();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getWorldScale)

static bool js_scene_Node_getEulerAngles(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    const cc::Vec3 &result = cobj->getEulerAngles();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getEulerAngles)

static bool js_scene_Node_getForward(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto *cobj = reinterpret_cast<cc::Node*>(nativeObject);
    const cc::Vec3 &result = cobj->getForward();
    _tempFloatArray[0] = result.x;
    _tempFloatArray[1] = result.y;
    _tempFloatArray[2] = result.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_getForward)

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

static bool js_scene_Node_inverseTransformPoint(void* nativeObject) // NOLINT(readability-identifier-naming)
{
    auto* cobj = reinterpret_cast<cc::Node*>(nativeObject);
    cc::Vec3 p{_tempFloatArray[0], _tempFloatArray[1], _tempFloatArray[2]};
    cc::Vec3 ret = cobj->inverseTransformPoint(p);
    _tempFloatArray[0] = ret.x;
    _tempFloatArray[1] = ret.y;
    _tempFloatArray[2] = ret.z;
    return true;
}
SE_BIND_FUNC_FAST(js_scene_Node_inverseTransformPoint)

enum NodeCommandID : uint8_t {
    NODE_COMMAND_ID_BEGIN = 10,

    NODE_COMMAND_ID_SET_POSITION,
    NODE_COMMAND_ID_SET_ROTATION,
    NODE_COMMAND_ID_SET_SCALE,

    NODE_COMMAND_SET_ROTATION_FROM_EULER,
    NODE_COMMAND_SET_RTS,
    NODE_COMMAND_SET_WORLD_POSITION,
    NODE_COMMAND_SET_WORLD_ROTATION,
    NODE_COMMAND_SET_WORLD_SCALE,
    NODE_COMMAND_SET_MATRIX,

    NODE_COMMAND_TRANSLATE,
    NODE_COMMAND_ROTATE,
    NODE_COMMAND_LOOK_AT,
    NODE_COMMAND_UPDATE_WORLD_TRANSFORM,
    NODE_COMMAND_SET_ANGLE,
    NODE_COMMAND_SET_FORWARD,

    NODE_COMMAND_UPDATE_SIBLING_INDEX,
    NODE_COMMAND_SET_ACTIVE,
    NODE_COMMAND_SET_SIBLING_INDEX,
    NODE_COMMAND_SET_PERSIS_NODE,
    NODE_COMMAND_INVALIDATE_CHILDREN,
    NODE_COMMAND_SET_CHANGED_FLAGS,
    NODE_COMMAND_SET_DIRTY_FLAG,
    NODE_COMMAND_SET_EVENT_MASK,

    NODE_COMMAND_ID_END
};

CC_FORCE_INLINE static bool isCommandValid(uint32_t commandID) {
    return commandID > NODE_COMMAND_ID_BEGIN && commandID < NODE_COMMAND_ID_END;
}

class NodeCommandQueueView final {
public:
    NodeCommandQueueView(void* arrayBuffer, uint32_t commandBytes)
    : _arrayBuffer(reinterpret_cast<uint8_t*>(arrayBuffer))
    , _commandBytes(commandBytes) {

    }

    CC_FORCE_INLINE uint8_t getUint8() {
        CC_ASSERT(_byteOffset < _commandBytes);
        uint8_t ret = *(_arrayBuffer + _byteOffset);
        _byteOffset += 1;
        return ret;
    }

    CC_FORCE_INLINE bool getBool() {
        return getUint8() != 0;
    }

    CC_FORCE_INLINE uint32_t getUint32() {
        CC_ASSERT(_byteOffset < _commandBytes);
        uint32_t ret = *reinterpret_cast<uint32_t*>(_arrayBuffer + _byteOffset);
        _byteOffset += 4;
        return ret;
    }

    CC_FORCE_INLINE int32_t getInt32() {
        CC_ASSERT(_byteOffset < _commandBytes);
        int32_t ret = *reinterpret_cast<int32_t*>(_arrayBuffer + _byteOffset);
        _byteOffset += 4;
        return ret;
    }

    CC_FORCE_INLINE uint64_t getBigUint64() {
        CC_ASSERT(_byteOffset < _commandBytes);
        uint64_t ret = *reinterpret_cast<uint64_t*>(_arrayBuffer + _byteOffset);
        _byteOffset += 8;
        return ret;
    }

    CC_FORCE_INLINE float getFloat32() {
        CC_ASSERT(_byteOffset < _commandBytes);
        float ret = *reinterpret_cast<float*>(_arrayBuffer + _byteOffset);
        _byteOffset += 4;
        return ret;
    }

    CC_FORCE_INLINE void increaseOffset(uint32_t offset) {
        _byteOffset += offset;
    }

    CC_FORCE_INLINE bool isFinished() const {
        return _byteOffset >= _commandBytes;
    }

    CC_FORCE_INLINE uint8_t* data() const {
        return _arrayBuffer + _byteOffset;
    }

private:
    uint8_t* _arrayBuffer{nullptr};
    uint32_t _commandBytes{0};
    uint32_t _byteOffset{0};
};

static void flushCommandsToNative(void *arrayBuffer, uint32_t commandBytes) {
    using namespace cc;
    if (commandBytes == 0) {
        return;
    }

    NodeCommandQueueView view(arrayBuffer, commandBytes);
    while (!view.isFinished()) {
        const uint8_t command = view.getUint8();
        bool ok = isCommandValid(command);
        CC_ASSERT(ok);
        if (!ok) {
            return;
        }

        Node* node = reinterpret_cast<Node*>(view.getBigUint64());
        if (node->getName() == "AddLabel") {
            int a = 0;
        }

        switch (command) {
            case NODE_COMMAND_ID_SET_POSITION: {
                node->setPositionInternal(view.getFloat32(), view.getFloat32(), view.getFloat32(), true);
                break;
            }
            case NODE_COMMAND_ID_SET_ROTATION: {
                node->setRotationInternal(view.getFloat32(), view.getFloat32(), view.getFloat32(), view.getFloat32(), true);
                break;
            }
            case NODE_COMMAND_ID_SET_SCALE: {
                node->setScaleInternal(view.getFloat32(), view.getFloat32(), view.getFloat32(), true);
                break;
            }
            case NODE_COMMAND_SET_ROTATION_FROM_EULER: {
                node->setRotationFromEuler(view.getFloat32(), view.getFloat32(), view.getFloat32());
                break;
            }
            case NODE_COMMAND_SET_RTS: {
                Vec3 position;
                Vec3* pPosition{nullptr};
                Quaternion rotation;
                Quaternion* pRotation{nullptr};
                Vec3 scale;
                Vec3* pScale{nullptr};

                // pos
                if (view.getUint8() != 0) {
                    position.set(view.getFloat32(), view.getFloat32(), view.getFloat32());
                    pPosition = &position;
                }

                // rot
                if (view.getUint8() != 0) {
                    rotation.set(view.getFloat32(), view.getFloat32(), view.getFloat32(), view.getFloat32());
                    pRotation = &rotation;
                }

                // scale
                if (view.getUint8() != 0) {
                    scale.set(view.getFloat32(), view.getFloat32(), view.getFloat32());
                    pScale = &scale;
                }

                node->setRTS(pRotation, pPosition, pScale);
                break;
            }
            case NODE_COMMAND_SET_WORLD_POSITION: {
                node->setWorldPosition(view.getFloat32(), view.getFloat32(), view.getFloat32());
                break;
            }
            case NODE_COMMAND_SET_WORLD_ROTATION: {
                node->setWorldRotation(view.getFloat32(), view.getFloat32(), view.getFloat32(), view.getFloat32());
                break;
            }
            case NODE_COMMAND_SET_WORLD_SCALE: {
                node->setWorldScale(view.getFloat32(), view.getFloat32(), view.getFloat32());
                break;
            }
            case NODE_COMMAND_SET_MATRIX: {
                Mat4 mat;
                memcpy(&mat.m, view.data(), sizeof(mat.m));
                view.increaseOffset(sizeof(mat.m));
                node->setMatrix(mat);
                break;
            }
            case NODE_COMMAND_TRANSLATE: {
                Vec3 trans{view.getFloat32(), view.getFloat32(), view.getFloat32()};
                if (view.getUint8()) {
                    node->translate(trans, static_cast<NodeSpace>(view.getUint32()));
                } else {
                    node->translate(trans);
                }
                break;
            }
            case NODE_COMMAND_ROTATE: {
                Quaternion rot{view.getFloat32(), view.getFloat32(), view.getFloat32(), view.getFloat32()};
                if (view.getUint8()) {
                    node->rotate(rot, static_cast<NodeSpace>(view.getUint32()));
                } else {
                    node->rotate(rot);
                }
                break;
            }
            case NODE_COMMAND_LOOK_AT: {
                Vec3 pos{view.getFloat32(), view.getFloat32(), view.getFloat32()};
                if (view.getUint8()) {
                    node->lookAt(pos, Vec3{view.getFloat32(), view.getFloat32(), view.getFloat32()});
                } else {
                    node->lookAt(pos);
                }
                break;
            }
            case NODE_COMMAND_UPDATE_WORLD_TRANSFORM: {
                node->updateWorldTransform();
                break;
            }
            case NODE_COMMAND_SET_ANGLE: {
                node->setAngle(view.getFloat32());
                break;
            }
            case NODE_COMMAND_SET_FORWARD: {
                node->setForward(Vec3{view.getFloat32(), view.getFloat32(), view.getFloat32()});
                break;
            }
            case NODE_COMMAND_UPDATE_SIBLING_INDEX: {
                node->updateSiblingIndex();
                break;
            }
            case NODE_COMMAND_SET_ACTIVE: {
                node->setActive(view.getBool());
                break;
            }
            case NODE_COMMAND_SET_SIBLING_INDEX: {
                node->setSiblingIndex(view.getInt32());
                break;
            }
            case NODE_COMMAND_SET_PERSIS_NODE: {
                node->setPersistNode(view.getBool());
                break;
            }
            case NODE_COMMAND_INVALIDATE_CHILDREN: {
                node->invalidateChildren(static_cast<TransformBit>(view.getUint32()));
                break;
            }
            case NODE_COMMAND_SET_CHANGED_FLAGS: {
                node->setChangedFlags(view.getUint32());
                break;
            }
            case NODE_COMMAND_SET_DIRTY_FLAG: {
                node->setDirtyFlag(view.getUint32());
                break;
            }
            case NODE_COMMAND_SET_EVENT_MASK: {
                node->setEventMask(view.getUint32());
                break;
            }
            default:
                CC_ASSERT(false);
                break;
        }
    }
}

static bool js_scene_Node__flushCommandsToNative(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if CC_LIKELY (argc == 2) {
        flushCommandsToNative(nodeCommandArrayBuffers[args[0].toUint32()], args[1].toUint32());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Node__flushCommandsToNative)

bool register_all_scene_manual(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("ns", &nsVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("ns", nsVal);
    }

    __jsb_cc_Root_proto->defineFunction("_registerListeners", _SE(js_root_registerListeners));

    __jsb_cc_scene_Camera_proto->defineFunction("screenPointToRay", _SE(js_scene_Camera_screenPointToRay));

    // Node TS wrapper will invoke this function to let native object listen some events.
    __jsb_cc_Node_proto->defineFunction("_registerListeners", _SE(js_scene_Node_registerListeners));

    __jsb_cc_Node_proto->defineFunction("_registerOnTransformChanged", _SE(js_scene_Node_registerOnTransformChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnParentChanged", _SE(js_scene_Node_registerOnParentChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnLayerChanged", _SE(js_scene_Node_registerOnLayerChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnChildRemoved", _SE(js_scene_Node_registerOnChildRemoved));
    __jsb_cc_Node_proto->defineFunction("_registerOnChildAdded", _SE(js_scene_Node_registerOnChildAdded));
    __jsb_cc_Node_proto->defineFunction("_registerOnSiblingOrderChanged", _SE(js_scene_Node_registerOnSiblingOrderChanged));

    se::Value jsbVal;
    obj->getProperty("jsb", &jsbVal);
    se::Value nodeVal;
    jsbVal.toObject()->getProperty("Node", &nodeVal);

    nodeVal.toObject()->defineFunction("_setTempFloatArray", _SE(js_scene_Node__setTempFloatArray));
    nodeVal.toObject()->defineFunction("_setCommandArrayBuffer", _SE(js_scene_Node__setCommandArrayBuffer));
    nodeVal.toObject()->defineFunction("_flushCommandsToNative", _SE(js_scene_Node__flushCommandsToNative));

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
    __jsb_cc_Node_proto->defineFunction("getAngle", _SE(js_scene_Node_getAngle));
    __jsb_cc_Node_proto->defineFunction("inverseTransformPoint", _SE(js_scene_Node_inverseTransformPoint));

    __jsb_cc_scene_Pass_proto->defineProperty("blocks", _SE(js_scene_Pass_blocks_getter), nullptr);

    __jsb_cc_scene_RenderScene_proto->defineProperty("root", _SE(js_scene_RenderScene_root_getter), nullptr);

    __jsb_cc_scene_Model_proto->defineFunction("_registerListeners", _SE(js_Model_registerListeners));
    __jsb_cc_MaterialInstance_proto->defineFunction("_registerListeners", _SE(js_assets_MaterialInstance_registerListeners));

    return true;
}
