#include "cocos/bindings/auto/jsb_assets_auto.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "core/assets/AssetsModuleHeader.h"
#include "3d/assets/Mesh.h"
#include "3d/assets/Morph.h"
#include "3d/assets/MorphRendering.h"
#include "3d/assets/Skeleton.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cc_BoundingBox_proto = nullptr; // NOLINT
se::Class* __jsb_cc_BoundingBox_class = nullptr;  // NOLINT

static bool js_assets_BoundingBox_get_min(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::BoundingBox>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_BoundingBox_get_min : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->min, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->min, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_BoundingBox_get_min)

static bool js_assets_BoundingBox_set_min(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::BoundingBox>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_BoundingBox_set_min : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->min, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_BoundingBox_set_min : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_BoundingBox_set_min)

static bool js_assets_BoundingBox_get_max(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::BoundingBox>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_BoundingBox_get_max : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->max, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->max, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_BoundingBox_get_max)

static bool js_assets_BoundingBox_set_max(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::BoundingBox>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_BoundingBox_set_max : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->max, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_BoundingBox_set_max : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_BoundingBox_set_max)


template<>
bool sevalue_to_native(const se::Value &from, cc::BoundingBox * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::BoundingBox*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("min", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->min), ctx);
    }
    json->getProperty("max", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->max), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_BoundingBox_finalize)

static bool js_assets_BoundingBox_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::BoundingBox* cobj = JSB_ALLOC(cc::BoundingBox);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::BoundingBox* cobj = JSB_ALLOC(cc::BoundingBox);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::BoundingBox* cobj = JSB_ALLOC(cc::BoundingBox);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->min), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->max), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_BoundingBox_constructor, __jsb_cc_BoundingBox_class, js_cc_BoundingBox_finalize)



static bool js_cc_BoundingBox_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::BoundingBox>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::BoundingBox>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_BoundingBox_finalize)

bool js_register_assets_BoundingBox(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("BoundingBox", obj, nullptr, _SE(js_assets_BoundingBox_constructor));

    cls->defineProperty("min", _SE(js_assets_BoundingBox_get_min), _SE(js_assets_BoundingBox_set_min));
    cls->defineProperty("max", _SE(js_assets_BoundingBox_get_max), _SE(js_assets_BoundingBox_set_max));
    cls->defineFinalizeFunction(_SE(js_cc_BoundingBox_finalize));
    cls->install();
    JSBClassType::registerClass<cc::BoundingBox>(cls);

    __jsb_cc_BoundingBox_proto = cls->getProto();
    __jsb_cc_BoundingBox_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_VertexIdChannel_proto = nullptr; // NOLINT
se::Class* __jsb_cc_VertexIdChannel_class = nullptr;  // NOLINT

static bool js_assets_VertexIdChannel_get_stream(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::VertexIdChannel>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_VertexIdChannel_get_stream : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stream, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stream, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_VertexIdChannel_get_stream)

static bool js_assets_VertexIdChannel_set_stream(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::VertexIdChannel>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_VertexIdChannel_set_stream : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stream, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_VertexIdChannel_set_stream : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_VertexIdChannel_set_stream)

static bool js_assets_VertexIdChannel_get_index(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::VertexIdChannel>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_VertexIdChannel_get_index : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->index, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->index, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_VertexIdChannel_get_index)

static bool js_assets_VertexIdChannel_set_index(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::VertexIdChannel>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_VertexIdChannel_set_index : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->index, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_VertexIdChannel_set_index : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_VertexIdChannel_set_index)


template<>
bool sevalue_to_native(const se::Value &from, cc::VertexIdChannel * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::VertexIdChannel*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("stream", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stream), ctx);
    }
    json->getProperty("index", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->index), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_VertexIdChannel_finalize)

static bool js_assets_VertexIdChannel_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::VertexIdChannel* cobj = JSB_ALLOC(cc::VertexIdChannel);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::VertexIdChannel* cobj = JSB_ALLOC(cc::VertexIdChannel);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::VertexIdChannel* cobj = JSB_ALLOC(cc::VertexIdChannel);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->stream), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->index), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_VertexIdChannel_constructor, __jsb_cc_VertexIdChannel_class, js_cc_VertexIdChannel_finalize)



static bool js_cc_VertexIdChannel_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::VertexIdChannel>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::VertexIdChannel>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_VertexIdChannel_finalize)

bool js_register_assets_VertexIdChannel(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("VertexIdChannel", obj, nullptr, _SE(js_assets_VertexIdChannel_constructor));

    cls->defineProperty("stream", _SE(js_assets_VertexIdChannel_get_stream), _SE(js_assets_VertexIdChannel_set_stream));
    cls->defineProperty("index", _SE(js_assets_VertexIdChannel_get_index), _SE(js_assets_VertexIdChannel_set_index));
    cls->defineFinalizeFunction(_SE(js_cc_VertexIdChannel_finalize));
    cls->install();
    JSBClassType::registerClass<cc::VertexIdChannel>(cls);

    __jsb_cc_VertexIdChannel_proto = cls->getProto();
    __jsb_cc_VertexIdChannel_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Asset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Asset_class = nullptr;  // NOLINT

static bool js_assets_Asset_addRef(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_addRef : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->addRef();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_addRef)

static bool js_assets_Asset_createNode(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_createNode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<void (cc::Error, cc::Node *)>, true> arg0 = {};
        do {
            if (args[0].isObject() && args[0].toObject()->isFunction())
            {
                se::Value jsThis(s.thisObject());
                se::Value jsFunc(args[0]);
                jsThis.toObject()->attachObject(jsFunc.toObject());
                auto lambda = [=](cc::Error larg0, cc::Node* larg1) -> void {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
        
                    CC_UNUSED bool ok = true;
                    se::ValueArray args;
                    args.resize(2);
                    ok &= nativevalue_to_se(larg0, args[0], nullptr /*ctx*/);
                    ok &= nativevalue_to_se(larg1, args[1], nullptr /*ctx*/);
                    se::Value rval;
                    se::Object* thisObj = jsThis.isObject() ? jsThis.toObject() : nullptr;
                    se::Object* funcObj = jsFunc.toObject();
                    bool succeed = funcObj->call(args, thisObj, &rval);
                    if (!succeed) {
                        se::ScriptEngine::getInstance()->clearException();
                    }
                };
                arg0.data = lambda;
            }
            else
            {
                arg0.data = nullptr;
            }
        } while(false)
        ;
        SE_PRECONDITION2(ok, false, "js_assets_Asset_createNode : Error processing arguments");
        cobj->createNode(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_createNode)

static bool js_assets_Asset_decRef(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_decRef : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->decRef();
        return true;
    }
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Asset_decRef : Error processing arguments");
        cobj->decRef(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_decRef)

static bool js_assets_Asset_deserialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_deserialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<std::any, true> arg0 = {};
        HolderType<std::any, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Asset_deserialize : Error processing arguments");
        cobj->deserialize(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_deserialize)

static bool js_assets_Asset_destroy(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->destroy();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_destroy : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_destroy)

static bool js_assets_Asset_getNativeAsset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_getNativeAsset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::any result = cobj->getNativeAsset();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_getNativeAsset : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_getNativeAsset)

static bool js_assets_Asset_getNativeDep(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_getNativeDep : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::NativeDep result = cobj->getNativeDep();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_getNativeDep : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_getNativeDep)

static bool js_assets_Asset_getNativeUrl(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_getNativeUrl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getNativeUrl();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_getNativeUrl : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_Asset_getNativeUrl)

static bool js_assets_Asset_getRefCount(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_getRefCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getRefCount();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_getRefCount : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_getRefCount)

static bool js_assets_Asset_getUuid(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_getUuid : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::string& result = cobj->getUuid();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_getUuid : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_Asset_getUuid)

static bool js_assets_Asset_initDefault(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_initDefault : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::optional<std::string>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Asset_initDefault : Error processing arguments");
        cobj->initDefault(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_initDefault)

static bool js_assets_Asset_isDefault(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_isDefault : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isDefault();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_isDefault : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_isDefault)

static bool js_assets_Asset_onLoaded(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_onLoaded : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onLoaded();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_onLoaded)

static bool js_assets_Asset_serialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_serialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::any, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Asset_serialize : Error processing arguments");
        std::any result = cobj->serialize(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_serialize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_serialize)

static bool js_assets_Asset_setNativeAsset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_setNativeAsset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::any, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Asset_setNativeAsset : Error processing arguments");
        cobj->setNativeAsset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_setNativeAsset)

static bool js_assets_Asset_setUuid(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_setUuid : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Asset_setUuid : Error processing arguments");
        cobj->setUuid(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_assets_Asset_setUuid)

static bool js_assets_Asset_toString(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_toString : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->toString();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_toString : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_toString)

static bool js_assets_Asset_validate(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Asset_validate : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->validate();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Asset_validate : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Asset_validate)


static bool js_cc_Asset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Asset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Asset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Asset_finalize)

bool js_register_assets_Asset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Asset", obj, nullptr, nullptr);

    cls->defineProperty("_uuid", _SE(js_assets_Asset_getUuid), _SE(js_assets_Asset_setUuid));
    cls->defineProperty("nativeUrl", _SE(js_assets_Asset_getNativeUrl), nullptr);
    cls->defineFunction("addRef", _SE(js_assets_Asset_addRef));
    cls->defineFunction("createNode", _SE(js_assets_Asset_createNode));
    cls->defineFunction("decRef", _SE(js_assets_Asset_decRef));
    cls->defineFunction("deserialize", _SE(js_assets_Asset_deserialize));
    cls->defineFunction("destroy", _SE(js_assets_Asset_destroy));
    cls->defineFunction("getNativeAsset", _SE(js_assets_Asset_getNativeAsset));
    cls->defineFunction("getNativeDep", _SE(js_assets_Asset_getNativeDep));
    cls->defineFunction("getRefCount", _SE(js_assets_Asset_getRefCount));
    cls->defineFunction("initDefault", _SE(js_assets_Asset_initDefault));
    cls->defineFunction("isDefault", _SE(js_assets_Asset_isDefault));
    cls->defineFunction("onLoaded", _SE(js_assets_Asset_onLoaded));
    cls->defineFunction("serialize", _SE(js_assets_Asset_serialize));
    cls->defineFunction("setNativeAsset", _SE(js_assets_Asset_setNativeAsset));
    cls->defineFunction("toString", _SE(js_assets_Asset_toString));
    cls->defineFunction("validate", _SE(js_assets_Asset_validate));
    cls->defineFinalizeFunction(_SE(js_cc_Asset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Asset>(cls);

    __jsb_cc_Asset_proto = cls->getProto();
    __jsb_cc_Asset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_BufferAsset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_BufferAsset_class = nullptr;  // NOLINT

static bool js_assets_BufferAsset_getBuffer(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::BufferAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_BufferAsset_getBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::shared_ptr<cc::ArrayBuffer>& result = cobj->getBuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_BufferAsset_getBuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_BufferAsset_getBuffer)


static bool js_cc_BufferAsset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::BufferAsset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::BufferAsset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_BufferAsset_finalize)

bool js_register_assets_BufferAsset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("BufferAsset", obj, __jsb_cc_Asset_proto, nullptr);

    cls->defineFunction("getBuffer", _SE(js_assets_BufferAsset_getBuffer));
    cls->defineFinalizeFunction(_SE(js_cc_BufferAsset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::BufferAsset>(cls);

    __jsb_cc_BufferAsset_proto = cls->getProto();
    __jsb_cc_BufferAsset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_TextureBase_proto = nullptr; // NOLINT
se::Class* __jsb_cc_TextureBase_class = nullptr;  // NOLINT

static bool js_assets_TextureBase_getAnisotropy(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getAnisotropy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int32_t result = cobj->getAnisotropy();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getAnisotropy : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getAnisotropy)

static bool js_assets_TextureBase_getGFXSampler(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getGFXSampler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Sampler* result = cobj->getGFXSampler();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getGFXSampler : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getGFXSampler)

static bool js_assets_TextureBase_getGFXTexture(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getGFXTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Texture* result = cobj->getGFXTexture();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getGFXTexture : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getGFXTexture)

static bool js_assets_TextureBase_getHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        uint64_t result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getHash)

static bool js_assets_TextureBase_getHeight(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getHeight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getHeight)

static bool js_assets_TextureBase_getId(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getId : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::string& result = cobj->getId();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getId : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getId)

static bool js_assets_TextureBase_getPixelFormat(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getPixelFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getPixelFormat());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getPixelFormat : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getPixelFormat)

static bool js_assets_TextureBase_getSamplerHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getSamplerHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        uint64_t result = cobj->getSamplerHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getSamplerHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getSamplerHash)

static bool js_assets_TextureBase_getWidth(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_getWidth : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_getWidth)

static bool js_assets_TextureBase_isCompressed(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_isCompressed : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isCompressed();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_isCompressed : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_isCompressed)

static bool js_assets_TextureBase_setAnisotropy(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_setAnisotropy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_setAnisotropy : Error processing arguments");
        cobj->setAnisotropy(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_setAnisotropy)

static bool js_assets_TextureBase_setFilters(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_setFilters : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<cc::Filter, false> arg0 = {};
        HolderType<cc::Filter, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_setFilters : Error processing arguments");
        cobj->setFilters(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_setFilters)

static bool js_assets_TextureBase_setMipFilter(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_setMipFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Filter, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_setMipFilter : Error processing arguments");
        cobj->setMipFilter(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_setMipFilter)

static bool js_assets_TextureBase_setWrapMode(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureBase_setWrapMode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<cc::WrapMode, false> arg0 = {};
        HolderType<cc::WrapMode, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_setWrapMode : Error processing arguments");
        cobj->setWrapMode(arg0.value(), arg1.value());
        return true;
    }
    if (argc == 3) {
        HolderType<cc::WrapMode, false> arg0 = {};
        HolderType<cc::WrapMode, false> arg1 = {};
        HolderType<cc::WrapMode, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureBase_setWrapMode : Error processing arguments");
        cobj->setWrapMode(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_assets_TextureBase_setWrapMode)


static bool js_cc_TextureBase_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::TextureBase>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::TextureBase>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_TextureBase_finalize)

bool js_register_assets_TextureBase(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("TextureBase", obj, __jsb_cc_Asset_proto, nullptr);

    cls->defineFunction("getAnisotropy", _SE(js_assets_TextureBase_getAnisotropy));
    cls->defineFunction("getGFXSampler", _SE(js_assets_TextureBase_getGFXSampler));
    cls->defineFunction("getGFXTexture", _SE(js_assets_TextureBase_getGFXTexture));
    cls->defineFunction("getHash", _SE(js_assets_TextureBase_getHash));
    cls->defineFunction("getHeight", _SE(js_assets_TextureBase_getHeight));
    cls->defineFunction("getId", _SE(js_assets_TextureBase_getId));
    cls->defineFunction("getPixelFormat", _SE(js_assets_TextureBase_getPixelFormat));
    cls->defineFunction("getSamplerHash", _SE(js_assets_TextureBase_getSamplerHash));
    cls->defineFunction("getWidth", _SE(js_assets_TextureBase_getWidth));
    cls->defineFunction("isCompressed", _SE(js_assets_TextureBase_isCompressed));
    cls->defineFunction("setAnisotropy", _SE(js_assets_TextureBase_setAnisotropy));
    cls->defineFunction("setFilters", _SE(js_assets_TextureBase_setFilters));
    cls->defineFunction("setMipFilter", _SE(js_assets_TextureBase_setMipFilter));
    cls->defineFunction("setWrapMode", _SE(js_assets_TextureBase_setWrapMode));
    cls->defineFinalizeFunction(_SE(js_cc_TextureBase_finalize));
    cls->install();
    JSBClassType::registerClass<cc::TextureBase>(cls);

    __jsb_cc_TextureBase_proto = cls->getProto();
    __jsb_cc_TextureBase_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IGeometricInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IGeometricInfo_class = nullptr;  // NOLINT

static bool js_assets_IGeometricInfo_get_positions(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_get_positions : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->positions, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->positions, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IGeometricInfo_get_positions)

static bool js_assets_IGeometricInfo_set_positions(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_set_positions : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->positions, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IGeometricInfo_set_positions : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IGeometricInfo_set_positions)

static bool js_assets_IGeometricInfo_get_indices(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_get_indices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->indices, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->indices, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IGeometricInfo_get_indices)

static bool js_assets_IGeometricInfo_set_indices(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_set_indices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->indices, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IGeometricInfo_set_indices : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IGeometricInfo_set_indices)

static bool js_assets_IGeometricInfo_get_doubleSided(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_get_doubleSided : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->doubleSided, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->doubleSided, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IGeometricInfo_get_doubleSided)

static bool js_assets_IGeometricInfo_set_doubleSided(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_set_doubleSided : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->doubleSided, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IGeometricInfo_set_doubleSided : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IGeometricInfo_set_doubleSided)

static bool js_assets_IGeometricInfo_get_boundingBox(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_get_boundingBox : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->boundingBox, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->boundingBox, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IGeometricInfo_get_boundingBox)

static bool js_assets_IGeometricInfo_set_boundingBox(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IGeometricInfo_set_boundingBox : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->boundingBox, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IGeometricInfo_set_boundingBox : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IGeometricInfo_set_boundingBox)


template<>
bool sevalue_to_native(const se::Value &from, cc::IGeometricInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IGeometricInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("positions", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->positions), ctx);
    }
    json->getProperty("indices", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->indices), ctx);
    }
    json->getProperty("doubleSided", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->doubleSided), ctx);
    }
    json->getProperty("boundingBox", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->boundingBox), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IGeometricInfo_finalize)

static bool js_assets_IGeometricInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IGeometricInfo* cobj = JSB_ALLOC(cc::IGeometricInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IGeometricInfo* cobj = JSB_ALLOC(cc::IGeometricInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IGeometricInfo* cobj = JSB_ALLOC(cc::IGeometricInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->positions), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->indices), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->doubleSided), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->boundingBox), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IGeometricInfo_constructor, __jsb_cc_IGeometricInfo_class, js_cc_IGeometricInfo_finalize)



static bool js_cc_IGeometricInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IGeometricInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IGeometricInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IGeometricInfo_finalize)

bool js_register_assets_IGeometricInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IGeometricInfo", obj, nullptr, _SE(js_assets_IGeometricInfo_constructor));

    cls->defineProperty("positions", _SE(js_assets_IGeometricInfo_get_positions), _SE(js_assets_IGeometricInfo_set_positions));
    cls->defineProperty("indices", _SE(js_assets_IGeometricInfo_get_indices), _SE(js_assets_IGeometricInfo_set_indices));
    cls->defineProperty("doubleSided", _SE(js_assets_IGeometricInfo_get_doubleSided), _SE(js_assets_IGeometricInfo_set_doubleSided));
    cls->defineProperty("boundingBox", _SE(js_assets_IGeometricInfo_get_boundingBox), _SE(js_assets_IGeometricInfo_set_boundingBox));
    cls->defineFinalizeFunction(_SE(js_cc_IGeometricInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IGeometricInfo>(cls);

    __jsb_cc_IGeometricInfo_proto = cls->getProto();
    __jsb_cc_IGeometricInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IFlatBuffer_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IFlatBuffer_class = nullptr;  // NOLINT

static bool js_assets_IFlatBuffer_get_stride(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IFlatBuffer_get_stride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stride, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stride, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IFlatBuffer_get_stride)

static bool js_assets_IFlatBuffer_set_stride(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IFlatBuffer_set_stride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stride, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IFlatBuffer_set_stride : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IFlatBuffer_set_stride)

static bool js_assets_IFlatBuffer_get_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IFlatBuffer_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->count, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IFlatBuffer_get_count)

static bool js_assets_IFlatBuffer_set_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IFlatBuffer_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IFlatBuffer_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IFlatBuffer_set_count)

static bool js_assets_IFlatBuffer_get_buffer(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IFlatBuffer_get_buffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->buffer, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->buffer, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IFlatBuffer_get_buffer)

static bool js_assets_IFlatBuffer_set_buffer(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IFlatBuffer_set_buffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->buffer, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IFlatBuffer_set_buffer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IFlatBuffer_set_buffer)


