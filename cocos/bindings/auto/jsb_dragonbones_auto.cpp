#include "cocos/bindings/auto/jsb_dragonbones_auto.h"
#if USE_DRAGONBONES > 0
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "editor-support/dragonbones-creator-support/CCDragonBonesHeaders.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_dragonBones_BaseObject_proto = nullptr;
se::Class* __jsb_dragonBones_BaseObject_class = nullptr;

static bool js_dragonbones_BaseObject_returnToPool(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::BaseObject>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_BaseObject_returnToPool : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->returnToPool();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_dragonbones_BaseObject_returnToPool)

static bool js_dragonbones_BaseObject_setMaxCount(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<size_t, false> arg0 = {};
        HolderType<unsigned int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        ok &= sevalue_to_native(args[1], &arg1, nullptr);
        SE_PRECONDITION2(ok, false, "js_dragonbones_BaseObject_setMaxCount : Error processing arguments");
        dragonBones::BaseObject::setMaxCount(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_dragonbones_BaseObject_setMaxCount)

static bool js_dragonbones_BaseObject_clearPool(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        dragonBones::BaseObject::clearPool();
        return true;
    }
    if (argc == 1) {
        HolderType<size_t, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_dragonbones_BaseObject_clearPool : Error processing arguments");
        dragonBones::BaseObject::clearPool(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_dragonbones_BaseObject_clearPool)



bool js_register_dragonbones_BaseObject(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("BaseObject", obj, nullptr, nullptr);

    cls->defineFunction("returnToPool", _SE(js_dragonbones_BaseObject_returnToPool));
    cls->defineStaticFunction("setMaxCount", _SE(js_dragonbones_BaseObject_setMaxCount));
    cls->defineStaticFunction("clearPool", _SE(js_dragonbones_BaseObject_clearPool));
    cls->install();
    JSBClassType::registerClass<dragonBones::BaseObject>(cls);

    __jsb_dragonBones_BaseObject_proto = cls->getProto();
    __jsb_dragonBones_BaseObject_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_dragonBones_Rectangle_proto = nullptr;
se::Class* __jsb_dragonBones_Rectangle_class = nullptr;

static bool js_dragonbones_Rectangle_clear(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Rectangle>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Rectangle_clear : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clear();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_dragonbones_Rectangle_clear)

SE_DECLARE_FINALIZE_FUNC(js_dragonBones_Rectangle_finalize)

static bool js_dragonbones_Rectangle_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    dragonBones::Rectangle* cobj = JSB_ALLOC(dragonBones::Rectangle);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_dragonbones_Rectangle_constructor, __jsb_dragonBones_Rectangle_class, js_dragonBones_Rectangle_finalize)



static bool js_dragonBones_Rectangle_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<dragonBones::Rectangle>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<dragonBones::Rectangle>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_dragonBones_Rectangle_finalize)

bool js_register_dragonbones_Rectangle(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Rectangle", obj, nullptr, _SE(js_dragonbones_Rectangle_constructor));

    cls->defineFunction("clear", _SE(js_dragonbones_Rectangle_clear));
    cls->defineFinalizeFunction(_SE(js_dragonBones_Rectangle_finalize));
    cls->install();
    JSBClassType::registerClass<dragonBones::Rectangle>(cls);

    __jsb_dragonBones_Rectangle_proto = cls->getProto();
    __jsb_dragonBones_Rectangle_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_dragonBones_Matrix_proto = nullptr;
se::Class* __jsb_dragonBones_Matrix_class = nullptr;

static bool js_dragonbones_Matrix_get_a(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_get_a : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->a, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->a, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Matrix_get_a)

static bool js_dragonbones_Matrix_set_a(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_set_a : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->a, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Matrix_set_a : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Matrix_set_a)

static bool js_dragonbones_Matrix_get_b(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_get_b : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->b, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->b, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Matrix_get_b)

static bool js_dragonbones_Matrix_set_b(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_set_b : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->b, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Matrix_set_b : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Matrix_set_b)

static bool js_dragonbones_Matrix_get_c(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_get_c : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->c, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->c, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Matrix_get_c)

static bool js_dragonbones_Matrix_set_c(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_set_c : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->c, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Matrix_set_c : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Matrix_set_c)

static bool js_dragonbones_Matrix_get_d(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_get_d : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->d, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->d, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Matrix_get_d)

static bool js_dragonbones_Matrix_set_d(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_set_d : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->d, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Matrix_set_d : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Matrix_set_d)

static bool js_dragonbones_Matrix_get_tx(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_get_tx : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->tx, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->tx, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Matrix_get_tx)

static bool js_dragonbones_Matrix_set_tx(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_set_tx : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->tx, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Matrix_set_tx : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Matrix_set_tx)

static bool js_dragonbones_Matrix_get_ty(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_get_ty : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->ty, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->ty, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Matrix_get_ty)

static bool js_dragonbones_Matrix_set_ty(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Matrix>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Matrix_set_ty : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->ty, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Matrix_set_ty : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Matrix_set_ty)



bool js_register_dragonbones_Matrix(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("Matrix", obj, nullptr, nullptr);

    cls->defineProperty("a", _SE(js_dragonbones_Matrix_get_a), _SE(js_dragonbones_Matrix_set_a));
    cls->defineProperty("b", _SE(js_dragonbones_Matrix_get_b), _SE(js_dragonbones_Matrix_set_b));
    cls->defineProperty("c", _SE(js_dragonbones_Matrix_get_c), _SE(js_dragonbones_Matrix_set_c));
    cls->defineProperty("d", _SE(js_dragonbones_Matrix_get_d), _SE(js_dragonbones_Matrix_set_d));
    cls->defineProperty("tx", _SE(js_dragonbones_Matrix_get_tx), _SE(js_dragonbones_Matrix_set_tx));
    cls->defineProperty("ty", _SE(js_dragonbones_Matrix_get_ty), _SE(js_dragonbones_Matrix_set_ty));
    cls->install();
    JSBClassType::registerClass<dragonBones::Matrix>(cls);

    __jsb_dragonBones_Matrix_proto = cls->getProto();
    __jsb_dragonBones_Matrix_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_dragonBones_Transform_proto = nullptr;
se::Class* __jsb_dragonBones_Transform_class = nullptr;

static bool js_dragonbones_Transform_normalizeRadian(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "js_dragonbones_Transform_normalizeRadian : Error processing arguments");
        float result = dragonBones::Transform::normalizeRadian(arg0.value());
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_dragonbones_Transform_normalizeRadian : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_dragonbones_Transform_normalizeRadian)

static bool js_dragonbones_Transform_get_x(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Transform>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Transform_get_x : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->x, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->x, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Transform_get_x)

static bool js_dragonbones_Transform_set_x(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Transform>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Transform_set_x : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->x, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Transform_set_x : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Transform_set_x)

static bool js_dragonbones_Transform_get_y(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Transform>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Transform_get_y : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->y, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->y, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Transform_get_y)

static bool js_dragonbones_Transform_set_y(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Transform>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Transform_set_y : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->y, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Transform_set_y : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Transform_set_y)

static bool js_dragonbones_Transform_get_skew(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<dragonBones::Transform>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Transform_get_skew : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->skew, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->skew, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_dragonbones_Transform_get_skew)

static bool js_dragonbones_Transform_set_skew(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    auto* cobj = SE_THIS_OBJECT<dragonBones::Transform>(s);
    SE_PRECONDITION2(cobj, false, "js_dragonbones_Transform_set_skew : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->skew, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_dragonbones_Transform_set_skew : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_dragonbones_Transform_set_skew)
