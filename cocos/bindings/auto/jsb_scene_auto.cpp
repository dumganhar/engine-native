#include "cocos/bindings/auto/jsb_scene_auto.h"
#include "cocos/bindings/auto/jsb_pipeline_auto.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "scene/Ambient.h"
#include "scene/Camera.h"
#include "scene/Define.h"
#include "scene/DirectionalLight.h"
#include "scene/DrawBatch2D.h"
#include "scene/Light.h"
#include "scene/Model.h"
#include "scene/Pass.h"
#include "scene/RenderScene.h"
#include "scene/RenderWindow.h"
#include "scene/SphereLight.h"
#include "scene/SpotLight.h"
#include "scene/SubModel.h"

#ifndef JSB_ALLOC
    #define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
    #define JSB_FREE(ptr) delete ptr
#endif
se::Object *__jsb_cc_scene_Light_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Light_class = nullptr; // NOLINT

static bool js_scene_Light_attachToScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_attachToScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderScene *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_attachToScene : Error processing arguments");
        cobj->attachToScene(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_attachToScene)

static bool js_scene_Light_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_destroy)

static bool js_scene_Light_detachFromScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_detachFromScene : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->detachFromScene();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_detachFromScene)

static bool js_scene_Light_getName(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getName : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::string &result = cobj->getName();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getName : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getName)

static bool js_scene_Light_getScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderScene *result = cobj->getScene();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getScene : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getScene)

static bool js_scene_Light_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_initialize : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->initialize();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_initialize)

static bool js_scene_Light_isBaked(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_isBaked : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isBaked();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_isBaked : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_isBaked)

static bool js_scene_Light_isUseColorTemperature(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_isUseColorTemperature : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isUseColorTemperature();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_isUseColorTemperature : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_isUseColorTemperature)

static bool js_scene_Light_setBaked(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setBaked : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setBaked : Error processing arguments");
        cobj->setBaked(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setBaked)

static bool js_scene_Light_setColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setColor : Error processing arguments");
        cobj->setColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setColor)

static bool js_scene_Light_setColorTemperature(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setColorTemperature : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setColorTemperature : Error processing arguments");
        cobj->setColorTemperature(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setColorTemperature)

static bool js_scene_Light_setColorTemperatureRGB(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setColorTemperatureRGB : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setColorTemperatureRGB : Error processing arguments");
        cobj->setColorTemperatureRGB(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setColorTemperatureRGB)

static bool js_scene_Light_setName(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setName : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setName : Error processing arguments");
        cobj->setName(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setName)

static bool js_scene_Light_setNode(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setNode : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Node *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setNode : Error processing arguments");
        cobj->setNode(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setNode)

static bool js_scene_Light_setUseColorTemperature(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setUseColorTemperature : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setUseColorTemperature : Error processing arguments");
        cobj->setUseColorTemperature(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setUseColorTemperature)

static bool js_scene_Light_update(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_update : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_update)

static bool js_scene_Light_nt2lm_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Light_nt2lm_static : Error processing arguments");
        float result = cc::scene::Light::nt2lm(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_nt2lm_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_nt2lm_static)

bool js_register_scene_Light(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Light", obj, nullptr, nullptr);

    cls->defineFunction("attachToScene", _SE(js_scene_Light_attachToScene));
    cls->defineFunction("destroy", _SE(js_scene_Light_destroy));
    cls->defineFunction("detachFromScene", _SE(js_scene_Light_detachFromScene));
    cls->defineFunction("getName", _SE(js_scene_Light_getName));
    cls->defineFunction("getScene", _SE(js_scene_Light_getScene));
    cls->defineFunction("initialize", _SE(js_scene_Light_initialize));
    cls->defineFunction("isBaked", _SE(js_scene_Light_isBaked));
    cls->defineFunction("isUseColorTemperature", _SE(js_scene_Light_isUseColorTemperature));
    cls->defineFunction("setBaked", _SE(js_scene_Light_setBaked));
    cls->defineFunction("setColor", _SE(js_scene_Light_setColor));
    cls->defineFunction("setColorTemperature", _SE(js_scene_Light_setColorTemperature));
    cls->defineFunction("setColorTemperatureRGB", _SE(js_scene_Light_setColorTemperatureRGB));
    cls->defineFunction("setName", _SE(js_scene_Light_setName));
    cls->defineFunction("setNode", _SE(js_scene_Light_setNode));
    cls->defineFunction("setUseColorTemperature", _SE(js_scene_Light_setUseColorTemperature));
    cls->defineFunction("update", _SE(js_scene_Light_update));
    cls->defineStaticFunction("nt2lm", _SE(js_scene_Light_nt2lm_static));
    cls->install();
    JSBClassType::registerClass<cc::scene::Light>(cls);

    __jsb_cc_scene_Light_proto = cls->getProto();
    __jsb_cc_scene_Light_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_DirectionalLight_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_DirectionalLight_class = nullptr; // NOLINT

static bool js_scene_DirectionalLight_setDirection(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DirectionalLight_setDirection : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_DirectionalLight_setDirection : Error processing arguments");
        cobj->setDirection(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_DirectionalLight_setDirection)

static bool js_scene_DirectionalLight_setIlluminance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DirectionalLight_setIlluminance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_DirectionalLight_setIlluminance : Error processing arguments");
        cobj->setIlluminance(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_DirectionalLight_setIlluminance)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_DirectionalLight_finalize)

static bool js_scene_DirectionalLight_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::DirectionalLight *cobj = JSB_ALLOC(cc::scene::DirectionalLight);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_DirectionalLight_constructor, __jsb_cc_scene_DirectionalLight_class, js_cc_scene_DirectionalLight_finalize)

static bool js_cc_scene_DirectionalLight_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::DirectionalLight>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_DirectionalLight_finalize)

bool js_register_scene_DirectionalLight(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("DirectionalLight", obj, __jsb_cc_scene_Light_proto, _SE(js_scene_DirectionalLight_constructor));

    cls->defineFunction("setDirection", _SE(js_scene_DirectionalLight_setDirection));
    cls->defineFunction("setIlluminance", _SE(js_scene_DirectionalLight_setIlluminance));
    cls->defineFinalizeFunction(_SE(js_cc_scene_DirectionalLight_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::DirectionalLight>(cls);

    __jsb_cc_scene_DirectionalLight_proto = cls->getProto();
    __jsb_cc_scene_DirectionalLight_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_SpotLight_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_SpotLight_class = nullptr; // NOLINT

static bool js_scene_SpotLight_getLuminance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getLuminance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getLuminance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getLuminance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getLuminance)

static bool js_scene_SpotLight_setAspect(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setAspect : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setAspect : Error processing arguments");
        cobj->setAspect(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setAspect)

static bool js_scene_SpotLight_setFrustum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setFrustum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::geometry::Frustum, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setFrustum : Error processing arguments");
        cobj->setFrustum(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setFrustum)

static bool js_scene_SpotLight_setLuminance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setLuminance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setLuminance : Error processing arguments");
        cobj->setLuminance(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setLuminance)

static bool js_scene_SpotLight_setRange(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setRange : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setRange : Error processing arguments");
        cobj->setRange(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setRange)

static bool js_scene_SpotLight_setSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setSize : Error processing arguments");
        cobj->setSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setSize)

static bool js_scene_SpotLight_setSpotAngle(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setSpotAngle : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setSpotAngle : Error processing arguments");
        cobj->setSpotAngle(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setSpotAngle)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_SpotLight_finalize)

static bool js_scene_SpotLight_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::SpotLight *cobj = JSB_ALLOC(cc::scene::SpotLight);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_SpotLight_constructor, __jsb_cc_scene_SpotLight_class, js_cc_scene_SpotLight_finalize)

static bool js_cc_scene_SpotLight_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::SpotLight>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_SpotLight_finalize)

bool js_register_scene_SpotLight(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("SpotLight", obj, __jsb_cc_scene_Light_proto, _SE(js_scene_SpotLight_constructor));

    cls->defineFunction("getLuminance", _SE(js_scene_SpotLight_getLuminance));
    cls->defineFunction("setAspect", _SE(js_scene_SpotLight_setAspect));
    cls->defineFunction("setFrustum", _SE(js_scene_SpotLight_setFrustum));
    cls->defineFunction("setLuminance", _SE(js_scene_SpotLight_setLuminance));
    cls->defineFunction("setRange", _SE(js_scene_SpotLight_setRange));
    cls->defineFunction("setSize", _SE(js_scene_SpotLight_setSize));
    cls->defineFunction("setSpotAngle", _SE(js_scene_SpotLight_setSpotAngle));
    cls->defineFinalizeFunction(_SE(js_cc_scene_SpotLight_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::SpotLight>(cls);

    __jsb_cc_scene_SpotLight_proto = cls->getProto();
    __jsb_cc_scene_SpotLight_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_SphereLight_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_SphereLight_class = nullptr; // NOLINT

static bool js_scene_SphereLight_getLuminance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_getLuminance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getLuminance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_getLuminance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_getLuminance)

static bool js_scene_SphereLight_setLuminance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setLuminance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setLuminance : Error processing arguments");
        cobj->setLuminance(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setLuminance)

static bool js_scene_SphereLight_setPosition(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setPosition : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setPosition : Error processing arguments");
        cobj->setPosition(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setPosition)

static bool js_scene_SphereLight_setRange(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setRange : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setRange : Error processing arguments");
        cobj->setRange(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setRange)

static bool js_scene_SphereLight_setSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setSize : Error processing arguments");
        cobj->setSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setSize)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_SphereLight_finalize)

static bool js_scene_SphereLight_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::SphereLight *cobj = JSB_ALLOC(cc::scene::SphereLight);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_SphereLight_constructor, __jsb_cc_scene_SphereLight_class, js_cc_scene_SphereLight_finalize)

static bool js_cc_scene_SphereLight_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::SphereLight>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_SphereLight_finalize)

bool js_register_scene_SphereLight(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("SphereLight", obj, __jsb_cc_scene_Light_proto, _SE(js_scene_SphereLight_constructor));

    cls->defineFunction("getLuminance", _SE(js_scene_SphereLight_getLuminance));
    cls->defineFunction("setLuminance", _SE(js_scene_SphereLight_setLuminance));
    cls->defineFunction("setPosition", _SE(js_scene_SphereLight_setPosition));
    cls->defineFunction("setRange", _SE(js_scene_SphereLight_setRange));
    cls->defineFunction("setSize", _SE(js_scene_SphereLight_setSize));
    cls->defineFinalizeFunction(_SE(js_cc_scene_SphereLight_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::SphereLight>(cls);

    __jsb_cc_scene_SphereLight_proto = cls->getProto();
    __jsb_cc_scene_SphereLight_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Model_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Model_class = nullptr; // NOLINT

static bool js_scene_Model_attachToScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_attachToScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderScene *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_attachToScene : Error processing arguments");
        cobj->attachToScene(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_attachToScene)

static bool js_scene_Model_createBoundingShape(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_createBoundingShape : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<std::optional<cc::Vec3>, true> arg0 = {};
        HolderType<std::optional<cc::Vec3>, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_createBoundingShape : Error processing arguments");
        cobj->createBoundingShape(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Model_createBoundingShape)

static bool js_scene_Model_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_destroy)

static bool js_scene_Model_detachFromScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_detachFromScene : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->detachFromScene();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_detachFromScene)

static bool js_scene_Model_getCastShadow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getCastShadow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->getCastShadow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getCastShadow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getCastShadow)

static bool js_scene_Model_getInstMatWorldIdx(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstMatWorldIdx : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        int32_t result = cobj->getInstMatWorldIdx();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstMatWorldIdx : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstMatWorldIdx)

static bool js_scene_Model_getInstanceAttributes(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstanceAttributes : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::gfx::Attribute> &result = cobj->getInstanceAttributes();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstanceAttributes : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstanceAttributes)

static bool js_scene_Model_getInstancedAttributeBlock(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstancedAttributeBlock : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::InstancedAttributeBlock *result = cobj->getInstancedAttributeBlock();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstancedAttributeBlock : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstancedAttributeBlock)

static bool js_scene_Model_getInstancedBuffer(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstancedBuffer : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned char *result = cobj->getInstancedBuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstancedBuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstancedBuffer)

static bool js_scene_Model_getInstancedBufferSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstancedBufferSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getInstancedBufferSize();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstancedBufferSize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstancedBufferSize)

static bool js_scene_Model_getLocalData(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getLocalData : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float *result = cobj->getLocalData();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getLocalData : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getLocalData)

static bool js_scene_Model_getMacroPatches(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getMacroPatches : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_getMacroPatches : Error processing arguments");
        std::vector<cc::scene::IMacroPatch> result = cobj->getMacroPatches(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getMacroPatches : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getMacroPatches)

static bool js_scene_Model_getNode(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getNode : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Node *result = cobj->getNode();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getNode : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getNode)

static bool js_scene_Model_getReceiveShadow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getReceiveShadow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->getReceiveShadow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getReceiveShadow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getReceiveShadow)

static bool js_scene_Model_getScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderScene *result = cobj->getScene();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getScene : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getScene)

static bool js_scene_Model_getSubModels(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getSubModels : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::SubModel *> &result = cobj->getSubModels();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getSubModels : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getSubModels)

static bool js_scene_Model_getTransform(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getTransform : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Node *result = cobj->getTransform();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getTransform : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getTransform)

static bool js_scene_Model_getTransformUpdated(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getTransformUpdated : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->getTransformUpdated();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getTransformUpdated : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getTransformUpdated)

static bool js_scene_Model_getUpdateStamp(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getUpdateStamp : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getUpdateStamp();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getUpdateStamp : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getUpdateStamp)

static bool js_scene_Model_getVisFlags(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getVisFlags : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getVisFlags();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getVisFlags : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getVisFlags)

static bool js_scene_Model_initSubModel(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_initSubModel : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 3) {
        HolderType<int, false>                    arg0 = {};
        HolderType<cc::RenderingSubMesh *, false> arg1 = {};
        HolderType<cc::Material *, false>         arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_initSubModel : Error processing arguments");
        cobj->initSubModel(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_scene_Model_initSubModel)

static bool js_scene_Model_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_initialize : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->initialize();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_initialize)

static bool js_scene_Model_isDynamicBatching(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_isDynamicBatching : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isDynamicBatching();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_isDynamicBatching : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_isDynamicBatching)

static bool js_scene_Model_isEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_isEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_isEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_isEnabled)

static bool js_scene_Model_isInited(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_isInited : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isInited();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_isInited : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_isInited)

static bool js_scene_Model_isInstancingEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_isInstancingEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isInstancingEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_isInstancingEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_isInstancingEnabled)

static bool js_scene_Model_onGlobalPipelineStateChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_onGlobalPipelineStateChanged : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->onGlobalPipelineStateChanged();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_onGlobalPipelineStateChanged)

static bool js_scene_Model_onMacroPatchesStateChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_onMacroPatchesStateChanged : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->onMacroPatchesStateChanged();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_onMacroPatchesStateChanged)

static bool js_scene_Model_setBounds(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setBounds : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::geometry::AABB *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setBounds : Error processing arguments");
        cobj->setBounds(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setBounds)

static bool js_scene_Model_setCastShadow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setCastShadow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setCastShadow : Error processing arguments");
        cobj->setCastShadow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setCastShadow)

static bool js_scene_Model_setDynamicBatching(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setDynamicBatching : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setDynamicBatching : Error processing arguments");
        cobj->setDynamicBatching(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setDynamicBatching)

static bool js_scene_Model_setEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setEnabled)