template<>
bool sevalue_to_native(const se::Value &from, cc::IFlatBuffer * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IFlatBuffer*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("stride", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stride), ctx);
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count), ctx);
    }
    json->getProperty("buffer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->buffer), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IFlatBuffer_finalize)

static bool js_assets_IFlatBuffer_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IFlatBuffer* cobj = JSB_ALLOC(cc::IFlatBuffer);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IFlatBuffer* cobj = JSB_ALLOC(cc::IFlatBuffer);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IFlatBuffer* cobj = JSB_ALLOC(cc::IFlatBuffer);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->stride), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->count), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->buffer), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IFlatBuffer_constructor, __jsb_cc_IFlatBuffer_class, js_cc_IFlatBuffer_finalize)



static bool js_cc_IFlatBuffer_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IFlatBuffer>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IFlatBuffer>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IFlatBuffer_finalize)

bool js_register_assets_IFlatBuffer(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IFlatBuffer", obj, nullptr, _SE(js_assets_IFlatBuffer_constructor));

    cls->defineProperty("stride", _SE(js_assets_IFlatBuffer_get_stride), _SE(js_assets_IFlatBuffer_set_stride));
    cls->defineProperty("count", _SE(js_assets_IFlatBuffer_get_count), _SE(js_assets_IFlatBuffer_set_count));
    cls->defineProperty("buffer", _SE(js_assets_IFlatBuffer_get_buffer), _SE(js_assets_IFlatBuffer_set_buffer));
    cls->defineFinalizeFunction(_SE(js_cc_IFlatBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IFlatBuffer>(cls);

    __jsb_cc_IFlatBuffer_proto = cls->getProto();
    __jsb_cc_IFlatBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_RenderingSubMesh_proto = nullptr; // NOLINT
se::Class* __jsb_cc_RenderingSubMesh_class = nullptr;  // NOLINT

static bool js_assets_RenderingSubMesh_enableVertexIdChannel(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_enableVertexIdChannel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::Device*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_enableVertexIdChannel : Error processing arguments");
        cobj->enableVertexIdChannel(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_enableVertexIdChannel)

static bool js_assets_RenderingSubMesh_genFlatBuffers(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_genFlatBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->genFlatBuffers();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_genFlatBuffers)

static bool js_assets_RenderingSubMesh_geometricInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_geometricInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::IGeometricInfo& result = cobj->geometricInfo();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_geometricInfo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_geometricInfo)

static bool js_assets_RenderingSubMesh_getAttributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getAttributes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::gfx::Attribute>& result = cobj->getAttributes();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getAttributes : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getAttributes)

static bool js_assets_RenderingSubMesh_getFlatBuffers(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getFlatBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::IFlatBuffer>& result = cobj->getFlatBuffers();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getFlatBuffers : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getFlatBuffers)

static bool js_assets_RenderingSubMesh_getIaInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getIaInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::gfx::InputAssemblerInfo& result = cobj->getIaInfo();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getIaInfo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getIaInfo)

static bool js_assets_RenderingSubMesh_getIndexBuffer(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getIndexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Buffer* result = cobj->getIndexBuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getIndexBuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getIndexBuffer)

static bool js_assets_RenderingSubMesh_getJointMappedBuffers(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getJointMappedBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::gfx::Buffer *>& result = cobj->getJointMappedBuffers();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getJointMappedBuffers : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getJointMappedBuffers)

static bool js_assets_RenderingSubMesh_getMesh(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getMesh : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::Mesh* result = cobj->getMesh();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getMesh : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getMesh)

static bool js_assets_RenderingSubMesh_getPrimitiveMode(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getPrimitiveMode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getPrimitiveMode());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getPrimitiveMode : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getPrimitiveMode)

static bool js_assets_RenderingSubMesh_getSubMeshIdx(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getSubMeshIdx : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::optional<unsigned int>& result = cobj->getSubMeshIdx();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getSubMeshIdx : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getSubMeshIdx)

static bool js_assets_RenderingSubMesh_getVertexBuffers(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_getVertexBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::gfx::Buffer *>& result = cobj->getVertexBuffers();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_getVertexBuffers : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_getVertexBuffers)

static bool js_assets_RenderingSubMesh_indirectBuffer(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_indirectBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Buffer* result = cobj->indirectBuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_indirectBuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_indirectBuffer)

static bool js_assets_RenderingSubMesh_setFlatBuffers(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_setFlatBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<cc::IFlatBuffer>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_setFlatBuffers : Error processing arguments");
        cobj->setFlatBuffers(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_setFlatBuffers)

static bool js_assets_RenderingSubMesh_setMesh(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_setMesh : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Mesh*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_setMesh : Error processing arguments");
        cobj->setMesh(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_setMesh)

static bool js_assets_RenderingSubMesh_setSubMeshIdx(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderingSubMesh_setSubMeshIdx : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_setSubMeshIdx : Error processing arguments");
        cobj->setSubMeshIdx(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_RenderingSubMesh_setSubMeshIdx)

SE_DECLARE_FINALIZE_FUNC(js_cc_RenderingSubMesh_finalize)

static bool js_assets_RenderingSubMesh_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    std::vector<cc::gfx::Buffer *> arg0;
    std::vector<cc::gfx::Attribute> arg1;
    cc::gfx::PrimitiveMode arg2;
    ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
    ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
    ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_RenderingSubMesh_constructor : Error processing arguments");
    cc::RenderingSubMesh* cobj = JSB_ALLOC(cc::RenderingSubMesh, arg0, arg1, arg2);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_RenderingSubMesh_constructor, __jsb_cc_RenderingSubMesh_class, js_cc_RenderingSubMesh_finalize)



static bool js_cc_RenderingSubMesh_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::RenderingSubMesh>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::RenderingSubMesh>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_RenderingSubMesh_finalize)

bool js_register_assets_RenderingSubMesh(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("RenderingSubMesh", obj, __jsb_cc_Asset_proto, _SE(js_assets_RenderingSubMesh_constructor));

    cls->defineFunction("enableVertexIdChannel", _SE(js_assets_RenderingSubMesh_enableVertexIdChannel));
    cls->defineFunction("genFlatBuffers", _SE(js_assets_RenderingSubMesh_genFlatBuffers));
    cls->defineFunction("geometricInfo", _SE(js_assets_RenderingSubMesh_geometricInfo));
    cls->defineFunction("getAttributes", _SE(js_assets_RenderingSubMesh_getAttributes));
    cls->defineFunction("getFlatBuffers", _SE(js_assets_RenderingSubMesh_getFlatBuffers));
    cls->defineFunction("getIaInfo", _SE(js_assets_RenderingSubMesh_getIaInfo));
    cls->defineFunction("getIndexBuffer", _SE(js_assets_RenderingSubMesh_getIndexBuffer));
    cls->defineFunction("getJointMappedBuffers", _SE(js_assets_RenderingSubMesh_getJointMappedBuffers));
    cls->defineFunction("getMesh", _SE(js_assets_RenderingSubMesh_getMesh));
    cls->defineFunction("getPrimitiveMode", _SE(js_assets_RenderingSubMesh_getPrimitiveMode));
    cls->defineFunction("getSubMeshIdx", _SE(js_assets_RenderingSubMesh_getSubMeshIdx));
    cls->defineFunction("getVertexBuffers", _SE(js_assets_RenderingSubMesh_getVertexBuffers));
    cls->defineFunction("indirectBuffer", _SE(js_assets_RenderingSubMesh_indirectBuffer));
    cls->defineFunction("setFlatBuffers", _SE(js_assets_RenderingSubMesh_setFlatBuffers));
    cls->defineFunction("setMesh", _SE(js_assets_RenderingSubMesh_setMesh));
    cls->defineFunction("setSubMeshIdx", _SE(js_assets_RenderingSubMesh_setSubMeshIdx));
    cls->defineFinalizeFunction(_SE(js_cc_RenderingSubMesh_finalize));
    cls->install();
    JSBClassType::registerClass<cc::RenderingSubMesh>(cls);

    __jsb_cc_RenderingSubMesh_proto = cls->getProto();
    __jsb_cc_RenderingSubMesh_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IMemoryImageSource_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IMemoryImageSource_class = nullptr;  // NOLINT

static bool js_assets_IMemoryImageSource_get_data(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_get_data : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->data, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->data, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMemoryImageSource_get_data)

static bool js_assets_IMemoryImageSource_set_data(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_set_data : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->data, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMemoryImageSource_set_data : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMemoryImageSource_set_data)

static bool js_assets_IMemoryImageSource_get_compressed(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_get_compressed : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->compressed, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->compressed, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMemoryImageSource_get_compressed)

static bool js_assets_IMemoryImageSource_set_compressed(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_set_compressed : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->compressed, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMemoryImageSource_set_compressed : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMemoryImageSource_set_compressed)

static bool js_assets_IMemoryImageSource_get_width(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->width, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMemoryImageSource_get_width)

static bool js_assets_IMemoryImageSource_set_width(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMemoryImageSource_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMemoryImageSource_set_width)

static bool js_assets_IMemoryImageSource_get_height(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->height, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMemoryImageSource_get_height)

static bool js_assets_IMemoryImageSource_set_height(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMemoryImageSource_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMemoryImageSource_set_height)

static bool js_assets_IMemoryImageSource_get_format(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->format, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMemoryImageSource_get_format)

static bool js_assets_IMemoryImageSource_set_format(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMemoryImageSource_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMemoryImageSource_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMemoryImageSource_set_format)


template<>
bool sevalue_to_native(const se::Value &from, cc::IMemoryImageSource * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IMemoryImageSource*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("data", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->data), ctx);
    }
    json->getProperty("compressed", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->compressed), ctx);
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width), ctx);
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height), ctx);
    }
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IMemoryImageSource_finalize)

static bool js_assets_IMemoryImageSource_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IMemoryImageSource* cobj = JSB_ALLOC(cc::IMemoryImageSource);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IMemoryImageSource* cobj = JSB_ALLOC(cc::IMemoryImageSource);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IMemoryImageSource* cobj = JSB_ALLOC(cc::IMemoryImageSource);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->data), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->compressed), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->width), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->height), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->format), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IMemoryImageSource_constructor, __jsb_cc_IMemoryImageSource_class, js_cc_IMemoryImageSource_finalize)



static bool js_cc_IMemoryImageSource_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IMemoryImageSource>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IMemoryImageSource>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IMemoryImageSource_finalize)

bool js_register_assets_IMemoryImageSource(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IMemoryImageSource", obj, nullptr, _SE(js_assets_IMemoryImageSource_constructor));

    cls->defineProperty("data", _SE(js_assets_IMemoryImageSource_get_data), _SE(js_assets_IMemoryImageSource_set_data));
    cls->defineProperty("compressed", _SE(js_assets_IMemoryImageSource_get_compressed), _SE(js_assets_IMemoryImageSource_set_compressed));
    cls->defineProperty("width", _SE(js_assets_IMemoryImageSource_get_width), _SE(js_assets_IMemoryImageSource_set_width));
    cls->defineProperty("height", _SE(js_assets_IMemoryImageSource_get_height), _SE(js_assets_IMemoryImageSource_set_height));
    cls->defineProperty("format", _SE(js_assets_IMemoryImageSource_get_format), _SE(js_assets_IMemoryImageSource_set_format));
    cls->defineFinalizeFunction(_SE(js_cc_IMemoryImageSource_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IMemoryImageSource>(cls);

    __jsb_cc_IMemoryImageSource_proto = cls->getProto();
    __jsb_cc_IMemoryImageSource_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ImageAsset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ImageAsset_class = nullptr;  // NOLINT

static bool js_assets_ImageAsset_getData(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ImageAsset_getData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const unsigned char* result = cobj->getData();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_ImageAsset_getData : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_ImageAsset_getData)

static bool js_assets_ImageAsset_getFormat(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ImageAsset_getFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        auto result = static_cast<int>(cobj->getFormat());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_ImageAsset_getFormat : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_ImageAsset_getFormat)

static bool js_assets_ImageAsset_getHeight(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ImageAsset_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_ImageAsset_getHeight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_ImageAsset_getHeight)

static bool js_assets_ImageAsset_getUrl(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ImageAsset_getUrl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getUrl();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_ImageAsset_getUrl : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_ImageAsset_getUrl)

static bool js_assets_ImageAsset_getWidth(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ImageAsset_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_ImageAsset_getWidth : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_assets_ImageAsset_getWidth)

static bool js_assets_ImageAsset_isCompressed(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ImageAsset_isCompressed : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isCompressed();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_ImageAsset_isCompressed : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_ImageAsset_isCompressed)

SE_DECLARE_FINALIZE_FUNC(js_cc_ImageAsset_finalize)

static bool js_assets_ImageAsset_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::ImageAsset* cobj = JSB_ALLOC(cc::ImageAsset);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ImageAsset_constructor, __jsb_cc_ImageAsset_class, js_cc_ImageAsset_finalize)



static bool js_cc_ImageAsset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ImageAsset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ImageAsset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ImageAsset_finalize)

bool js_register_assets_ImageAsset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ImageAsset", obj, __jsb_cc_Asset_proto, _SE(js_assets_ImageAsset_constructor));

    cls->defineProperty("width", _SE(js_assets_ImageAsset_getWidth), nullptr);
    cls->defineProperty("height", _SE(js_assets_ImageAsset_getHeight), nullptr);
    cls->defineProperty("format", _SE(js_assets_ImageAsset_getFormat), nullptr);
    cls->defineProperty("url", _SE(js_assets_ImageAsset_getUrl), nullptr);
    cls->defineProperty("data", _SE(js_assets_ImageAsset_getData), nullptr);
    cls->defineFunction("isCompressed", _SE(js_assets_ImageAsset_isCompressed));
    cls->defineFinalizeFunction(_SE(js_cc_ImageAsset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ImageAsset>(cls);

    __jsb_cc_ImageAsset_proto = cls->getProto();
    __jsb_cc_ImageAsset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_SimpleTexture_proto = nullptr; // NOLINT
se::Class* __jsb_cc_SimpleTexture_class = nullptr;  // NOLINT

static bool js_assets_SimpleTexture_assignImage(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SimpleTexture_assignImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<cc::ImageAsset*, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_SimpleTexture_assignImage : Error processing arguments");
        cobj->assignImage(arg0.value(), arg1.value());
        return true;
    }
    if (argc == 3) {
        HolderType<cc::ImageAsset*, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        HolderType<unsigned int, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_SimpleTexture_assignImage : Error processing arguments");
        cobj->assignImage(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_assets_SimpleTexture_assignImage)

static bool js_assets_SimpleTexture_checkTextureLoaded(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SimpleTexture_checkTextureLoaded : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->checkTextureLoaded();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_SimpleTexture_checkTextureLoaded)

static bool js_assets_SimpleTexture_mipmapLevel(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SimpleTexture_mipmapLevel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->mipmapLevel();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_SimpleTexture_mipmapLevel : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_SimpleTexture_mipmapLevel)

static bool js_assets_SimpleTexture_updateImage(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SimpleTexture_updateImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->updateImage();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_SimpleTexture_updateImage)

static bool js_assets_SimpleTexture_updateMipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SimpleTexture_updateMipmaps : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_SimpleTexture_updateMipmaps : Error processing arguments");
        cobj->updateMipmaps(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_SimpleTexture_updateMipmaps)

static bool js_assets_SimpleTexture_uploadData(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
    SE_PRECONDITION2( cobj, false, "js_assets_SimpleTexture_uploadData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 1) {
            HolderType<const unsigned char*, false> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->uploadData(arg0.value());
            return true;
        }
    } while(false);

    do {
        if (argc == 2) {
            HolderType<const unsigned char*, false> arg0 = {};
            HolderType<unsigned int, false> arg1 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->uploadData(arg0.value(), arg1.value());
            return true;
        }
    } while(false);

    do {
        if (argc == 3) {
            HolderType<const unsigned char*, false> arg0 = {};
            HolderType<unsigned int, false> arg1 = {};
            HolderType<unsigned int, false> arg2 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
            if (!ok) { ok = true; break; }
            ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->uploadData(arg0.value(), arg1.value(), arg2.value());
            return true;
        }
    } while(false);

    do {
        if (argc == 1) {
            HolderType<cc::ArrayBuffer, true> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->uploadData(arg0.value());
            return true;
        }
    } while(false);

    do {
        if (argc == 2) {
            HolderType<cc::ArrayBuffer, true> arg0 = {};
            HolderType<unsigned int, false> arg1 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->uploadData(arg0.value(), arg1.value());
            return true;
        }
    } while(false);

    do {
        if (argc == 3) {
            HolderType<cc::ArrayBuffer, true> arg0 = {};
            HolderType<unsigned int, false> arg1 = {};
            HolderType<unsigned int, false> arg2 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
            if (!ok) { ok = true; break; }
            ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->uploadData(arg0.value(), arg1.value(), arg2.value());
            return true;
        }
    } while(false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_assets_SimpleTexture_uploadData)


static bool js_cc_SimpleTexture_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::SimpleTexture>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::SimpleTexture>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_SimpleTexture_finalize)

bool js_register_assets_SimpleTexture(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("SimpleTexture", obj, __jsb_cc_TextureBase_proto, nullptr);

    cls->defineFunction("assignImage", _SE(js_assets_SimpleTexture_assignImage));
    cls->defineFunction("checkTextureLoaded", _SE(js_assets_SimpleTexture_checkTextureLoaded));
    cls->defineFunction("mipmapLevel", _SE(js_assets_SimpleTexture_mipmapLevel));
    cls->defineFunction("updateImage", _SE(js_assets_SimpleTexture_updateImage));
    cls->defineFunction("updateMipmaps", _SE(js_assets_SimpleTexture_updateMipmaps));
    cls->defineFunction("uploadData", _SE(js_assets_SimpleTexture_uploadData));
    cls->defineFinalizeFunction(_SE(js_cc_SimpleTexture_finalize));
    cls->install();
    JSBClassType::registerClass<cc::SimpleTexture>(cls);

    __jsb_cc_SimpleTexture_proto = cls->getProto();
    __jsb_cc_SimpleTexture_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ITexture2DSerializeData_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ITexture2DSerializeData_class = nullptr;  // NOLINT

static bool js_assets_ITexture2DSerializeData_get_base(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DSerializeData_get_base : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->base, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->base, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITexture2DSerializeData_get_base)

static bool js_assets_ITexture2DSerializeData_set_base(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DSerializeData_set_base : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->base, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITexture2DSerializeData_set_base : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITexture2DSerializeData_set_base)

static bool js_assets_ITexture2DSerializeData_get_mipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DSerializeData_get_mipmaps : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->mipmaps, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->mipmaps, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITexture2DSerializeData_get_mipmaps)

static bool js_assets_ITexture2DSerializeData_set_mipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DSerializeData_set_mipmaps : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->mipmaps, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITexture2DSerializeData_set_mipmaps : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITexture2DSerializeData_set_mipmaps)


template<>
bool sevalue_to_native(const se::Value &from, cc::ITexture2DSerializeData * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ITexture2DSerializeData*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("base", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->base), ctx);
    }
    json->getProperty("mipmaps", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->mipmaps), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ITexture2DSerializeData_finalize)

static bool js_assets_ITexture2DSerializeData_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ITexture2DSerializeData* cobj = JSB_ALLOC(cc::ITexture2DSerializeData);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ITexture2DSerializeData* cobj = JSB_ALLOC(cc::ITexture2DSerializeData);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ITexture2DSerializeData* cobj = JSB_ALLOC(cc::ITexture2DSerializeData);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->base), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->mipmaps), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ITexture2DSerializeData_constructor, __jsb_cc_ITexture2DSerializeData_class, js_cc_ITexture2DSerializeData_finalize)



static bool js_cc_ITexture2DSerializeData_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ITexture2DSerializeData>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ITexture2DSerializeData>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ITexture2DSerializeData_finalize)

