
// clang-format off
#include "cocos/bindings/auto/jsb_pipeline_auto.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "renderer/pipeline/forward/ForwardPipeline.h"
#include "renderer/pipeline/forward/ForwardFlow.h"
#include "renderer/pipeline/forward/ForwardStage.h"
#include "renderer/pipeline/shadow/ShadowFlow.h"
#include "renderer/pipeline/shadow/ShadowStage.h"
#include "renderer/pipeline/RenderPipeline.h"
#include "renderer/pipeline/RenderFlow.h"
#include "renderer/pipeline/RenderStage.h"
#include "renderer/pipeline/Define.h"
#include "renderer/pipeline/GlobalDescriptorSetManager.h"
#include "renderer/pipeline/InstancedBuffer.h"
#include "renderer/pipeline/deferred/DeferredPipeline.h"
#include "renderer/pipeline/deferred/MainFlow.h"
#include "renderer/pipeline/deferred/GbufferStage.h"
#include "renderer/pipeline/deferred/LightingStage.h"
#include "renderer/pipeline/deferred/BloomStage.h"
#include "renderer/pipeline/deferred/PostprocessStage.h"
#include "renderer/pipeline/PipelineSceneData.h"
#include "cocos/renderer/gfx-base/GFXBase.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cc_pipeline_RenderQueueDesc_proto = nullptr; // NOLINT
se::Class* __jsb_cc_pipeline_RenderQueueDesc_class = nullptr;  // NOLINT

static bool js_pipeline_RenderQueueDesc_get_isTransparent(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::RenderQueueDesc>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_RenderQueueDesc_get_isTransparent : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isTransparent, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->isTransparent, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_pipeline_RenderQueueDesc_get_isTransparent)

static bool js_pipeline_RenderQueueDesc_set_isTransparent(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::RenderQueueDesc>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_RenderQueueDesc_set_isTransparent : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isTransparent, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_pipeline_RenderQueueDesc_set_isTransparent : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_pipeline_RenderQueueDesc_set_isTransparent)

static bool js_pipeline_RenderQueueDesc_get_sortMode(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::RenderQueueDesc>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_RenderQueueDesc_get_sortMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->sortMode, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->sortMode, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_pipeline_RenderQueueDesc_get_sortMode)

static bool js_pipeline_RenderQueueDesc_set_sortMode(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::RenderQueueDesc>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_RenderQueueDesc_set_sortMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->sortMode, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_pipeline_RenderQueueDesc_set_sortMode : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_pipeline_RenderQueueDesc_set_sortMode)

static bool js_pipeline_RenderQueueDesc_get_stages(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::RenderQueueDesc>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_RenderQueueDesc_get_stages : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stages, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stages, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_pipeline_RenderQueueDesc_get_stages)

static bool js_pipeline_RenderQueueDesc_set_stages(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::RenderQueueDesc>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_RenderQueueDesc_set_stages : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stages, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_pipeline_RenderQueueDesc_set_stages : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_pipeline_RenderQueueDesc_set_stages)


template<>
bool sevalue_to_native(const se::Value &from, cc::pipeline::RenderQueueDesc * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::pipeline::RenderQueueDesc*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("isTransparent", &field, true);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isTransparent), ctx);
    }
    json->getProperty("sortMode", &field, true);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->sortMode), ctx);
    }
    json->getProperty("stages", &field, true);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stages), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_pipeline_RenderQueueDesc_finalize)

static bool js_pipeline_RenderQueueDesc_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        auto *ptr = JSB_MAKE_PRIVATE_OBJECT(cc::pipeline::RenderQueueDesc);
        s.thisObject()->setPrivateObject(ptr);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;
        auto *ptr = JSB_MAKE_PRIVATE_OBJECT(cc::pipeline::RenderQueueDesc);
        auto cobj = ptr->get<cc::pipeline::RenderQueueDesc>();
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            delete ptr;
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }
        s.thisObject()->setPrivateObject(ptr);
        return true;
    }
    auto *ptr = JSB_MAKE_PRIVATE_OBJECT(cc::pipeline::RenderQueueDesc);
    auto cobj = ptr->get<cc::pipeline::RenderQueueDesc>();
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->isTransparent), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->sortMode), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->stages), nullptr);
    }

    if(!ok) {
        delete ptr;
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }
    s.thisObject()->setPrivateObject(ptr);
    return true;
}
SE_BIND_CTOR(js_pipeline_RenderQueueDesc_constructor, __jsb_cc_pipeline_RenderQueueDesc_class, js_cc_pipeline_RenderQueueDesc_finalize)

static bool js_cc_pipeline_RenderQueueDesc_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_pipeline_RenderQueueDesc_finalize)