static bool js_scene_Model_setInstMatWorldIdx(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setInstMatWorldIdx : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<int32_t, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setInstMatWorldIdx : Error processing arguments");
        cobj->setInstMatWorldIdx(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setInstMatWorldIdx)

static bool js_scene_Model_setLocalBuffer(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setLocalBuffer : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::Buffer *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setLocalBuffer : Error processing arguments");
        cobj->setLocalBuffer(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setLocalBuffer)

static bool js_scene_Model_setNode(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setNode : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Node *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setNode : Error processing arguments");
        cobj->setNode(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setNode)

static bool js_scene_Model_setReceiveShadow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setReceiveShadow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setReceiveShadow : Error processing arguments");
        cobj->setReceiveShadow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setReceiveShadow)

static bool js_scene_Model_setSubModel(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setSubModel : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false>          arg0 = {};
        HolderType<cc::scene::SubModel *, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setSubModel : Error processing arguments");
        cobj->setSubModel(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setSubModel)

static bool js_scene_Model_setSubModelMaterial(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setSubModelMaterial : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<int, false>            arg0 = {};
        HolderType<cc::Material *, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setSubModelMaterial : Error processing arguments");
        cobj->setSubModelMaterial(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setSubModelMaterial)

static bool js_scene_Model_setSubModelMesh(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setSubModelMesh : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<int, false>                    arg0 = {};
        HolderType<cc::RenderingSubMesh *, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setSubModelMesh : Error processing arguments");
        cobj->setSubModelMesh(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setSubModelMesh)

static bool js_scene_Model_setTransform(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setTransform : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Node *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setTransform : Error processing arguments");
        cobj->setTransform(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setTransform)

static bool js_scene_Model_setVisFlags(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setVisFlags : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setVisFlags : Error processing arguments");
        cobj->setVisFlags(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setVisFlags)

static bool js_scene_Model_updateInstancedAttributes(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateInstancedAttributes : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<std::vector<cc::gfx::Attribute>, true> arg0 = {};
        HolderType<cc::scene::Pass *, false>              arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_updateInstancedAttributes : Error processing arguments");
        cobj->updateInstancedAttributes(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateInstancedAttributes)

static bool js_scene_Model_updateLightingmap(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateLightingmap : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::Texture2D *, false> arg0 = {};
        HolderType<cc::Vec4, true>         arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_updateLightingmap : Error processing arguments");
        cobj->updateLightingmap(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateLightingmap)

static bool js_scene_Model_updateTransform(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateTransform : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_updateTransform : Error processing arguments");
        cobj->updateTransform(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateTransform)

static bool js_scene_Model_updateUBOs(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateUBOs : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_updateUBOs : Error processing arguments");
        cobj->updateUBOs(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateUBOs)

static bool js_scene_Model_updateWorldBound(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateWorldBound : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->updateWorldBound();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateWorldBound)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Model_finalize)

static bool js_scene_Model_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::Model *cobj = JSB_ALLOC(cc::scene::Model);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Model_constructor, __jsb_cc_scene_Model_class, js_cc_scene_Model_finalize)

static bool js_cc_scene_Model_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Model>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Model_finalize)

bool js_register_scene_Model(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Model", obj, nullptr, _SE(js_scene_Model_constructor));

    cls->defineFunction("attachToScene", _SE(js_scene_Model_attachToScene));
    cls->defineFunction("createBoundingShape", _SE(js_scene_Model_createBoundingShape));
    cls->defineFunction("destroy", _SE(js_scene_Model_destroy));
    cls->defineFunction("detachFromScene", _SE(js_scene_Model_detachFromScene));
    cls->defineFunction("getCastShadow", _SE(js_scene_Model_getCastShadow));
    cls->defineFunction("getInstMatWorldIdx", _SE(js_scene_Model_getInstMatWorldIdx));
    cls->defineFunction("getInstanceAttributes", _SE(js_scene_Model_getInstanceAttributes));
    cls->defineFunction("getInstancedAttributeBlock", _SE(js_scene_Model_getInstancedAttributeBlock));
    cls->defineFunction("getInstancedBuffer", _SE(js_scene_Model_getInstancedBuffer));
    cls->defineFunction("getInstancedBufferSize", _SE(js_scene_Model_getInstancedBufferSize));
    cls->defineFunction("getLocalData", _SE(js_scene_Model_getLocalData));
    cls->defineFunction("getMacroPatches", _SE(js_scene_Model_getMacroPatches));
    cls->defineFunction("getNode", _SE(js_scene_Model_getNode));
    cls->defineFunction("getReceiveShadow", _SE(js_scene_Model_getReceiveShadow));
    cls->defineFunction("getScene", _SE(js_scene_Model_getScene));
    cls->defineFunction("getSubModels", _SE(js_scene_Model_getSubModels));
    cls->defineFunction("getTransform", _SE(js_scene_Model_getTransform));
    cls->defineFunction("getTransformUpdated", _SE(js_scene_Model_getTransformUpdated));
    cls->defineFunction("getUpdateStamp", _SE(js_scene_Model_getUpdateStamp));
    cls->defineFunction("getVisFlags", _SE(js_scene_Model_getVisFlags));
    cls->defineFunction("initSubModel", _SE(js_scene_Model_initSubModel));
    cls->defineFunction("initialize", _SE(js_scene_Model_initialize));
    cls->defineFunction("isDynamicBatching", _SE(js_scene_Model_isDynamicBatching));
    cls->defineFunction("isEnabled", _SE(js_scene_Model_isEnabled));
    cls->defineFunction("isInited", _SE(js_scene_Model_isInited));
    cls->defineFunction("isInstancingEnabled", _SE(js_scene_Model_isInstancingEnabled));
    cls->defineFunction("onGlobalPipelineStateChanged", _SE(js_scene_Model_onGlobalPipelineStateChanged));
    cls->defineFunction("onMacroPatchesStateChanged", _SE(js_scene_Model_onMacroPatchesStateChanged));
    cls->defineFunction("setBounds", _SE(js_scene_Model_setBounds));
    cls->defineFunction("setCastShadow", _SE(js_scene_Model_setCastShadow));
    cls->defineFunction("setDynamicBatching", _SE(js_scene_Model_setDynamicBatching));
    cls->defineFunction("setEnabled", _SE(js_scene_Model_setEnabled));
    cls->defineFunction("setInstMatWorldIdx", _SE(js_scene_Model_setInstMatWorldIdx));
    cls->defineFunction("setLocalBuffer", _SE(js_scene_Model_setLocalBuffer));
    cls->defineFunction("setNode", _SE(js_scene_Model_setNode));
    cls->defineFunction("setReceiveShadow", _SE(js_scene_Model_setReceiveShadow));
    cls->defineFunction("setSubModel", _SE(js_scene_Model_setSubModel));
    cls->defineFunction("setSubModelMaterial", _SE(js_scene_Model_setSubModelMaterial));
    cls->defineFunction("setSubModelMesh", _SE(js_scene_Model_setSubModelMesh));
    cls->defineFunction("setTransform", _SE(js_scene_Model_setTransform));
    cls->defineFunction("setVisFlags", _SE(js_scene_Model_setVisFlags));
    cls->defineFunction("updateInstancedAttributes", _SE(js_scene_Model_updateInstancedAttributes));
    cls->defineFunction("updateLightingmap", _SE(js_scene_Model_updateLightingmap));
    cls->defineFunction("updateTransform", _SE(js_scene_Model_updateTransform));
    cls->defineFunction("updateUBOs", _SE(js_scene_Model_updateUBOs));
    cls->defineFunction("updateWorldBound", _SE(js_scene_Model_updateWorldBound));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Model_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Model>(cls);

    __jsb_cc_scene_Model_proto = cls->getProto();
    __jsb_cc_scene_Model_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Fog_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Fog_class = nullptr; // NOLINT

static bool js_scene_Fog_activate(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_activate : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->activate();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_activate)

static bool js_scene_Fog_getColorArray(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getColorArray : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::array<float, 4> &result = cobj->getColorArray();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getColorArray : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getColorArray)

static bool js_scene_Fog_getFogAtten(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogAtten : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFogAtten();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogAtten : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogAtten)

static bool js_scene_Fog_getFogColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Color &result = cobj->getFogColor();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogColor : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogColor)

static bool js_scene_Fog_getFogDensity(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogDensity : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFogDensity();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogDensity : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogDensity)

static bool js_scene_Fog_getFogEnd(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogEnd : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFogEnd();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogEnd : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogEnd)

static bool js_scene_Fog_getFogRange(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogRange : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFogRange();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogRange : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogRange)

static bool js_scene_Fog_getFogStart(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogStart : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFogStart();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogStart : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogStart)

static bool js_scene_Fog_getFogTop(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getFogTop : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFogTop();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getFogTop : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getFogTop)

static bool js_scene_Fog_getType(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_getType : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getType());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_getType : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_getType)

static bool js_scene_Fog_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::FogInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_initialize)

static bool js_scene_Fog_isEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_isEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Fog_isEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_isEnabled)

static bool js_scene_Fog_setEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setEnabled)

static bool js_scene_Fog_setFogAtten(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setFogAtten : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setFogAtten : Error processing arguments");
        cobj->setFogAtten(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setFogAtten)

static bool js_scene_Fog_setFogColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setFogColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setFogColor : Error processing arguments");
        cobj->setFogColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setFogColor)

static bool js_scene_Fog_setFogDensity(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setFogDensity : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setFogDensity : Error processing arguments");
        cobj->setFogDensity(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setFogDensity)

static bool js_scene_Fog_setFogEnd(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setFogEnd : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setFogEnd : Error processing arguments");
        cobj->setFogEnd(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setFogEnd)

static bool js_scene_Fog_setFogStart(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setFogStart : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setFogStart : Error processing arguments");
        cobj->setFogStart(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setFogStart)

static bool js_scene_Fog_setFogTop(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setFogTop : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setFogTop : Error processing arguments");
        cobj->setFogTop(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setFogTop)

static bool js_scene_Fog_setType(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setType : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::FogType, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setType : Error processing arguments");
        cobj->setType(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setType)

static bool js_scene_Fog_setfogRange(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Fog_setfogRange : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Fog_setfogRange : Error processing arguments");
        cobj->setfogRange(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Fog_setfogRange)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Fog_finalize)

static bool js_scene_Fog_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::Fog *cobj = JSB_ALLOC(cc::scene::Fog);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Fog_constructor, __jsb_cc_scene_Fog_class, js_cc_scene_Fog_finalize)

static bool js_cc_scene_Fog_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Fog>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Fog>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Fog_finalize)

bool js_register_scene_Fog(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Fog", obj, nullptr, _SE(js_scene_Fog_constructor));

    cls->defineFunction("activate", _SE(js_scene_Fog_activate));
    cls->defineFunction("getColorArray", _SE(js_scene_Fog_getColorArray));
    cls->defineFunction("getFogAtten", _SE(js_scene_Fog_getFogAtten));
    cls->defineFunction("getFogColor", _SE(js_scene_Fog_getFogColor));
    cls->defineFunction("getFogDensity", _SE(js_scene_Fog_getFogDensity));
    cls->defineFunction("getFogEnd", _SE(js_scene_Fog_getFogEnd));
    cls->defineFunction("getFogRange", _SE(js_scene_Fog_getFogRange));
    cls->defineFunction("getFogStart", _SE(js_scene_Fog_getFogStart));
    cls->defineFunction("getFogTop", _SE(js_scene_Fog_getFogTop));
    cls->defineFunction("getType", _SE(js_scene_Fog_getType));
    cls->defineFunction("initialize", _SE(js_scene_Fog_initialize));
    cls->defineFunction("isEnabled", _SE(js_scene_Fog_isEnabled));
    cls->defineFunction("setEnabled", _SE(js_scene_Fog_setEnabled));
    cls->defineFunction("setFogAtten", _SE(js_scene_Fog_setFogAtten));
    cls->defineFunction("setFogColor", _SE(js_scene_Fog_setFogColor));
    cls->defineFunction("setFogDensity", _SE(js_scene_Fog_setFogDensity));
    cls->defineFunction("setFogEnd", _SE(js_scene_Fog_setFogEnd));
    cls->defineFunction("setFogStart", _SE(js_scene_Fog_setFogStart));
    cls->defineFunction("setFogTop", _SE(js_scene_Fog_setFogTop));
    cls->defineFunction("setType", _SE(js_scene_Fog_setType));
    cls->defineFunction("setfogRange", _SE(js_scene_Fog_setfogRange));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Fog_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Fog>(cls);

    __jsb_cc_scene_Fog_proto = cls->getProto();
    __jsb_cc_scene_Fog_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_IPassStates_proto = nullptr; // NOLINT
se::Class * __jsb_cc_IPassStates_class = nullptr; // NOLINT

static bool js_scene_IPassStates_get_priority(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_priority : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->priority, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->priority, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_priority)

static bool js_scene_IPassStates_set_priority(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_priority : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->priority, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_priority : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_priority)

static bool js_scene_IPassStates_get_primitive(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_primitive : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->primitive, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->primitive, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_primitive)

static bool js_scene_IPassStates_set_primitive(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_primitive : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->primitive, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_primitive : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_primitive)

static bool js_scene_IPassStates_get_stage(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_stage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->stage, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stage, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_stage)

static bool js_scene_IPassStates_set_stage(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_stage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stage, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_stage : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_stage)

static bool js_scene_IPassStates_get_rasterizerState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_rasterizerState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->rasterizerState, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->rasterizerState, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_rasterizerState)

static bool js_scene_IPassStates_set_rasterizerState(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_rasterizerState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->rasterizerState, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_rasterizerState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_rasterizerState)

static bool js_scene_IPassStates_get_depthStencilState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_depthStencilState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->depthStencilState, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->depthStencilState, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_depthStencilState)

static bool js_scene_IPassStates_set_depthStencilState(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_depthStencilState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStencilState, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_depthStencilState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_depthStencilState)

static bool js_scene_IPassStates_get_blendState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_blendState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->blendState, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->blendState, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_blendState)

static bool js_scene_IPassStates_set_blendState(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_blendState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendState, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_blendState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_blendState)

static bool js_scene_IPassStates_get_dynamicStates(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_dynamicStates : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->dynamicStates, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->dynamicStates, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_dynamicStates)

static bool js_scene_IPassStates_set_dynamicStates(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_dynamicStates : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->dynamicStates, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_dynamicStates : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_dynamicStates)

static bool js_scene_IPassStates_get_phase(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_get_phase : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->phase, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->phase, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassStates_get_phase)

static bool js_scene_IPassStates_set_phase(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassStates_set_phase : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->phase, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassStates_set_phase : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassStates_set_phase)

template <>
bool sevalue_to_native(const se::Value &from, cc::IPassStates *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::IPassStates *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    json->getProperty("priority", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->priority), ctx);
    }
    json->getProperty("primitive", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->primitive), ctx);
    }
    json->getProperty("stage", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stage), ctx);
    }
    json->getProperty("rasterizerState", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->rasterizerState), ctx);
    }
    json->getProperty("depthStencilState", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStencilState), ctx);
    }
    json->getProperty("blendState", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendState), ctx);
    }
    json->getProperty("dynamicStates", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->dynamicStates), ctx);
    }
    json->getProperty("phase", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->phase), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IPassStates_finalize)

static bool js_scene_IPassStates_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::IPassStates *cobj = JSB_ALLOC(cc::IPassStates);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if (argc == 1 && args[0].isObject()) {
        se::Object *json = args[0].toObject();
        se::Value   field;

        cc::IPassStates *cobj = JSB_ALLOC(cc::IPassStates);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if (!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IPassStates *cobj = JSB_ALLOC(cc::IPassStates);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->priority), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->primitive), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->stage), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->rasterizerState), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->depthStencilState), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->blendState), nullptr);
    }
    if (argc > 6 && !args[6].isUndefined()) {
        ok &= sevalue_to_native(args[6], &(cobj->dynamicStates), nullptr);
    }
    if (argc > 7 && !args[7].isUndefined()) {
        ok &= sevalue_to_native(args[7], &(cobj->phase), nullptr);
    }

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_IPassStates_constructor, __jsb_cc_IPassStates_class, js_cc_IPassStates_finalize)

static bool js_cc_IPassStates_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IPassStates>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::IPassStates>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IPassStates_finalize)

bool js_register_scene_IPassStates(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("IPassStates", obj, nullptr, _SE(js_scene_IPassStates_constructor));

    cls->defineProperty("priority", _SE(js_scene_IPassStates_get_priority), _SE(js_scene_IPassStates_set_priority));
    cls->defineProperty("primitive", _SE(js_scene_IPassStates_get_primitive), _SE(js_scene_IPassStates_set_primitive));
    cls->defineProperty("stage", _SE(js_scene_IPassStates_get_stage), _SE(js_scene_IPassStates_set_stage));
    cls->defineProperty("rasterizerState", _SE(js_scene_IPassStates_get_rasterizerState), _SE(js_scene_IPassStates_set_rasterizerState));
    cls->defineProperty("depthStencilState", _SE(js_scene_IPassStates_get_depthStencilState), _SE(js_scene_IPassStates_set_depthStencilState));
    cls->defineProperty("blendState", _SE(js_scene_IPassStates_get_blendState), _SE(js_scene_IPassStates_set_blendState));
    cls->defineProperty("dynamicStates", _SE(js_scene_IPassStates_get_dynamicStates), _SE(js_scene_IPassStates_set_dynamicStates));
    cls->defineProperty("phase", _SE(js_scene_IPassStates_get_phase), _SE(js_scene_IPassStates_set_phase));
    cls->defineFinalizeFunction(_SE(js_cc_IPassStates_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IPassStates>(cls);

    __jsb_cc_IPassStates_proto = cls->getProto();
    __jsb_cc_IPassStates_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_IPassInfo_proto = nullptr; // NOLINT
se::Class * __jsb_cc_IPassInfo_class = nullptr; // NOLINT

static bool js_scene_IPassInfo_get_program(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_get_program : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->program, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->program, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfo_get_program)

static bool js_scene_IPassInfo_set_program(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_set_program : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->program, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfo_set_program : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfo_set_program)

static bool js_scene_IPassInfo_get_embeddedMacros(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_get_embeddedMacros : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->embeddedMacros, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->embeddedMacros, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfo_get_embeddedMacros)

static bool js_scene_IPassInfo_set_embeddedMacros(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_set_embeddedMacros : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->embeddedMacros, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfo_set_embeddedMacros : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfo_set_embeddedMacros)

static bool js_scene_IPassInfo_get_propertyIndex(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_get_propertyIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->propertyIndex, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->propertyIndex, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfo_get_propertyIndex)

static bool js_scene_IPassInfo_set_propertyIndex(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_set_propertyIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->propertyIndex, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfo_set_propertyIndex : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfo_set_propertyIndex)

static bool js_scene_IPassInfo_get_switch_(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_get_switch_ : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->switch_, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->switch_, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfo_get_switch_)

static bool js_scene_IPassInfo_set_switch_(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_set_switch_ : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->switch_, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfo_set_switch_ : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfo_set_switch_)

static bool js_scene_IPassInfo_get_properties(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_get_properties : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->properties, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->properties, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfo_get_properties)

static bool js_scene_IPassInfo_set_properties(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfo_set_properties : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->properties, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfo_set_properties : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfo_set_properties)

template <>
bool sevalue_to_native(const se::Value &from, cc::IPassInfo *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::IPassInfo *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    json->getProperty("program", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->program), ctx);
    }
    json->getProperty("embeddedMacros", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->embeddedMacros), ctx);
    }
    json->getProperty("propertyIndex", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->propertyIndex), ctx);
    }
    json->getProperty("switch_", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->switch_), ctx);
    }
    json->getProperty("properties", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->properties), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IPassInfo_finalize)

static bool js_scene_IPassInfo_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::IPassInfo *cobj = JSB_ALLOC(cc::IPassInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if (argc == 1 && args[0].isObject()) {
        se::Object *json = args[0].toObject();
        se::Value   field;

        cc::IPassInfo *cobj = JSB_ALLOC(cc::IPassInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if (!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IPassInfo *cobj = JSB_ALLOC(cc::IPassInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->program), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->embeddedMacros), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->propertyIndex), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->switch_), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->properties), nullptr);
    }

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_IPassInfo_constructor, __jsb_cc_IPassInfo_class, js_cc_IPassInfo_finalize)

static bool js_cc_IPassInfo_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IPassInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::IPassInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IPassInfo_finalize)