bool js_register_assets_ITexture2DSerializeData(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ITexture2DSerializeData", obj, nullptr, _SE(js_assets_ITexture2DSerializeData_constructor));

    cls->defineProperty("base", _SE(js_assets_ITexture2DSerializeData_get_base), _SE(js_assets_ITexture2DSerializeData_set_base));
    cls->defineProperty("mipmaps", _SE(js_assets_ITexture2DSerializeData_get_mipmaps), _SE(js_assets_ITexture2DSerializeData_set_mipmaps));
    cls->defineFinalizeFunction(_SE(js_cc_ITexture2DSerializeData_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ITexture2DSerializeData>(cls);

    __jsb_cc_ITexture2DSerializeData_proto = cls->getProto();
    __jsb_cc_ITexture2DSerializeData_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ITexture2DCreateInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ITexture2DCreateInfo_class = nullptr;  // NOLINT

static bool js_assets_ITexture2DCreateInfo_get_width(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->width, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITexture2DCreateInfo_get_width)

static bool js_assets_ITexture2DCreateInfo_set_width(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITexture2DCreateInfo_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITexture2DCreateInfo_set_width)

static bool js_assets_ITexture2DCreateInfo_get_height(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->height, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITexture2DCreateInfo_get_height)

static bool js_assets_ITexture2DCreateInfo_set_height(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITexture2DCreateInfo_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITexture2DCreateInfo_set_height)

static bool js_assets_ITexture2DCreateInfo_get_format(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->format, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITexture2DCreateInfo_get_format)

static bool js_assets_ITexture2DCreateInfo_set_format(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITexture2DCreateInfo_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITexture2DCreateInfo_set_format)

static bool js_assets_ITexture2DCreateInfo_get_mipmapLevel(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_get_mipmapLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->mipmapLevel, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->mipmapLevel, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITexture2DCreateInfo_get_mipmapLevel)

static bool js_assets_ITexture2DCreateInfo_set_mipmapLevel(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITexture2DCreateInfo_set_mipmapLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->mipmapLevel, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITexture2DCreateInfo_set_mipmapLevel : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITexture2DCreateInfo_set_mipmapLevel)


template<>
bool sevalue_to_native(const se::Value &from, cc::ITexture2DCreateInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ITexture2DCreateInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width), ctx);
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height), ctx);
    }
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format), ctx);
    }
    json->getProperty("mipmapLevel", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->mipmapLevel), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ITexture2DCreateInfo_finalize)

static bool js_assets_ITexture2DCreateInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ITexture2DCreateInfo* cobj = JSB_ALLOC(cc::ITexture2DCreateInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ITexture2DCreateInfo* cobj = JSB_ALLOC(cc::ITexture2DCreateInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ITexture2DCreateInfo* cobj = JSB_ALLOC(cc::ITexture2DCreateInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->width), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->height), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->format), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->mipmapLevel), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ITexture2DCreateInfo_constructor, __jsb_cc_ITexture2DCreateInfo_class, js_cc_ITexture2DCreateInfo_finalize)



static bool js_cc_ITexture2DCreateInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ITexture2DCreateInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ITexture2DCreateInfo_finalize)

bool js_register_assets_ITexture2DCreateInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ITexture2DCreateInfo", obj, nullptr, _SE(js_assets_ITexture2DCreateInfo_constructor));

    cls->defineProperty("width", _SE(js_assets_ITexture2DCreateInfo_get_width), _SE(js_assets_ITexture2DCreateInfo_set_width));
    cls->defineProperty("height", _SE(js_assets_ITexture2DCreateInfo_get_height), _SE(js_assets_ITexture2DCreateInfo_set_height));
    cls->defineProperty("format", _SE(js_assets_ITexture2DCreateInfo_get_format), _SE(js_assets_ITexture2DCreateInfo_set_format));
    cls->defineProperty("mipmapLevel", _SE(js_assets_ITexture2DCreateInfo_get_mipmapLevel), _SE(js_assets_ITexture2DCreateInfo_set_mipmapLevel));
    cls->defineFinalizeFunction(_SE(js_cc_ITexture2DCreateInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ITexture2DCreateInfo>(cls);

    __jsb_cc_ITexture2DCreateInfo_proto = cls->getProto();
    __jsb_cc_ITexture2DCreateInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Texture2D_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Texture2D_class = nullptr;  // NOLINT

static bool js_assets_Texture2D_create(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_create : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_create : Error processing arguments");
        cobj->create(arg0.value(), arg1.value());
        return true;
    }
    if (argc == 3) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        HolderType<cc::PixelFormat, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_create : Error processing arguments");
        cobj->create(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    if (argc == 4) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        HolderType<cc::PixelFormat, false> arg2 = {};
        HolderType<unsigned int, false> arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_create : Error processing arguments");
        cobj->create(arg0.value(), arg1.value(), arg2.value(), arg3.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_create)

static bool js_assets_Texture2D_description(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_description : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->description();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_description : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_description)

static bool js_assets_Texture2D_getGfxTextureCreateInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_getGfxTextureCreateInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        HolderType<cc::gfx::TextureUsageBit, false> arg0 = {};
        HolderType<cc::gfx::Format, false> arg1 = {};
        HolderType<unsigned int, false> arg2 = {};
        HolderType<cc::gfx::TextureFlagBit, false> arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_getGfxTextureCreateInfo : Error processing arguments");
        cc::gfx::TextureInfo result = cobj->getGfxTextureCreateInfo(arg0.value(), arg1.value(), arg2.value(), arg3.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_getGfxTextureCreateInfo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_getGfxTextureCreateInfo)

static bool js_assets_Texture2D_getHtmlElementObj(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_getHtmlElementObj : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        void** result = cobj->getHtmlElementObj();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_getHtmlElementObj : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_getHtmlElementObj)

static bool js_assets_Texture2D_getImage(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_getImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::ImageAsset* result = cobj->getImage();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_getImage : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_getImage)

static bool js_assets_Texture2D_getMipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_getMipmaps : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::ImageAsset *>& result = cobj->getMipmaps();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_getMipmaps : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_getMipmaps)

static bool js_assets_Texture2D_getMipmapsUuids(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_getMipmapsUuids : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<std::string>& result = cobj->getMipmapsUuids();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_getMipmapsUuids : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_getMipmapsUuids)

static bool js_assets_Texture2D_initialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->initialize();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_initialize)

static bool js_assets_Texture2D_releaseTexture(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_releaseTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->releaseTexture();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_releaseTexture)

static bool js_assets_Texture2D_reset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_reset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::ITexture2DCreateInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_reset : Error processing arguments");
        cobj->reset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_reset)

static bool js_assets_Texture2D_setImage(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_setImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::ImageAsset*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_setImage : Error processing arguments");
        cobj->setImage(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_setImage)

static bool js_assets_Texture2D_setMipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Texture2D_setMipmaps : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<cc::ImageAsset *>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Texture2D_setMipmaps : Error processing arguments");
        cobj->setMipmaps(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Texture2D_setMipmaps)

SE_DECLARE_FINALIZE_FUNC(js_cc_Texture2D_finalize)

static bool js_assets_Texture2D_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::Texture2D* cobj = JSB_ALLOC(cc::Texture2D);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_Texture2D_constructor, __jsb_cc_Texture2D_class, js_cc_Texture2D_finalize)



static bool js_cc_Texture2D_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Texture2D>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Texture2D>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Texture2D_finalize)

bool js_register_assets_Texture2D(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Texture2D", obj, __jsb_cc_SimpleTexture_proto, _SE(js_assets_Texture2D_constructor));

    cls->defineFunction("create", _SE(js_assets_Texture2D_create));
    cls->defineFunction("description", _SE(js_assets_Texture2D_description));
    cls->defineFunction("getGfxTextureCreateInfo", _SE(js_assets_Texture2D_getGfxTextureCreateInfo));
    cls->defineFunction("getHtmlElementObj", _SE(js_assets_Texture2D_getHtmlElementObj));
    cls->defineFunction("getImage", _SE(js_assets_Texture2D_getImage));
    cls->defineFunction("getMipmaps", _SE(js_assets_Texture2D_getMipmaps));
    cls->defineFunction("getMipmapsUuids", _SE(js_assets_Texture2D_getMipmapsUuids));
    cls->defineFunction("initialize", _SE(js_assets_Texture2D_initialize));
    cls->defineFunction("releaseTexture", _SE(js_assets_Texture2D_releaseTexture));
    cls->defineFunction("reset", _SE(js_assets_Texture2D_reset));
    cls->defineFunction("setImage", _SE(js_assets_Texture2D_setImage));
    cls->defineFunction("setMipmaps", _SE(js_assets_Texture2D_setMipmaps));
    cls->defineFinalizeFunction(_SE(js_cc_Texture2D_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Texture2D>(cls);

    __jsb_cc_Texture2D_proto = cls->getProto();
    __jsb_cc_Texture2D_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IPropertyInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IPropertyInfo_class = nullptr;  // NOLINT

static bool js_assets_IPropertyInfo_get_type(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->type, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IPropertyInfo_get_type)

static bool js_assets_IPropertyInfo_set_type(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IPropertyInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IPropertyInfo_set_type)

static bool js_assets_IPropertyInfo_get_handleInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_get_handleInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->handleInfo, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->handleInfo, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IPropertyInfo_get_handleInfo)

static bool js_assets_IPropertyInfo_set_handleInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_set_handleInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->handleInfo, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IPropertyInfo_set_handleInfo : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IPropertyInfo_set_handleInfo)

static bool js_assets_IPropertyInfo_get_samplerHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_get_samplerHash : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->samplerHash, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->samplerHash, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IPropertyInfo_get_samplerHash)

static bool js_assets_IPropertyInfo_set_samplerHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_set_samplerHash : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->samplerHash, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IPropertyInfo_set_samplerHash : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IPropertyInfo_set_samplerHash)

static bool js_assets_IPropertyInfo_get_value(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_get_value : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->value, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->value, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IPropertyInfo_get_value)

static bool js_assets_IPropertyInfo_set_value(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IPropertyInfo_set_value : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->value, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IPropertyInfo_set_value : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IPropertyInfo_set_value)


template<>
bool sevalue_to_native(const se::Value &from, cc::IPropertyInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IPropertyInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type), ctx);
    }
    json->getProperty("handleInfo", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->handleInfo), ctx);
    }
    json->getProperty("samplerHash", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->samplerHash), ctx);
    }
    json->getProperty("value", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->value), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IPropertyInfo_finalize)

static bool js_assets_IPropertyInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IPropertyInfo* cobj = JSB_ALLOC(cc::IPropertyInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IPropertyInfo* cobj = JSB_ALLOC(cc::IPropertyInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IPropertyInfo* cobj = JSB_ALLOC(cc::IPropertyInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->type), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->handleInfo), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->samplerHash), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->value), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IPropertyInfo_constructor, __jsb_cc_IPropertyInfo_class, js_cc_IPropertyInfo_finalize)



static bool js_cc_IPropertyInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IPropertyInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IPropertyInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IPropertyInfo_finalize)

bool js_register_assets_IPropertyInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IPropertyInfo", obj, nullptr, _SE(js_assets_IPropertyInfo_constructor));

    cls->defineProperty("type", _SE(js_assets_IPropertyInfo_get_type), _SE(js_assets_IPropertyInfo_set_type));
    cls->defineProperty("handleInfo", _SE(js_assets_IPropertyInfo_get_handleInfo), _SE(js_assets_IPropertyInfo_set_handleInfo));
    cls->defineProperty("samplerHash", _SE(js_assets_IPropertyInfo_get_samplerHash), _SE(js_assets_IPropertyInfo_set_samplerHash));
    cls->defineProperty("value", _SE(js_assets_IPropertyInfo_get_value), _SE(js_assets_IPropertyInfo_set_value));
    cls->defineFinalizeFunction(_SE(js_cc_IPropertyInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IPropertyInfo>(cls);

    __jsb_cc_IPropertyInfo_proto = cls->getProto();
    __jsb_cc_IPropertyInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ITechniqueInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ITechniqueInfo_class = nullptr;  // NOLINT

static bool js_assets_ITechniqueInfo_get_passes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITechniqueInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITechniqueInfo_get_passes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->passes, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->passes, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITechniqueInfo_get_passes)

static bool js_assets_ITechniqueInfo_set_passes(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITechniqueInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITechniqueInfo_set_passes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->passes, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITechniqueInfo_set_passes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITechniqueInfo_set_passes)

static bool js_assets_ITechniqueInfo_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITechniqueInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITechniqueInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITechniqueInfo_get_name)

static bool js_assets_ITechniqueInfo_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITechniqueInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITechniqueInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITechniqueInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITechniqueInfo_set_name)


template<>
bool sevalue_to_native(const se::Value &from, cc::ITechniqueInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ITechniqueInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("passes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->passes), ctx);
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ITechniqueInfo_finalize)

static bool js_assets_ITechniqueInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ITechniqueInfo* cobj = JSB_ALLOC(cc::ITechniqueInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ITechniqueInfo* cobj = JSB_ALLOC(cc::ITechniqueInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ITechniqueInfo* cobj = JSB_ALLOC(cc::ITechniqueInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->passes), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->name), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ITechniqueInfo_constructor, __jsb_cc_ITechniqueInfo_class, js_cc_ITechniqueInfo_finalize)



static bool js_cc_ITechniqueInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ITechniqueInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ITechniqueInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ITechniqueInfo_finalize)

bool js_register_assets_ITechniqueInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ITechniqueInfo", obj, nullptr, _SE(js_assets_ITechniqueInfo_constructor));

    cls->defineProperty("passes", _SE(js_assets_ITechniqueInfo_get_passes), _SE(js_assets_ITechniqueInfo_set_passes));
    cls->defineProperty("name", _SE(js_assets_ITechniqueInfo_get_name), _SE(js_assets_ITechniqueInfo_set_name));
    cls->defineFinalizeFunction(_SE(js_cc_ITechniqueInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ITechniqueInfo>(cls);

    __jsb_cc_ITechniqueInfo_proto = cls->getProto();
    __jsb_cc_ITechniqueInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IBlockInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IBlockInfo_class = nullptr;  // NOLINT

static bool js_assets_IBlockInfo_get_binding(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_get_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->binding, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->binding, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBlockInfo_get_binding)

static bool js_assets_IBlockInfo_set_binding(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_set_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->binding, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBlockInfo_set_binding : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBlockInfo_set_binding)

static bool js_assets_IBlockInfo_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBlockInfo_get_name)

static bool js_assets_IBlockInfo_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBlockInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBlockInfo_set_name)

static bool js_assets_IBlockInfo_get_members(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_get_members : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->members, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->members, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBlockInfo_get_members)

static bool js_assets_IBlockInfo_set_members(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_set_members : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->members, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBlockInfo_set_members : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBlockInfo_set_members)

static bool js_assets_IBlockInfo_get_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->count, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBlockInfo_get_count)

static bool js_assets_IBlockInfo_set_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBlockInfo_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBlockInfo_set_count)

static bool js_assets_IBlockInfo_get_stageFlags(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_get_stageFlags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stageFlags, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stageFlags, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBlockInfo_get_stageFlags)

static bool js_assets_IBlockInfo_set_stageFlags(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_set_stageFlags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stageFlags, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBlockInfo_set_stageFlags : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBlockInfo_set_stageFlags)

static bool js_assets_IBlockInfo_get_descriptorType(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_get_descriptorType : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->descriptorType, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->descriptorType, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBlockInfo_get_descriptorType)

static bool js_assets_IBlockInfo_set_descriptorType(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBlockInfo_set_descriptorType : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->descriptorType, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBlockInfo_set_descriptorType : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBlockInfo_set_descriptorType)


template<>
bool sevalue_to_native(const se::Value &from, cc::IBlockInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IBlockInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("binding", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->binding), ctx);
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    json->getProperty("members", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->members), ctx);
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count), ctx);
    }
    json->getProperty("stageFlags", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stageFlags), ctx);
    }
    json->getProperty("descriptorType", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->descriptorType), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IBlockInfo_finalize)

static bool js_assets_IBlockInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IBlockInfo* cobj = JSB_ALLOC(cc::IBlockInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IBlockInfo* cobj = JSB_ALLOC(cc::IBlockInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IBlockInfo* cobj = JSB_ALLOC(cc::IBlockInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->binding), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->name), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->members), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->count), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->stageFlags), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->descriptorType), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IBlockInfo_constructor, __jsb_cc_IBlockInfo_class, js_cc_IBlockInfo_finalize)



static bool js_cc_IBlockInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IBlockInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IBlockInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IBlockInfo_finalize)

bool js_register_assets_IBlockInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IBlockInfo", obj, nullptr, _SE(js_assets_IBlockInfo_constructor));

    cls->defineProperty("binding", _SE(js_assets_IBlockInfo_get_binding), _SE(js_assets_IBlockInfo_set_binding));
    cls->defineProperty("name", _SE(js_assets_IBlockInfo_get_name), _SE(js_assets_IBlockInfo_set_name));
    cls->defineProperty("members", _SE(js_assets_IBlockInfo_get_members), _SE(js_assets_IBlockInfo_set_members));
    cls->defineProperty("count", _SE(js_assets_IBlockInfo_get_count), _SE(js_assets_IBlockInfo_set_count));
    cls->defineProperty("stageFlags", _SE(js_assets_IBlockInfo_get_stageFlags), _SE(js_assets_IBlockInfo_set_stageFlags));
    cls->defineProperty("descriptorType", _SE(js_assets_IBlockInfo_get_descriptorType), _SE(js_assets_IBlockInfo_set_descriptorType));
    cls->defineFinalizeFunction(_SE(js_cc_IBlockInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IBlockInfo>(cls);

    __jsb_cc_IBlockInfo_proto = cls->getProto();
    __jsb_cc_IBlockInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ISamplerTextureInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ISamplerTextureInfo_class = nullptr;  // NOLINT

static bool js_assets_ISamplerTextureInfo_get_binding(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_get_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->binding, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->binding, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISamplerTextureInfo_get_binding)

static bool js_assets_ISamplerTextureInfo_set_binding(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_set_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->binding, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISamplerTextureInfo_set_binding : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISamplerTextureInfo_set_binding)

static bool js_assets_ISamplerTextureInfo_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISamplerTextureInfo_get_name)

static bool js_assets_ISamplerTextureInfo_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISamplerTextureInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISamplerTextureInfo_set_name)

static bool js_assets_ISamplerTextureInfo_get_type(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->type, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISamplerTextureInfo_get_type)

static bool js_assets_ISamplerTextureInfo_set_type(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISamplerTextureInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISamplerTextureInfo_set_type)

static bool js_assets_ISamplerTextureInfo_get_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->count, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISamplerTextureInfo_get_count)

static bool js_assets_ISamplerTextureInfo_set_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISamplerTextureInfo_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISamplerTextureInfo_set_count)

static bool js_assets_ISamplerTextureInfo_get_stageFlags(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_get_stageFlags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stageFlags, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stageFlags, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISamplerTextureInfo_get_stageFlags)

static bool js_assets_ISamplerTextureInfo_set_stageFlags(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_set_stageFlags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stageFlags, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISamplerTextureInfo_set_stageFlags : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISamplerTextureInfo_set_stageFlags)

static bool js_assets_ISamplerTextureInfo_get_descriptorType(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_get_descriptorType : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->descriptorType, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->descriptorType, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISamplerTextureInfo_get_descriptorType)

static bool js_assets_ISamplerTextureInfo_set_descriptorType(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISamplerTextureInfo_set_descriptorType : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->descriptorType, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISamplerTextureInfo_set_descriptorType : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISamplerTextureInfo_set_descriptorType)


template<>
bool sevalue_to_native(const se::Value &from, cc::ISamplerTextureInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ISamplerTextureInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("binding", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->binding), ctx);
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type), ctx);
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count), ctx);
    }
    json->getProperty("stageFlags", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stageFlags), ctx);
    }
    json->getProperty("descriptorType", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->descriptorType), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ISamplerTextureInfo_finalize)

