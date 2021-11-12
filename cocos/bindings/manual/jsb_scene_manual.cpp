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

static bool js_root_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_root_registerListeners : Invalid Native Object");

#define ROOT_DISPATCH_EVENT_TO_JS(eventType, jsFuncName)                                         \
    cobj->getEventProcessor()->on(eventType, [](cc::Root *rootObj) {                             \
        se::AutoHandleScope hs;                                                                  \
        se::Value           rootVal;                                                             \
        bool                ok = nativevalue_to_se(rootObj, rootVal);                            \
        SE_PRECONDITION2_VOID(ok, "js_root_registerListeners : Error processing arguments");     \
        if (rootVal.isObject()) {                                                                \
            se::Value funcVal;                                                                   \
            ok = rootVal.toObject()->getProperty(#jsFuncName, &funcVal) && funcVal.isObject();   \
            SE_PRECONDITION2_VOID(ok, "js_root_registerListeners : Error processing arguments"); \
            funcVal.toObject()->call(se::EmptyValueArray, rootVal.toObject());                   \
        }                                                                                        \
    })

    ROOT_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::ROOT_BATCH2D_INIT, _onBatch2DInit);
    ROOT_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::ROOT_BATCH2D_UPDATE, _onBatch2DUpdate);
    ROOT_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::ROOT_BATCH2D_UPLOAD_BUFFERS, _onBatch2DUploadBuffers);
    ROOT_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::ROOT_BATCH2D_RESET, _onBatch2DReset);

    return true;
}
SE_BIND_FUNC(js_root_registerListeners) // NOLINT(readability-identifier-naming)

static void registerOnTransformChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::TRANSFORM_CHANGED,
        [jsObject](cc::TransformBit transformBit) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onTransformChanged", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onTransformChanged.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(transformBit, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        });
}

static void registerOnParentChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::PARENT_CHANGED,
        [jsObject](cc::Node *oldParent) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onParentChanged", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onParentChanged.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(oldParent, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        });
}

static void registerOnLayerChanged(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::LAYER_CHANGED,
        [jsObject](uint32_t layer) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onLayerChanged", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onLayerChanged.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(layer, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        });
}