bool js_register_scene_IPassInfo(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("IPassInfo", obj, __jsb_cc_IPassStates_proto, _SE(js_scene_IPassInfo_constructor));

    cls->defineProperty("program", _SE(js_scene_IPassInfo_get_program), _SE(js_scene_IPassInfo_set_program));
    cls->defineProperty("embeddedMacros", _SE(js_scene_IPassInfo_get_embeddedMacros), _SE(js_scene_IPassInfo_set_embeddedMacros));
    cls->defineProperty("propertyIndex", _SE(js_scene_IPassInfo_get_propertyIndex), _SE(js_scene_IPassInfo_set_propertyIndex));
    cls->defineProperty("switch_", _SE(js_scene_IPassInfo_get_switch_), _SE(js_scene_IPassInfo_set_switch_));
    cls->defineProperty("properties", _SE(js_scene_IPassInfo_get_properties), _SE(js_scene_IPassInfo_set_properties));
    cls->defineFinalizeFunction(_SE(js_cc_IPassInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IPassInfo>(cls);

    __jsb_cc_IPassInfo_proto = cls->getProto();
    __jsb_cc_IPassInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_IPassInfoFull_proto = nullptr; // NOLINT
se::Class * __jsb_cc_IPassInfoFull_class = nullptr; // NOLINT

static bool js_scene_IPassInfoFull_get_passIndex(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfoFull_get_passIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->passIndex, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->passIndex, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfoFull_get_passIndex)

static bool js_scene_IPassInfoFull_set_passIndex(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfoFull_set_passIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->passIndex, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfoFull_set_passIndex : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfoFull_set_passIndex)

static bool js_scene_IPassInfoFull_get_defines(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfoFull_get_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->defines, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->defines, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfoFull_get_defines)

static bool js_scene_IPassInfoFull_set_defines(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfoFull_set_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->defines, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfoFull_set_defines : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfoFull_set_defines)

static bool js_scene_IPassInfoFull_get_stateOverrides(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfoFull_get_stateOverrides : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->stateOverrides, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stateOverrides, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IPassInfoFull_get_stateOverrides)

static bool js_scene_IPassInfoFull_set_stateOverrides(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IPassInfoFull_set_stateOverrides : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stateOverrides, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IPassInfoFull_set_stateOverrides : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IPassInfoFull_set_stateOverrides)

template <>
bool sevalue_to_native(const se::Value &from, cc::IPassInfoFull *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::IPassInfoFull *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    json->getProperty("passIndex", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->passIndex), ctx);
    }
    json->getProperty("defines", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->defines), ctx);
    }
    json->getProperty("stateOverrides", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stateOverrides), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IPassInfoFull_finalize)

static bool js_scene_IPassInfoFull_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::IPassInfoFull *cobj = JSB_ALLOC(cc::IPassInfoFull);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if (argc == 1 && args[0].isObject()) {
        se::Object *json = args[0].toObject();
        se::Value   field;

        cc::IPassInfoFull *cobj = JSB_ALLOC(cc::IPassInfoFull);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if (!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IPassInfoFull *cobj = JSB_ALLOC(cc::IPassInfoFull);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->passIndex), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->defines), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->stateOverrides), nullptr);
    }

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_IPassInfoFull_constructor, __jsb_cc_IPassInfoFull_class, js_cc_IPassInfoFull_finalize)

static bool js_cc_IPassInfoFull_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IPassInfoFull>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::IPassInfoFull>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IPassInfoFull_finalize)

bool js_register_scene_IPassInfoFull(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("IPassInfoFull", obj, __jsb_cc_IPassInfo_proto, _SE(js_scene_IPassInfoFull_constructor));

    cls->defineProperty("passIndex", _SE(js_scene_IPassInfoFull_get_passIndex), _SE(js_scene_IPassInfoFull_set_passIndex));
    cls->defineProperty("defines", _SE(js_scene_IPassInfoFull_get_defines), _SE(js_scene_IPassInfoFull_set_defines));
    cls->defineProperty("stateOverrides", _SE(js_scene_IPassInfoFull_get_stateOverrides), _SE(js_scene_IPassInfoFull_set_stateOverrides));
    cls->defineFinalizeFunction(_SE(js_cc_IPassInfoFull_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IPassInfoFull>(cls);

    __jsb_cc_IPassInfoFull_proto = cls->getProto();
    __jsb_cc_IPassInfoFull_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_ShadowInfo_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_ShadowInfo_class = nullptr; // NOLINT

static bool js_scene_ShadowInfo_get_shadowColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_shadowColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->shadowColor, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->shadowColor, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_shadowColor)

static bool js_scene_ShadowInfo_set_shadowColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_shadowColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->shadowColor, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_shadowColor : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_shadowColor)

static bool js_scene_ShadowInfo_get_enabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_enabled : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->enabled, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->enabled, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_enabled)

static bool js_scene_ShadowInfo_set_enabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_enabled : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->enabled, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_enabled : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_enabled)

static bool js_scene_ShadowInfo_get_normal(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_normal : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->normal, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->normal, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_normal)

static bool js_scene_ShadowInfo_set_normal(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_normal : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->normal, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_normal : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_normal)

static bool js_scene_ShadowInfo_get_distance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_distance : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->distance, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->distance, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_distance)

static bool js_scene_ShadowInfo_set_distance(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_distance : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->distance, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_distance : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_distance)

static bool js_scene_ShadowInfo_get_autoAdapt(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_autoAdapt : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->autoAdapt, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->autoAdapt, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_autoAdapt)

static bool js_scene_ShadowInfo_set_autoAdapt(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_autoAdapt : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->autoAdapt, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_autoAdapt : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_autoAdapt)

static bool js_scene_ShadowInfo_get_bias(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_bias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->bias, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->bias, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_bias)

static bool js_scene_ShadowInfo_set_bias(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_bias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->bias, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_bias : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_bias)

static bool js_scene_ShadowInfo_get_normalBias(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_normalBias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->normalBias, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->normalBias, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_normalBias)

static bool js_scene_ShadowInfo_set_normalBias(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_normalBias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->normalBias, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_normalBias : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_normalBias)

static bool js_scene_ShadowInfo_get_near(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_near : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->near, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->near, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_near)

static bool js_scene_ShadowInfo_set_near(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_near : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->near, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_near : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_near)

static bool js_scene_ShadowInfo_get_far(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_far : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->far, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->far, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_far)

static bool js_scene_ShadowInfo_set_far(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_far : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->far, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_far : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_far)

static bool js_scene_ShadowInfo_get_orthoSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_orthoSize : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->orthoSize, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->orthoSize, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_orthoSize)

static bool js_scene_ShadowInfo_set_orthoSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_orthoSize : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->orthoSize, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_orthoSize : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_orthoSize)

static bool js_scene_ShadowInfo_get_maxReceived(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_maxReceived : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->maxReceived, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->maxReceived, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_maxReceived)

static bool js_scene_ShadowInfo_set_maxReceived(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_maxReceived : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->maxReceived, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_maxReceived : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_maxReceived)

static bool js_scene_ShadowInfo_get_saturation(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_saturation : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->saturation, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->saturation, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_saturation)

static bool js_scene_ShadowInfo_set_saturation(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_saturation : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->saturation, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_saturation : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_saturation)

static bool js_scene_ShadowInfo_get_size(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_size : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->size, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->size, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_size)

static bool js_scene_ShadowInfo_set_size(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_size : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->size, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_size : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_size)

static bool js_scene_ShadowInfo_get_pcf(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_pcf : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->pcf, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->pcf, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_pcf)

static bool js_scene_ShadowInfo_set_pcf(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_pcf : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->pcf, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_pcf : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_pcf)

static bool js_scene_ShadowInfo_get_type(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->type, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->type, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_ShadowInfo_get_type)

static bool js_scene_ShadowInfo_set_type(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_ShadowInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_ShadowInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_ShadowInfo_set_type)

template <>
bool sevalue_to_native(const se::Value &from, cc::scene::ShadowInfo *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::scene::ShadowInfo *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    json->getProperty("shadowColor", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->shadowColor), ctx);
    }
    json->getProperty("enabled", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->enabled), ctx);
    }
    json->getProperty("normal", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->normal), ctx);
    }
    json->getProperty("distance", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->distance), ctx);
    }
    json->getProperty("autoAdapt", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->autoAdapt), ctx);
    }
    json->getProperty("bias", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->bias), ctx);
    }
    json->getProperty("normalBias", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->normalBias), ctx);
    }
    json->getProperty("near", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->near), ctx);
    }
    json->getProperty("far", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->far), ctx);
    }
    json->getProperty("orthoSize", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->orthoSize), ctx);
    }
    json->getProperty("maxReceived", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->maxReceived), ctx);
    }
    json->getProperty("saturation", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->saturation), ctx);
    }
    json->getProperty("size", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->size), ctx);
    }
    json->getProperty("pcf", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->pcf), ctx);
    }
    json->getProperty("type", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_ShadowInfo_finalize)

static bool js_scene_ShadowInfo_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::scene::ShadowInfo *cobj = JSB_ALLOC(cc::scene::ShadowInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if (argc == 1 && args[0].isObject()) {
        se::Object *json = args[0].toObject();
        se::Value   field;

        cc::scene::ShadowInfo *cobj = JSB_ALLOC(cc::scene::ShadowInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if (!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::scene::ShadowInfo *cobj = JSB_ALLOC(cc::scene::ShadowInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->shadowColor), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->enabled), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->normal), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->distance), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->autoAdapt), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->bias), nullptr);
    }
    if (argc > 6 && !args[6].isUndefined()) {
        ok &= sevalue_to_native(args[6], &(cobj->normalBias), nullptr);
    }
    if (argc > 7 && !args[7].isUndefined()) {
        ok &= sevalue_to_native(args[7], &(cobj->near), nullptr);
    }
    if (argc > 8 && !args[8].isUndefined()) {
        ok &= sevalue_to_native(args[8], &(cobj->far), nullptr);
    }
    if (argc > 9 && !args[9].isUndefined()) {
        ok &= sevalue_to_native(args[9], &(cobj->orthoSize), nullptr);
    }
    if (argc > 10 && !args[10].isUndefined()) {
        ok &= sevalue_to_native(args[10], &(cobj->maxReceived), nullptr);
    }
    if (argc > 11 && !args[11].isUndefined()) {
        ok &= sevalue_to_native(args[11], &(cobj->saturation), nullptr);
    }
    if (argc > 12 && !args[12].isUndefined()) {
        ok &= sevalue_to_native(args[12], &(cobj->size), nullptr);
    }
    if (argc > 13 && !args[13].isUndefined()) {
        ok &= sevalue_to_native(args[13], &(cobj->pcf), nullptr);
    }
    if (argc > 14 && !args[14].isUndefined()) {
        ok &= sevalue_to_native(args[14], &(cobj->type), nullptr);
    }

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_ShadowInfo_constructor, __jsb_cc_scene_ShadowInfo_class, js_cc_scene_ShadowInfo_finalize)

static bool js_cc_scene_ShadowInfo_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::ShadowInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::ShadowInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_ShadowInfo_finalize)

bool js_register_scene_ShadowInfo(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("ShadowInfo", obj, nullptr, _SE(js_scene_ShadowInfo_constructor));

    cls->defineProperty("shadowColor", _SE(js_scene_ShadowInfo_get_shadowColor), _SE(js_scene_ShadowInfo_set_shadowColor));
    cls->defineProperty("enabled", _SE(js_scene_ShadowInfo_get_enabled), _SE(js_scene_ShadowInfo_set_enabled));
    cls->defineProperty("normal", _SE(js_scene_ShadowInfo_get_normal), _SE(js_scene_ShadowInfo_set_normal));
    cls->defineProperty("distance", _SE(js_scene_ShadowInfo_get_distance), _SE(js_scene_ShadowInfo_set_distance));
    cls->defineProperty("autoAdapt", _SE(js_scene_ShadowInfo_get_autoAdapt), _SE(js_scene_ShadowInfo_set_autoAdapt));
    cls->defineProperty("bias", _SE(js_scene_ShadowInfo_get_bias), _SE(js_scene_ShadowInfo_set_bias));
    cls->defineProperty("normalBias", _SE(js_scene_ShadowInfo_get_normalBias), _SE(js_scene_ShadowInfo_set_normalBias));
    cls->defineProperty("near", _SE(js_scene_ShadowInfo_get_near), _SE(js_scene_ShadowInfo_set_near));
    cls->defineProperty("far", _SE(js_scene_ShadowInfo_get_far), _SE(js_scene_ShadowInfo_set_far));
    cls->defineProperty("orthoSize", _SE(js_scene_ShadowInfo_get_orthoSize), _SE(js_scene_ShadowInfo_set_orthoSize));
    cls->defineProperty("maxReceived", _SE(js_scene_ShadowInfo_get_maxReceived), _SE(js_scene_ShadowInfo_set_maxReceived));
    cls->defineProperty("saturation", _SE(js_scene_ShadowInfo_get_saturation), _SE(js_scene_ShadowInfo_set_saturation));
    cls->defineProperty("size", _SE(js_scene_ShadowInfo_get_size), _SE(js_scene_ShadowInfo_set_size));
    cls->defineProperty("pcf", _SE(js_scene_ShadowInfo_get_pcf), _SE(js_scene_ShadowInfo_set_pcf));
    cls->defineProperty("type", _SE(js_scene_ShadowInfo_get_type), _SE(js_scene_ShadowInfo_set_type));
    cls->defineFinalizeFunction(_SE(js_cc_scene_ShadowInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::ShadowInfo>(cls);

    __jsb_cc_scene_ShadowInfo_proto = cls->getProto();
    __jsb_cc_scene_ShadowInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Shadow_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Shadow_class = nullptr; // NOLINT

static bool js_scene_Shadow_activate(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_activate : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->activate();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_activate)

static bool js_scene_Shadow_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_destroy)

static bool js_scene_Shadow_getBias(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getBias : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getBias();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getBias : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getBias)

static bool js_scene_Shadow_getDistance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getDistance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getDistance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getDistance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getDistance)

static bool js_scene_Shadow_getFar(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getFar : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFar();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getFar : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getFar)

static bool js_scene_Shadow_getInstancingMaterial(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getInstancingMaterial : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Material *result = cobj->getInstancingMaterial();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getInstancingMaterial : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getInstancingMaterial)

static bool js_scene_Shadow_getMatLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getMatLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getMatLight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getMatLight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getMatLight)

static bool js_scene_Shadow_getMaterial(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getMaterial : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Material *result = cobj->getMaterial();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getMaterial : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getMaterial)

static bool js_scene_Shadow_getNear(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getNear : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getNear();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getNear : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getNear)

static bool js_scene_Shadow_getNormal(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getNormal : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getNormal();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getNormal : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getNormal)

static bool js_scene_Shadow_getNormalBias(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getNormalBias : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getNormalBias();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getNormalBias : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getNormalBias)

static bool js_scene_Shadow_getOrthoSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getOrthoSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getOrthoSize();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getOrthoSize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getOrthoSize)

static bool js_scene_Shadow_getPcf(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getPcf : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getPcf());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getPcf : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getPcf)

static bool js_scene_Shadow_getPlanarInstanceShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getPlanarInstanceShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::scene::IMacroPatch>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getPlanarInstanceShader : Error processing arguments");
        cc::gfx::Shader *result = cobj->getPlanarInstanceShader(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getPlanarInstanceShader : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getPlanarInstanceShader)

static bool js_scene_Shadow_getPlanarShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getPlanarShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::scene::IMacroPatch>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getPlanarShader : Error processing arguments");
        cc::gfx::Shader *result = cobj->getPlanarShader(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getPlanarShader : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getPlanarShader)

static bool js_scene_Shadow_getSaturation(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getSaturation : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getSaturation();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getSaturation : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getSaturation)

static bool js_scene_Shadow_getShadowColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getShadowColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Color &result = cobj->getShadowColor();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getShadowColor : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getShadowColor)

static bool js_scene_Shadow_getShadowColor4f(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getShadowColor4f : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::array<float, 4> &result = cobj->getShadowColor4f();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getShadowColor4f : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getShadowColor4f)

static bool js_scene_Shadow_getSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec2 &result = cobj->getSize();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getSize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getSize)

static bool js_scene_Shadow_getType(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_getType : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getType());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_getType : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_getType)

static bool js_scene_Shadow_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::ShadowInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_initialize)

static bool js_scene_Shadow_isAutoAdapt(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_isAutoAdapt : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isAutoAdapt();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_isAutoAdapt : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_isAutoAdapt)

static bool js_scene_Shadow_isEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_isEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_isEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_isEnabled)

static bool js_scene_Shadow_isShadowMapDirty(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_isShadowMapDirty : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isShadowMapDirty();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_isShadowMapDirty : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_isShadowMapDirty)