bool js_register_pipeline_RenderQueueDesc(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("RenderQueueDesc", obj, nullptr, _SE(js_pipeline_RenderQueueDesc_constructor));

    cls->defineProperty("isTransparent", _SE(js_pipeline_RenderQueueDesc_get_isTransparent), _SE(js_pipeline_RenderQueueDesc_set_isTransparent));
    cls->defineProperty("sortMode", _SE(js_pipeline_RenderQueueDesc_get_sortMode), _SE(js_pipeline_RenderQueueDesc_set_sortMode));
    cls->defineProperty("stages", _SE(js_pipeline_RenderQueueDesc_get_stages), _SE(js_pipeline_RenderQueueDesc_set_stages));
    cls->defineFinalizeFunction(_SE(js_cc_pipeline_RenderQueueDesc_finalize));
    cls->install();
    JSBClassType::registerClass<cc::pipeline::RenderQueueDesc>(cls);

    __jsb_cc_pipeline_RenderQueueDesc_proto = cls->getProto();
    __jsb_cc_pipeline_RenderQueueDesc_class = cls;


    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_pipeline_GlobalDSManager_proto = nullptr; // NOLINT
se::Class* __jsb_cc_pipeline_GlobalDSManager_class = nullptr;  // NOLINT

static bool js_pipeline_GlobalDSManager_bindBuffer(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_bindBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<cc::gfx::Buffer*, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_bindBuffer : Error processing arguments");
        cobj->bindBuffer(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_bindBuffer)

static bool js_pipeline_GlobalDSManager_bindSampler(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_bindSampler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<cc::gfx::Sampler*, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_bindSampler : Error processing arguments");
        cobj->bindSampler(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_bindSampler)

static bool js_pipeline_GlobalDSManager_bindTexture(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_bindTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<cc::gfx::Texture*, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_bindTexture : Error processing arguments");
        cobj->bindTexture(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_bindTexture)

static bool js_pipeline_GlobalDSManager_getDescriptorSetLayout(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_getDescriptorSetLayout : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::DescriptorSetLayout* result = cobj->getDescriptorSetLayout();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getDescriptorSetLayout : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_getDescriptorSetLayout)

static bool js_pipeline_GlobalDSManager_getDescriptorSetMap(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_getDescriptorSetMap : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::unordered_map<unsigned int, cc::gfx::DescriptorSet *> result = cobj->getDescriptorSetMap();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getDescriptorSetMap : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_getDescriptorSetMap)

static bool js_pipeline_GlobalDSManager_getGlobalDescriptorSet(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_getGlobalDescriptorSet : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::DescriptorSet* result = cobj->getGlobalDescriptorSet();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getGlobalDescriptorSet : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_getGlobalDescriptorSet)

static bool js_pipeline_GlobalDSManager_getLinearSampler(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_getLinearSampler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Sampler* result = cobj->getLinearSampler();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getLinearSampler : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_getLinearSampler)

static bool js_pipeline_GlobalDSManager_getOrCreateDescriptorSet(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_getOrCreateDescriptorSet : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getOrCreateDescriptorSet : Error processing arguments");
        cc::gfx::DescriptorSet* result = cobj->getOrCreateDescriptorSet(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getOrCreateDescriptorSet : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_getOrCreateDescriptorSet)

static bool js_pipeline_GlobalDSManager_getPointSampler(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_getPointSampler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Sampler* result = cobj->getPointSampler();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_pipeline_GlobalDSManager_getPointSampler : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_getPointSampler)

static bool js_pipeline_GlobalDSManager_update(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::pipeline::GlobalDSManager>(s);
    SE_PRECONDITION2(cobj, false, "js_pipeline_GlobalDSManager_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_pipeline_GlobalDSManager_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_pipeline_GlobalDSManager_finalize)

static bool js_pipeline_GlobalDSManager_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    auto *ptr = JSB_MAKE_PRIVATE_OBJECT(cc::pipeline::GlobalDSManager);
    s.thisObject()->setPrivateObject(ptr);
    return true;
}
SE_BIND_CTOR(js_pipeline_GlobalDSManager_constructor, __jsb_cc_pipeline_GlobalDSManager_class, js_cc_pipeline_GlobalDSManager_finalize)

static bool js_cc_pipeline_GlobalDSManager_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_pipeline_GlobalDSManager_finalize)

bool js_register_pipeline_GlobalDSManager(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("GlobalDSManager", obj, nullptr, _SE(js_pipeline_GlobalDSManager_constructor));

    cls->defineFunction("bindBuffer", _SE(js_pipeline_GlobalDSManager_bindBuffer));
    cls->defineFunction("bindSampler", _SE(js_pipeline_GlobalDSManager_bindSampler));
    cls->defineFunction("bindTexture", _SE(js_pipeline_GlobalDSManager_bindTexture));
    cls->defineFunction("getDescriptorSetLayout", _SE(js_pipeline_GlobalDSManager_getDescriptorSetLayout));
    cls->defineFunction("getDescriptorSetMap", _SE(js_pipeline_GlobalDSManager_getDescriptorSetMap));
    cls->defineFunction("getGlobalDescriptorSet", _SE(js_pipeline_GlobalDSManager_getGlobalDescriptorSet));
    cls->defineFunction("getLinearSampler", _SE(js_pipeline_GlobalDSManager_getLinearSampler));
    cls->defineFunction("getOrCreateDescriptorSet", _SE(js_pipeline_GlobalDSManager_getOrCreateDescriptorSet));
    cls->defineFunction("getPointSampler", _SE(js_pipeline_GlobalDSManager_getPointSampler));
    cls->defineFunction("update", _SE(js_pipeline_GlobalDSManager_update));
    cls->defineFinalizeFunction(_SE(js_cc_pipeline_GlobalDSManager_finalize));
    cls->install();
    JSBClassType::registerClass<cc::pipeline::GlobalDSManager>(cls);

    __jsb_cc_pipeline_GlobalDSManager_proto = cls->getProto();
    __jsb_cc_pipeline_GlobalDSManager_class = cls;


    se::ScriptEngine::getInstance()->clearException();
    return true;
}