static void registerOnChildRemoved(cc::Node *node, se::Object *jsObject) {
    node->on(
        cc::NodeEventType::CHILD_REMOVED,
        [jsObject](cc::Node *child) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onChildRemoved", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onChildRemoved.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(child, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        });
}

static void registerOnChildAdded(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->on(
        cc::NodeEventType::CHILD_ADDED,
        [jsObject](cc::Node *child) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onChildAdded", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onChildAdded.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(child, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        },
        skip);
}

static void registerOnActiveNode(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->on(
        cc::EventTypesToJS::NODE_ACTIVE_NODE,
        [jsObject](bool shouldActiveNow) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onActiveNode", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onActiveNode.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(shouldActiveNow, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        },
        skip);
}

static void registerOnBatchCreated(cc::Node *node, se::Object *jsObject) {
    cc::CallbackInfoBase::ID skip;
    node->on(
        cc::EventTypesToJS::NODE_ON_BATCH_CREATED,
        [jsObject](bool dontChildPrefab) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            jsObject->getProperty("_onBatchCreated", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onBatchCreated.");

            se::ValueArray args;
            se::Value      arg0;
            nativevalue_to_se(dontChildPrefab, arg0);
            args.push_back(arg0);
            funcVal.toObject()->call(args, jsObject);
        },
        skip);
}

static bool js_scene_Node_registerListeners(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerListeners : Invalid Native Object");

    auto *jsObject = s.thisObject();

#define NODE_DISPATCH_EVENT_TO_JS(eventType, jsFuncName)                                                 \
    cobj->on(                                                                                            \
        eventType, [jsObject]() {                                                                        \
            se::AutoHandleScope hs;                                                                      \
            se::Value           funcVal;                                                                 \
            bool                ok = jsObject->getProperty(#jsFuncName, &funcVal) && funcVal.isObject(); \
            SE_PRECONDITION2_VOID(ok, "js_scene_Node_registerListeners : Error processing arguments");   \
            funcVal.toObject()->call(se::EmptyValueArray, jsObject);                                     \
        });

    registerOnActiveNode(cobj, jsObject);
    registerOnBatchCreated(cobj, jsObject);

    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_REATTACH, _onReAttach);
    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_REMOVE_PERSIST_ROOT_NODE, _onRemovePersistRootNode);
    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_DESTROY_COMPONENTS, _onDestroyComponents);
    NODE_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::NODE_UI_TRANSFORM_DIRTY, _onUiTransformDirty);
    NODE_DISPATCH_EVENT_TO_JS(cc::NodeEventType::SIBLING_ORDER_CHANGED, _onSiblingOrderChanged);

    cobj->on(
        cc::NodeEventType::NODE_DESTROYED,
        [](cc::Node *node) {
            se::AutoHandleScope hs;
            se::Value           funcVal;
            se::Value           nodeVal;
            nativevalue_to_se(node, nodeVal);
            nodeVal.toObject()->getProperty("_onNodeDestroyed", &funcVal);
            SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onNodeDestroyed.");

            se::ValueArray args;
            args.emplace_back(nodeVal);
            funcVal.toObject()->call(args, nodeVal.toObject());
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


static bool js_scene_Pass_blocks_getter(se::State &s) {
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_registerListeners : Invalid Native Object");
    auto *thiz = s.thisObject();

    se::Value blocksVal;
    if (thiz->getProperty("_blocks", &blocksVal) && blocksVal.isObject() && blocksVal.toObject()->isArray()) {
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
                block.size * 4)};
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

#define MODEL_DISPATCH_EVENT_TO_JS(eventType, jsFuncName)                                        \
    cobj->getEventProcessor().on(eventType, [=](uint32_t stamp) {                                \
        se::AutoHandleScope hs;                                                                  \
        se::Value           funcVal;                                                             \
        bool                ok = thiz->getProperty(#jsFuncName, &funcVal) && funcVal.isObject(); \
        SE_PRECONDITION2_VOID(ok, "js_Model_registerListeners : Could not find callback");       \
        se::ValueArray args;                                                                     \
        args.emplace_back(se::Value(stamp));                                                     \
        funcVal.toObject()->call(args, thiz);                                                    \
    })

    MODEL_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::MODEL_UPDATE_TRANSFORM, updateTransform);
    MODEL_DISPATCH_EVENT_TO_JS(cc::EventTypesToJS::MODEL_UPDATE_UBO, updateUBOs);

#undef MODEL_DISPATCH_EVENT_TO_JS

    cobj->getEventProcessor().on(cc::EventTypesToJS::MODEL_UPDATE_LOCAL_DESCRIPTORS, [=](index_t subModelIndex, cc::gfx::DescriptorSet *descriptorSet) {
        se::AutoHandleScope hs;
        se::Value           funcVal;
        bool                ok = thiz->getProperty("_updateLocalDescriptors", &funcVal) && funcVal.isObject() && funcVal.toObject()->isFunction();
        SE_PRECONDITION2_VOID(ok, "Not function named _updateLocalDescriptors.");

        se::ValueArray args;
        args.resize(2);
        nativevalue_to_se(subModelIndex, args[0]);
        nativevalue_to_se(descriptorSet, args[1]);
        funcVal.toObject()->call(args, thiz);
    });

    cobj->getEventProcessor().on(cc::EventTypesToJS::MODEL_UPDATE_INSTANCED_ATTRIBUTES, [=](const std::vector<cc::gfx::Attribute> &attributes, cc::scene::Pass *pass) {
        se::AutoHandleScope hs;
        se::Value           funcVal;
        bool                ok = thiz->getProperty("_updateInstancedAttributes", &funcVal) && funcVal.isObject() && funcVal.toObject()->isFunction();
        SE_PRECONDITION2_VOID(ok, "Not function named _updateInstancedAttributes.");

        se::ValueArray args;
        args.resize(2);
        nativevalue_to_se(attributes, args[0]);
        nativevalue_to_se(pass, args[1]);
        funcVal.toObject()->call(args, thiz);
    });

    cobj->getEventProcessor().on(cc::EventTypesToJS::MODEL_GET_MACRO_PATCHES, [=](index_t subModelIndex, std::vector<cc::scene::IMacroPatch> *pPatches) {
        se::AutoHandleScope hs;
        se::Value           funcVal;
        bool                ok = thiz->getProperty("getMacroPatches", &funcVal) && funcVal.isObject() && funcVal.toObject()->isFunction();
        SE_PRECONDITION2_VOID(ok, "Not function named getMacroPatches.");

        se::ValueArray args;
        se::Value      rval;
        args.resize(1);
        nativevalue_to_se(subModelIndex, args[0]);
        ok = funcVal.toObject()->call(args, thiz, &rval);
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
        se::Object *jsObject = matVal.toObject();
        se::Value   funcVal;
        jsObject->getProperty("_onRebuildPSO", &funcVal);
        SE_PRECONDITION2_VOID(funcVal.isObject() && funcVal.toObject()->isFunction(), "Not function named _onRebuildPSO.");
        funcVal.toObject()->call(se::EmptyValueArray, jsObject);
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

    __jsb_cc_Root_proto->defineFunction("_registerListeners", _SE(js_root_registerListeners));

    // Node TS wrapper will invoke this function to let native object listen some events.
    __jsb_cc_Node_proto->defineFunction("_registerListeners", _SE(js_scene_Node_registerListeners));

    __jsb_cc_Node_proto->defineFunction("_registerOnTransformChanged", _SE(js_scene_Node_registerOnTransformChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnParentChanged", _SE(js_scene_Node_registerOnParentChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnLayerChanged", _SE(js_scene_Node_registerOnLayerChanged));
    __jsb_cc_Node_proto->defineFunction("_registerOnChildRemoved", _SE(js_scene_Node_registerOnChildRemoved));
    __jsb_cc_Node_proto->defineFunction("_registerOnChildAdded", _SE(js_scene_Node_registerOnChildAdded));

    __jsb_cc_scene_Pass_proto->defineProperty("blocks", _SE(js_scene_Pass_blocks_getter), nullptr);

    __jsb_cc_scene_RenderScene_proto->defineProperty("root", _SE(js_scene_RenderScene_root_getter), nullptr);

    __jsb_cc_scene_Model_proto->defineFunction("_registerListeners", _SE(js_Model_registerListeners));
    __jsb_cc_MaterialInstance_proto->defineFunction("_registerListeners", _SE(js_assets_MaterialInstance_registerListeners));

    return true;
}