static bool js_assets_ISamplerTextureInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ISamplerTextureInfo* cobj = JSB_ALLOC(cc::ISamplerTextureInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ISamplerTextureInfo* cobj = JSB_ALLOC(cc::ISamplerTextureInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ISamplerTextureInfo* cobj = JSB_ALLOC(cc::ISamplerTextureInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->binding), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->name), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->type), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->count), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->stageFlags), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->descriptorType), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ISamplerTextureInfo_constructor, __jsb_cc_ISamplerTextureInfo_class, js_cc_ISamplerTextureInfo_finalize)



static bool js_cc_ISamplerTextureInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ISamplerTextureInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ISamplerTextureInfo_finalize)

bool js_register_assets_ISamplerTextureInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ISamplerTextureInfo", obj, nullptr, _SE(js_assets_ISamplerTextureInfo_constructor));

    cls->defineProperty("binding", _SE(js_assets_ISamplerTextureInfo_get_binding), _SE(js_assets_ISamplerTextureInfo_set_binding));
    cls->defineProperty("name", _SE(js_assets_ISamplerTextureInfo_get_name), _SE(js_assets_ISamplerTextureInfo_set_name));
    cls->defineProperty("type", _SE(js_assets_ISamplerTextureInfo_get_type), _SE(js_assets_ISamplerTextureInfo_set_type));
    cls->defineProperty("count", _SE(js_assets_ISamplerTextureInfo_get_count), _SE(js_assets_ISamplerTextureInfo_set_count));
    cls->defineProperty("stageFlags", _SE(js_assets_ISamplerTextureInfo_get_stageFlags), _SE(js_assets_ISamplerTextureInfo_set_stageFlags));
    cls->defineProperty("descriptorType", _SE(js_assets_ISamplerTextureInfo_get_descriptorType), _SE(js_assets_ISamplerTextureInfo_set_descriptorType));
    cls->defineFinalizeFunction(_SE(js_cc_ISamplerTextureInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ISamplerTextureInfo>(cls);

    __jsb_cc_ISamplerTextureInfo_proto = cls->getProto();
    __jsb_cc_ISamplerTextureInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IAttributeInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IAttributeInfo_class = nullptr;  // NOLINT

static bool js_assets_IAttributeInfo_get_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IAttributeInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IAttributeInfo_get_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->defines, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->defines, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IAttributeInfo_get_defines)

static bool js_assets_IAttributeInfo_set_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IAttributeInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IAttributeInfo_set_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->defines, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IAttributeInfo_set_defines : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IAttributeInfo_set_defines)


template<>
bool sevalue_to_native(const se::Value &from, cc::IAttributeInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IAttributeInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("defines", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->defines), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IAttributeInfo_finalize)

static bool js_assets_IAttributeInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IAttributeInfo* cobj = JSB_ALLOC(cc::IAttributeInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IAttributeInfo* cobj = JSB_ALLOC(cc::IAttributeInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->defines), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IAttributeInfo_constructor, __jsb_cc_IAttributeInfo_class, js_cc_IAttributeInfo_finalize)



static bool js_cc_IAttributeInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IAttributeInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IAttributeInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IAttributeInfo_finalize)

bool js_register_assets_IAttributeInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IAttributeInfo", obj, __jsb_cc_gfx_Attribute_proto, _SE(js_assets_IAttributeInfo_constructor));

    cls->defineProperty("defines", _SE(js_assets_IAttributeInfo_get_defines), _SE(js_assets_IAttributeInfo_set_defines));
    cls->defineFinalizeFunction(_SE(js_cc_IAttributeInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IAttributeInfo>(cls);

    __jsb_cc_IAttributeInfo_proto = cls->getProto();
    __jsb_cc_IAttributeInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IDefineInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IDefineInfo_class = nullptr;  // NOLINT

static bool js_assets_IDefineInfo_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IDefineInfo_get_name)

static bool js_assets_IDefineInfo_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IDefineInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IDefineInfo_set_name)

static bool js_assets_IDefineInfo_get_type(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->type, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IDefineInfo_get_type)

static bool js_assets_IDefineInfo_set_type(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IDefineInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IDefineInfo_set_type)

static bool js_assets_IDefineInfo_get_range(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_get_range : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->range, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->range, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IDefineInfo_get_range)

static bool js_assets_IDefineInfo_set_range(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_set_range : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->range, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IDefineInfo_set_range : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IDefineInfo_set_range)

static bool js_assets_IDefineInfo_get_options(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_get_options : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->options, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->options, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IDefineInfo_get_options)

static bool js_assets_IDefineInfo_set_options(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_set_options : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->options, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IDefineInfo_set_options : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IDefineInfo_set_options)

static bool js_assets_IDefineInfo_get_defaultVal(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_get_defaultVal : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->defaultVal, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->defaultVal, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IDefineInfo_get_defaultVal)

static bool js_assets_IDefineInfo_set_defaultVal(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IDefineInfo_set_defaultVal : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->defaultVal, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IDefineInfo_set_defaultVal : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IDefineInfo_set_defaultVal)


template<>
bool sevalue_to_native(const se::Value &from, cc::IDefineInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IDefineInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type), ctx);
    }
    json->getProperty("range", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->range), ctx);
    }
    json->getProperty("options", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->options), ctx);
    }
    json->getProperty("defaultVal", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->defaultVal), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IDefineInfo_finalize)

static bool js_assets_IDefineInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IDefineInfo* cobj = JSB_ALLOC(cc::IDefineInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IDefineInfo* cobj = JSB_ALLOC(cc::IDefineInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IDefineInfo* cobj = JSB_ALLOC(cc::IDefineInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->name), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->type), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->range), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->options), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->defaultVal), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IDefineInfo_constructor, __jsb_cc_IDefineInfo_class, js_cc_IDefineInfo_finalize)



static bool js_cc_IDefineInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IDefineInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IDefineInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IDefineInfo_finalize)

bool js_register_assets_IDefineInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IDefineInfo", obj, nullptr, _SE(js_assets_IDefineInfo_constructor));

    cls->defineProperty("name", _SE(js_assets_IDefineInfo_get_name), _SE(js_assets_IDefineInfo_set_name));
    cls->defineProperty("type", _SE(js_assets_IDefineInfo_get_type), _SE(js_assets_IDefineInfo_set_type));
    cls->defineProperty("range", _SE(js_assets_IDefineInfo_get_range), _SE(js_assets_IDefineInfo_set_range));
    cls->defineProperty("options", _SE(js_assets_IDefineInfo_get_options), _SE(js_assets_IDefineInfo_set_options));
    cls->defineProperty("defaultVal", _SE(js_assets_IDefineInfo_get_defaultVal), _SE(js_assets_IDefineInfo_set_defaultVal));
    cls->defineFinalizeFunction(_SE(js_cc_IDefineInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IDefineInfo>(cls);

    __jsb_cc_IDefineInfo_proto = cls->getProto();
    __jsb_cc_IDefineInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IBuiltin_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IBuiltin_class = nullptr;  // NOLINT

static bool js_assets_IBuiltin_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltin>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltin_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltin_get_name)

static bool js_assets_IBuiltin_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltin>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltin_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltin_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltin_set_name)

static bool js_assets_IBuiltin_get_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltin>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltin_get_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->defines, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->defines, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltin_get_defines)

static bool js_assets_IBuiltin_set_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltin>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltin_set_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->defines, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltin_set_defines : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltin_set_defines)


template<>
bool sevalue_to_native(const se::Value &from, cc::IBuiltin * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IBuiltin*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    json->getProperty("defines", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->defines), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IBuiltin_finalize)

static bool js_assets_IBuiltin_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IBuiltin* cobj = JSB_ALLOC(cc::IBuiltin);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IBuiltin* cobj = JSB_ALLOC(cc::IBuiltin);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IBuiltin* cobj = JSB_ALLOC(cc::IBuiltin);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->name), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->defines), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IBuiltin_constructor, __jsb_cc_IBuiltin_class, js_cc_IBuiltin_finalize)



static bool js_cc_IBuiltin_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IBuiltin>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IBuiltin>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IBuiltin_finalize)

bool js_register_assets_IBuiltin(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IBuiltin", obj, nullptr, _SE(js_assets_IBuiltin_constructor));

    cls->defineProperty("name", _SE(js_assets_IBuiltin_get_name), _SE(js_assets_IBuiltin_set_name));
    cls->defineProperty("defines", _SE(js_assets_IBuiltin_get_defines), _SE(js_assets_IBuiltin_set_defines));
    cls->defineFinalizeFunction(_SE(js_cc_IBuiltin_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IBuiltin>(cls);

    __jsb_cc_IBuiltin_proto = cls->getProto();
    __jsb_cc_IBuiltin_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IBuiltinInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IBuiltinInfo_class = nullptr;  // NOLINT

static bool js_assets_IBuiltinInfo_get_blocks(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltinInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltinInfo_get_blocks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blocks, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->blocks, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltinInfo_get_blocks)

static bool js_assets_IBuiltinInfo_set_blocks(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltinInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltinInfo_set_blocks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blocks, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltinInfo_set_blocks : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltinInfo_set_blocks)

static bool js_assets_IBuiltinInfo_get_samplerTextures(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltinInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltinInfo_get_samplerTextures : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->samplerTextures, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->samplerTextures, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltinInfo_get_samplerTextures)

static bool js_assets_IBuiltinInfo_set_samplerTextures(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltinInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltinInfo_set_samplerTextures : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->samplerTextures, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltinInfo_set_samplerTextures : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltinInfo_set_samplerTextures)


template<>
bool sevalue_to_native(const se::Value &from, cc::IBuiltinInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IBuiltinInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("blocks", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blocks), ctx);
    }
    json->getProperty("samplerTextures", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->samplerTextures), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IBuiltinInfo_finalize)

static bool js_assets_IBuiltinInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IBuiltinInfo* cobj = JSB_ALLOC(cc::IBuiltinInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IBuiltinInfo* cobj = JSB_ALLOC(cc::IBuiltinInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IBuiltinInfo* cobj = JSB_ALLOC(cc::IBuiltinInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->blocks), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->samplerTextures), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IBuiltinInfo_constructor, __jsb_cc_IBuiltinInfo_class, js_cc_IBuiltinInfo_finalize)



static bool js_cc_IBuiltinInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IBuiltinInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IBuiltinInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IBuiltinInfo_finalize)

bool js_register_assets_IBuiltinInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IBuiltinInfo", obj, nullptr, _SE(js_assets_IBuiltinInfo_constructor));

    cls->defineProperty("blocks", _SE(js_assets_IBuiltinInfo_get_blocks), _SE(js_assets_IBuiltinInfo_set_blocks));
    cls->defineProperty("samplerTextures", _SE(js_assets_IBuiltinInfo_get_samplerTextures), _SE(js_assets_IBuiltinInfo_set_samplerTextures));
    cls->defineFinalizeFunction(_SE(js_cc_IBuiltinInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IBuiltinInfo>(cls);

    __jsb_cc_IBuiltinInfo_proto = cls->getProto();
    __jsb_cc_IBuiltinInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IBuiltins_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IBuiltins_class = nullptr;  // NOLINT

static bool js_assets_IBuiltins_get_globals(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltins_get_globals : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->globals, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->globals, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltins_get_globals)

static bool js_assets_IBuiltins_set_globals(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltins_set_globals : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->globals, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltins_set_globals : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltins_set_globals)

static bool js_assets_IBuiltins_get_locals(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltins_get_locals : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->locals, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->locals, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltins_get_locals)

static bool js_assets_IBuiltins_set_locals(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltins_set_locals : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->locals, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltins_set_locals : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltins_set_locals)

static bool js_assets_IBuiltins_get_statistics(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltins_get_statistics : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->statistics, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->statistics, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IBuiltins_get_statistics)

static bool js_assets_IBuiltins_set_statistics(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IBuiltins_set_statistics : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->statistics, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IBuiltins_set_statistics : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IBuiltins_set_statistics)


template<>
bool sevalue_to_native(const se::Value &from, cc::IBuiltins * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IBuiltins*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("globals", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->globals), ctx);
    }
    json->getProperty("locals", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->locals), ctx);
    }
    json->getProperty("statistics", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->statistics), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IBuiltins_finalize)

static bool js_assets_IBuiltins_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IBuiltins* cobj = JSB_ALLOC(cc::IBuiltins);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IBuiltins* cobj = JSB_ALLOC(cc::IBuiltins);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IBuiltins* cobj = JSB_ALLOC(cc::IBuiltins);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->globals), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->locals), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->statistics), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IBuiltins_constructor, __jsb_cc_IBuiltins_class, js_cc_IBuiltins_finalize)



static bool js_cc_IBuiltins_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IBuiltins>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IBuiltins>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IBuiltins_finalize)

bool js_register_assets_IBuiltins(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IBuiltins", obj, nullptr, _SE(js_assets_IBuiltins_constructor));

    cls->defineProperty("globals", _SE(js_assets_IBuiltins_get_globals), _SE(js_assets_IBuiltins_set_globals));
    cls->defineProperty("locals", _SE(js_assets_IBuiltins_get_locals), _SE(js_assets_IBuiltins_set_locals));
    cls->defineProperty("statistics", _SE(js_assets_IBuiltins_get_statistics), _SE(js_assets_IBuiltins_set_statistics));
    cls->defineFinalizeFunction(_SE(js_cc_IBuiltins_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IBuiltins>(cls);

    __jsb_cc_IBuiltins_proto = cls->getProto();
    __jsb_cc_IBuiltins_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IShaderSource_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IShaderSource_class = nullptr;  // NOLINT

static bool js_assets_IShaderSource_get_vert(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderSource_get_vert : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vert, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->vert, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderSource_get_vert)

static bool js_assets_IShaderSource_set_vert(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderSource_set_vert : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vert, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderSource_set_vert : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderSource_set_vert)

static bool js_assets_IShaderSource_get_frag(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderSource_get_frag : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->frag, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->frag, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderSource_get_frag)

static bool js_assets_IShaderSource_set_frag(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderSource>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderSource_set_frag : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->frag, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderSource_set_frag : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderSource_set_frag)


template<>
bool sevalue_to_native(const se::Value &from, cc::IShaderSource * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IShaderSource*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("vert", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vert), ctx);
    }
    json->getProperty("frag", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->frag), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IShaderSource_finalize)

static bool js_assets_IShaderSource_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IShaderSource* cobj = JSB_ALLOC(cc::IShaderSource);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IShaderSource* cobj = JSB_ALLOC(cc::IShaderSource);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IShaderSource* cobj = JSB_ALLOC(cc::IShaderSource);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->vert), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->frag), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IShaderSource_constructor, __jsb_cc_IShaderSource_class, js_cc_IShaderSource_finalize)



static bool js_cc_IShaderSource_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IShaderSource>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IShaderSource>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IShaderSource_finalize)

bool js_register_assets_IShaderSource(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IShaderSource", obj, nullptr, _SE(js_assets_IShaderSource_constructor));

    cls->defineProperty("vert", _SE(js_assets_IShaderSource_get_vert), _SE(js_assets_IShaderSource_set_vert));
    cls->defineProperty("frag", _SE(js_assets_IShaderSource_get_frag), _SE(js_assets_IShaderSource_set_frag));
    cls->defineFinalizeFunction(_SE(js_cc_IShaderSource_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IShaderSource>(cls);

    __jsb_cc_IShaderSource_proto = cls->getProto();
    __jsb_cc_IShaderSource_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IShaderInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IShaderInfo_class = nullptr;  // NOLINT

static bool js_assets_IShaderInfo_getSource(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_getSource : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_getSource : Error processing arguments");
        const cc::IShaderSource* result = cobj->getSource(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_getSource : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_IShaderInfo_getSource)

static bool js_assets_IShaderInfo_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_name)

static bool js_assets_IShaderInfo_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_name)

static bool js_assets_IShaderInfo_get_hash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_hash : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->hash, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->hash, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_hash)

static bool js_assets_IShaderInfo_set_hash(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_hash : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->hash, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_hash : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_hash)

static bool js_assets_IShaderInfo_get_glsl4(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_glsl4 : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->glsl4, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->glsl4, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_glsl4)

static bool js_assets_IShaderInfo_set_glsl4(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_glsl4 : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->glsl4, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_glsl4 : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_glsl4)

static bool js_assets_IShaderInfo_get_glsl3(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_glsl3 : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->glsl3, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->glsl3, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_glsl3)

static bool js_assets_IShaderInfo_set_glsl3(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_glsl3 : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->glsl3, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_glsl3 : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_glsl3)

static bool js_assets_IShaderInfo_get_glsl1(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_glsl1 : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->glsl1, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->glsl1, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_glsl1)

static bool js_assets_IShaderInfo_set_glsl1(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_glsl1 : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->glsl1, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_glsl1 : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_glsl1)

static bool js_assets_IShaderInfo_get_builtins(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_builtins : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->builtins, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->builtins, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_builtins)

static bool js_assets_IShaderInfo_set_builtins(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_builtins : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->builtins, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_builtins : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_builtins)

static bool js_assets_IShaderInfo_get_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->defines, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->defines, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_defines)

static bool js_assets_IShaderInfo_set_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->defines, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_defines : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_defines)

static bool js_assets_IShaderInfo_get_blocks(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_blocks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blocks, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->blocks, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_blocks)

static bool js_assets_IShaderInfo_set_blocks(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_blocks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blocks, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_blocks : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_blocks)

static bool js_assets_IShaderInfo_get_samplerTextures(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_samplerTextures : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->samplerTextures, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->samplerTextures, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_samplerTextures)

static bool js_assets_IShaderInfo_set_samplerTextures(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_samplerTextures : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->samplerTextures, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_samplerTextures : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_samplerTextures)

static bool js_assets_IShaderInfo_get_attributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_get_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->attributes, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->attributes, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IShaderInfo_get_attributes)

static bool js_assets_IShaderInfo_set_attributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IShaderInfo_set_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->attributes, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IShaderInfo_set_attributes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IShaderInfo_set_attributes)


template<>
bool sevalue_to_native(const se::Value &from, cc::IShaderInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IShaderInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    json->getProperty("hash", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->hash), ctx);
    }
    json->getProperty("glsl4", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->glsl4), ctx);
    }
    json->getProperty("glsl3", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->glsl3), ctx);
    }
    json->getProperty("glsl1", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->glsl1), ctx);
    }
    json->getProperty("builtins", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->builtins), ctx);
    }
    json->getProperty("defines", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->defines), ctx);
    }
    json->getProperty("blocks", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blocks), ctx);
    }
    json->getProperty("samplerTextures", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->samplerTextures), ctx);
    }
    json->getProperty("attributes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->attributes), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IShaderInfo_finalize)

static bool js_assets_IShaderInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IShaderInfo* cobj = JSB_ALLOC(cc::IShaderInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IShaderInfo* cobj = JSB_ALLOC(cc::IShaderInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IShaderInfo* cobj = JSB_ALLOC(cc::IShaderInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->name), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->hash), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->glsl4), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->glsl3), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->glsl1), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->builtins), nullptr);
    }
    if (argc > 6 && !args[6].isUndefined()) {
        ok &= sevalue_to_native(args[6], &(cobj->defines), nullptr);
    }
    if (argc > 7 && !args[7].isUndefined()) {
        ok &= sevalue_to_native(args[7], &(cobj->blocks), nullptr);
    }
    if (argc > 8 && !args[8].isUndefined()) {
        ok &= sevalue_to_native(args[8], &(cobj->samplerTextures), nullptr);
    }
    if (argc > 9 && !args[9].isUndefined()) {
        ok &= sevalue_to_native(args[9], &(cobj->attributes), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IShaderInfo_constructor, __jsb_cc_IShaderInfo_class, js_cc_IShaderInfo_finalize)



static bool js_cc_IShaderInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IShaderInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IShaderInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IShaderInfo_finalize)