static bool js_scene_Shadow_setAutoAdapt(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setAutoAdapt : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setAutoAdapt : Error processing arguments");
        cobj->setAutoAdapt(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setAutoAdapt)

static bool js_scene_Shadow_setBias(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setBias : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setBias : Error processing arguments");
        cobj->setBias(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setBias)

static bool js_scene_Shadow_setDistance(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setDistance : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setDistance : Error processing arguments");
        cobj->setDistance(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setDistance)

static bool js_scene_Shadow_setEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setEnabled)

static bool js_scene_Shadow_setFar(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setFar : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setFar : Error processing arguments");
        cobj->setFar(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setFar)

static bool js_scene_Shadow_setNear(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setNear : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setNear : Error processing arguments");
        cobj->setNear(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setNear)

static bool js_scene_Shadow_setNormal(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setNormal : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setNormal : Error processing arguments");
        cobj->setNormal(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setNormal)

static bool js_scene_Shadow_setNormalBias(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setNormalBias : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setNormalBias : Error processing arguments");
        cobj->setNormalBias(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setNormalBias)

static bool js_scene_Shadow_setOrthoSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setOrthoSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setOrthoSize : Error processing arguments");
        cobj->setOrthoSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setOrthoSize)

static bool js_scene_Shadow_setPcf(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setPcf : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::PCFType, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setPcf : Error processing arguments");
        cobj->setPcf(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setPcf)

static bool js_scene_Shadow_setSaturation(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setSaturation : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setSaturation : Error processing arguments");
        cobj->setSaturation(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setSaturation)

static bool js_scene_Shadow_setShadowColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setShadowColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setShadowColor : Error processing arguments");
        cobj->setShadowColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setShadowColor)

static bool js_scene_Shadow_setShadowMapDirty(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setShadowMapDirty : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setShadowMapDirty : Error processing arguments");
        cobj->setShadowMapDirty(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setShadowMapDirty)

static bool js_scene_Shadow_setSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec2, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setSize : Error processing arguments");
        cobj->setSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setSize)

static bool js_scene_Shadow_setType(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Shadow_setType : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::ShadowType, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Shadow_setType : Error processing arguments");
        cobj->setType(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Shadow_setType)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Shadow_finalize)

static bool js_scene_Shadow_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::Shadow *cobj = JSB_ALLOC(cc::scene::Shadow);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Shadow_constructor, __jsb_cc_scene_Shadow_class, js_cc_scene_Shadow_finalize)

static bool js_cc_scene_Shadow_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Shadow>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Shadow>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Shadow_finalize)

bool js_register_scene_Shadow(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Shadow", obj, nullptr, _SE(js_scene_Shadow_constructor));

    cls->defineFunction("activate", _SE(js_scene_Shadow_activate));
    cls->defineFunction("destroy", _SE(js_scene_Shadow_destroy));
    cls->defineFunction("getBias", _SE(js_scene_Shadow_getBias));
    cls->defineFunction("getDistance", _SE(js_scene_Shadow_getDistance));
    cls->defineFunction("getFar", _SE(js_scene_Shadow_getFar));
    cls->defineFunction("getInstancingMaterial", _SE(js_scene_Shadow_getInstancingMaterial));
    cls->defineFunction("getMatLight", _SE(js_scene_Shadow_getMatLight));
    cls->defineFunction("getMaterial", _SE(js_scene_Shadow_getMaterial));
    cls->defineFunction("getNear", _SE(js_scene_Shadow_getNear));
    cls->defineFunction("getNormal", _SE(js_scene_Shadow_getNormal));
    cls->defineFunction("getNormalBias", _SE(js_scene_Shadow_getNormalBias));
    cls->defineFunction("getOrthoSize", _SE(js_scene_Shadow_getOrthoSize));
    cls->defineFunction("getPcf", _SE(js_scene_Shadow_getPcf));
    cls->defineFunction("getPlanarInstanceShader", _SE(js_scene_Shadow_getPlanarInstanceShader));
    cls->defineFunction("getPlanarShader", _SE(js_scene_Shadow_getPlanarShader));
    cls->defineFunction("getSaturation", _SE(js_scene_Shadow_getSaturation));
    cls->defineFunction("getShadowColor", _SE(js_scene_Shadow_getShadowColor));
    cls->defineFunction("getShadowColor4f", _SE(js_scene_Shadow_getShadowColor4f));
    cls->defineFunction("getSize", _SE(js_scene_Shadow_getSize));
    cls->defineFunction("getType", _SE(js_scene_Shadow_getType));
    cls->defineFunction("initialize", _SE(js_scene_Shadow_initialize));
    cls->defineFunction("isAutoAdapt", _SE(js_scene_Shadow_isAutoAdapt));
    cls->defineFunction("isEnabled", _SE(js_scene_Shadow_isEnabled));
    cls->defineFunction("isShadowMapDirty", _SE(js_scene_Shadow_isShadowMapDirty));
    cls->defineFunction("setAutoAdapt", _SE(js_scene_Shadow_setAutoAdapt));
    cls->defineFunction("setBias", _SE(js_scene_Shadow_setBias));
    cls->defineFunction("setDistance", _SE(js_scene_Shadow_setDistance));
    cls->defineFunction("setEnabled", _SE(js_scene_Shadow_setEnabled));
    cls->defineFunction("setFar", _SE(js_scene_Shadow_setFar));
    cls->defineFunction("setNear", _SE(js_scene_Shadow_setNear));
    cls->defineFunction("setNormal", _SE(js_scene_Shadow_setNormal));
    cls->defineFunction("setNormalBias", _SE(js_scene_Shadow_setNormalBias));
    cls->defineFunction("setOrthoSize", _SE(js_scene_Shadow_setOrthoSize));
    cls->defineFunction("setPcf", _SE(js_scene_Shadow_setPcf));
    cls->defineFunction("setSaturation", _SE(js_scene_Shadow_setSaturation));
    cls->defineFunction("setShadowColor", _SE(js_scene_Shadow_setShadowColor));
    cls->defineFunction("setShadowMapDirty", _SE(js_scene_Shadow_setShadowMapDirty));
    cls->defineFunction("setSize", _SE(js_scene_Shadow_setSize));
    cls->defineFunction("setType", _SE(js_scene_Shadow_setType));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Shadow_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Shadow>(cls);

    __jsb_cc_scene_Shadow_proto = cls->getProto();
    __jsb_cc_scene_Shadow_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Skybox_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Skybox_class = nullptr; // NOLINT

static bool js_scene_Skybox_activate(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_activate : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->activate();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_activate)

static bool js_scene_Skybox_getEnvmap(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_getEnvmap : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::TextureCube *result = cobj->getEnvmap();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_getEnvmap : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_getEnvmap)

static bool js_scene_Skybox_getModel(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_getModel : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::Model *result = cobj->getModel();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_getModel : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_getModel)

static bool js_scene_Skybox_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::SkyboxInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_initialize)

static bool js_scene_Skybox_isEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_isEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_isEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_isEnabled)

static bool js_scene_Skybox_isRGBE(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_isRGBE : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isRGBE();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_isRGBE : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_isRGBE)

static bool js_scene_Skybox_isUseIBL(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_isUseIBL : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isUseIBL();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_isUseIBL : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_isUseIBL)

static bool js_scene_Skybox_setEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_setEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_setEnabled)

static bool js_scene_Skybox_setEnvmap(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_setEnvmap : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::TextureCube *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_setEnvmap : Error processing arguments");
        cobj->setEnvmap(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_setEnvmap)

static bool js_scene_Skybox_setIsRGBE(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_setIsRGBE : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_setIsRGBE : Error processing arguments");
        cobj->setIsRGBE(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_setIsRGBE)

static bool js_scene_Skybox_setUseIBL(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Skybox_setUseIBL : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Skybox_setUseIBL : Error processing arguments");
        cobj->setUseIBL(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Skybox_setUseIBL)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Skybox_finalize)

static bool js_scene_Skybox_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::Skybox *cobj = JSB_ALLOC(cc::scene::Skybox);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Skybox_constructor, __jsb_cc_scene_Skybox_class, js_cc_scene_Skybox_finalize)

static bool js_cc_scene_Skybox_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Skybox>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Skybox>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Skybox_finalize)

bool js_register_scene_Skybox(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Skybox", obj, nullptr, _SE(js_scene_Skybox_constructor));

    cls->defineFunction("activate", _SE(js_scene_Skybox_activate));
    cls->defineFunction("getEnvmap", _SE(js_scene_Skybox_getEnvmap));
    cls->defineFunction("getModel", _SE(js_scene_Skybox_getModel));
    cls->defineFunction("initialize", _SE(js_scene_Skybox_initialize));
    cls->defineFunction("isEnabled", _SE(js_scene_Skybox_isEnabled));
    cls->defineFunction("isRGBE", _SE(js_scene_Skybox_isRGBE));
    cls->defineFunction("isUseIBL", _SE(js_scene_Skybox_isUseIBL));
    cls->defineFunction("setEnabled", _SE(js_scene_Skybox_setEnabled));
    cls->defineFunction("setEnvmap", _SE(js_scene_Skybox_setEnvmap));
    cls->defineFunction("setIsRGBE", _SE(js_scene_Skybox_setIsRGBE));
    cls->defineFunction("setUseIBL", _SE(js_scene_Skybox_setUseIBL));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Skybox_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Skybox>(cls);

    __jsb_cc_scene_Skybox_proto = cls->getProto();
    __jsb_cc_scene_Skybox_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_AmbientInfo_proto = nullptr; // NOLINT
se::Class * __jsb_cc_AmbientInfo_class = nullptr; // NOLINT

static bool js_scene_AmbientInfo_getGroundAlbedo(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_AmbientInfo_getGroundAlbedo : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Color &result = cobj->getGroundAlbedo();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_AmbientInfo_getGroundAlbedo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_AmbientInfo_getGroundAlbedo)

static bool js_scene_AmbientInfo_getSkyColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_AmbientInfo_getSkyColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Color &result = cobj->getSkyColor();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_AmbientInfo_getSkyColor : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_AmbientInfo_getSkyColor)

static bool js_scene_AmbientInfo_getSkyIllum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_AmbientInfo_getSkyIllum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getSkyIllum();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_AmbientInfo_getSkyIllum : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_AmbientInfo_getSkyIllum)

static bool js_scene_AmbientInfo_setGroundAlbedo(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_AmbientInfo_setGroundAlbedo : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_AmbientInfo_setGroundAlbedo : Error processing arguments");
        cobj->setGroundAlbedo(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_AmbientInfo_setGroundAlbedo)

static bool js_scene_AmbientInfo_setSkyColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_AmbientInfo_setSkyColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_AmbientInfo_setSkyColor : Error processing arguments");
        cobj->setSkyColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_AmbientInfo_setSkyColor)

static bool js_scene_AmbientInfo_setSkyIllum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_AmbientInfo_setSkyIllum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_AmbientInfo_setSkyIllum : Error processing arguments");
        cobj->setSkyIllum(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_AmbientInfo_setSkyIllum)

SE_DECLARE_FINALIZE_FUNC(js_cc_AmbientInfo_finalize)

static bool js_scene_AmbientInfo_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::AmbientInfo *cobj = JSB_ALLOC(cc::AmbientInfo);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_AmbientInfo_constructor, __jsb_cc_AmbientInfo_class, js_cc_AmbientInfo_finalize)

static bool js_cc_AmbientInfo_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::AmbientInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::AmbientInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_AmbientInfo_finalize)

bool js_register_scene_AmbientInfo(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("AmbientInfo", obj, nullptr, _SE(js_scene_AmbientInfo_constructor));

    cls->defineFunction("getGroundAlbedo", _SE(js_scene_AmbientInfo_getGroundAlbedo));
    cls->defineFunction("getSkyColor", _SE(js_scene_AmbientInfo_getSkyColor));
    cls->defineFunction("getSkyIllum", _SE(js_scene_AmbientInfo_getSkyIllum));
    cls->defineFunction("setGroundAlbedo", _SE(js_scene_AmbientInfo_setGroundAlbedo));
    cls->defineFunction("setSkyColor", _SE(js_scene_AmbientInfo_setSkyColor));
    cls->defineFunction("setSkyIllum", _SE(js_scene_AmbientInfo_setSkyIllum));
    cls->defineFinalizeFunction(_SE(js_cc_AmbientInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::AmbientInfo>(cls);

    __jsb_cc_AmbientInfo_proto = cls->getProto();
    __jsb_cc_AmbientInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Ambient_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Ambient_class = nullptr; // NOLINT

static bool js_scene_Ambient_getAlbedoArray(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_getAlbedoArray : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::array<float, 4> &result = cobj->getAlbedoArray();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_getAlbedoArray : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_getAlbedoArray)

static bool js_scene_Ambient_getColorArray(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_getColorArray : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::array<float, 4> &result = cobj->getColorArray();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_getColorArray : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_getColorArray)

static bool js_scene_Ambient_getGroundAlbedo(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_getGroundAlbedo : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Color &result = cobj->getGroundAlbedo();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_getGroundAlbedo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_getGroundAlbedo)

static bool js_scene_Ambient_getSkyColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_getSkyColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Color &result = cobj->getSkyColor();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_getSkyColor : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_getSkyColor)

static bool js_scene_Ambient_getSkyIllum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_getSkyIllum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getSkyIllum();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_getSkyIllum : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_getSkyIllum)

static bool js_scene_Ambient_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::AmbientInfo *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_initialize)

static bool js_scene_Ambient_isEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_isEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_isEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_isEnabled)

static bool js_scene_Ambient_setEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_setEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_setEnabled)

static bool js_scene_Ambient_setGroundAlbedo(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_setGroundAlbedo : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_setGroundAlbedo : Error processing arguments");
        cobj->setGroundAlbedo(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_setGroundAlbedo)

static bool js_scene_Ambient_setSkyColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_setSkyColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_setSkyColor : Error processing arguments");
        cobj->setSkyColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_setSkyColor)

static bool js_scene_Ambient_setSkyIllum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Ambient_setSkyIllum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Ambient_setSkyIllum : Error processing arguments");
        cobj->setSkyIllum(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Ambient_setSkyIllum)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Ambient_finalize)

static bool js_scene_Ambient_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::Ambient *cobj = JSB_ALLOC(cc::scene::Ambient);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Ambient_constructor, __jsb_cc_scene_Ambient_class, js_cc_scene_Ambient_finalize)

static bool js_cc_scene_Ambient_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Ambient>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Ambient>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Ambient_finalize)

bool js_register_scene_Ambient(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Ambient", obj, nullptr, _SE(js_scene_Ambient_constructor));

    cls->defineFunction("getAlbedoArray", _SE(js_scene_Ambient_getAlbedoArray));
    cls->defineFunction("getColorArray", _SE(js_scene_Ambient_getColorArray));
    cls->defineFunction("getGroundAlbedo", _SE(js_scene_Ambient_getGroundAlbedo));
    cls->defineFunction("getSkyColor", _SE(js_scene_Ambient_getSkyColor));
    cls->defineFunction("getSkyIllum", _SE(js_scene_Ambient_getSkyIllum));
    cls->defineFunction("initialize", _SE(js_scene_Ambient_initialize));
    cls->defineFunction("isEnabled", _SE(js_scene_Ambient_isEnabled));
    cls->defineFunction("setEnabled", _SE(js_scene_Ambient_setEnabled));
    cls->defineFunction("setGroundAlbedo", _SE(js_scene_Ambient_setGroundAlbedo));
    cls->defineFunction("setSkyColor", _SE(js_scene_Ambient_setSkyColor));
    cls->defineFunction("setSkyIllum", _SE(js_scene_Ambient_setSkyIllum));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Ambient_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Ambient>(cls);

    __jsb_cc_scene_Ambient_proto = cls->getProto();
    __jsb_cc_scene_Ambient_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_IRenderWindowInfo_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_IRenderWindowInfo_class = nullptr; // NOLINT

static bool js_scene_IRenderWindowInfo_get_title(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_get_title : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->title, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->title, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderWindowInfo_get_title)

static bool js_scene_IRenderWindowInfo_set_title(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_set_title : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->title, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderWindowInfo_set_title : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderWindowInfo_set_title)

static bool js_scene_IRenderWindowInfo_get_width(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->width, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->width, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderWindowInfo_get_width)

static bool js_scene_IRenderWindowInfo_set_width(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderWindowInfo_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderWindowInfo_set_width)

static bool js_scene_IRenderWindowInfo_get_height(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->height, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->height, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderWindowInfo_get_height)

static bool js_scene_IRenderWindowInfo_set_height(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderWindowInfo_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderWindowInfo_set_height)

static bool js_scene_IRenderWindowInfo_get_renderPassInfo(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_get_renderPassInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->renderPassInfo, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->renderPassInfo, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderWindowInfo_get_renderPassInfo)

static bool js_scene_IRenderWindowInfo_set_renderPassInfo(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_set_renderPassInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->renderPassInfo, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderWindowInfo_set_renderPassInfo : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderWindowInfo_set_renderPassInfo)

static bool js_scene_IRenderWindowInfo_get_swapchainBufferIndices(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_get_swapchainBufferIndices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->swapchainBufferIndices, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->swapchainBufferIndices, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderWindowInfo_get_swapchainBufferIndices)

static bool js_scene_IRenderWindowInfo_set_swapchainBufferIndices(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_set_swapchainBufferIndices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->swapchainBufferIndices, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderWindowInfo_set_swapchainBufferIndices : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderWindowInfo_set_swapchainBufferIndices)

static bool js_scene_IRenderWindowInfo_get_shouldSyncSizeWithSwapchain(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_get_shouldSyncSizeWithSwapchain : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->shouldSyncSizeWithSwapchain, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->shouldSyncSizeWithSwapchain, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderWindowInfo_get_shouldSyncSizeWithSwapchain)

static bool js_scene_IRenderWindowInfo_set_shouldSyncSizeWithSwapchain(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderWindowInfo_set_shouldSyncSizeWithSwapchain : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->shouldSyncSizeWithSwapchain, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderWindowInfo_set_shouldSyncSizeWithSwapchain : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderWindowInfo_set_shouldSyncSizeWithSwapchain)

template <>
bool sevalue_to_native(const se::Value &from, cc::scene::IRenderWindowInfo *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::scene::IRenderWindowInfo *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    json->getProperty("title", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->title), ctx);
    }
    json->getProperty("width", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width), ctx);
    }
    json->getProperty("height", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height), ctx);
    }
    json->getProperty("renderPassInfo", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->renderPassInfo), ctx);
    }
    json->getProperty("swapchainBufferIndices", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->swapchainBufferIndices), ctx);
    }
    json->getProperty("shouldSyncSizeWithSwapchain", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->shouldSyncSizeWithSwapchain), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_IRenderWindowInfo_finalize)

static bool js_scene_IRenderWindowInfo_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::scene::IRenderWindowInfo *cobj = JSB_ALLOC(cc::scene::IRenderWindowInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if (argc == 1 && args[0].isObject()) {
        se::Object *json = args[0].toObject();
        se::Value   field;

        cc::scene::IRenderWindowInfo *cobj = JSB_ALLOC(cc::scene::IRenderWindowInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if (!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::scene::IRenderWindowInfo *cobj = JSB_ALLOC(cc::scene::IRenderWindowInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->title), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->width), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->height), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->renderPassInfo), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->swapchainBufferIndices), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->shouldSyncSizeWithSwapchain), nullptr);
    }

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_IRenderWindowInfo_constructor, __jsb_cc_scene_IRenderWindowInfo_class, js_cc_scene_IRenderWindowInfo_finalize)

static bool js_cc_scene_IRenderWindowInfo_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderWindowInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_IRenderWindowInfo_finalize)

bool js_register_scene_IRenderWindowInfo(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("IRenderWindowInfo", obj, nullptr, _SE(js_scene_IRenderWindowInfo_constructor));

    cls->defineProperty("title", _SE(js_scene_IRenderWindowInfo_get_title), _SE(js_scene_IRenderWindowInfo_set_title));
    cls->defineProperty("width", _SE(js_scene_IRenderWindowInfo_get_width), _SE(js_scene_IRenderWindowInfo_set_width));
    cls->defineProperty("height", _SE(js_scene_IRenderWindowInfo_get_height), _SE(js_scene_IRenderWindowInfo_set_height));
    cls->defineProperty("renderPassInfo", _SE(js_scene_IRenderWindowInfo_get_renderPassInfo), _SE(js_scene_IRenderWindowInfo_set_renderPassInfo));
    cls->defineProperty("swapchainBufferIndices", _SE(js_scene_IRenderWindowInfo_get_swapchainBufferIndices), _SE(js_scene_IRenderWindowInfo_set_swapchainBufferIndices));
    cls->defineProperty("shouldSyncSizeWithSwapchain", _SE(js_scene_IRenderWindowInfo_get_shouldSyncSizeWithSwapchain), _SE(js_scene_IRenderWindowInfo_set_shouldSyncSizeWithSwapchain));
    cls->defineFinalizeFunction(_SE(js_cc_scene_IRenderWindowInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::IRenderWindowInfo>(cls);

    __jsb_cc_scene_IRenderWindowInfo_proto = cls->getProto();
    __jsb_cc_scene_IRenderWindowInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_RenderWindow_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_RenderWindow_class = nullptr; // NOLINT

static bool js_scene_RenderWindow_attachCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_attachCamera : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Camera *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_attachCamera : Error processing arguments");
        cobj->attachCamera(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_attachCamera)

static bool js_scene_RenderWindow_clearCameras(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_clearCameras : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->clearCameras();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_clearCameras)

static bool js_scene_RenderWindow_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_destroy)

static bool js_scene_RenderWindow_detachCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_detachCamera : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Camera *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_detachCamera : Error processing arguments");
        cobj->detachCamera(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_detachCamera)

static bool js_scene_RenderWindow_extractRenderCameras(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_extractRenderCameras : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::scene::Camera *>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_extractRenderCameras : Error processing arguments");
        cobj->extractRenderCameras(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_extractRenderCameras)

static bool js_scene_RenderWindow_getCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_getCamera : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::Camera *> &result = cobj->getCamera();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_getCamera : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_getCamera)

static bool js_scene_RenderWindow_getFramebuffer(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_getFramebuffer : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::Framebuffer *result = cobj->getFramebuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_getFramebuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_getFramebuffer)

static bool js_scene_RenderWindow_getHeight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_getHeight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_getHeight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_getHeight)

static bool js_scene_RenderWindow_getWidth(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_getWidth : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_getWidth : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_getWidth)

static bool js_scene_RenderWindow_hasOffScreenAttachments(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_hasOffScreenAttachments : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->hasOffScreenAttachments();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_hasOffScreenAttachments : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_hasOffScreenAttachments)

static bool js_scene_RenderWindow_hasOnScreenAttachments(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_hasOnScreenAttachments : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->hasOnScreenAttachments();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_hasOnScreenAttachments : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_hasOnScreenAttachments)

static bool js_scene_RenderWindow_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::gfx::Device *, false>           arg0 = {};
        HolderType<cc::scene::IRenderWindowInfo, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_initialize : Error processing arguments");
        bool result = cobj->initialize(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_initialize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_initialize)

static bool js_scene_RenderWindow_resize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_resize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_resize : Error processing arguments");
        cobj->resize(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_resize)

static bool js_scene_RenderWindow_shouldSyncSizeWithSwapchain(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_shouldSyncSizeWithSwapchain : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->shouldSyncSizeWithSwapchain();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_shouldSyncSizeWithSwapchain : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_shouldSyncSizeWithSwapchain)

static bool js_scene_RenderWindow_sortCameras(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_sortCameras : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->sortCameras();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderWindow_sortCameras)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_RenderWindow_finalize)

static bool js_scene_RenderWindow_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::RenderWindow *cobj = JSB_ALLOC(cc::scene::RenderWindow);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_RenderWindow_constructor, __jsb_cc_scene_RenderWindow_class, js_cc_scene_RenderWindow_finalize)

static bool js_cc_scene_RenderWindow_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::RenderWindow>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_RenderWindow_finalize)

bool js_register_scene_RenderWindow(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("RenderWindow", obj, nullptr, _SE(js_scene_RenderWindow_constructor));

    cls->defineFunction("attachCamera", _SE(js_scene_RenderWindow_attachCamera));
    cls->defineFunction("clearCameras", _SE(js_scene_RenderWindow_clearCameras));
    cls->defineFunction("destroy", _SE(js_scene_RenderWindow_destroy));
    cls->defineFunction("detachCamera", _SE(js_scene_RenderWindow_detachCamera));
    cls->defineFunction("extractRenderCameras", _SE(js_scene_RenderWindow_extractRenderCameras));
    cls->defineFunction("getCamera", _SE(js_scene_RenderWindow_getCamera));
    cls->defineFunction("getFramebuffer", _SE(js_scene_RenderWindow_getFramebuffer));
    cls->defineFunction("getHeight", _SE(js_scene_RenderWindow_getHeight));
    cls->defineFunction("getWidth", _SE(js_scene_RenderWindow_getWidth));
    cls->defineFunction("hasOffScreenAttachments", _SE(js_scene_RenderWindow_hasOffScreenAttachments));
    cls->defineFunction("hasOnScreenAttachments", _SE(js_scene_RenderWindow_hasOnScreenAttachments));
    cls->defineFunction("initialize", _SE(js_scene_RenderWindow_initialize));
    cls->defineFunction("resize", _SE(js_scene_RenderWindow_resize));
    cls->defineFunction("shouldSyncSizeWithSwapchain", _SE(js_scene_RenderWindow_shouldSyncSizeWithSwapchain));
    cls->defineFunction("sortCameras", _SE(js_scene_RenderWindow_sortCameras));
    cls->defineFinalizeFunction(_SE(js_cc_scene_RenderWindow_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::RenderWindow>(cls);

    __jsb_cc_scene_RenderWindow_proto = cls->getProto();
    __jsb_cc_scene_RenderWindow_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Camera_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Camera_class = nullptr; // NOLINT

static bool js_scene_Camera_attachToScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_attachToScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderScene *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_attachToScene : Error processing arguments");
        cobj->attachToScene(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_attachToScene)

static bool js_scene_Camera_changeTargetWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_changeTargetWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderWindow *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_changeTargetWindow : Error processing arguments");
        cobj->changeTargetWindow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_changeTargetWindow)

static bool js_scene_Camera_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_destroy)

static bool js_scene_Camera_detachCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_detachCamera : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->detachCamera();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_detachCamera)

static bool js_scene_Camera_detachFromScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_detachFromScene : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->detachFromScene();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_detachFromScene)

static bool js_scene_Camera_getAperture(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getAperture : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getAperture());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getAperture : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getAperture)

static bool js_scene_Camera_getApertureValue(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getApertureValue : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getApertureValue();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getApertureValue : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getApertureValue)

static bool js_scene_Camera_getAspect(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getAspect : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getAspect();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getAspect : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getAspect)

static bool js_scene_Camera_getClearColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getClearColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::gfx::Color &result = cobj->getClearColor();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getClearColor : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getClearColor)

static bool js_scene_Camera_getClearDepth(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getClearDepth : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getClearDepth();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getClearDepth : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getClearDepth)

static bool js_scene_Camera_getClearFlag(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getClearFlag : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getClearFlag());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getClearFlag : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getClearFlag)

static bool js_scene_Camera_getClearStencil(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getClearStencil : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getClearStencil();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getClearStencil : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getClearStencil)

static bool js_scene_Camera_getEc(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getEc : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getEc();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getEc : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getEc)

static bool js_scene_Camera_getExposure(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getExposure : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getExposure();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getExposure : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getExposure)

static bool js_scene_Camera_getFarClip(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getFarClip : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFarClip();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getFarClip : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getFarClip)

static bool js_scene_Camera_getForward(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getForward : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getForward();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getForward : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getForward)

static bool js_scene_Camera_getFov(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getFov : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFov();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getFov : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getFov)

static bool js_scene_Camera_getFovAxis(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getFovAxis : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getFovAxis());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getFovAxis : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getFovAxis)

static bool js_scene_Camera_getFrustum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getFrustum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::geometry::Frustum &result = cobj->getFrustum();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getFrustum : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getFrustum)

static bool js_scene_Camera_getHeight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getHeight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getHeight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getHeight)

static bool js_scene_Camera_getIso(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getIso : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getIso());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getIso : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getIso)

static bool js_scene_Camera_getIsoValue(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getIsoValue : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getIsoValue();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getIsoValue : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getIsoValue)

static bool js_scene_Camera_getMatProj(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getMatProj : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getMatProj();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getMatProj : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getMatProj)

static bool js_scene_Camera_getMatProjInv(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getMatProjInv : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getMatProjInv();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getMatProjInv : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getMatProjInv)

static bool js_scene_Camera_getMatView(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getMatView : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getMatView();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getMatView : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getMatView)

static bool js_scene_Camera_getMatViewProj(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getMatViewProj : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getMatViewProj();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getMatViewProj : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getMatViewProj)

static bool js_scene_Camera_getMatViewProjInv(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getMatViewProjInv : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Mat4 &result = cobj->getMatViewProjInv();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getMatViewProjInv : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getMatViewProjInv)

static bool js_scene_Camera_getName(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getName : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::string &result = cobj->getName();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getName : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getName)

static bool js_scene_Camera_getNearClip(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getNearClip : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getNearClip();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getNearClip : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getNearClip)

static bool js_scene_Camera_getNode(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getNode : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Node *result = cobj->getNode();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getNode : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getNode)

static bool js_scene_Camera_getOrthoHeight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getOrthoHeight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getOrthoHeight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getOrthoHeight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getOrthoHeight)

static bool js_scene_Camera_getPosition(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getPosition : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec3 &result = cobj->getPosition();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getPosition : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getPosition)

static bool js_scene_Camera_getPriority(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getPriority : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getPriority();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getPriority : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getPriority)

static bool js_scene_Camera_getProjectionType(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getProjectionType : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getProjectionType());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getProjectionType : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getProjectionType)

static bool js_scene_Camera_getScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderScene *result = cobj->getScene();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getScene : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getScene)

static bool js_scene_Camera_getScreenScale(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getScreenScale : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getScreenScale();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getScreenScale : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getScreenScale)

static bool js_scene_Camera_getShutter(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getShutter : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getShutter());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getShutter : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getShutter)

static bool js_scene_Camera_getShutterValue(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getShutterValue : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getShutterValue();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getShutterValue : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getShutterValue)

static bool js_scene_Camera_getViewport(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getViewport : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const cc::Vec4 &result = cobj->getViewport();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getViewport : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getViewport)

static bool js_scene_Camera_getVisibility(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getVisibility : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getVisibility();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getVisibility : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getVisibility)

static bool js_scene_Camera_getWidth(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getWidth : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getWidth : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getWidth)

static bool js_scene_Camera_getWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_getWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderWindow *result = cobj->getWindow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_getWindow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_getWindow)

static bool js_scene_Camera_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::ICameraInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_initialize : Error processing arguments");
        bool result = cobj->initialize(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_initialize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_initialize)

static bool js_scene_Camera_isEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_isEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_isEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_isEnabled)

static bool js_scene_Camera_isWindowSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_isWindowSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isWindowSize();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_isWindowSize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_isWindowSize)

static bool js_scene_Camera_resize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_resize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_resize : Error processing arguments");
        cobj->resize(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_resize)