bool js_register_assets_IShaderInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IShaderInfo", obj, nullptr, _SE(js_assets_IShaderInfo_constructor));

    cls->defineProperty("name", _SE(js_assets_IShaderInfo_get_name), _SE(js_assets_IShaderInfo_set_name));
    cls->defineProperty("hash", _SE(js_assets_IShaderInfo_get_hash), _SE(js_assets_IShaderInfo_set_hash));
    cls->defineProperty("glsl4", _SE(js_assets_IShaderInfo_get_glsl4), _SE(js_assets_IShaderInfo_set_glsl4));
    cls->defineProperty("glsl3", _SE(js_assets_IShaderInfo_get_glsl3), _SE(js_assets_IShaderInfo_set_glsl3));
    cls->defineProperty("glsl1", _SE(js_assets_IShaderInfo_get_glsl1), _SE(js_assets_IShaderInfo_set_glsl1));
    cls->defineProperty("builtins", _SE(js_assets_IShaderInfo_get_builtins), _SE(js_assets_IShaderInfo_set_builtins));
    cls->defineProperty("defines", _SE(js_assets_IShaderInfo_get_defines), _SE(js_assets_IShaderInfo_set_defines));
    cls->defineProperty("blocks", _SE(js_assets_IShaderInfo_get_blocks), _SE(js_assets_IShaderInfo_set_blocks));
    cls->defineProperty("samplerTextures", _SE(js_assets_IShaderInfo_get_samplerTextures), _SE(js_assets_IShaderInfo_set_samplerTextures));
    cls->defineProperty("attributes", _SE(js_assets_IShaderInfo_get_attributes), _SE(js_assets_IShaderInfo_set_attributes));
    cls->defineFunction("getSource", _SE(js_assets_IShaderInfo_getSource));
    cls->defineFinalizeFunction(_SE(js_cc_IShaderInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IShaderInfo>(cls);

    __jsb_cc_IShaderInfo_proto = cls->getProto();
    __jsb_cc_IShaderInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_EffectAsset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_EffectAsset_class = nullptr;  // NOLINT

static bool js_assets_EffectAsset_registerAsset_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::EffectAsset*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_assets_EffectAsset_registerAsset_static : Error processing arguments");
        cc::EffectAsset::registerAsset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_EffectAsset_registerAsset_static)

static bool js_assets_EffectAsset_remove_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 1) {
            HolderType<cc::EffectAsset*, false> arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            cc::EffectAsset::remove(arg0.value());
            return true;
        }
    } while (false);
    do {
        if (argc == 1) {
            HolderType<std::string, true> arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            cc::EffectAsset::remove(arg0.value());
            return true;
        }
    } while (false);
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_assets_EffectAsset_remove_static)

static bool js_assets_EffectAsset_get_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_assets_EffectAsset_get_static : Error processing arguments");
        cc::EffectAsset* result = cc::EffectAsset::get(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_EffectAsset_get_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_EffectAsset_get_static)

static bool js_assets_EffectAsset_getAll_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::unordered_map<std::string, cc::EffectAsset *>& result = cc::EffectAsset::getAll();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_EffectAsset_getAll_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_EffectAsset_getAll_static)

SE_DECLARE_FINALIZE_FUNC(js_cc_EffectAsset_finalize)

static bool js_assets_EffectAsset_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::EffectAsset* cobj = JSB_ALLOC(cc::EffectAsset);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_EffectAsset_constructor, __jsb_cc_EffectAsset_class, js_cc_EffectAsset_finalize)



static bool js_cc_EffectAsset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::EffectAsset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::EffectAsset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_EffectAsset_finalize)

bool js_register_assets_EffectAsset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("EffectAsset", obj, __jsb_cc_Asset_proto, _SE(js_assets_EffectAsset_constructor));

    cls->defineStaticFunction("registerAsset", _SE(js_assets_EffectAsset_registerAsset_static));
    cls->defineStaticFunction("remove", _SE(js_assets_EffectAsset_remove_static));
    cls->defineStaticFunction("get", _SE(js_assets_EffectAsset_get_static));
    cls->defineStaticFunction("getAll", _SE(js_assets_EffectAsset_getAll_static));
    cls->defineFinalizeFunction(_SE(js_cc_EffectAsset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::EffectAsset>(cls);

    __jsb_cc_EffectAsset_proto = cls->getProto();
    __jsb_cc_EffectAsset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_JsonAsset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_JsonAsset_class = nullptr;  // NOLINT

SE_DECLARE_FINALIZE_FUNC(js_cc_JsonAsset_finalize)

static bool js_assets_JsonAsset_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::JsonAsset* cobj = JSB_ALLOC(cc::JsonAsset);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_JsonAsset_constructor, __jsb_cc_JsonAsset_class, js_cc_JsonAsset_finalize)



static bool js_cc_JsonAsset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::JsonAsset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::JsonAsset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_JsonAsset_finalize)

bool js_register_assets_JsonAsset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("JsonAsset", obj, __jsb_cc_Asset_proto, _SE(js_assets_JsonAsset_constructor));

    cls->defineFinalizeFunction(_SE(js_cc_JsonAsset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::JsonAsset>(cls);

    __jsb_cc_JsonAsset_proto = cls->getProto();
    __jsb_cc_JsonAsset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IMaterialInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IMaterialInfo_class = nullptr;  // NOLINT

static bool js_assets_IMaterialInfo_get_effectAsset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_get_effectAsset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->effectAsset, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->effectAsset, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMaterialInfo_get_effectAsset)

static bool js_assets_IMaterialInfo_set_effectAsset(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_set_effectAsset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->effectAsset, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMaterialInfo_set_effectAsset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMaterialInfo_set_effectAsset)

static bool js_assets_IMaterialInfo_get_effectName(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_get_effectName : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->effectName, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->effectName, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMaterialInfo_get_effectName)

static bool js_assets_IMaterialInfo_set_effectName(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_set_effectName : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->effectName, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMaterialInfo_set_effectName : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMaterialInfo_set_effectName)

static bool js_assets_IMaterialInfo_get_technique(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_get_technique : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->technique, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->technique, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMaterialInfo_get_technique)

static bool js_assets_IMaterialInfo_set_technique(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_set_technique : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->technique, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMaterialInfo_set_technique : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMaterialInfo_set_technique)

static bool js_assets_IMaterialInfo_get_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_get_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->defines, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->defines, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMaterialInfo_get_defines)

static bool js_assets_IMaterialInfo_set_defines(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_set_defines : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->defines, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMaterialInfo_set_defines : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMaterialInfo_set_defines)

static bool js_assets_IMaterialInfo_get_states(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_get_states : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->states, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->states, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMaterialInfo_get_states)

static bool js_assets_IMaterialInfo_set_states(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMaterialInfo_set_states : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->states, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMaterialInfo_set_states : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMaterialInfo_set_states)


template<>
bool sevalue_to_native(const se::Value &from, cc::IMaterialInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IMaterialInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("effectAsset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->effectAsset), ctx);
    }
    json->getProperty("effectName", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->effectName), ctx);
    }
    json->getProperty("technique", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->technique), ctx);
    }
    json->getProperty("defines", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->defines), ctx);
    }
    json->getProperty("states", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->states), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IMaterialInfo_finalize)

static bool js_assets_IMaterialInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IMaterialInfo* cobj = JSB_ALLOC(cc::IMaterialInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IMaterialInfo* cobj = JSB_ALLOC(cc::IMaterialInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IMaterialInfo* cobj = JSB_ALLOC(cc::IMaterialInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->effectAsset), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->effectName), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->technique), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->defines), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->states), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IMaterialInfo_constructor, __jsb_cc_IMaterialInfo_class, js_cc_IMaterialInfo_finalize)



static bool js_cc_IMaterialInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IMaterialInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IMaterialInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IMaterialInfo_finalize)

bool js_register_assets_IMaterialInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IMaterialInfo", obj, nullptr, _SE(js_assets_IMaterialInfo_constructor));

    cls->defineProperty("effectAsset", _SE(js_assets_IMaterialInfo_get_effectAsset), _SE(js_assets_IMaterialInfo_set_effectAsset));
    cls->defineProperty("effectName", _SE(js_assets_IMaterialInfo_get_effectName), _SE(js_assets_IMaterialInfo_set_effectName));
    cls->defineProperty("technique", _SE(js_assets_IMaterialInfo_get_technique), _SE(js_assets_IMaterialInfo_set_technique));
    cls->defineProperty("defines", _SE(js_assets_IMaterialInfo_get_defines), _SE(js_assets_IMaterialInfo_set_defines));
    cls->defineProperty("states", _SE(js_assets_IMaterialInfo_get_states), _SE(js_assets_IMaterialInfo_set_states));
    cls->defineFinalizeFunction(_SE(js_cc_IMaterialInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IMaterialInfo>(cls);

    __jsb_cc_IMaterialInfo_proto = cls->getProto();
    __jsb_cc_IMaterialInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Material_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Material_class = nullptr;  // NOLINT

static bool js_assets_Material_copy(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_copy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<const cc::Material*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_copy : Error processing arguments");
        cobj->copy(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_copy)

static bool js_assets_Material_getEffectAsset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getEffectAsset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::EffectAsset* result = cobj->getEffectAsset();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getEffectAsset : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getEffectAsset)

static bool js_assets_Material_getEffectName(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getEffectName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getEffectName();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getEffectName : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getEffectName)

static bool js_assets_Material_getHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        uint64_t result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getHash)

static bool js_assets_Material_getParent(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getParent : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::Material* result = cobj->getParent();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getParent : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getParent)

static bool js_assets_Material_getPasses(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getPasses : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::vector<cc::scene::Pass *>& result = cobj->getPasses();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getPasses : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getPasses)

static bool js_assets_Material_getProperty(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getProperty : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_getProperty : Error processing arguments");
        std::variant<std::monostate, std::variant<std::monostate, float, int, cc::Vec2, cc::Vec3, cc::Vec4, cc::Color, cc::Mat3, cc::Mat4, cc::Quaternion, cc::TextureBase *, cc::gfx::Texture *>, std::vector<std::variant<std::monostate, float, int, cc::Vec2, cc::Vec3, cc::Vec4, cc::Color, cc::Mat3, cc::Mat4, cc::Quaternion, cc::TextureBase *, cc::gfx::Texture *>>>* result = cobj->getProperty(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getProperty : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    if (argc == 2) {
        HolderType<std::string, true> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_getProperty : Error processing arguments");
        std::variant<std::monostate, std::variant<std::monostate, float, int, cc::Vec2, cc::Vec3, cc::Vec4, cc::Color, cc::Mat3, cc::Mat4, cc::Quaternion, cc::TextureBase *, cc::gfx::Texture *>, std::vector<std::variant<std::monostate, float, int, cc::Vec2, cc::Vec3, cc::Vec4, cc::Color, cc::Mat3, cc::Mat4, cc::Quaternion, cc::TextureBase *, cc::gfx::Texture *>>>* result = cobj->getProperty(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getProperty : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getProperty)

static bool js_assets_Material_getTechniqueIndex(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_getTechniqueIndex : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getTechniqueIndex();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getTechniqueIndex : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getTechniqueIndex)

static bool js_assets_Material_initialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::IMaterialInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_initialize)

static bool js_assets_Material_overridePipelineStates(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_overridePipelineStates : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<cc::IPassStates, true> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_overridePipelineStates : Error processing arguments");
        cobj->overridePipelineStates(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_Material_overridePipelineStates)

static bool js_assets_Material_reset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_reset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::IMaterialInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_reset : Error processing arguments");
        cobj->reset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_reset)

static bool js_assets_Material_resetUniforms(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_resetUniforms : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->resetUniforms();
        return true;
    }
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_resetUniforms : Error processing arguments");
        cobj->resetUniforms(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_resetUniforms)

static bool js_assets_Material_setEffectAsset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_setEffectAsset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::EffectAsset*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_setEffectAsset : Error processing arguments");
        cobj->setEffectAsset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_setEffectAsset)

static bool js_assets_Material_update(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Material_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->update();
        return true;
    }
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Material_update : Error processing arguments");
        cobj->update(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_update)

static bool js_assets_Material_getHashForMaterial_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Material*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getHashForMaterial_static : Error processing arguments");
        uint64_t result = cc::Material::getHashForMaterial(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Material_getHashForMaterial_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Material_getHashForMaterial_static)

SE_DECLARE_FINALIZE_FUNC(js_cc_Material_finalize)

static bool js_assets_Material_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::Material* cobj = JSB_ALLOC(cc::Material);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_Material_constructor, __jsb_cc_Material_class, js_cc_Material_finalize)



static bool js_cc_Material_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Material>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Material>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Material_finalize)

bool js_register_assets_Material(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Material", obj, __jsb_cc_Asset_proto, _SE(js_assets_Material_constructor));

    cls->defineFunction("copy", _SE(js_assets_Material_copy));
    cls->defineFunction("getEffectAsset", _SE(js_assets_Material_getEffectAsset));
    cls->defineFunction("getEffectName", _SE(js_assets_Material_getEffectName));
    cls->defineFunction("getHash", _SE(js_assets_Material_getHash));
    cls->defineFunction("getParent", _SE(js_assets_Material_getParent));
    cls->defineFunction("getPasses", _SE(js_assets_Material_getPasses));
    cls->defineFunction("getProperty", _SE(js_assets_Material_getProperty));
    cls->defineFunction("getTechniqueIndex", _SE(js_assets_Material_getTechniqueIndex));
    cls->defineFunction("initialize", _SE(js_assets_Material_initialize));
    cls->defineFunction("overridePipelineStates", _SE(js_assets_Material_overridePipelineStates));
    cls->defineFunction("reset", _SE(js_assets_Material_reset));
    cls->defineFunction("resetUniforms", _SE(js_assets_Material_resetUniforms));
    cls->defineFunction("setEffectAsset", _SE(js_assets_Material_setEffectAsset));
    cls->defineFunction("update", _SE(js_assets_Material_update));
    cls->defineStaticFunction("getHashForMaterial", _SE(js_assets_Material_getHashForMaterial_static));
    cls->defineFinalizeFunction(_SE(js_cc_Material_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Material>(cls);

    __jsb_cc_Material_proto = cls->getProto();
    __jsb_cc_Material_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Prefab_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Prefab_class = nullptr;  // NOLINT

static bool js_assets_Prefab__instantiate(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Prefab>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Prefab__instantiate : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::Node* result = cobj->_instantiate();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Prefab__instantiate : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Prefab__instantiate)

SE_DECLARE_FINALIZE_FUNC(js_cc_Prefab_finalize)

static bool js_assets_Prefab_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::Prefab* cobj = JSB_ALLOC(cc::Prefab);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_Prefab_constructor, __jsb_cc_Prefab_class, js_cc_Prefab_finalize)



static bool js_cc_Prefab_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Prefab>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Prefab>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Prefab_finalize)

bool js_register_assets_Prefab(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Prefab", obj, __jsb_cc_Asset_proto, _SE(js_assets_Prefab_constructor));

    cls->defineFunction("_instantiate", _SE(js_assets_Prefab__instantiate));
    cls->defineFinalizeFunction(_SE(js_cc_Prefab_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Prefab>(cls);

    __jsb_cc_Prefab_proto = cls->getProto();
    __jsb_cc_Prefab_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IRenderTextureCreateInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IRenderTextureCreateInfo_class = nullptr;  // NOLINT

static bool js_assets_IRenderTextureCreateInfo_get_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->name, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IRenderTextureCreateInfo_get_name)

static bool js_assets_IRenderTextureCreateInfo_set_name(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IRenderTextureCreateInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IRenderTextureCreateInfo_set_name)

static bool js_assets_IRenderTextureCreateInfo_get_width(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->width, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IRenderTextureCreateInfo_get_width)

static bool js_assets_IRenderTextureCreateInfo_set_width(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IRenderTextureCreateInfo_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IRenderTextureCreateInfo_set_width)

static bool js_assets_IRenderTextureCreateInfo_get_height(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->height, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IRenderTextureCreateInfo_get_height)

static bool js_assets_IRenderTextureCreateInfo_set_height(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IRenderTextureCreateInfo_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IRenderTextureCreateInfo_set_height)

static bool js_assets_IRenderTextureCreateInfo_get_passInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_get_passInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->passInfo, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->passInfo, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IRenderTextureCreateInfo_get_passInfo)

static bool js_assets_IRenderTextureCreateInfo_set_passInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IRenderTextureCreateInfo_set_passInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->passInfo, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IRenderTextureCreateInfo_set_passInfo : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IRenderTextureCreateInfo_set_passInfo)


template<>
bool sevalue_to_native(const se::Value &from, cc::IRenderTextureCreateInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IRenderTextureCreateInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name), ctx);
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width), ctx);
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height), ctx);
    }
    json->getProperty("passInfo", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->passInfo), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IRenderTextureCreateInfo_finalize)

static bool js_assets_IRenderTextureCreateInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IRenderTextureCreateInfo* cobj = JSB_ALLOC(cc::IRenderTextureCreateInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IRenderTextureCreateInfo* cobj = JSB_ALLOC(cc::IRenderTextureCreateInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IRenderTextureCreateInfo* cobj = JSB_ALLOC(cc::IRenderTextureCreateInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->name), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->width), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->height), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->passInfo), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IRenderTextureCreateInfo_constructor, __jsb_cc_IRenderTextureCreateInfo_class, js_cc_IRenderTextureCreateInfo_finalize)



static bool js_cc_IRenderTextureCreateInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IRenderTextureCreateInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IRenderTextureCreateInfo_finalize)

bool js_register_assets_IRenderTextureCreateInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IRenderTextureCreateInfo", obj, nullptr, _SE(js_assets_IRenderTextureCreateInfo_constructor));

    cls->defineProperty("name", _SE(js_assets_IRenderTextureCreateInfo_get_name), _SE(js_assets_IRenderTextureCreateInfo_set_name));
    cls->defineProperty("width", _SE(js_assets_IRenderTextureCreateInfo_get_width), _SE(js_assets_IRenderTextureCreateInfo_set_width));
    cls->defineProperty("height", _SE(js_assets_IRenderTextureCreateInfo_get_height), _SE(js_assets_IRenderTextureCreateInfo_set_height));
    cls->defineProperty("passInfo", _SE(js_assets_IRenderTextureCreateInfo_get_passInfo), _SE(js_assets_IRenderTextureCreateInfo_set_passInfo));
    cls->defineFinalizeFunction(_SE(js_cc_IRenderTextureCreateInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IRenderTextureCreateInfo>(cls);

    __jsb_cc_IRenderTextureCreateInfo_proto = cls->getProto();
    __jsb_cc_IRenderTextureCreateInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_RenderTexture_proto = nullptr; // NOLINT
se::Class* __jsb_cc_RenderTexture_class = nullptr;  // NOLINT

static bool js_assets_RenderTexture_getHeight(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderTexture_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderTexture_getHeight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_getHeight)

static bool js_assets_RenderTexture_getWidth(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderTexture_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderTexture_getWidth : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_getWidth)

static bool js_assets_RenderTexture_getWindow(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderTexture_getWindow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::scene::RenderWindow* result = cobj->getWindow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_RenderTexture_getWindow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_getWindow)

static bool js_assets_RenderTexture_initWindow(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2( cobj, false, "js_assets_RenderTexture_initWindow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 1) {
            HolderType<cc::IRenderTextureCreateInfo, true> arg0 = {};

            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            cobj->initWindow(arg0.value());
            return true;
        }
    } while(false);

    do {
        if (argc == 0) {

            cobj->initWindow();
            return true;
        }
    } while(false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_initWindow)

static bool js_assets_RenderTexture_initialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderTexture_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::IRenderTextureCreateInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderTexture_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_initialize)

static bool js_assets_RenderTexture_reset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderTexture_reset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::IRenderTextureCreateInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderTexture_reset : Error processing arguments");
        cobj->reset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_reset)

static bool js_assets_RenderTexture_resize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_RenderTexture_resize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_RenderTexture_resize : Error processing arguments");
        cobj->resize(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_RenderTexture_resize)

SE_DECLARE_FINALIZE_FUNC(js_cc_RenderTexture_finalize)

static bool js_assets_RenderTexture_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::RenderTexture* cobj = JSB_ALLOC(cc::RenderTexture);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_RenderTexture_constructor, __jsb_cc_RenderTexture_class, js_cc_RenderTexture_finalize)



static bool js_cc_RenderTexture_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::RenderTexture>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::RenderTexture>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_RenderTexture_finalize)

bool js_register_assets_RenderTexture(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("RenderTexture", obj, __jsb_cc_TextureBase_proto, _SE(js_assets_RenderTexture_constructor));

    cls->defineFunction("getHeight", _SE(js_assets_RenderTexture_getHeight));
    cls->defineFunction("getWidth", _SE(js_assets_RenderTexture_getWidth));
    cls->defineFunction("getWindow", _SE(js_assets_RenderTexture_getWindow));
    cls->defineFunction("initWindow", _SE(js_assets_RenderTexture_initWindow));
    cls->defineFunction("initialize", _SE(js_assets_RenderTexture_initialize));
    cls->defineFunction("reset", _SE(js_assets_RenderTexture_reset));
    cls->defineFunction("resize", _SE(js_assets_RenderTexture_resize));
    cls->defineFinalizeFunction(_SE(js_cc_RenderTexture_finalize));
    cls->install();
    JSBClassType::registerClass<cc::RenderTexture>(cls);

    __jsb_cc_RenderTexture_proto = cls->getProto();
    __jsb_cc_RenderTexture_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_SceneAsset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_SceneAsset_class = nullptr;  // NOLINT

static bool js_assets_SceneAsset_getScene(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SceneAsset>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SceneAsset_getScene : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::Scene* result = cobj->getScene();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_SceneAsset_getScene : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_SceneAsset_getScene)

SE_DECLARE_FINALIZE_FUNC(js_cc_SceneAsset_finalize)

static bool js_assets_SceneAsset_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::SceneAsset* cobj = JSB_ALLOC(cc::SceneAsset);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_SceneAsset_constructor, __jsb_cc_SceneAsset_class, js_cc_SceneAsset_finalize)



static bool js_cc_SceneAsset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::SceneAsset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::SceneAsset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_SceneAsset_finalize)

bool js_register_assets_SceneAsset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("SceneAsset", obj, __jsb_cc_Asset_proto, _SE(js_assets_SceneAsset_constructor));

    cls->defineFunction("getScene", _SE(js_assets_SceneAsset_getScene));
    cls->defineFinalizeFunction(_SE(js_cc_SceneAsset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::SceneAsset>(cls);

    __jsb_cc_SceneAsset_proto = cls->getProto();
    __jsb_cc_SceneAsset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_TextAsset_proto = nullptr; // NOLINT
se::Class* __jsb_cc_TextAsset_class = nullptr;  // NOLINT

SE_DECLARE_FINALIZE_FUNC(js_cc_TextAsset_finalize)

static bool js_assets_TextAsset_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::TextAsset* cobj = JSB_ALLOC(cc::TextAsset);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_TextAsset_constructor, __jsb_cc_TextAsset_class, js_cc_TextAsset_finalize)



static bool js_cc_TextAsset_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::TextAsset>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::TextAsset>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_TextAsset_finalize)

bool js_register_assets_TextAsset(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("TextAsset", obj, __jsb_cc_Asset_proto, _SE(js_assets_TextAsset_constructor));

    cls->defineFinalizeFunction(_SE(js_cc_TextAsset_finalize));
    cls->install();
    JSBClassType::registerClass<cc::TextAsset>(cls);

    __jsb_cc_TextAsset_proto = cls->getProto();
    __jsb_cc_TextAsset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ITextureCubeMipmap_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ITextureCubeMipmap_class = nullptr;  // NOLINT

static bool js_assets_ITextureCubeMipmap_get_front(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_get_front : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->front, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->front, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeMipmap_get_front)

static bool js_assets_ITextureCubeMipmap_set_front(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_set_front : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->front, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeMipmap_set_front : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeMipmap_set_front)

static bool js_assets_ITextureCubeMipmap_get_back(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_get_back : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->back, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->back, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeMipmap_get_back)

static bool js_assets_ITextureCubeMipmap_set_back(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_set_back : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->back, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeMipmap_set_back : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeMipmap_set_back)

static bool js_assets_ITextureCubeMipmap_get_left(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_get_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->left, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->left, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeMipmap_get_left)

static bool js_assets_ITextureCubeMipmap_set_left(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_set_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->left, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeMipmap_set_left : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeMipmap_set_left)

static bool js_assets_ITextureCubeMipmap_get_right(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_get_right : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->right, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->right, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeMipmap_get_right)

static bool js_assets_ITextureCubeMipmap_set_right(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_set_right : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->right, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeMipmap_set_right : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeMipmap_set_right)

static bool js_assets_ITextureCubeMipmap_get_top(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_get_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->top, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->top, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeMipmap_get_top)

static bool js_assets_ITextureCubeMipmap_set_top(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_set_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->top, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeMipmap_set_top : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeMipmap_set_top)

static bool js_assets_ITextureCubeMipmap_get_bottom(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_get_bottom : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->bottom, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->bottom, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeMipmap_get_bottom)

static bool js_assets_ITextureCubeMipmap_set_bottom(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeMipmap_set_bottom : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->bottom, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeMipmap_set_bottom : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeMipmap_set_bottom)


template<>
bool sevalue_to_native(const se::Value &from, cc::ITextureCubeMipmap * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ITextureCubeMipmap*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("front", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->front), ctx);
    }
    json->getProperty("back", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->back), ctx);
    }
    json->getProperty("left", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->left), ctx);
    }
    json->getProperty("right", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->right), ctx);
    }
    json->getProperty("top", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->top), ctx);
    }
    json->getProperty("bottom", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->bottom), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ITextureCubeMipmap_finalize)

static bool js_assets_ITextureCubeMipmap_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ITextureCubeMipmap* cobj = JSB_ALLOC(cc::ITextureCubeMipmap);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ITextureCubeMipmap* cobj = JSB_ALLOC(cc::ITextureCubeMipmap);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ITextureCubeMipmap* cobj = JSB_ALLOC(cc::ITextureCubeMipmap);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->front), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->back), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->left), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->right), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->top), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->bottom), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ITextureCubeMipmap_constructor, __jsb_cc_ITextureCubeMipmap_class, js_cc_ITextureCubeMipmap_finalize)



static bool js_cc_ITextureCubeMipmap_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeMipmap>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ITextureCubeMipmap_finalize)

bool js_register_assets_ITextureCubeMipmap(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ITextureCubeMipmap", obj, nullptr, _SE(js_assets_ITextureCubeMipmap_constructor));

    cls->defineProperty("front", _SE(js_assets_ITextureCubeMipmap_get_front), _SE(js_assets_ITextureCubeMipmap_set_front));
    cls->defineProperty("back", _SE(js_assets_ITextureCubeMipmap_get_back), _SE(js_assets_ITextureCubeMipmap_set_back));
    cls->defineProperty("left", _SE(js_assets_ITextureCubeMipmap_get_left), _SE(js_assets_ITextureCubeMipmap_set_left));
    cls->defineProperty("right", _SE(js_assets_ITextureCubeMipmap_get_right), _SE(js_assets_ITextureCubeMipmap_set_right));
    cls->defineProperty("top", _SE(js_assets_ITextureCubeMipmap_get_top), _SE(js_assets_ITextureCubeMipmap_set_top));
    cls->defineProperty("bottom", _SE(js_assets_ITextureCubeMipmap_get_bottom), _SE(js_assets_ITextureCubeMipmap_set_bottom));
    cls->defineFinalizeFunction(_SE(js_cc_ITextureCubeMipmap_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ITextureCubeMipmap>(cls);

    __jsb_cc_ITextureCubeMipmap_proto = cls->getProto();
    __jsb_cc_ITextureCubeMipmap_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ITextureCubeSerializeMipmapData_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ITextureCubeSerializeMipmapData_class = nullptr;  // NOLINT

static bool js_assets_ITextureCubeSerializeMipmapData_get_front(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_get_front : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->front, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->front, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeMipmapData_get_front)

static bool js_assets_ITextureCubeSerializeMipmapData_set_front(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_set_front : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->front, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeMipmapData_set_front : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeMipmapData_set_front)

static bool js_assets_ITextureCubeSerializeMipmapData_get_back(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_get_back : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->back, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->back, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeMipmapData_get_back)

static bool js_assets_ITextureCubeSerializeMipmapData_set_back(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_set_back : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->back, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeMipmapData_set_back : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeMipmapData_set_back)

static bool js_assets_ITextureCubeSerializeMipmapData_get_left(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_get_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->left, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->left, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeMipmapData_get_left)

static bool js_assets_ITextureCubeSerializeMipmapData_set_left(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_set_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->left, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeMipmapData_set_left : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeMipmapData_set_left)

static bool js_assets_ITextureCubeSerializeMipmapData_get_right(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_get_right : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->right, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->right, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeMipmapData_get_right)

static bool js_assets_ITextureCubeSerializeMipmapData_set_right(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_set_right : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->right, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeMipmapData_set_right : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeMipmapData_set_right)

static bool js_assets_ITextureCubeSerializeMipmapData_get_top(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_get_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->top, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->top, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeMipmapData_get_top)

static bool js_assets_ITextureCubeSerializeMipmapData_set_top(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_set_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->top, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeMipmapData_set_top : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeMipmapData_set_top)

static bool js_assets_ITextureCubeSerializeMipmapData_get_bottom(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_get_bottom : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->bottom, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->bottom, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeMipmapData_get_bottom)

static bool js_assets_ITextureCubeSerializeMipmapData_set_bottom(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeMipmapData_set_bottom : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->bottom, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeMipmapData_set_bottom : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeMipmapData_set_bottom)


template<>
bool sevalue_to_native(const se::Value &from, cc::ITextureCubeSerializeMipmapData * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ITextureCubeSerializeMipmapData*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("front", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->front), ctx);
    }
    json->getProperty("back", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->back), ctx);
    }
    json->getProperty("left", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->left), ctx);
    }
    json->getProperty("right", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->right), ctx);
    }
    json->getProperty("top", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->top), ctx);
    }
    json->getProperty("bottom", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->bottom), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ITextureCubeSerializeMipmapData_finalize)

static bool js_assets_ITextureCubeSerializeMipmapData_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ITextureCubeSerializeMipmapData* cobj = JSB_ALLOC(cc::ITextureCubeSerializeMipmapData);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ITextureCubeSerializeMipmapData* cobj = JSB_ALLOC(cc::ITextureCubeSerializeMipmapData);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ITextureCubeSerializeMipmapData* cobj = JSB_ALLOC(cc::ITextureCubeSerializeMipmapData);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->front), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->back), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->left), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->right), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->top), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->bottom), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ITextureCubeSerializeMipmapData_constructor, __jsb_cc_ITextureCubeSerializeMipmapData_class, js_cc_ITextureCubeSerializeMipmapData_finalize)



static bool js_cc_ITextureCubeSerializeMipmapData_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeMipmapData>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ITextureCubeSerializeMipmapData_finalize)

bool js_register_assets_ITextureCubeSerializeMipmapData(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ITextureCubeSerializeMipmapData", obj, nullptr, _SE(js_assets_ITextureCubeSerializeMipmapData_constructor));

    cls->defineProperty("front", _SE(js_assets_ITextureCubeSerializeMipmapData_get_front), _SE(js_assets_ITextureCubeSerializeMipmapData_set_front));
    cls->defineProperty("back", _SE(js_assets_ITextureCubeSerializeMipmapData_get_back), _SE(js_assets_ITextureCubeSerializeMipmapData_set_back));
    cls->defineProperty("left", _SE(js_assets_ITextureCubeSerializeMipmapData_get_left), _SE(js_assets_ITextureCubeSerializeMipmapData_set_left));
    cls->defineProperty("right", _SE(js_assets_ITextureCubeSerializeMipmapData_get_right), _SE(js_assets_ITextureCubeSerializeMipmapData_set_right));
    cls->defineProperty("top", _SE(js_assets_ITextureCubeSerializeMipmapData_get_top), _SE(js_assets_ITextureCubeSerializeMipmapData_set_top));
    cls->defineProperty("bottom", _SE(js_assets_ITextureCubeSerializeMipmapData_get_bottom), _SE(js_assets_ITextureCubeSerializeMipmapData_set_bottom));
    cls->defineFinalizeFunction(_SE(js_cc_ITextureCubeSerializeMipmapData_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ITextureCubeSerializeMipmapData>(cls);

    __jsb_cc_ITextureCubeSerializeMipmapData_proto = cls->getProto();
    __jsb_cc_ITextureCubeSerializeMipmapData_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_ITextureCubeSerializeData_proto = nullptr; // NOLINT
se::Class* __jsb_cc_ITextureCubeSerializeData_class = nullptr;  // NOLINT

static bool js_assets_ITextureCubeSerializeData_get_base(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeData_get_base : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->base, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->base, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeData_get_base)

static bool js_assets_ITextureCubeSerializeData_set_base(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeData_set_base : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->base, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeData_set_base : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeData_set_base)

static bool js_assets_ITextureCubeSerializeData_get_rgbe(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeData_get_rgbe : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->rgbe, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->rgbe, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeData_get_rgbe)

static bool js_assets_ITextureCubeSerializeData_set_rgbe(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeData_set_rgbe : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->rgbe, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeData_set_rgbe : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeData_set_rgbe)

static bool js_assets_ITextureCubeSerializeData_get_mipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeData_get_mipmaps : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->mipmaps, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->mipmaps, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ITextureCubeSerializeData_get_mipmaps)

static bool js_assets_ITextureCubeSerializeData_set_mipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ITextureCubeSerializeData_set_mipmaps : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->mipmaps, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ITextureCubeSerializeData_set_mipmaps : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ITextureCubeSerializeData_set_mipmaps)


template<>
bool sevalue_to_native(const se::Value &from, cc::ITextureCubeSerializeData * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::ITextureCubeSerializeData*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("base", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->base), ctx);
    }
    json->getProperty("rgbe", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->rgbe), ctx);
    }
    json->getProperty("mipmaps", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->mipmaps), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_ITextureCubeSerializeData_finalize)

static bool js_assets_ITextureCubeSerializeData_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::ITextureCubeSerializeData* cobj = JSB_ALLOC(cc::ITextureCubeSerializeData);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::ITextureCubeSerializeData* cobj = JSB_ALLOC(cc::ITextureCubeSerializeData);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::ITextureCubeSerializeData* cobj = JSB_ALLOC(cc::ITextureCubeSerializeData);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->base), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->rgbe), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->mipmaps), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ITextureCubeSerializeData_constructor, __jsb_cc_ITextureCubeSerializeData_class, js_cc_ITextureCubeSerializeData_finalize)



static bool js_cc_ITextureCubeSerializeData_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ITextureCubeSerializeData>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ITextureCubeSerializeData_finalize)

bool js_register_assets_ITextureCubeSerializeData(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ITextureCubeSerializeData", obj, nullptr, _SE(js_assets_ITextureCubeSerializeData_constructor));

    cls->defineProperty("base", _SE(js_assets_ITextureCubeSerializeData_get_base), _SE(js_assets_ITextureCubeSerializeData_set_base));
    cls->defineProperty("rgbe", _SE(js_assets_ITextureCubeSerializeData_get_rgbe), _SE(js_assets_ITextureCubeSerializeData_set_rgbe));
    cls->defineProperty("mipmaps", _SE(js_assets_ITextureCubeSerializeData_get_mipmaps), _SE(js_assets_ITextureCubeSerializeData_set_mipmaps));
    cls->defineFinalizeFunction(_SE(js_cc_ITextureCubeSerializeData_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ITextureCubeSerializeData>(cls);

    __jsb_cc_ITextureCubeSerializeData_proto = cls->getProto();
    __jsb_cc_ITextureCubeSerializeData_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_TextureCube_proto = nullptr; // NOLINT
se::Class* __jsb_cc_TextureCube_class = nullptr;  // NOLINT

static bool js_assets_TextureCube_getGfxTextureCreateInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_getGfxTextureCreateInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        HolderType<cc::gfx::TextureUsageBit, false> arg0 = {};
        HolderType<cc::gfx::Format, false> arg1 = {};
        HolderType<unsigned int, false> arg2 = {};
        HolderType<cc::gfx::TextureFlagBit, false> arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_getGfxTextureCreateInfo : Error processing arguments");
        cc::gfx::TextureInfo result = cobj->getGfxTextureCreateInfo(arg0.value(), arg1.value(), arg2.value(), arg3.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_getGfxTextureCreateInfo : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_getGfxTextureCreateInfo)

static bool js_assets_TextureCube_getImage(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_getImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::ITextureCubeMipmap* result = cobj->getImage();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_getImage : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_getImage)

static bool js_assets_TextureCube_getMipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_getMipmaps : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::ITextureCubeMipmap>& result = cobj->getMipmaps();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_getMipmaps : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_getMipmaps)

static bool js_assets_TextureCube_initialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->initialize();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_initialize)

static bool js_assets_TextureCube_releaseTexture(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_releaseTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->releaseTexture();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_releaseTexture)

static bool js_assets_TextureCube_reset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_reset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::ITexture2DCreateInfo, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_reset : Error processing arguments");
        cobj->reset(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_reset)

static bool js_assets_TextureCube_setImage(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_setImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::ITextureCubeMipmap, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_setImage : Error processing arguments");
        cobj->setImage(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_setImage)

static bool js_assets_TextureCube_setMipmaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_TextureCube_setMipmaps : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<cc::ITextureCubeMipmap>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_setMipmaps : Error processing arguments");
        cobj->setMipmaps(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_setMipmaps)

static bool js_assets_TextureCube_fromTexture2DArray_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<cc::Texture2D *>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_fromTexture2DArray_static : Error processing arguments");
        cc::TextureCube* result = cc::TextureCube::fromTexture2DArray(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_TextureCube_fromTexture2DArray_static : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_TextureCube_fromTexture2DArray_static)

SE_DECLARE_FINALIZE_FUNC(js_cc_TextureCube_finalize)

static bool js_assets_TextureCube_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::TextureCube* cobj = JSB_ALLOC(cc::TextureCube);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_TextureCube_constructor, __jsb_cc_TextureCube_class, js_cc_TextureCube_finalize)



static bool js_cc_TextureCube_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::TextureCube>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::TextureCube>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_TextureCube_finalize)

bool js_register_assets_TextureCube(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("TextureCube", obj, __jsb_cc_SimpleTexture_proto, _SE(js_assets_TextureCube_constructor));

    cls->defineFunction("getGfxTextureCreateInfo", _SE(js_assets_TextureCube_getGfxTextureCreateInfo));
    cls->defineFunction("getImage", _SE(js_assets_TextureCube_getImage));
    cls->defineFunction("getMipmaps", _SE(js_assets_TextureCube_getMipmaps));
    cls->defineFunction("initialize", _SE(js_assets_TextureCube_initialize));
    cls->defineFunction("releaseTexture", _SE(js_assets_TextureCube_releaseTexture));
    cls->defineFunction("reset", _SE(js_assets_TextureCube_reset));
    cls->defineFunction("setImage", _SE(js_assets_TextureCube_setImage));
    cls->defineFunction("setMipmaps", _SE(js_assets_TextureCube_setMipmaps));
    cls->defineStaticFunction("fromTexture2DArray", _SE(js_assets_TextureCube_fromTexture2DArray_static));
    cls->defineFinalizeFunction(_SE(js_cc_TextureCube_finalize));
    cls->install();
    JSBClassType::registerClass<cc::TextureCube>(cls);

    __jsb_cc_TextureCube_proto = cls->getProto();
    __jsb_cc_TextureCube_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_IMeshBufferView_proto = nullptr; // NOLINT
se::Class* __jsb_cc_IMeshBufferView_class = nullptr;  // NOLINT

static bool js_assets_IMeshBufferView_get_offset(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_get_offset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->offset, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->offset, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMeshBufferView_get_offset)

static bool js_assets_IMeshBufferView_set_offset(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_set_offset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->offset, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMeshBufferView_set_offset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMeshBufferView_set_offset)

static bool js_assets_IMeshBufferView_get_length(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_get_length : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->length, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->length, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMeshBufferView_get_length)

static bool js_assets_IMeshBufferView_set_length(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_set_length : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->length, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMeshBufferView_set_length : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMeshBufferView_set_length)

static bool js_assets_IMeshBufferView_get_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->count, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMeshBufferView_get_count)