static bool js_scene_Camera_screenToWorld(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_screenToWorld : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::Vec3, true> arg0 = {};
        HolderType<cc::Vec3, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_screenToWorld : Error processing arguments");
        const cc::Vec3 &result = cobj->screenToWorld(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_screenToWorld : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_screenToWorld)

static bool js_scene_Camera_setAperture(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setAperture : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::CameraAperture, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setAperture : Error processing arguments");
        cobj->setAperture(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setAperture)

static bool js_scene_Camera_setClearColor(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setClearColor : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::Color, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setClearColor : Error processing arguments");
        cobj->setClearColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setClearColor)

static bool js_scene_Camera_setClearDepth(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setClearDepth : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setClearDepth : Error processing arguments");
        cobj->setClearDepth(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setClearDepth)

static bool js_scene_Camera_setClearFlag(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setClearFlag : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::ClearFlagBit, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setClearFlag : Error processing arguments");
        cobj->setClearFlag(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setClearFlag)

static bool js_scene_Camera_setClearStencil(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setClearStencil : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setClearStencil : Error processing arguments");
        cobj->setClearStencil(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setClearStencil)

static bool js_scene_Camera_setEc(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setEc : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setEc : Error processing arguments");
        cobj->setEc(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setEc)

static bool js_scene_Camera_setEnabled(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setEnabled : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setEnabled)

static bool js_scene_Camera_setFarClip(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setFarClip : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setFarClip : Error processing arguments");
        cobj->setFarClip(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setFarClip)

static bool js_scene_Camera_setFixedSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setFixedSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setFixedSize : Error processing arguments");
        cobj->setFixedSize(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setFixedSize)

static bool js_scene_Camera_setForward(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setForward : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setForward : Error processing arguments");
        cobj->setForward(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setForward)

static bool js_scene_Camera_setFov(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setFov : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setFov : Error processing arguments");
        cobj->setFov(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setFov)

static bool js_scene_Camera_setFovAxis(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setFovAxis : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::CameraFOVAxis, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setFovAxis : Error processing arguments");
        cobj->setFovAxis(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setFovAxis)

static bool js_scene_Camera_setFrustum(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setFrustum : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::geometry::Frustum, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setFrustum : Error processing arguments");
        cobj->setFrustum(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setFrustum)

static bool js_scene_Camera_setIso(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setIso : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::CameraISO, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setIso : Error processing arguments");
        cobj->setIso(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setIso)

static bool js_scene_Camera_setNearClip(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setNearClip : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setNearClip : Error processing arguments");
        cobj->setNearClip(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setNearClip)

static bool js_scene_Camera_setNode(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setNode : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Node *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setNode : Error processing arguments");
        cobj->setNode(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setNode)

static bool js_scene_Camera_setOrthoHeight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setOrthoHeight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setOrthoHeight : Error processing arguments");
        cobj->setOrthoHeight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setOrthoHeight)

static bool js_scene_Camera_setPosition(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setPosition : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setPosition : Error processing arguments");
        cobj->setPosition(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setPosition)

static bool js_scene_Camera_setPriority(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setPriority : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setPriority : Error processing arguments");
        cobj->setPriority(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setPriority)

static bool js_scene_Camera_setProjectionType(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setProjectionType : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::CameraProjection, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setProjectionType : Error processing arguments");
        cobj->setProjectionType(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setProjectionType)

static bool js_scene_Camera_setScreenScale(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setScreenScale : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setScreenScale : Error processing arguments");
        cobj->setScreenScale(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setScreenScale)

static bool js_scene_Camera_setShutter(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setShutter : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::CameraShutter, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setShutter : Error processing arguments");
        cobj->setShutter(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setShutter)

static bool js_scene_Camera_setViewport(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setViewport : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::Vec4, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setViewport : Error processing arguments");
        cobj->setViewport(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setViewport)

static bool js_scene_Camera_setVisibility(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setVisibility : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setVisibility : Error processing arguments");
        cobj->setVisibility(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setVisibility)

static bool js_scene_Camera_setWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderWindow *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setWindow : Error processing arguments");
        cobj->setWindow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setWindow)

static bool js_scene_Camera_setWindowSize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_setWindowSize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_setWindowSize : Error processing arguments");
        cobj->setWindowSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_setWindowSize)

static bool js_scene_Camera_update(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_update : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cobj->update();
        return true;
    }
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_update : Error processing arguments");
        cobj->update(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_update)

static bool js_scene_Camera_worldMatrixToScreen(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_worldMatrixToScreen : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 4) {
        HolderType<cc::Mat4, true>      arg0 = {};
        HolderType<cc::Mat4, true>      arg1 = {};
        HolderType<unsigned int, false> arg2 = {};
        HolderType<unsigned int, false> arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_worldMatrixToScreen : Error processing arguments");
        const cc::Mat4 &result = cobj->worldMatrixToScreen(arg0.value(), arg1.value(), arg2.value(), arg3.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_worldMatrixToScreen : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_worldMatrixToScreen)

static bool js_scene_Camera_worldToScreen(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_worldToScreen : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::Vec3, true> arg0 = {};
        HolderType<cc::Vec3, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Camera_worldToScreen : Error processing arguments");
        const cc::Vec3 &result = cobj->worldToScreen(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Camera_worldToScreen : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Camera_worldToScreen)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Camera_finalize)

static bool js_scene_Camera_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    CC_UNUSED bool   ok   = true;
    const auto &     args = s.args();
    cc::gfx::Device *arg0 = nullptr;
    ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_constructor : Error processing arguments");
    cc::scene::Camera *cobj = JSB_ALLOC(cc::scene::Camera, arg0);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Camera_constructor, __jsb_cc_scene_Camera_class, js_cc_scene_Camera_finalize)

static bool js_cc_scene_Camera_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Camera>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Camera_finalize)

bool js_register_scene_Camera(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Camera", obj, nullptr, _SE(js_scene_Camera_constructor));

    cls->defineFunction("attachToScene", _SE(js_scene_Camera_attachToScene));
    cls->defineFunction("changeTargetWindow", _SE(js_scene_Camera_changeTargetWindow));
    cls->defineFunction("destroy", _SE(js_scene_Camera_destroy));
    cls->defineFunction("detachCamera", _SE(js_scene_Camera_detachCamera));
    cls->defineFunction("detachFromScene", _SE(js_scene_Camera_detachFromScene));
    cls->defineFunction("getAperture", _SE(js_scene_Camera_getAperture));
    cls->defineFunction("getApertureValue", _SE(js_scene_Camera_getApertureValue));
    cls->defineFunction("getAspect", _SE(js_scene_Camera_getAspect));
    cls->defineFunction("getClearColor", _SE(js_scene_Camera_getClearColor));
    cls->defineFunction("getClearDepth", _SE(js_scene_Camera_getClearDepth));
    cls->defineFunction("getClearFlag", _SE(js_scene_Camera_getClearFlag));
    cls->defineFunction("getClearStencil", _SE(js_scene_Camera_getClearStencil));
    cls->defineFunction("getEc", _SE(js_scene_Camera_getEc));
    cls->defineFunction("getExposure", _SE(js_scene_Camera_getExposure));
    cls->defineFunction("getFarClip", _SE(js_scene_Camera_getFarClip));
    cls->defineFunction("getForward", _SE(js_scene_Camera_getForward));
    cls->defineFunction("getFov", _SE(js_scene_Camera_getFov));
    cls->defineFunction("getFovAxis", _SE(js_scene_Camera_getFovAxis));
    cls->defineFunction("getFrustum", _SE(js_scene_Camera_getFrustum));
    cls->defineFunction("getHeight", _SE(js_scene_Camera_getHeight));
    cls->defineFunction("getIso", _SE(js_scene_Camera_getIso));
    cls->defineFunction("getIsoValue", _SE(js_scene_Camera_getIsoValue));
    cls->defineFunction("getMatProj", _SE(js_scene_Camera_getMatProj));
    cls->defineFunction("getMatProjInv", _SE(js_scene_Camera_getMatProjInv));
    cls->defineFunction("getMatView", _SE(js_scene_Camera_getMatView));
    cls->defineFunction("getMatViewProj", _SE(js_scene_Camera_getMatViewProj));
    cls->defineFunction("getMatViewProjInv", _SE(js_scene_Camera_getMatViewProjInv));
    cls->defineFunction("getName", _SE(js_scene_Camera_getName));
    cls->defineFunction("getNearClip", _SE(js_scene_Camera_getNearClip));
    cls->defineFunction("getNode", _SE(js_scene_Camera_getNode));
    cls->defineFunction("getOrthoHeight", _SE(js_scene_Camera_getOrthoHeight));
    cls->defineFunction("getPosition", _SE(js_scene_Camera_getPosition));
    cls->defineFunction("getPriority", _SE(js_scene_Camera_getPriority));
    cls->defineFunction("getProjectionType", _SE(js_scene_Camera_getProjectionType));
    cls->defineFunction("getScene", _SE(js_scene_Camera_getScene));
    cls->defineFunction("getScreenScale", _SE(js_scene_Camera_getScreenScale));
    cls->defineFunction("getShutter", _SE(js_scene_Camera_getShutter));
    cls->defineFunction("getShutterValue", _SE(js_scene_Camera_getShutterValue));
    cls->defineFunction("getViewport", _SE(js_scene_Camera_getViewport));
    cls->defineFunction("getVisibility", _SE(js_scene_Camera_getVisibility));
    cls->defineFunction("getWidth", _SE(js_scene_Camera_getWidth));
    cls->defineFunction("getWindow", _SE(js_scene_Camera_getWindow));
    cls->defineFunction("initialize", _SE(js_scene_Camera_initialize));
    cls->defineFunction("isEnabled", _SE(js_scene_Camera_isEnabled));
    cls->defineFunction("isWindowSize", _SE(js_scene_Camera_isWindowSize));
    cls->defineFunction("resize", _SE(js_scene_Camera_resize));
    cls->defineFunction("screenToWorld", _SE(js_scene_Camera_screenToWorld));
    cls->defineFunction("setAperture", _SE(js_scene_Camera_setAperture));
    cls->defineFunction("setClearColor", _SE(js_scene_Camera_setClearColor));
    cls->defineFunction("setClearDepth", _SE(js_scene_Camera_setClearDepth));
    cls->defineFunction("setClearFlag", _SE(js_scene_Camera_setClearFlag));
    cls->defineFunction("setClearStencil", _SE(js_scene_Camera_setClearStencil));
    cls->defineFunction("setEc", _SE(js_scene_Camera_setEc));
    cls->defineFunction("setEnabled", _SE(js_scene_Camera_setEnabled));
    cls->defineFunction("setFarClip", _SE(js_scene_Camera_setFarClip));
    cls->defineFunction("setFixedSize", _SE(js_scene_Camera_setFixedSize));
    cls->defineFunction("setForward", _SE(js_scene_Camera_setForward));
    cls->defineFunction("setFov", _SE(js_scene_Camera_setFov));
    cls->defineFunction("setFovAxis", _SE(js_scene_Camera_setFovAxis));
    cls->defineFunction("setFrustum", _SE(js_scene_Camera_setFrustum));
    cls->defineFunction("setIso", _SE(js_scene_Camera_setIso));
    cls->defineFunction("setNearClip", _SE(js_scene_Camera_setNearClip));
    cls->defineFunction("setNode", _SE(js_scene_Camera_setNode));
    cls->defineFunction("setOrthoHeight", _SE(js_scene_Camera_setOrthoHeight));
    cls->defineFunction("setPosition", _SE(js_scene_Camera_setPosition));
    cls->defineFunction("setPriority", _SE(js_scene_Camera_setPriority));
    cls->defineFunction("setProjectionType", _SE(js_scene_Camera_setProjectionType));
    cls->defineFunction("setScreenScale", _SE(js_scene_Camera_setScreenScale));
    cls->defineFunction("setShutter", _SE(js_scene_Camera_setShutter));
    cls->defineFunction("setViewport", _SE(js_scene_Camera_setViewport));
    cls->defineFunction("setVisibility", _SE(js_scene_Camera_setVisibility));
    cls->defineFunction("setWindow", _SE(js_scene_Camera_setWindow));
    cls->defineFunction("setWindowSize", _SE(js_scene_Camera_setWindowSize));
    cls->defineFunction("update", _SE(js_scene_Camera_update));
    cls->defineFunction("worldMatrixToScreen", _SE(js_scene_Camera_worldMatrixToScreen));
    cls->defineFunction("worldToScreen", _SE(js_scene_Camera_worldToScreen));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Camera_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Camera>(cls);

    __jsb_cc_scene_Camera_proto = cls->getProto();
    __jsb_cc_scene_Camera_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_DrawBatch2D_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_DrawBatch2D_class = nullptr; // NOLINT

template <>
bool sevalue_to_native(const se::Value &from, cc::scene::DrawBatch2D *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::scene::DrawBatch2D *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_DrawBatch2D_finalize)

static bool js_scene_DrawBatch2D_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::scene::DrawBatch2D *cobj = JSB_ALLOC(cc::scene::DrawBatch2D);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::scene::DrawBatch2D *cobj = JSB_ALLOC(cc::scene::DrawBatch2D);

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_DrawBatch2D_constructor, __jsb_cc_scene_DrawBatch2D_class, js_cc_scene_DrawBatch2D_finalize)

static bool js_cc_scene_DrawBatch2D_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_DrawBatch2D_finalize)

bool js_register_scene_DrawBatch2D(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("DrawBatch2D", obj, nullptr, _SE(js_scene_DrawBatch2D_constructor));

    cls->defineFinalizeFunction(_SE(js_cc_scene_DrawBatch2D_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::DrawBatch2D>(cls);

    __jsb_cc_scene_DrawBatch2D_proto = cls->getProto();
    __jsb_cc_scene_DrawBatch2D_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_IRenderSceneInfo_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_IRenderSceneInfo_class = nullptr; // NOLINT

static bool js_scene_IRenderSceneInfo_get_name(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderSceneInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderSceneInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value      jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_IRenderSceneInfo_get_name)

static bool js_scene_IRenderSceneInfo_set_name(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &args = s.args();
    auto *      cobj = SE_THIS_OBJECT<cc::scene::IRenderSceneInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_IRenderSceneInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_IRenderSceneInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_IRenderSceneInfo_set_name)

template <>
bool sevalue_to_native(const se::Value &from, cc::scene::IRenderSceneInfo *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *      data = reinterpret_cast<cc::scene::IRenderSceneInfo *>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool      ok = true;
    json->getProperty("name", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_IRenderSceneInfo_finalize)

static bool js_scene_IRenderSceneInfo_constructor(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    const auto &   args = s.args();
    size_t         argc = args.size();

    if (argc == 0) {
        cc::scene::IRenderSceneInfo *cobj = JSB_ALLOC(cc::scene::IRenderSceneInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::scene::IRenderSceneInfo *cobj = JSB_ALLOC(cc::scene::IRenderSceneInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->name), nullptr);
    }

    if (!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_IRenderSceneInfo_constructor, __jsb_cc_scene_IRenderSceneInfo_class, js_cc_scene_IRenderSceneInfo_finalize)

static bool js_cc_scene_IRenderSceneInfo_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::IRenderSceneInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::IRenderSceneInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_IRenderSceneInfo_finalize)

bool js_register_scene_IRenderSceneInfo(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("IRenderSceneInfo", obj, nullptr, _SE(js_scene_IRenderSceneInfo_constructor));

    cls->defineProperty("name", _SE(js_scene_IRenderSceneInfo_get_name), _SE(js_scene_IRenderSceneInfo_set_name));
    cls->defineFinalizeFunction(_SE(js_cc_scene_IRenderSceneInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::IRenderSceneInfo>(cls);

    __jsb_cc_scene_IRenderSceneInfo_proto = cls->getProto();
    __jsb_cc_scene_IRenderSceneInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_RenderScene_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_RenderScene_class = nullptr; // NOLINT

static bool js_scene_RenderScene_addBatch(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addBatch : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::DrawBatch2D *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addBatch : Error processing arguments");
        cobj->addBatch(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addBatch)

static bool js_scene_RenderScene_addCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addCamera : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Camera *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addCamera : Error processing arguments");
        cobj->addCamera(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addCamera)

static bool js_scene_RenderScene_addDirectionalLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addDirectionalLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::DirectionalLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addDirectionalLight : Error processing arguments");
        cobj->addDirectionalLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addDirectionalLight)

static bool js_scene_RenderScene_addModel(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addModel : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Model *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addModel : Error processing arguments");
        cobj->addModel(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addModel)

static bool js_scene_RenderScene_addSphereLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addSphereLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::SphereLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addSphereLight : Error processing arguments");
        cobj->addSphereLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addSphereLight)

static bool js_scene_RenderScene_addSpotLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addSpotLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::SpotLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addSpotLight : Error processing arguments");
        cobj->addSpotLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addSpotLight)

static bool js_scene_RenderScene_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_destroy)

static bool js_scene_RenderScene_generateModelId(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_generateModelId : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        uint64_t result = cobj->generateModelId();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_generateModelId : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_generateModelId)

static bool js_scene_RenderScene_getBatches(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getBatches : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::DrawBatch2D *> &result = cobj->getBatches();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getBatches : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getBatches)

static bool js_scene_RenderScene_getCameras(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getCameras : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::Camera *> &result = cobj->getCameras();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getCameras : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getCameras)

static bool js_scene_RenderScene_getDrawBatch2Ds(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getDrawBatch2Ds : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::DrawBatch2D *> &result = cobj->getDrawBatch2Ds();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getDrawBatch2Ds : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getDrawBatch2Ds)

static bool js_scene_RenderScene_getMainLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getMainLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::DirectionalLight *result = cobj->getMainLight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getMainLight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getMainLight)

static bool js_scene_RenderScene_getModels(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getModels : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::Model *> &result = cobj->getModels();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getModels : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getModels)

static bool js_scene_RenderScene_getName(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getName : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::string &result = cobj->getName();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getName : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getName)

static bool js_scene_RenderScene_getSphereLights(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getSphereLights : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::SphereLight *> &result = cobj->getSphereLights();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getSphereLights : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getSphereLights)

static bool js_scene_RenderScene_getSpotLights(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getSpotLights : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::SpotLight *> &result = cobj->getSpotLights();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getSpotLights : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getSpotLights)

static bool js_scene_RenderScene_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::IRenderSceneInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_initialize : Error processing arguments");
        bool result = cobj->initialize(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_initialize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_initialize)

static bool js_scene_RenderScene_onGlobalPipelineStateChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_onGlobalPipelineStateChanged : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->onGlobalPipelineStateChanged();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_onGlobalPipelineStateChanged)

static bool js_scene_RenderScene_removeBatch(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    auto *         cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeBatch : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    do {
        if (argc == 1) {
            HolderType<cc::scene::DrawBatch2D *, false> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) {
                ok = true;
                break;
            }
            cobj->removeBatch(arg0.value());
            return true;
        }
    } while (false);

    do {
        if (argc == 1) {
            HolderType<int, false> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) {
                ok = true;
                break;
            }
            cobj->removeBatch(arg0.value());
            return true;
        }
    } while (false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeBatch)

static bool js_scene_RenderScene_removeBatches(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeBatches : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->removeBatches();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeBatches)

static bool js_scene_RenderScene_removeCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeCamera : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Camera *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeCamera : Error processing arguments");
        cobj->removeCamera(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeCamera)

static bool js_scene_RenderScene_removeCameras(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeCameras : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->removeCameras();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeCameras)

static bool js_scene_RenderScene_removeDirectionalLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeDirectionalLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::DirectionalLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeDirectionalLight : Error processing arguments");
        cobj->removeDirectionalLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeDirectionalLight)

static bool js_scene_RenderScene_removeModel(se::State &s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok   = true;
    auto *         cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeModel : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    do {
        if (argc == 1) {
            HolderType<cc::scene::Model *, false> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) {
                ok = true;
                break;
            }
            cobj->removeModel(arg0.value());
            return true;
        }
    } while (false);

    do {
        if (argc == 1) {
            HolderType<int, false> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) {
                ok = true;
                break;
            }
            cobj->removeModel(arg0.value());
            return true;
        }
    } while (false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeModel)

static bool js_scene_RenderScene_removeModels(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeModels : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->removeModels();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeModels)

static bool js_scene_RenderScene_removeSphereLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSphereLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::SphereLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeSphereLight : Error processing arguments");
        cobj->removeSphereLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSphereLight)

static bool js_scene_RenderScene_removeSphereLights(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSphereLights : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->removeSphereLights();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSphereLights)

static bool js_scene_RenderScene_removeSpotLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSpotLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::SpotLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeSpotLight : Error processing arguments");
        cobj->removeSpotLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSpotLight)

static bool js_scene_RenderScene_removeSpotLights(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSpotLights : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->removeSpotLights();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSpotLights)

static bool js_scene_RenderScene_setMainLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_setMainLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::DirectionalLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_setMainLight : Error processing arguments");
        cobj->setMainLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_setMainLight)

static bool js_scene_RenderScene_unsetMainLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_unsetMainLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::DirectionalLight *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_unsetMainLight : Error processing arguments");
        cobj->unsetMainLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_unsetMainLight)

static bool js_scene_RenderScene_update(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_update : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_update : Error processing arguments");
        cobj->update(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_RenderScene_finalize)

static bool js_scene_RenderScene_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::RenderScene *cobj = JSB_ALLOC(cc::scene::RenderScene);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_RenderScene_constructor, __jsb_cc_scene_RenderScene_class, js_cc_scene_RenderScene_finalize)

static bool js_cc_scene_RenderScene_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::RenderScene>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_RenderScene_finalize)

bool js_register_scene_RenderScene(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("RenderScene", obj, nullptr, _SE(js_scene_RenderScene_constructor));

    cls->defineFunction("addBatch", _SE(js_scene_RenderScene_addBatch));
    cls->defineFunction("addCamera", _SE(js_scene_RenderScene_addCamera));
    cls->defineFunction("addDirectionalLight", _SE(js_scene_RenderScene_addDirectionalLight));
    cls->defineFunction("addModel", _SE(js_scene_RenderScene_addModel));
    cls->defineFunction("addSphereLight", _SE(js_scene_RenderScene_addSphereLight));
    cls->defineFunction("addSpotLight", _SE(js_scene_RenderScene_addSpotLight));
    cls->defineFunction("destroy", _SE(js_scene_RenderScene_destroy));
    cls->defineFunction("generateModelId", _SE(js_scene_RenderScene_generateModelId));
    cls->defineFunction("getBatches", _SE(js_scene_RenderScene_getBatches));
    cls->defineFunction("getCameras", _SE(js_scene_RenderScene_getCameras));
    cls->defineFunction("getDrawBatch2Ds", _SE(js_scene_RenderScene_getDrawBatch2Ds));
    cls->defineFunction("getMainLight", _SE(js_scene_RenderScene_getMainLight));
    cls->defineFunction("getModels", _SE(js_scene_RenderScene_getModels));
    cls->defineFunction("getName", _SE(js_scene_RenderScene_getName));
    cls->defineFunction("getSphereLights", _SE(js_scene_RenderScene_getSphereLights));
    cls->defineFunction("getSpotLights", _SE(js_scene_RenderScene_getSpotLights));
    cls->defineFunction("initialize", _SE(js_scene_RenderScene_initialize));
    cls->defineFunction("onGlobalPipelineStateChanged", _SE(js_scene_RenderScene_onGlobalPipelineStateChanged));
    cls->defineFunction("removeBatch", _SE(js_scene_RenderScene_removeBatch));
    cls->defineFunction("removeBatches", _SE(js_scene_RenderScene_removeBatches));
    cls->defineFunction("removeCamera", _SE(js_scene_RenderScene_removeCamera));
    cls->defineFunction("removeCameras", _SE(js_scene_RenderScene_removeCameras));
    cls->defineFunction("removeDirectionalLight", _SE(js_scene_RenderScene_removeDirectionalLight));
    cls->defineFunction("removeModel", _SE(js_scene_RenderScene_removeModel));
    cls->defineFunction("removeModels", _SE(js_scene_RenderScene_removeModels));
    cls->defineFunction("removeSphereLight", _SE(js_scene_RenderScene_removeSphereLight));
    cls->defineFunction("removeSphereLights", _SE(js_scene_RenderScene_removeSphereLights));
    cls->defineFunction("removeSpotLight", _SE(js_scene_RenderScene_removeSpotLight));
    cls->defineFunction("removeSpotLights", _SE(js_scene_RenderScene_removeSpotLights));
    cls->defineFunction("setMainLight", _SE(js_scene_RenderScene_setMainLight));
    cls->defineFunction("unsetMainLight", _SE(js_scene_RenderScene_unsetMainLight));
    cls->defineFunction("update", _SE(js_scene_RenderScene_update));
    cls->defineFinalizeFunction(_SE(js_cc_scene_RenderScene_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::RenderScene>(cls);

    __jsb_cc_scene_RenderScene_proto = cls->getProto();
    __jsb_cc_scene_RenderScene_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_Root_proto = nullptr; // NOLINT
se::Class * __jsb_cc_Root_class = nullptr; // NOLINT

static bool js_scene_Root_activeWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_activeWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderWindow *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_activeWindow : Error processing arguments");
        cobj->activeWindow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_activeWindow)

static bool js_scene_Root_createCamera(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_createCamera : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::Camera *result = cobj->createCamera();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_createCamera : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_createCamera)

static bool js_scene_Root_createScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_createScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::IRenderSceneInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_createScene : Error processing arguments");
        cc::scene::RenderScene *result = cobj->createScene(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_createScene : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_createScene)

static bool js_scene_Root_createWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_createWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::IRenderWindowInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_createWindow : Error processing arguments");
        cc::scene::RenderWindow *result = cobj->createWindow(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_createWindow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_createWindow)

static bool js_scene_Root_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroy)

static bool js_scene_Root_destroyLight(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroyLight : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Light *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_destroyLight : Error processing arguments");
        cobj->destroyLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroyLight)

static bool js_scene_Root_destroyModel(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroyModel : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Model *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_destroyModel : Error processing arguments");
        cobj->destroyModel(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroyModel)

static bool js_scene_Root_destroyScene(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroyScene : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderScene *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_destroyScene : Error processing arguments");
        cobj->destroyScene(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroyScene)

static bool js_scene_Root_destroyScenes(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroyScenes : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroyScenes();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroyScenes)

static bool js_scene_Root_destroyWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroyWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderWindow *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_destroyWindow : Error processing arguments");
        cobj->destroyWindow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroyWindow)

static bool js_scene_Root_destroyWindows(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_destroyWindows : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroyWindows();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_destroyWindows)

static bool js_scene_Root_frameMove(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_frameMove : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_frameMove : Error processing arguments");
        cobj->frameMove(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_frameMove)

static bool js_scene_Root_getBatcher2D(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getBatcher2D : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::DrawBatch2D *result = cobj->getBatcher2D();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getBatcher2D : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getBatcher2D)

static bool js_scene_Root_getCumulativeTime(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getCumulativeTime : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getCumulativeTime();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getCumulativeTime : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getCumulativeTime)

static bool js_scene_Root_getCurWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getCurWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderWindow *result = cobj->getCurWindow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getCurWindow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getCurWindow)

static bool js_scene_Root_getDataPoolManager(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getDataPoolManager : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::DataPoolManager *result = cobj->getDataPoolManager();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getDataPoolManager : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getDataPoolManager)

static bool js_scene_Root_getDevice(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getDevice : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::Device *result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getDevice : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getDevice)

static bool js_scene_Root_getFixedFPS(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getFixedFPS : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getFixedFPS();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getFixedFPS : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getFixedFPS)

static bool js_scene_Root_getFps(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getFps : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getFps();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getFps : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getFps)

static bool js_scene_Root_getFrameCount(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getFrameCount : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getFrameCount();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getFrameCount : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getFrameCount)

static bool js_scene_Root_getFrameTime(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getFrameTime : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        float result = cobj->getFrameTime();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getFrameTime : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getFrameTime)

static bool js_scene_Root_getMainWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getMainWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderWindow *result = cobj->getMainWindow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getMainWindow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getMainWindow)

static bool js_scene_Root_getPipeline(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getPipeline : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::pipeline::RenderPipeline *result = cobj->getPipeline();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getPipeline : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getPipeline)

static bool js_scene_Root_getScenes(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getScenes : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::RenderScene *> &result = cobj->getScenes();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getScenes : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getScenes)

static bool js_scene_Root_getTempWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getTempWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::scene::RenderWindow *result = cobj->getTempWindow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getTempWindow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getTempWindow)

static bool js_scene_Root_getWindows(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_getWindows : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::RenderWindow *> &result = cobj->getWindows();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getWindows : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getWindows)

static bool js_scene_Root_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_initialize : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->initialize();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_initialize)

static bool js_scene_Root_isUsingDeferredPipeline(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_isUsingDeferredPipeline : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isUsingDeferredPipeline();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_isUsingDeferredPipeline : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_isUsingDeferredPipeline)

static bool js_scene_Root_onGlobalPipelineStateChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_onGlobalPipelineStateChanged : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->onGlobalPipelineStateChanged();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_onGlobalPipelineStateChanged)

static bool js_scene_Root_resetCumulativeTime(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_resetCumulativeTime : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->resetCumulativeTime();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_resetCumulativeTime)

static bool js_scene_Root_resize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_resize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_resize : Error processing arguments");
        cobj->resize(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Root_resize)

static bool js_scene_Root_setCurWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_setCurWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderWindow *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_setCurWindow : Error processing arguments");
        cobj->setCurWindow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_setCurWindow)

static bool js_scene_Root_setFixedFPS(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_setFixedFPS : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_setFixedFPS : Error processing arguments");
        cobj->setFixedFPS(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_setFixedFPS)

static bool js_scene_Root_setRenderPipeline(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_setRenderPipeline : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->setRenderPipeline();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_setRenderPipeline : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    if (argc == 1) {
        HolderType<cc::pipeline::RenderPipeline *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_setRenderPipeline : Error processing arguments");
        bool result = cobj->setRenderPipeline(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_setRenderPipeline : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_setRenderPipeline)

static bool js_scene_Root_setTempWindow(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Root_setTempWindow : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderWindow *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Root_setTempWindow : Error processing arguments");
        cobj->setTempWindow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Root_setTempWindow)

static bool js_scene_Root_getInstance_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Root *result = cc::Root::getInstance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Root_getInstance_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Root_getInstance_static)

SE_DECLARE_FINALIZE_FUNC(js_cc_Root_finalize)

static bool js_scene_Root_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    CC_UNUSED bool   ok   = true;
    const auto &     args = s.args();
    cc::gfx::Device *arg0 = nullptr;
    ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Root_constructor : Error processing arguments");
    cc::Root *cobj = JSB_ALLOC(cc::Root, arg0);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Root_constructor, __jsb_cc_Root_class, js_cc_Root_finalize)

static bool js_cc_Root_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Root>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::Root>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Root_finalize)

bool js_register_scene_Root(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Root", obj, nullptr, _SE(js_scene_Root_constructor));

    cls->defineFunction("activeWindow", _SE(js_scene_Root_activeWindow));
    cls->defineFunction("createCamera", _SE(js_scene_Root_createCamera));
    cls->defineFunction("createScene", _SE(js_scene_Root_createScene));
    cls->defineFunction("createWindow", _SE(js_scene_Root_createWindow));
    cls->defineFunction("destroy", _SE(js_scene_Root_destroy));
    cls->defineFunction("destroyLight", _SE(js_scene_Root_destroyLight));
    cls->defineFunction("destroyModel", _SE(js_scene_Root_destroyModel));
    cls->defineFunction("destroyScene", _SE(js_scene_Root_destroyScene));
    cls->defineFunction("destroyScenes", _SE(js_scene_Root_destroyScenes));
    cls->defineFunction("destroyWindow", _SE(js_scene_Root_destroyWindow));
    cls->defineFunction("destroyWindows", _SE(js_scene_Root_destroyWindows));
    cls->defineFunction("frameMove", _SE(js_scene_Root_frameMove));
    cls->defineFunction("getBatcher2D", _SE(js_scene_Root_getBatcher2D));
    cls->defineFunction("getCumulativeTime", _SE(js_scene_Root_getCumulativeTime));
    cls->defineFunction("getCurWindow", _SE(js_scene_Root_getCurWindow));
    cls->defineFunction("getDataPoolManager", _SE(js_scene_Root_getDataPoolManager));
    cls->defineFunction("getDevice", _SE(js_scene_Root_getDevice));
    cls->defineFunction("getFixedFPS", _SE(js_scene_Root_getFixedFPS));
    cls->defineFunction("getFps", _SE(js_scene_Root_getFps));
    cls->defineFunction("getFrameCount", _SE(js_scene_Root_getFrameCount));
    cls->defineFunction("getFrameTime", _SE(js_scene_Root_getFrameTime));
    cls->defineFunction("getMainWindow", _SE(js_scene_Root_getMainWindow));
    cls->defineFunction("getPipeline", _SE(js_scene_Root_getPipeline));
    cls->defineFunction("getScenes", _SE(js_scene_Root_getScenes));
    cls->defineFunction("getTempWindow", _SE(js_scene_Root_getTempWindow));
    cls->defineFunction("getWindows", _SE(js_scene_Root_getWindows));
    cls->defineFunction("initialize", _SE(js_scene_Root_initialize));
    cls->defineFunction("isUsingDeferredPipeline", _SE(js_scene_Root_isUsingDeferredPipeline));
    cls->defineFunction("onGlobalPipelineStateChanged", _SE(js_scene_Root_onGlobalPipelineStateChanged));
    cls->defineFunction("resetCumulativeTime", _SE(js_scene_Root_resetCumulativeTime));
    cls->defineFunction("resize", _SE(js_scene_Root_resize));
    cls->defineFunction("setCurWindow", _SE(js_scene_Root_setCurWindow));
    cls->defineFunction("setFixedFPS", _SE(js_scene_Root_setFixedFPS));
    cls->defineFunction("setRenderPipeline", _SE(js_scene_Root_setRenderPipeline));
    cls->defineFunction("setTempWindow", _SE(js_scene_Root_setTempWindow));
    cls->defineStaticFunction("getInstance", _SE(js_scene_Root_getInstance_static));
    cls->defineFinalizeFunction(_SE(js_cc_Root_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Root>(cls);

    __jsb_cc_Root_proto = cls->getProto();
    __jsb_cc_Root_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_Pass_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_Pass_class = nullptr; // NOLINT

static bool js_scene_Pass_beginChangeStatesSilently(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_beginChangeStatesSilently : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->beginChangeStatesSilently();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_beginChangeStatesSilently)

static bool js_scene_Pass_bindSampler(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_bindSampler : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false>       arg0 = {};
        HolderType<cc::gfx::Sampler *, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_bindSampler : Error processing arguments");
        cobj->bindSampler(arg0.value(), arg1.value());
        return true;
    }
    if (argc == 3) {
        HolderType<unsigned int, false>       arg0 = {};
        HolderType<cc::gfx::Sampler *, false> arg1 = {};
        HolderType<int, false>                arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_bindSampler : Error processing arguments");
        cobj->bindSampler(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_bindSampler)

static bool js_scene_Pass_bindTexture(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_bindTexture : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false>       arg0 = {};
        HolderType<cc::gfx::Texture *, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_bindTexture : Error processing arguments");
        cobj->bindTexture(arg0.value(), arg1.value());
        return true;
    }
    if (argc == 3) {
        HolderType<unsigned int, false>       arg0 = {};
        HolderType<cc::gfx::Texture *, false> arg1 = {};
        HolderType<int, false>                arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_bindTexture : Error processing arguments");
        cobj->bindTexture(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_bindTexture)

static bool js_scene_Pass_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_destroy)

static bool js_scene_Pass_endChangeStatesSilently(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_endChangeStatesSilently : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->endChangeStatesSilently();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_endChangeStatesSilently)

static bool js_scene_Pass_getBatchingScheme(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getBatchingScheme : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getBatchingScheme());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBatchingScheme : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBatchingScheme)

static bool js_scene_Pass_getBinding(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getBinding : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBinding : Error processing arguments");
        int32_t result = cobj->getBinding(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBinding : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBinding)

static bool js_scene_Pass_getBlendState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getBlendState : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::BlendState *result = cobj->getBlendState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBlendState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBlendState)

static bool js_scene_Pass_getBlocks(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getBlocks : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::IBlockRef> &result = cobj->getBlocks();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBlocks : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBlocks)

static bool js_scene_Pass_getDefines(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDefines : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::unordered_map<std::string, std::variant<int, float, bool, std::string>> &result = cobj->getDefines();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDefines : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDefines)

static bool js_scene_Pass_getDepthStencilState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDepthStencilState : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::DepthStencilState *result = cobj->getDepthStencilState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDepthStencilState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDepthStencilState)

static bool js_scene_Pass_getDescriptorSet(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDescriptorSet : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::DescriptorSet *result = cobj->getDescriptorSet();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDescriptorSet : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDescriptorSet)

static bool js_scene_Pass_getDevice(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDevice : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::Device *result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDevice : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDevice)

static bool js_scene_Pass_getDynamicState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDynamicState : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getDynamicState());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDynamicState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDynamicState)

static bool js_scene_Pass_getDynamics(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDynamics : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::unordered_map<unsigned int, cc::scene::PassDynamicsValue> &result = cobj->getDynamics();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDynamics : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDynamics)

static bool js_scene_Pass_getHandle(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getHandle : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHandle : Error processing arguments");
        unsigned int result = cobj->getHandle(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHandle : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    if (argc == 2) {
        HolderType<std::string, true>   arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHandle : Error processing arguments");
        unsigned int result = cobj->getHandle(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHandle : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    if (argc == 3) {
        HolderType<std::string, true>    arg0 = {};
        HolderType<unsigned int, false>  arg1 = {};
        HolderType<cc::gfx::Type, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHandle : Error processing arguments");
        unsigned int result = cobj->getHandle(arg0.value(), arg1.value(), arg2.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHandle : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getHandle)

static bool js_scene_Pass_getHash(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getHash : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        uint64_t result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getHash)

static bool js_scene_Pass_getLocalSetLayout(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getLocalSetLayout : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::DescriptorSetLayout *result = cobj->getLocalSetLayout();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getLocalSetLayout : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getLocalSetLayout)

static bool js_scene_Pass_getPassIndex(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPassIndex : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        int result = cobj->getPassIndex();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPassIndex : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPassIndex)

static bool js_scene_Pass_getPassInfoFull(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPassInfoFull : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::IPassInfoFull result = cobj->getPassInfoFull();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPassInfoFull : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPassInfoFull)

static bool js_scene_Pass_getPhase(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPhase : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        unsigned int result = cobj->getPhase();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPhase : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPhase)

static bool js_scene_Pass_getPipelineLayout(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPipelineLayout : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::PipelineLayout *result = cobj->getPipelineLayout();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPipelineLayout : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPipelineLayout)

static bool js_scene_Pass_getPrimitive(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPrimitive : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getPrimitive());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPrimitive : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPrimitive)

static bool js_scene_Pass_getPriority(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPriority : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getPriority());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPriority : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPriority)

static bool js_scene_Pass_getProgram(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getProgram : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::string &result = cobj->getProgram();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getProgram : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getProgram)

static bool js_scene_Pass_getProperties(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getProperties : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::unordered_map<std::string, cc::IPropertyInfo> &result = cobj->getProperties();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getProperties : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getProperties)

static bool js_scene_Pass_getPropertyIndex(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPropertyIndex : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        int result = cobj->getPropertyIndex();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPropertyIndex : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPropertyIndex)

static bool js_scene_Pass_getRasterizerState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getRasterizerState : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::RasterizerState *result = cobj->getRasterizerState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getRasterizerState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getRasterizerState)

static bool js_scene_Pass_getRoot(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getRoot : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::Root *result = cobj->getRoot();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getRoot : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getRoot)

static bool js_scene_Pass_getShaderInfo(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getShaderInfo : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::IProgramInfo *result = cobj->getShaderInfo();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getShaderInfo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getShaderInfo)

static bool js_scene_Pass_getShaderVariant(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getShaderVariant : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::scene::IMacroPatch>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getShaderVariant : Error processing arguments");
        cc::gfx::Shader *result = cobj->getShaderVariant(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getShaderVariant : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getShaderVariant)

static bool js_scene_Pass_getStage(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getStage : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getStage());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getStage : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getStage)

static bool js_scene_Pass_initPassFromTarget(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_initPassFromTarget : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 4) {
        HolderType<cc::scene::Pass *, false>            arg0 = {};
        HolderType<cc::gfx::DepthStencilState *, false> arg1 = {};
        HolderType<cc::gfx::BlendState *, false>        arg2 = {};
        HolderType<uint64_t, false>                     arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_initPassFromTarget : Error processing arguments");
        cobj->initPassFromTarget(arg0.value(), arg1.value(), arg2.value(), arg3.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_initPassFromTarget)

static bool js_scene_Pass_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::IPassInfoFull, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_initialize)

static bool js_scene_Pass_isRootBufferDirty(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_isRootBufferDirty : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->isRootBufferDirty();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_isRootBufferDirty : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_isRootBufferDirty)

static bool js_scene_Pass_overridePipelineStates(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_overridePipelineStates : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::IPassInfo, true>   arg0 = {};
        HolderType<cc::IPassStates, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_overridePipelineStates : Error processing arguments");
        cobj->overridePipelineStates(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_overridePipelineStates)

static bool js_scene_Pass_resetTexture(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_resetTexture : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_resetTexture : Error processing arguments");
        cobj->resetTexture(arg0.value());
        return true;
    }
    if (argc == 2) {
        HolderType<std::string, true> arg0 = {};
        HolderType<int, false>        arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_resetTexture : Error processing arguments");
        cobj->resetTexture(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_resetTexture)

static bool js_scene_Pass_resetTextures(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_resetTextures : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->resetTextures();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_resetTextures)

static bool js_scene_Pass_resetUBOs(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_resetUBOs : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->resetUBOs();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_resetUBOs)

static bool js_scene_Pass_resetUniform(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_resetUniform : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_resetUniform : Error processing arguments");
        cobj->resetUniform(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_resetUniform)

static bool js_scene_Pass_setDynamicState(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setDynamicState : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::gfx::DynamicStateFlagBit, false> arg0 = {};
        HolderType<int32_t, false>                      arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setDynamicState : Error processing arguments");
        cobj->setDynamicState(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setDynamicState)

static bool js_scene_Pass_setUniform(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setUniform : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false>                                                                                                                                                arg0 = {};
        HolderType<std::variant<std::monostate, float, int, cc::Vec2, cc::Vec3, cc::Vec4, cc::Color, cc::Mat3, cc::Mat4, cc::Quaternion, cc::TextureBase *, cc::gfx::Texture *>, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setUniform : Error processing arguments");
        cobj->setUniform(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setUniform)

static bool js_scene_Pass_setUniformArray(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setUniformArray : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<unsigned int, false>                                                                                                                                                             arg0 = {};
        HolderType<std::vector<std::variant<std::monostate, float, int, cc::Vec2, cc::Vec3, cc::Vec4, cc::Color, cc::Mat3, cc::Mat4, cc::Quaternion, cc::TextureBase *, cc::gfx::Texture *>>, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setUniformArray : Error processing arguments");
        cobj->setUniformArray(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setUniformArray)

static bool js_scene_Pass_tryCompile(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_tryCompile : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        bool result = cobj->tryCompile();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_tryCompile : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_tryCompile)

static bool js_scene_Pass_update(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_update : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_update)

static bool js_scene_Pass_getPassHash_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::scene::Pass *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPassHash_static : Error processing arguments");
        uint64_t result = cc::scene::Pass::getPassHash(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPassHash_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPassHash_static)

static bool js_scene_Pass_getPropertyTypeFromHandle_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPropertyTypeFromHandle_static : Error processing arguments");
        auto result = static_cast<int>(cc::scene::Pass::getPropertyTypeFromHandle(arg0.value()));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPropertyTypeFromHandle_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPropertyTypeFromHandle_static)

static bool js_scene_Pass_getOffsetFromHandle_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getOffsetFromHandle_static : Error processing arguments");
        unsigned int result = cc::scene::Pass::getOffsetFromHandle(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getOffsetFromHandle_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getOffsetFromHandle_static)

static bool js_scene_Pass_getBindingFromHandle_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBindingFromHandle_static : Error processing arguments");
        unsigned int result = cc::scene::Pass::getBindingFromHandle(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBindingFromHandle_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBindingFromHandle_static)

static bool js_scene_Pass_getTypeFromHandle_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getTypeFromHandle_static : Error processing arguments");
        auto result = static_cast<int>(cc::scene::Pass::getTypeFromHandle(arg0.value()));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getTypeFromHandle_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getTypeFromHandle_static)

static bool js_scene_Pass_fillPipelineInfo_static(se::State &s) // NOLINT(readability-identifier-naming)
{
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 2) {
        HolderType<cc::scene::Pass *, false> arg0 = {};
        HolderType<cc::IPassStates, true>    arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        ok &= sevalue_to_native(args[1], &arg1, nullptr);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_fillPipelineInfo_static : Error processing arguments");
        cc::scene::Pass::fillPipelineInfo(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_fillPipelineInfo_static)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Pass_finalize)

static bool js_scene_Pass_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::Pass *cobj = JSB_ALLOC(cc::scene::Pass);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Pass_constructor, __jsb_cc_scene_Pass_class, js_cc_scene_Pass_finalize)

static bool js_cc_scene_Pass_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Pass>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Pass_finalize)

bool js_register_scene_Pass(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("Pass", obj, nullptr, _SE(js_scene_Pass_constructor));

    cls->defineFunction("beginChangeStatesSilently", _SE(js_scene_Pass_beginChangeStatesSilently));
    cls->defineFunction("bindSampler", _SE(js_scene_Pass_bindSampler));
    cls->defineFunction("bindTexture", _SE(js_scene_Pass_bindTexture));
    cls->defineFunction("destroy", _SE(js_scene_Pass_destroy));
    cls->defineFunction("endChangeStatesSilently", _SE(js_scene_Pass_endChangeStatesSilently));
    cls->defineFunction("getBatchingScheme", _SE(js_scene_Pass_getBatchingScheme));
    cls->defineFunction("getBinding", _SE(js_scene_Pass_getBinding));
    cls->defineFunction("getBlendState", _SE(js_scene_Pass_getBlendState));
    cls->defineFunction("getBlocks", _SE(js_scene_Pass_getBlocks));
    cls->defineFunction("getDefines", _SE(js_scene_Pass_getDefines));
    cls->defineFunction("getDepthStencilState", _SE(js_scene_Pass_getDepthStencilState));
    cls->defineFunction("getDescriptorSet", _SE(js_scene_Pass_getDescriptorSet));
    cls->defineFunction("getDevice", _SE(js_scene_Pass_getDevice));
    cls->defineFunction("getDynamicState", _SE(js_scene_Pass_getDynamicState));
    cls->defineFunction("getDynamics", _SE(js_scene_Pass_getDynamics));
    cls->defineFunction("getHandle", _SE(js_scene_Pass_getHandle));
    cls->defineFunction("getHash", _SE(js_scene_Pass_getHash));
    cls->defineFunction("getLocalSetLayout", _SE(js_scene_Pass_getLocalSetLayout));
    cls->defineFunction("getPassIndex", _SE(js_scene_Pass_getPassIndex));
    cls->defineFunction("getPassInfoFull", _SE(js_scene_Pass_getPassInfoFull));
    cls->defineFunction("getPhase", _SE(js_scene_Pass_getPhase));
    cls->defineFunction("getPipelineLayout", _SE(js_scene_Pass_getPipelineLayout));
    cls->defineFunction("getPrimitive", _SE(js_scene_Pass_getPrimitive));
    cls->defineFunction("getPriority", _SE(js_scene_Pass_getPriority));
    cls->defineFunction("getProgram", _SE(js_scene_Pass_getProgram));
    cls->defineFunction("getProperties", _SE(js_scene_Pass_getProperties));
    cls->defineFunction("getPropertyIndex", _SE(js_scene_Pass_getPropertyIndex));
    cls->defineFunction("getRasterizerState", _SE(js_scene_Pass_getRasterizerState));
    cls->defineFunction("getRoot", _SE(js_scene_Pass_getRoot));
    cls->defineFunction("getShaderInfo", _SE(js_scene_Pass_getShaderInfo));
    cls->defineFunction("getShaderVariant", _SE(js_scene_Pass_getShaderVariant));
    cls->defineFunction("getStage", _SE(js_scene_Pass_getStage));
    cls->defineFunction("initPassFromTarget", _SE(js_scene_Pass_initPassFromTarget));
    cls->defineFunction("initialize", _SE(js_scene_Pass_initialize));
    cls->defineFunction("isRootBufferDirty", _SE(js_scene_Pass_isRootBufferDirty));
    cls->defineFunction("overridePipelineStates", _SE(js_scene_Pass_overridePipelineStates));
    cls->defineFunction("resetTexture", _SE(js_scene_Pass_resetTexture));
    cls->defineFunction("resetTextures", _SE(js_scene_Pass_resetTextures));
    cls->defineFunction("resetUBOs", _SE(js_scene_Pass_resetUBOs));
    cls->defineFunction("resetUniform", _SE(js_scene_Pass_resetUniform));
    cls->defineFunction("setDynamicState", _SE(js_scene_Pass_setDynamicState));
    cls->defineFunction("setUniform", _SE(js_scene_Pass_setUniform));
    cls->defineFunction("setUniformArray", _SE(js_scene_Pass_setUniformArray));
    cls->defineFunction("tryCompile", _SE(js_scene_Pass_tryCompile));
    cls->defineFunction("update", _SE(js_scene_Pass_update));
    cls->defineStaticFunction("getPassHash", _SE(js_scene_Pass_getPassHash_static));
    cls->defineStaticFunction("getPropertyTypeFromHandle", _SE(js_scene_Pass_getPropertyTypeFromHandle_static));
    cls->defineStaticFunction("getOffsetFromHandle", _SE(js_scene_Pass_getOffsetFromHandle_static));
    cls->defineStaticFunction("getBindingFromHandle", _SE(js_scene_Pass_getBindingFromHandle_static));
    cls->defineStaticFunction("getTypeFromHandle", _SE(js_scene_Pass_getTypeFromHandle_static));
    cls->defineStaticFunction("fillPipelineInfo", _SE(js_scene_Pass_fillPipelineInfo_static));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Pass_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Pass>(cls);

    __jsb_cc_scene_Pass_proto = cls->getProto();
    __jsb_cc_scene_Pass_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object *__jsb_cc_scene_SubModel_proto = nullptr; // NOLINT
se::Class * __jsb_cc_scene_SubModel_class = nullptr; // NOLINT

static bool js_scene_SubModel_destroy(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_destroy : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_destroy)

static bool js_scene_SubModel_getPass(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getPass : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPass : Error processing arguments");
        cc::scene::Pass *result = cobj->getPass(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPass : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getPass)

static bool js_scene_SubModel_getPasses(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getPasses : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::Pass *> &result = cobj->getPasses();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPasses : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getPasses)

static bool js_scene_SubModel_getPatches(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getPatches : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::scene::IMacroPatch> &result = cobj->getPatches();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPatches : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getPatches)

static bool js_scene_SubModel_getPlanarInstanceShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getPlanarInstanceShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::Shader *result = cobj->getPlanarInstanceShader();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPlanarInstanceShader : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getPlanarInstanceShader)

static bool js_scene_SubModel_getPlanarShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getPlanarShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        cc::gfx::Shader *result = cobj->getPlanarShader();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPlanarShader : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getPlanarShader)

static bool js_scene_SubModel_getPriority(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getPriority : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getPriority());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getPriority : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getPriority)

static bool js_scene_SubModel_getShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getShader : Error processing arguments");
        cc::gfx::Shader *result = cobj->getShader(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getShader : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getShader)

static bool js_scene_SubModel_getShaders(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_getShaders : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 0) {
        const std::vector<cc::gfx::Shader *> &result = cobj->getShaders();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_getShaders : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_getShaders)

static bool js_scene_SubModel_initPlanarShadowInstanceShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_initPlanarShadowInstanceShader : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->initPlanarShadowInstanceShader();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_initPlanarShadowInstanceShader)

static bool js_scene_SubModel_initPlanarShadowShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_initPlanarShadowShader : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->initPlanarShadowShader();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_initPlanarShadowShader)

static bool js_scene_SubModel_initialize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_initialize : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 3) {
        HolderType<cc::RenderingSubMesh *, false>             arg0 = {};
        HolderType<std::vector<cc::scene::Pass *>, true>      arg1 = {};
        HolderType<std::vector<cc::scene::IMacroPatch>, true> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_initialize : Error processing arguments");
        cobj->initialize(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_initialize)

static bool js_scene_SubModel_onMacroPatchesStateChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_onMacroPatchesStateChanged : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::scene::IMacroPatch>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_onMacroPatchesStateChanged : Error processing arguments");
        cobj->onMacroPatchesStateChanged(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_onMacroPatchesStateChanged)

static bool js_scene_SubModel_onPipelineStateChanged(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_onPipelineStateChanged : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->onPipelineStateChanged();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_onPipelineStateChanged)

static bool js_scene_SubModel_setDescriptorSet(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setDescriptorSet : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::DescriptorSet *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setDescriptorSet : Error processing arguments");
        cobj->setDescriptorSet(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setDescriptorSet)

static bool js_scene_SubModel_setInputAssembler(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setInputAssembler : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::InputAssembler *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setInputAssembler : Error processing arguments");
        cobj->setInputAssembler(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setInputAssembler)

static bool js_scene_SubModel_setPasses(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setPasses : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::scene::Pass *>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setPasses : Error processing arguments");
        cobj->setPasses(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setPasses)

static bool js_scene_SubModel_setPlanarInstanceShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setPlanarInstanceShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::Shader *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setPlanarInstanceShader : Error processing arguments");
        cobj->setPlanarInstanceShader(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setPlanarInstanceShader)

static bool js_scene_SubModel_setPlanarShader(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setPlanarShader : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::gfx::Shader *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setPlanarShader : Error processing arguments");
        cobj->setPlanarShader(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setPlanarShader)

static bool js_scene_SubModel_setPriority(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setPriority : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::pipeline::RenderPriority, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setPriority : Error processing arguments");
        cobj->setPriority(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setPriority)

static bool js_scene_SubModel_setShaders(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setShaders : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<std::vector<cc::gfx::Shader *>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setShaders : Error processing arguments");
        cobj->setShaders(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setShaders)

static bool js_scene_SubModel_setSubMesh(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_setSubMesh : Invalid Native Object");
    const auto &   args = s.args();
    size_t         argc = args.size();
    CC_UNUSED bool ok   = true;
    if (argc == 1) {
        HolderType<cc::RenderingSubMesh *, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SubModel_setSubMesh : Error processing arguments");
        cobj->setSubMesh(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_setSubMesh)

static bool js_scene_SubModel_update(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_update : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_SubModel_finalize)

static bool js_scene_SubModel_constructor(se::State &s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::scene::SubModel *cobj = JSB_ALLOC(cc::scene::SubModel);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_SubModel_constructor, __jsb_cc_scene_SubModel_class, js_cc_scene_SubModel_finalize)

static bool js_cc_scene_SubModel_finalize(se::State &s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::SubModel>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto *cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_SubModel_finalize)

bool js_register_scene_SubModel(se::Object *obj) // NOLINT(readability-identifier-naming)
{
    auto *cls = se::Class::create("SubModel", obj, nullptr, _SE(js_scene_SubModel_constructor));

    cls->defineFunction("destroy", _SE(js_scene_SubModel_destroy));
    cls->defineFunction("getPass", _SE(js_scene_SubModel_getPass));
    cls->defineFunction("getPasses", _SE(js_scene_SubModel_getPasses));
    cls->defineFunction("getPatches", _SE(js_scene_SubModel_getPatches));
    cls->defineFunction("getPlanarInstanceShader", _SE(js_scene_SubModel_getPlanarInstanceShader));
    cls->defineFunction("getPlanarShader", _SE(js_scene_SubModel_getPlanarShader));
    cls->defineFunction("getPriority", _SE(js_scene_SubModel_getPriority));
    cls->defineFunction("getShader", _SE(js_scene_SubModel_getShader));
    cls->defineFunction("getShaders", _SE(js_scene_SubModel_getShaders));
    cls->defineFunction("initPlanarShadowInstanceShader", _SE(js_scene_SubModel_initPlanarShadowInstanceShader));
    cls->defineFunction("initPlanarShadowShader", _SE(js_scene_SubModel_initPlanarShadowShader));
    cls->defineFunction("initialize", _SE(js_scene_SubModel_initialize));
    cls->defineFunction("onMacroPatchesStateChanged", _SE(js_scene_SubModel_onMacroPatchesStateChanged));
    cls->defineFunction("onPipelineStateChanged", _SE(js_scene_SubModel_onPipelineStateChanged));
    cls->defineFunction("setDescriptorSet", _SE(js_scene_SubModel_setDescriptorSet));
    cls->defineFunction("setInputAssembler", _SE(js_scene_SubModel_setInputAssembler));
    cls->defineFunction("setPasses", _SE(js_scene_SubModel_setPasses));
    cls->defineFunction("setPlanarInstanceShader", _SE(js_scene_SubModel_setPlanarInstanceShader));
    cls->defineFunction("setPlanarShader", _SE(js_scene_SubModel_setPlanarShader));
    cls->defineFunction("setPriority", _SE(js_scene_SubModel_setPriority));
    cls->defineFunction("setShaders", _SE(js_scene_SubModel_setShaders));
    cls->defineFunction("setSubMesh", _SE(js_scene_SubModel_setSubMesh));
    cls->defineFunction("update", _SE(js_scene_SubModel_update));
    cls->defineFinalizeFunction(_SE(js_cc_scene_SubModel_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::SubModel>(cls);

    __jsb_cc_scene_SubModel_proto = cls->getProto();
    __jsb_cc_scene_SubModel_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
bool register_all_scene(se::Object *obj) // NOLINT
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("ns", &nsVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("ns", nsVal);
    }
    se::Object *ns = nsVal.toObject();

    js_register_scene_RenderScene(ns);
    js_register_scene_IRenderSceneInfo(ns);
    js_register_scene_Light(ns);
    js_register_scene_DirectionalLight(ns);
    js_register_scene_Fog(ns);
    js_register_scene_ShadowInfo(ns);
    js_register_scene_DrawBatch2D(ns);
    js_register_scene_SphereLight(ns);
    js_register_scene_IPassStates(ns);
    js_register_scene_IPassInfo(ns);
    js_register_scene_RenderWindow(ns);
    js_register_scene_Shadow(ns);
    js_register_scene_SubModel(ns);
    js_register_scene_AmbientInfo(ns);
    js_register_scene_IPassInfoFull(ns);
    js_register_scene_Ambient(ns);
    js_register_scene_IRenderWindowInfo(ns);
    js_register_scene_Model(ns);
    js_register_scene_Root(ns);
    js_register_scene_Camera(ns);
    js_register_scene_Pass(ns);
    js_register_scene_Skybox(ns);
    js_register_scene_SpotLight(ns);
    return true;
}