static bool js_assets_IMeshBufferView_set_count(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMeshBufferView_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMeshBufferView_set_count)

static bool js_assets_IMeshBufferView_get_stride(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_get_stride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stride, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->stride, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IMeshBufferView_get_stride)

static bool js_assets_IMeshBufferView_set_stride(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IMeshBufferView_set_stride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stride, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IMeshBufferView_set_stride : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IMeshBufferView_set_stride)


template<>
bool sevalue_to_native(const se::Value &from, cc::IMeshBufferView * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::IMeshBufferView*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("offset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->offset), ctx);
    }
    json->getProperty("length", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->length), ctx);
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count), ctx);
    }
    json->getProperty("stride", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stride), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_IMeshBufferView_finalize)

static bool js_assets_IMeshBufferView_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::IMeshBufferView* cobj = JSB_ALLOC(cc::IMeshBufferView);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::IMeshBufferView* cobj = JSB_ALLOC(cc::IMeshBufferView);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::IMeshBufferView* cobj = JSB_ALLOC(cc::IMeshBufferView);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->offset), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->length), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->count), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->stride), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IMeshBufferView_constructor, __jsb_cc_IMeshBufferView_class, js_cc_IMeshBufferView_finalize)



static bool js_cc_IMeshBufferView_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::IMeshBufferView>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::IMeshBufferView>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_IMeshBufferView_finalize)

bool js_register_assets_IMeshBufferView(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("IMeshBufferView", obj, nullptr, _SE(js_assets_IMeshBufferView_constructor));

    cls->defineProperty("offset", _SE(js_assets_IMeshBufferView_get_offset), _SE(js_assets_IMeshBufferView_set_offset));
    cls->defineProperty("length", _SE(js_assets_IMeshBufferView_get_length), _SE(js_assets_IMeshBufferView_set_length));
    cls->defineProperty("count", _SE(js_assets_IMeshBufferView_get_count), _SE(js_assets_IMeshBufferView_set_count));
    cls->defineProperty("stride", _SE(js_assets_IMeshBufferView_get_stride), _SE(js_assets_IMeshBufferView_set_stride));
    cls->defineFinalizeFunction(_SE(js_cc_IMeshBufferView_finalize));
    cls->install();
    JSBClassType::registerClass<cc::IMeshBufferView>(cls);

    __jsb_cc_IMeshBufferView_proto = cls->getProto();
    __jsb_cc_IMeshBufferView_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_MorphTarget_proto = nullptr; // NOLINT
se::Class* __jsb_cc_MorphTarget_class = nullptr;  // NOLINT


template<>
bool sevalue_to_native(const se::Value &from, cc::MorphTarget * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::MorphTarget*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("displacements", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->displacements), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_MorphTarget_finalize)

static bool js_assets_MorphTarget_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::MorphTarget* cobj = JSB_ALLOC(cc::MorphTarget);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::MorphTarget* cobj = JSB_ALLOC(cc::MorphTarget);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->displacements), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_MorphTarget_constructor, __jsb_cc_MorphTarget_class, js_cc_MorphTarget_finalize)



static bool js_cc_MorphTarget_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::MorphTarget>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::MorphTarget>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_MorphTarget_finalize)

bool js_register_assets_MorphTarget(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("MorphTarget", obj, nullptr, _SE(js_assets_MorphTarget_constructor));

    cls->defineFinalizeFunction(_SE(js_cc_MorphTarget_finalize));
    cls->install();
    JSBClassType::registerClass<cc::MorphTarget>(cls);

    __jsb_cc_MorphTarget_proto = cls->getProto();
    __jsb_cc_MorphTarget_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_SubMeshMorph_proto = nullptr; // NOLINT
se::Class* __jsb_cc_SubMeshMorph_class = nullptr;  // NOLINT

static bool js_assets_SubMeshMorph_get_attributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SubMeshMorph_get_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->attributes, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->attributes, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_SubMeshMorph_get_attributes)

static bool js_assets_SubMeshMorph_set_attributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SubMeshMorph_set_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->attributes, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_SubMeshMorph_set_attributes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_SubMeshMorph_set_attributes)

static bool js_assets_SubMeshMorph_get_targets(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SubMeshMorph_get_targets : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->targets, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->targets, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_SubMeshMorph_get_targets)

static bool js_assets_SubMeshMorph_set_targets(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SubMeshMorph_set_targets : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->targets, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_SubMeshMorph_set_targets : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_SubMeshMorph_set_targets)

static bool js_assets_SubMeshMorph_get_weights(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SubMeshMorph_get_weights : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->weights, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->weights, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_SubMeshMorph_get_weights)

static bool js_assets_SubMeshMorph_set_weights(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_SubMeshMorph_set_weights : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->weights, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_SubMeshMorph_set_weights : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_SubMeshMorph_set_weights)


template<>
bool sevalue_to_native(const se::Value &from, cc::SubMeshMorph * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::SubMeshMorph*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("attributes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->attributes), ctx);
    }
    json->getProperty("targets", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->targets), ctx);
    }
    json->getProperty("weights", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->weights), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_SubMeshMorph_finalize)

static bool js_assets_SubMeshMorph_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::SubMeshMorph* cobj = JSB_ALLOC(cc::SubMeshMorph);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::SubMeshMorph* cobj = JSB_ALLOC(cc::SubMeshMorph);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::SubMeshMorph* cobj = JSB_ALLOC(cc::SubMeshMorph);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->attributes), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->targets), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->weights), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_SubMeshMorph_constructor, __jsb_cc_SubMeshMorph_class, js_cc_SubMeshMorph_finalize)



static bool js_cc_SubMeshMorph_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::SubMeshMorph>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::SubMeshMorph>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_SubMeshMorph_finalize)

bool js_register_assets_SubMeshMorph(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("SubMeshMorph", obj, nullptr, _SE(js_assets_SubMeshMorph_constructor));

    cls->defineProperty("attributes", _SE(js_assets_SubMeshMorph_get_attributes), _SE(js_assets_SubMeshMorph_set_attributes));
    cls->defineProperty("targets", _SE(js_assets_SubMeshMorph_get_targets), _SE(js_assets_SubMeshMorph_set_targets));
    cls->defineProperty("weights", _SE(js_assets_SubMeshMorph_get_weights), _SE(js_assets_SubMeshMorph_set_weights));
    cls->defineFinalizeFunction(_SE(js_cc_SubMeshMorph_finalize));
    cls->install();
    JSBClassType::registerClass<cc::SubMeshMorph>(cls);

    __jsb_cc_SubMeshMorph_proto = cls->getProto();
    __jsb_cc_SubMeshMorph_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Morph_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Morph_class = nullptr;  // NOLINT

static bool js_assets_Morph_get_subMeshMorphs(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Morph_get_subMeshMorphs : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->subMeshMorphs, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->subMeshMorphs, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_Morph_get_subMeshMorphs)

static bool js_assets_Morph_set_subMeshMorphs(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Morph_set_subMeshMorphs : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->subMeshMorphs, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_Morph_set_subMeshMorphs : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_Morph_set_subMeshMorphs)

static bool js_assets_Morph_get_weights(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Morph_get_weights : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->weights, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->weights, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_Morph_get_weights)

static bool js_assets_Morph_set_weights(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Morph_set_weights : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->weights, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_Morph_set_weights : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_Morph_set_weights)

static bool js_assets_Morph_get_targetNames(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Morph_get_targetNames : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->targetNames, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->targetNames, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_Morph_get_targetNames)

static bool js_assets_Morph_set_targetNames(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Morph_set_targetNames : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->targetNames, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_Morph_set_targetNames : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_Morph_set_targetNames)


template<>
bool sevalue_to_native(const se::Value &from, cc::Morph * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::Morph*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("subMeshMorphs", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->subMeshMorphs), ctx);
    }
    json->getProperty("weights", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->weights), ctx);
    }
    json->getProperty("targetNames", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->targetNames), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_Morph_finalize)

static bool js_assets_Morph_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::Morph* cobj = JSB_ALLOC(cc::Morph);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::Morph* cobj = JSB_ALLOC(cc::Morph);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::Morph* cobj = JSB_ALLOC(cc::Morph);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->subMeshMorphs), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->weights), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->targetNames), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_Morph_constructor, __jsb_cc_Morph_class, js_cc_Morph_finalize)



static bool js_cc_Morph_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Morph>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Morph>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Morph_finalize)

bool js_register_assets_Morph(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Morph", obj, nullptr, _SE(js_assets_Morph_constructor));

    cls->defineProperty("subMeshMorphs", _SE(js_assets_Morph_get_subMeshMorphs), _SE(js_assets_Morph_set_subMeshMorphs));
    cls->defineProperty("weights", _SE(js_assets_Morph_get_weights), _SE(js_assets_Morph_set_weights));
    cls->defineProperty("targetNames", _SE(js_assets_Morph_get_targetNames), _SE(js_assets_Morph_set_targetNames));
    cls->defineFinalizeFunction(_SE(js_cc_Morph_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Morph>(cls);

    __jsb_cc_Morph_proto = cls->getProto();
    __jsb_cc_Morph_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Mesh_IVertexBundle_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Mesh_IVertexBundle_class = nullptr;  // NOLINT

static bool js_assets_IVertexBundle_get_view(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IVertexBundle>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IVertexBundle_get_view : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->view, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->view, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IVertexBundle_get_view)

static bool js_assets_IVertexBundle_set_view(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IVertexBundle>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IVertexBundle_set_view : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->view, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IVertexBundle_set_view : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IVertexBundle_set_view)

static bool js_assets_IVertexBundle_get_attributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IVertexBundle>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IVertexBundle_get_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->attributes, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->attributes, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IVertexBundle_get_attributes)

static bool js_assets_IVertexBundle_set_attributes(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IVertexBundle>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IVertexBundle_set_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->attributes, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IVertexBundle_set_attributes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IVertexBundle_set_attributes)


template<>
bool sevalue_to_native(const se::Value &from, cc::Mesh::IVertexBundle * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::Mesh::IVertexBundle*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("view", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->view), ctx);
    }
    json->getProperty("attributes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->attributes), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_Mesh_IVertexBundle_finalize)

static bool js_assets_IVertexBundle_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::Mesh::IVertexBundle* cobj = JSB_ALLOC(cc::Mesh::IVertexBundle);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::Mesh::IVertexBundle* cobj = JSB_ALLOC(cc::Mesh::IVertexBundle);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::Mesh::IVertexBundle* cobj = JSB_ALLOC(cc::Mesh::IVertexBundle);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->view), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->attributes), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IVertexBundle_constructor, __jsb_cc_Mesh_IVertexBundle_class, js_cc_Mesh_IVertexBundle_finalize)



static bool js_cc_Mesh_IVertexBundle_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Mesh::IVertexBundle>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Mesh::IVertexBundle>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Mesh_IVertexBundle_finalize)

bool js_register_assets_Mesh_IVertexBundle(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create({"Mesh","IVertexBundle"}, obj, nullptr, _SE(js_assets_IVertexBundle_constructor));

    cls->defineProperty("view", _SE(js_assets_IVertexBundle_get_view), _SE(js_assets_IVertexBundle_set_view));
    cls->defineProperty("attributes", _SE(js_assets_IVertexBundle_get_attributes), _SE(js_assets_IVertexBundle_set_attributes));
    cls->defineFinalizeFunction(_SE(js_cc_Mesh_IVertexBundle_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Mesh::IVertexBundle>(cls);

    __jsb_cc_Mesh_IVertexBundle_proto = cls->getProto();
    __jsb_cc_Mesh_IVertexBundle_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Mesh_ISubMesh_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Mesh_ISubMesh_class = nullptr;  // NOLINT

static bool js_assets_ISubMesh_get_vertexBundelIndices(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_get_vertexBundelIndices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vertexBundelIndices, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->vertexBundelIndices, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISubMesh_get_vertexBundelIndices)

static bool js_assets_ISubMesh_set_vertexBundelIndices(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_set_vertexBundelIndices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vertexBundelIndices, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISubMesh_set_vertexBundelIndices : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISubMesh_set_vertexBundelIndices)

static bool js_assets_ISubMesh_get_primitiveMode(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_get_primitiveMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->primitiveMode, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->primitiveMode, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISubMesh_get_primitiveMode)

static bool js_assets_ISubMesh_set_primitiveMode(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_set_primitiveMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->primitiveMode, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISubMesh_set_primitiveMode : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISubMesh_set_primitiveMode)

static bool js_assets_ISubMesh_get_indexView(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_get_indexView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->indexView, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->indexView, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISubMesh_get_indexView)

static bool js_assets_ISubMesh_set_indexView(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_set_indexView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->indexView, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISubMesh_set_indexView : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISubMesh_set_indexView)

static bool js_assets_ISubMesh_get_jointMapIndex(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_get_jointMapIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->jointMapIndex, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->jointMapIndex, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ISubMesh_get_jointMapIndex)

static bool js_assets_ISubMesh_set_jointMapIndex(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ISubMesh_set_jointMapIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->jointMapIndex, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ISubMesh_set_jointMapIndex : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ISubMesh_set_jointMapIndex)


template<>
bool sevalue_to_native(const se::Value &from, cc::Mesh::ISubMesh * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::Mesh::ISubMesh*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("vertexBundelIndices", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vertexBundelIndices), ctx);
    }
    json->getProperty("primitiveMode", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->primitiveMode), ctx);
    }
    json->getProperty("indexView", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->indexView), ctx);
    }
    json->getProperty("jointMapIndex", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->jointMapIndex), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_Mesh_ISubMesh_finalize)

static bool js_assets_ISubMesh_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::Mesh::ISubMesh* cobj = JSB_ALLOC(cc::Mesh::ISubMesh);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::Mesh::ISubMesh* cobj = JSB_ALLOC(cc::Mesh::ISubMesh);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::Mesh::ISubMesh* cobj = JSB_ALLOC(cc::Mesh::ISubMesh);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->vertexBundelIndices), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->primitiveMode), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->indexView), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->jointMapIndex), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ISubMesh_constructor, __jsb_cc_Mesh_ISubMesh_class, js_cc_Mesh_ISubMesh_finalize)



static bool js_cc_Mesh_ISubMesh_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Mesh::ISubMesh>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Mesh_ISubMesh_finalize)

bool js_register_assets_Mesh_ISubMesh(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create({"Mesh","ISubMesh"}, obj, nullptr, _SE(js_assets_ISubMesh_constructor));

    cls->defineProperty("vertexBundelIndices", _SE(js_assets_ISubMesh_get_vertexBundelIndices), _SE(js_assets_ISubMesh_set_vertexBundelIndices));
    cls->defineProperty("primitiveMode", _SE(js_assets_ISubMesh_get_primitiveMode), _SE(js_assets_ISubMesh_set_primitiveMode));
    cls->defineProperty("indexView", _SE(js_assets_ISubMesh_get_indexView), _SE(js_assets_ISubMesh_set_indexView));
    cls->defineProperty("jointMapIndex", _SE(js_assets_ISubMesh_get_jointMapIndex), _SE(js_assets_ISubMesh_set_jointMapIndex));
    cls->defineFinalizeFunction(_SE(js_cc_Mesh_ISubMesh_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Mesh::ISubMesh>(cls);

    __jsb_cc_Mesh_ISubMesh_proto = cls->getProto();
    __jsb_cc_Mesh_ISubMesh_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Mesh_IStruct_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Mesh_IStruct_class = nullptr;  // NOLINT

static bool js_assets_IStruct_get_vertexBundles(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_get_vertexBundles : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vertexBundles, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->vertexBundles, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IStruct_get_vertexBundles)

static bool js_assets_IStruct_set_vertexBundles(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_set_vertexBundles : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vertexBundles, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IStruct_set_vertexBundles : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IStruct_set_vertexBundles)

static bool js_assets_IStruct_get_primitives(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_get_primitives : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->primitives, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->primitives, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IStruct_get_primitives)

static bool js_assets_IStruct_set_primitives(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_set_primitives : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->primitives, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IStruct_set_primitives : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IStruct_set_primitives)

static bool js_assets_IStruct_get_minPosition(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_get_minPosition : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->minPosition, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->minPosition, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IStruct_get_minPosition)

static bool js_assets_IStruct_set_minPosition(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_set_minPosition : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->minPosition, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IStruct_set_minPosition : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IStruct_set_minPosition)

static bool js_assets_IStruct_get_maxPosition(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_get_maxPosition : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->maxPosition, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->maxPosition, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IStruct_get_maxPosition)

static bool js_assets_IStruct_set_maxPosition(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_set_maxPosition : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->maxPosition, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IStruct_set_maxPosition : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IStruct_set_maxPosition)

static bool js_assets_IStruct_get_jointMaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_get_jointMaps : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->jointMaps, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->jointMaps, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IStruct_get_jointMaps)

static bool js_assets_IStruct_set_jointMaps(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_set_jointMaps : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->jointMaps, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IStruct_set_jointMaps : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IStruct_set_jointMaps)

static bool js_assets_IStruct_get_morph(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_get_morph : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->morph, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->morph, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_IStruct_get_morph)

static bool js_assets_IStruct_set_morph(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_IStruct_set_morph : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->morph, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_IStruct_set_morph : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_IStruct_set_morph)


template<>
bool sevalue_to_native(const se::Value &from, cc::Mesh::IStruct * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::Mesh::IStruct*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("vertexBundles", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vertexBundles), ctx);
    }
    json->getProperty("primitives", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->primitives), ctx);
    }
    json->getProperty("minPosition", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->minPosition), ctx);
    }
    json->getProperty("maxPosition", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->maxPosition), ctx);
    }
    json->getProperty("jointMaps", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->jointMaps), ctx);
    }
    json->getProperty("morph", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->morph), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_Mesh_IStruct_finalize)

static bool js_assets_IStruct_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::Mesh::IStruct* cobj = JSB_ALLOC(cc::Mesh::IStruct);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::Mesh::IStruct* cobj = JSB_ALLOC(cc::Mesh::IStruct);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::Mesh::IStruct* cobj = JSB_ALLOC(cc::Mesh::IStruct);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->vertexBundles), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->primitives), nullptr);
    }
    if (argc > 2 && !args[2].isUndefined()) {
        ok &= sevalue_to_native(args[2], &(cobj->minPosition), nullptr);
    }
    if (argc > 3 && !args[3].isUndefined()) {
        ok &= sevalue_to_native(args[3], &(cobj->maxPosition), nullptr);
    }
    if (argc > 4 && !args[4].isUndefined()) {
        ok &= sevalue_to_native(args[4], &(cobj->jointMaps), nullptr);
    }
    if (argc > 5 && !args[5].isUndefined()) {
        ok &= sevalue_to_native(args[5], &(cobj->morph), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_IStruct_constructor, __jsb_cc_Mesh_IStruct_class, js_cc_Mesh_IStruct_finalize)



static bool js_cc_Mesh_IStruct_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Mesh::IStruct>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Mesh::IStruct>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Mesh_IStruct_finalize)

bool js_register_assets_Mesh_IStruct(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create({"Mesh","IStruct"}, obj, nullptr, _SE(js_assets_IStruct_constructor));

    cls->defineProperty("vertexBundles", _SE(js_assets_IStruct_get_vertexBundles), _SE(js_assets_IStruct_set_vertexBundles));
    cls->defineProperty("primitives", _SE(js_assets_IStruct_get_primitives), _SE(js_assets_IStruct_set_primitives));
    cls->defineProperty("minPosition", _SE(js_assets_IStruct_get_minPosition), _SE(js_assets_IStruct_set_minPosition));
    cls->defineProperty("maxPosition", _SE(js_assets_IStruct_get_maxPosition), _SE(js_assets_IStruct_set_maxPosition));
    cls->defineProperty("jointMaps", _SE(js_assets_IStruct_get_jointMaps), _SE(js_assets_IStruct_set_jointMaps));
    cls->defineProperty("morph", _SE(js_assets_IStruct_get_morph), _SE(js_assets_IStruct_set_morph));
    cls->defineFinalizeFunction(_SE(js_cc_Mesh_IStruct_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Mesh::IStruct>(cls);

    __jsb_cc_Mesh_IStruct_proto = cls->getProto();
    __jsb_cc_Mesh_IStruct_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Mesh_ICreateInfo_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Mesh_ICreateInfo_class = nullptr;  // NOLINT

static bool js_assets_ICreateInfo_get_structInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ICreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ICreateInfo_get_structInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->structInfo, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->structInfo, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ICreateInfo_get_structInfo)

static bool js_assets_ICreateInfo_set_structInfo(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ICreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ICreateInfo_set_structInfo : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->structInfo, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ICreateInfo_set_structInfo : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ICreateInfo_set_structInfo)

static bool js_assets_ICreateInfo_get_data(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ICreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ICreateInfo_get_data : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->data, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->data, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_assets_ICreateInfo_get_data)

static bool js_assets_ICreateInfo_set_data(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<cc::Mesh::ICreateInfo>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_ICreateInfo_set_data : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->data, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_ICreateInfo_set_data : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_assets_ICreateInfo_set_data)


template<>
bool sevalue_to_native(const se::Value &from, cc::Mesh::ICreateInfo * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<cc::Mesh::ICreateInfo*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("structInfo", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->structInfo), ctx);
    }
    json->getProperty("data", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->data), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_Mesh_ICreateInfo_finalize)

static bool js_assets_ICreateInfo_constructor(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0)
    {
        cc::Mesh::ICreateInfo* cobj = JSB_ALLOC(cc::Mesh::ICreateInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::Mesh::ICreateInfo* cobj = JSB_ALLOC(cc::Mesh::ICreateInfo);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    cc::Mesh::ICreateInfo* cobj = JSB_ALLOC(cc::Mesh::ICreateInfo);
    if (argc > 0 && !args[0].isUndefined()) {
        ok &= sevalue_to_native(args[0], &(cobj->structInfo), nullptr);
    }
    if (argc > 1 && !args[1].isUndefined()) {
        ok &= sevalue_to_native(args[1], &(cobj->data), nullptr);
    }

    if(!ok) {
        JSB_FREE(cobj);
        SE_REPORT_ERROR("Argument convertion error");
        return false;
    }

    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_ICreateInfo_constructor, __jsb_cc_Mesh_ICreateInfo_class, js_cc_Mesh_ICreateInfo_finalize)



static bool js_cc_Mesh_ICreateInfo_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Mesh::ICreateInfo>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Mesh::ICreateInfo>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Mesh_ICreateInfo_finalize)

bool js_register_assets_Mesh_ICreateInfo(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create({"Mesh","ICreateInfo"}, obj, nullptr, _SE(js_assets_ICreateInfo_constructor));

    cls->defineProperty("structInfo", _SE(js_assets_ICreateInfo_get_structInfo), _SE(js_assets_ICreateInfo_set_structInfo));
    cls->defineProperty("data", _SE(js_assets_ICreateInfo_get_data), _SE(js_assets_ICreateInfo_set_data));
    cls->defineFinalizeFunction(_SE(js_cc_Mesh_ICreateInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Mesh::ICreateInfo>(cls);

    __jsb_cc_Mesh_ICreateInfo_proto = cls->getProto();
    __jsb_cc_Mesh_ICreateInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Mesh_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Mesh_class = nullptr;  // NOLINT

static bool js_assets_Mesh_copyIndices(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_copyIndices : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<std::variant<cc::TypedArrayTemp<signed char>, cc::TypedArrayTemp<short>, cc::TypedArrayTemp<int>, cc::TypedArrayTemp<unsigned char>, cc::TypedArrayTemp<unsigned short>, cc::TypedArrayTemp<unsigned int>, cc::TypedArrayTemp<float>, cc::TypedArrayTemp<double>>, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_copyIndices : Error processing arguments");
        bool result = cobj->copyIndices(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_copyIndices : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_copyIndices)

static bool js_assets_Mesh_destroyRenderingMesh(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_destroyRenderingMesh : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroyRenderingMesh();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_destroyRenderingMesh)

static bool js_assets_Mesh_getBoneSpaceBounds(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getBoneSpaceBounds : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Skeleton*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getBoneSpaceBounds : Error processing arguments");
        std::vector<cc::geometry::AABB> result = cobj->getBoneSpaceBounds(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getBoneSpaceBounds : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getBoneSpaceBounds)

static bool js_assets_Mesh_getData(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2( cobj, false, "js_assets_Mesh_getData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 0) {

            cc::TypedArrayTemp<unsigned char>& result = cobj->getData();
            ok &= nativevalue_to_se(result, s.rval(), s.thisObject() /*ctx*/);
            SE_PRECONDITION2(ok, false, "js_assets_Mesh_getData : Error processing arguments");
            SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
            return true;
        }
    } while(false);

    do {
        if (argc == 0) {

            const cc::TypedArrayTemp<unsigned char>& result = cobj->getData();
            ok &= nativevalue_to_se(result, s.rval(), s.thisObject() /*ctx*/);
            SE_PRECONDITION2(ok, false, "js_assets_Mesh_getData : Error processing arguments");
            SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
            return true;
        }
    } while(false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getData)

static bool js_assets_Mesh_getHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        uint64_t result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getHash)

static bool js_assets_Mesh_getJointBufferIndices(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getJointBufferIndices : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<int>& result = cobj->getJointBufferIndices();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getJointBufferIndices : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getJointBufferIndices)

static bool js_assets_Mesh_getMaxPosition(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getMaxPosition : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getMaxPosition();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getMaxPosition : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getMaxPosition)

static bool js_assets_Mesh_getMinPosition(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getMinPosition : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getMinPosition();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getMinPosition : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getMinPosition)

static bool js_assets_Mesh_getRenderingSubMeshes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getRenderingSubMeshes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::RenderingSubMesh *>& result = cobj->getRenderingSubMeshes();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getRenderingSubMeshes : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getRenderingSubMeshes)

static bool js_assets_Mesh_getStruct(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getStruct : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Mesh::IStruct& result = cobj->getStruct();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getStruct : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getStruct)

static bool js_assets_Mesh_getSubMeshCount(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_getSubMeshCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getSubMeshCount();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_getSubMeshCount : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_getSubMeshCount)

static bool js_assets_Mesh_initialize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->initialize();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_initialize)

static bool js_assets_Mesh_readAttribute(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_readAttribute : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<const char*, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_readAttribute : Error processing arguments");
        std::variant<cc::TypedArrayTemp<signed char>, cc::TypedArrayTemp<short>, cc::TypedArrayTemp<int>, cc::TypedArrayTemp<unsigned char>, cc::TypedArrayTemp<unsigned short>, cc::TypedArrayTemp<unsigned int>, cc::TypedArrayTemp<float>, cc::TypedArrayTemp<double>> result = cobj->readAttribute(arg0.value(), arg1.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_readAttribute : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_readAttribute)

static bool js_assets_Mesh_readIndices(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_readIndices : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_readIndices : Error processing arguments");
        std::variant<cc::TypedArrayTemp<signed char>, cc::TypedArrayTemp<short>, cc::TypedArrayTemp<int>, cc::TypedArrayTemp<unsigned char>, cc::TypedArrayTemp<unsigned short>, cc::TypedArrayTemp<unsigned int>, cc::TypedArrayTemp<float>, cc::TypedArrayTemp<double>> result = cobj->readIndices(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_readIndices : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_readIndices)

static bool js_assets_Mesh_validateMergingMesh(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Mesh_validateMergingMesh : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Mesh*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_validateMergingMesh : Error processing arguments");
        bool result = cobj->validateMergingMesh(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Mesh_validateMergingMesh : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Mesh_validateMergingMesh)

SE_DECLARE_FINALIZE_FUNC(js_cc_Mesh_finalize)

static bool js_assets_Mesh_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::Mesh* cobj = JSB_ALLOC(cc::Mesh);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_Mesh_constructor, __jsb_cc_Mesh_class, js_cc_Mesh_finalize)



static bool js_cc_Mesh_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Mesh>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Mesh>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Mesh_finalize)

bool js_register_assets_Mesh(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Mesh", obj, __jsb_cc_Asset_proto, _SE(js_assets_Mesh_constructor));

    cls->defineFunction("copyIndices", _SE(js_assets_Mesh_copyIndices));
    cls->defineFunction("destroyRenderingMesh", _SE(js_assets_Mesh_destroyRenderingMesh));
    cls->defineFunction("getBoneSpaceBounds", _SE(js_assets_Mesh_getBoneSpaceBounds));
    cls->defineFunction("getData", _SE(js_assets_Mesh_getData));
    cls->defineFunction("getHash", _SE(js_assets_Mesh_getHash));
    cls->defineFunction("getJointBufferIndices", _SE(js_assets_Mesh_getJointBufferIndices));
    cls->defineFunction("getMaxPosition", _SE(js_assets_Mesh_getMaxPosition));
    cls->defineFunction("getMinPosition", _SE(js_assets_Mesh_getMinPosition));
    cls->defineFunction("getRenderingSubMeshes", _SE(js_assets_Mesh_getRenderingSubMeshes));
    cls->defineFunction("getStruct", _SE(js_assets_Mesh_getStruct));
    cls->defineFunction("getSubMeshCount", _SE(js_assets_Mesh_getSubMeshCount));
    cls->defineFunction("initialize", _SE(js_assets_Mesh_initialize));
    cls->defineFunction("readAttribute", _SE(js_assets_Mesh_readAttribute));
    cls->defineFunction("readIndices", _SE(js_assets_Mesh_readIndices));
    cls->defineFunction("validateMergingMesh", _SE(js_assets_Mesh_validateMergingMesh));
    cls->defineFinalizeFunction(_SE(js_cc_Mesh_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Mesh>(cls);

    __jsb_cc_Mesh_proto = cls->getProto();
    __jsb_cc_Mesh_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_MorphRendering_proto = nullptr; // NOLINT
se::Class* __jsb_cc_MorphRendering_class = nullptr;  // NOLINT

static bool js_assets_MorphRendering_createInstance(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::MorphRendering>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_MorphRendering_createInstance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::MorphRenderingInstance* result = cobj->createInstance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_MorphRendering_createInstance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_MorphRendering_createInstance)


static bool js_cc_MorphRendering_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::MorphRendering>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::MorphRendering>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_MorphRendering_finalize)

bool js_register_assets_MorphRendering(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("MorphRendering", obj, nullptr, nullptr);

    cls->defineFunction("createInstance", _SE(js_assets_MorphRendering_createInstance));
    cls->defineFinalizeFunction(_SE(js_cc_MorphRendering_finalize));
    cls->install();
    JSBClassType::registerClass<cc::MorphRendering>(cls);

    __jsb_cc_MorphRendering_proto = cls->getProto();
    __jsb_cc_MorphRendering_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_MorphRenderingInstance_proto = nullptr; // NOLINT
se::Class* __jsb_cc_MorphRenderingInstance_class = nullptr;  // NOLINT

static bool js_assets_MorphRenderingInstance_adaptPipelineState(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::MorphRenderingInstance>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_MorphRenderingInstance_adaptPipelineState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<cc::gfx::DescriptorSet*, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_MorphRenderingInstance_adaptPipelineState : Error processing arguments");
        cobj->adaptPipelineState(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_MorphRenderingInstance_adaptPipelineState)

static bool js_assets_MorphRenderingInstance_destroy(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::MorphRenderingInstance>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_MorphRenderingInstance_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_MorphRenderingInstance_destroy)

static bool js_assets_MorphRenderingInstance_requiredPatches(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::MorphRenderingInstance>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_MorphRenderingInstance_requiredPatches : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_MorphRenderingInstance_requiredPatches : Error processing arguments");
        std::vector<cc::scene::IMacroPatch> result = cobj->requiredPatches(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_MorphRenderingInstance_requiredPatches : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_MorphRenderingInstance_requiredPatches)

static bool js_assets_MorphRenderingInstance_setWeights(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::MorphRenderingInstance>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_MorphRenderingInstance_setWeights : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<std::vector<float>, true> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_MorphRenderingInstance_setWeights : Error processing arguments");
        cobj->setWeights(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_assets_MorphRenderingInstance_setWeights)


static bool js_cc_MorphRenderingInstance_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::MorphRenderingInstance>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::MorphRenderingInstance>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_MorphRenderingInstance_finalize)

bool js_register_assets_MorphRenderingInstance(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("MorphRenderingInstance", obj, nullptr, nullptr);

    cls->defineFunction("adaptPipelineState", _SE(js_assets_MorphRenderingInstance_adaptPipelineState));
    cls->defineFunction("destroy", _SE(js_assets_MorphRenderingInstance_destroy));
    cls->defineFunction("requiredPatches", _SE(js_assets_MorphRenderingInstance_requiredPatches));
    cls->defineFunction("setWeights", _SE(js_assets_MorphRenderingInstance_setWeights));
    cls->defineFinalizeFunction(_SE(js_cc_MorphRenderingInstance_finalize));
    cls->install();
    JSBClassType::registerClass<cc::MorphRenderingInstance>(cls);

    __jsb_cc_MorphRenderingInstance_proto = cls->getProto();
    __jsb_cc_MorphRenderingInstance_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_StdMorphRendering_proto = nullptr; // NOLINT
se::Class* __jsb_cc_StdMorphRendering_class = nullptr;  // NOLINT

SE_DECLARE_FINALIZE_FUNC(js_cc_StdMorphRendering_finalize)

static bool js_assets_StdMorphRendering_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    cc::Mesh* arg0 = nullptr;
    cc::gfx::Device* arg1 = nullptr;
    ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
    ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_assets_StdMorphRendering_constructor : Error processing arguments");
    cc::StdMorphRendering* cobj = JSB_ALLOC(cc::StdMorphRendering, arg0, arg1);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_assets_StdMorphRendering_constructor, __jsb_cc_StdMorphRendering_class, js_cc_StdMorphRendering_finalize)



static bool js_cc_StdMorphRendering_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::StdMorphRendering>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::StdMorphRendering>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_StdMorphRendering_finalize)

bool js_register_assets_StdMorphRendering(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("StdMorphRendering", obj, __jsb_cc_MorphRendering_proto, _SE(js_assets_StdMorphRendering_constructor));

    cls->defineFinalizeFunction(_SE(js_cc_StdMorphRendering_finalize));
    cls->install();
    JSBClassType::registerClass<cc::StdMorphRendering>(cls);

    __jsb_cc_StdMorphRendering_proto = cls->getProto();
    __jsb_cc_StdMorphRendering_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_Skeleton_proto = nullptr; // NOLINT
se::Class* __jsb_cc_Skeleton_class = nullptr;  // NOLINT

static bool js_assets_Skeleton_getBindposes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Skeleton_getBindposes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::Mat4>& result = cobj->getBindposes();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Skeleton_getBindposes : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Skeleton_getBindposes)

static bool js_assets_Skeleton_getHash(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Skeleton_getHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        uint64_t result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Skeleton_getHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Skeleton_getHash)

static bool js_assets_Skeleton_getInverseBindposes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Skeleton_getInverseBindposes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::Mat4>& result = cobj->getInverseBindposes();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Skeleton_getInverseBindposes : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Skeleton_getInverseBindposes)

static bool js_assets_Skeleton_getJoints(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Skeleton_getJoints : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<std::string>& result = cobj->getJoints();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_assets_Skeleton_getJoints : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_assets_Skeleton_getJoints)

static bool js_assets_Skeleton_setBindposes(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Skeleton_setBindposes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<cc::Mat4>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Skeleton_setBindposes : Error processing arguments");
        cobj->setBindposes(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Skeleton_setBindposes)

static bool js_assets_Skeleton_setJoints(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
    SE_PRECONDITION2(cobj, false, "js_assets_Skeleton_setJoints : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<std::string>, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_assets_Skeleton_setJoints : Error processing arguments");
        cobj->setJoints(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_assets_Skeleton_setJoints)


static bool js_cc_Skeleton_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::Skeleton>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::Skeleton>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_Skeleton_finalize)

bool js_register_assets_Skeleton(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Skeleton", obj, __jsb_cc_Asset_proto, nullptr);

    cls->defineFunction("getBindposes", _SE(js_assets_Skeleton_getBindposes));
    cls->defineFunction("getHash", _SE(js_assets_Skeleton_getHash));
    cls->defineFunction("getInverseBindposes", _SE(js_assets_Skeleton_getInverseBindposes));
    cls->defineFunction("getJoints", _SE(js_assets_Skeleton_getJoints));
    cls->defineFunction("setBindposes", _SE(js_assets_Skeleton_setBindposes));
    cls->defineFunction("setJoints", _SE(js_assets_Skeleton_setJoints));
    cls->defineFinalizeFunction(_SE(js_cc_Skeleton_finalize));
    cls->install();
    JSBClassType::registerClass<cc::Skeleton>(cls);

    __jsb_cc_Skeleton_proto = cls->getProto();
    __jsb_cc_Skeleton_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
bool register_all_assets(se::Object* obj)    // NOLINT
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("ns", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("ns", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_assets_Asset(ns);
    js_register_assets_BoundingBox(ns);
    js_register_assets_BufferAsset(ns);
    js_register_assets_EffectAsset(ns);
    js_register_assets_IAttributeInfo(ns);
    js_register_assets_IBlockInfo(ns);
    js_register_assets_IBuiltin(ns);
    js_register_assets_IBuiltinInfo(ns);
    js_register_assets_IBuiltins(ns);
    js_register_assets_IDefineInfo(ns);
    js_register_assets_IFlatBuffer(ns);
    js_register_assets_IGeometricInfo(ns);
    js_register_assets_IMaterialInfo(ns);
    js_register_assets_IMemoryImageSource(ns);
    js_register_assets_IMeshBufferView(ns);
    js_register_assets_IPropertyInfo(ns);
    js_register_assets_IRenderTextureCreateInfo(ns);
    js_register_assets_ISamplerTextureInfo(ns);
    js_register_assets_IShaderInfo(ns);
    js_register_assets_IShaderSource(ns);
    js_register_assets_ITechniqueInfo(ns);
    js_register_assets_ITexture2DCreateInfo(ns);
    js_register_assets_ITexture2DSerializeData(ns);
    js_register_assets_ITextureCubeMipmap(ns);
    js_register_assets_ITextureCubeSerializeData(ns);
    js_register_assets_ITextureCubeSerializeMipmapData(ns);
    js_register_assets_ImageAsset(ns);
    js_register_assets_JsonAsset(ns);
    js_register_assets_Material(ns);
    js_register_assets_Mesh(ns);
    js_register_assets_Mesh_ICreateInfo(ns);
    js_register_assets_Mesh_IStruct(ns);
    js_register_assets_Mesh_ISubMesh(ns);
    js_register_assets_Mesh_IVertexBundle(ns);
    js_register_assets_Morph(ns);
    js_register_assets_MorphRendering(ns);
    js_register_assets_MorphRenderingInstance(ns);
    js_register_assets_MorphTarget(ns);
    js_register_assets_Prefab(ns);
    js_register_assets_RenderTexture(ns);
    js_register_assets_RenderingSubMesh(ns);
    js_register_assets_SceneAsset(ns);
    js_register_assets_SimpleTexture(ns);
    js_register_assets_Skeleton(ns);
    js_register_assets_StdMorphRendering(ns);
    js_register_assets_SubMeshMorph(ns);
    js_register_assets_TextAsset(ns);
    js_register_assets_Texture2D(ns);
    js_register_assets_TextureBase(ns);
    js_register_assets_TextureCube(ns);
    js_register_assets_VertexIdChannel(ns);
    return true;
}

