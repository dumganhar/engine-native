/****************************************************************************
 Copyright (c) 2017-2021 Xiamen Yaji Software Co., Ltd.

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
#include <cassert>
#include <cstdint>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>
#include "bindings/jswrapper/HandleObject.h"
#include "bindings/jswrapper/SeApi.h"
#include "bindings/jswrapper/Value.h"
#include "bindings/jswrapper/v8/Object.h"
#include "bindings/manual/jsb_classtype.h"
#include "bindings/manual/jsb_conversions.h"
#include "cocos/base/Map.h"
#include "cocos/base/Vector.h"
#include "cocos/core/TypedArray.h"
#include "cocos/core/assets/AssetsModuleHeader.h"
#include "cocos/math/Geometry.h"
#include "cocos/math/Quaternion.h"
#include "cocos/math/Vec2.h"
#include "cocos/math/Vec3.h"
#include "core/ArrayBuffer.h"
#include "core/geometry/AABB.h"
#include "extensions/cocos-ext.h"
#include "network/Downloader.h"

#include "cocos/core/geometry/Geometry.h"
#include "renderer/core/MaterialInstance.h"
#include "scene/Fog.h"
#include "scene/Shadow.h"
#include "scene/Skybox.h"

#if USE_SPINE
    #include "cocos/editor-support/spine-creator-support/spine-cocos2dx.h"
#endif

namespace cc {
namespace gfx {
struct Rect;
struct Viewport;
struct Color;
struct Offset;
struct Extent;
struct TextureSubres;
struct TextureCopy;
struct BufferTextureCopy;
struct BufferInfo;
struct BufferViewInfo;
struct TextureInfo;
struct DescriptorSetInfo;
struct BindingMappingInfo;
struct ShaderStage;
struct UniformSampler;
struct UniformBlock;
struct Uniform;
struct ShaderInfo;
struct DrawInfo;
struct IndirectBuffer;
struct SamplerInfo;
struct ColorAttachment;
struct DepthStencilAttachment;
struct SubPassInfo;
struct RenderPassInfo;
struct QueueInfo;
struct PipelineLayoutInfo;
struct DescriptorSetLayoutBinding;
struct DescriptorSetLayoutInfo;
struct FramebufferInfo;
struct CommandBufferInfo;
struct InputAssemblerInfo;
} // namespace gfx
} // namespace cc

//#include "Box2D/Box2D.h"

#define SE_PRECONDITION2_VOID(condition, ...)                                                           \
    do {                                                                                                \
        if (!(condition)) {                                                                             \
            CC_LOG_ERROR("jsb: ERROR: File %s: Line: %d, Function: %s\n", __FILE__, __LINE__, __FUNCTION__); \
            CC_LOG_ERROR(__VA_ARGS__);                                                                       \
            return;                                                                                     \
        }                                                                                               \
    } while (0)

#define SE_PRECONDITION2(condition, ret_value, ...)                                                     \
    do {                                                                                                \
        if (!(condition)) {                                                                             \
            CC_LOG_ERROR("jsb: ERROR: File %s: Line: %d, Function: %s\n", __FILE__, __LINE__, __FUNCTION__); \
            CC_LOG_ERROR(__VA_ARGS__);                                                                       \
            return (ret_value);                                                                         \
        }                                                                                               \
    } while (0)

#define SE_PRECONDITION3(condition, ret_value, failed_code) \
    do {                                                    \
        if (!(condition)) {                                 \
            failed_code;                                    \
            return (ret_value);                             \
        }                                                   \
    } while (0)

#define SE_PRECONDITION4(condition, ret_value, errorCode)                                               \
    do {                                                                                                \
        if (!(condition)) {                                                                             \
            CC_LOG_ERROR("jsb: ERROR: File %s: Line: %d, Function: %s\n", __FILE__, __LINE__, __FUNCTION__); \
            __glErrorCode = errorCode;                                                                  \
            return (ret_value);                                                                         \
        }                                                                                               \
    } while (0)

#define SE_PRECONDITION_ERROR_BREAK(condition, ...)                                                 \
    if (!(condition)) {                                                                             \
        CC_LOG_ERROR("jsb: ERROR: File %s: Line: %d, Function: %s\n", __FILE__, __LINE__, __FUNCTION__); \
        CC_LOG_ERROR(__VA_ARGS__);                                                                       \
        break;                                                                                      \
    }

#if CC_ENABLE_CACHE_JSB_FUNC_RESULT
    #define SE_HOLD_RETURN_VALUE(retCXXValue, thisObject, jsValue)                       \
        if (is_jsb_object_v<typename std::decay<decltype(retCXXValue)>::type>) {         \
            (thisObject)->setProperty(std::string("__cache") + __FUNCTION__, (jsValue)); \
        }
#else
    #define SE_HOLD_RETURN_VALUE(...)
#endif

#if __clang__
    #if defined(__has_feature) && __has_feature(cxx_static_assert) && __has_feature(cxx_relaxed_constexpr)
        #define HAS_CONSTEXPR 1
    #else
        #define HAS_CONSTEXPR 0
    #endif
#elif defined(_MSVC_LANG) && _MSVC_LANG >= 201703L
    #define HAS_CONSTEXPR 1
#else
    #define HAS_CONSTEXPR 0
#endif

#if HAS_CONSTEXPR
    #define CC_STATIC_ASSERT static_assert
    #define CC_CONSTEXPR     constexpr
#else
    #define CC_CONSTEXPR
    #define CC_STATIC_ASSERT(cond, msg) assert(cond)
#endif

#if __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wc++17-extensions"
#endif

// se value -> native value
bool seval_to_ccvalue(const se::Value &v, cc::Value *ret);                               // NOLINT(readability-identifier-naming)
bool seval_to_ccvaluemap(const se::Value &v, cc::ValueMap *ret);                         // NOLINT(readability-identifier-naming)
bool seval_to_ccvaluemapintkey(const se::Value &v, cc::ValueMapIntKey *ret);             // NOLINT(readability-identifier-naming)
bool seval_to_ccvaluevector(const se::Value &v, cc::ValueVector *ret);                   // NOLINT(readability-identifier-naming)
bool sevals_variadic_to_ccvaluevector(const se::ValueArray &args, cc::ValueVector *ret); // NOLINT(readability-identifier-naming)

bool seval_to_Data(const se::Value &v, cc::Data *ret);                                // NOLINT(readability-identifier-naming)
bool seval_to_DownloaderHints(const se::Value &v, cc::network::DownloaderHints *ret); // NOLINT(readability-identifier-naming)

template <typename T>
bool seval_to_native_ptr(const se::Value &v, T *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);

    if (v.isObject()) {
        T ptr = static_cast<T>(v.toObject()->getPrivateData());
        if (ptr == nullptr) {
            // This should never happen, return 'false' to mark the conversion fails.
            *ret = nullptr;
            return false;
        }

        *ret = ptr;
        return true;
    }
    if (v.isNullOrUndefined()) {
        // If js value is null or undefined, the convertion should be successful.
        // So we should return 'true' to indicate the convertion succeeds and mark
        // the out value to 'nullptr'.
        *ret = nullptr;
        return true;
    }

    // If js value isn't null, undefined and Object, mark the convertion fails.
    *ret = nullptr;
    return false;
}

template <typename T>
typename std::enable_if<std::is_class<T>::value && !std::is_same<T, std::string>::value, T>::type
seval_to_type(const se::Value &v, bool &ok) { // NOLINT(readability-identifier-naming)
    if (!v.isObject()) {
        ok = false;
        return T();
    }
    T *nativeObj = static_cast<T *>(v.toObject()->getPrivateData());
    ok           = true;
    return *nativeObj;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
seval_to_type(const se::Value &v, bool &ok) { // NOLINT(readability-identifier-naming)
    if (!v.isNumber()) {
        ok = false;
        return 0;
    }
    ok = true;
    return v.toInt32();
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, T>::type
seval_to_type(const se::Value &v, bool &ok) { // NOLINT(readability-identifier-naming)
    if (!v.isNumber()) {
        ok = false;
        return static_cast<T>(0);
    }
    ok = true;
    return static_cast<T>(v.toInt32());
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
seval_to_type(const se::Value &v, bool &ok) { // NOLINT(readability-identifier-naming)
    if (!v.isNumber()) {
        ok = false;
        return 0;
    }
    ok = true;
    return v.toFloat();
}

template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, T>::type
seval_to_type(const se::Value &v, bool &ok) { // NOLINT(readability-identifier-naming)
    if (!v.isString()) {
        ok = false;
        return "";
    }
    ok = true;
    return v.toString();
}

template <typename T>
typename std::enable_if<std::is_pointer<T>::value && std::is_class<typename std::remove_pointer<T>::type>::value, bool>::type
seval_to_std_vector(const se::Value &v, std::vector<T> *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object *obj = v.toObject();
    assert(obj->isArray());

    bool     ok  = true;
    uint32_t len = 0;
    ok           = obj->getArrayLength(&len);
    if (!ok) {
        ret->clear();
        return false;
    }

    ret->resize(len);

    se::Value tmp;
    for (uint32_t i = 0; i < len; ++i) {
        ok = obj->getArrayElement(i, &tmp);
        if (!ok) {
            ret->clear();
            return false;
        }

        if (tmp.isObject()) {
            T nativeObj = static_cast<T>(tmp.toObject()->getPrivateData());
            (*ret)[i]   = nativeObj;
        } else if (tmp.isNullOrUndefined()) {
            (*ret)[i] = nullptr;
        } else {
            ret->clear();
            return false;
        }
    }

    return true;
}

template <typename T>
typename std::enable_if<!std::is_pointer<T>::value, bool>::type
seval_to_std_vector(const se::Value &v, std::vector<T> *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object *obj = v.toObject();
    assert(obj->isArray());

    bool     ok  = true;
    uint32_t len = 0;
    ok           = obj->getArrayLength(&len);
    if (!ok) {
        ret->clear();
        return false;
    }

    ret->resize(len);

    se::Value tmp;
    for (uint32_t i = 0; i < len; ++i) {
        ok = obj->getArrayElement(i, &tmp);
        if (!ok) {
            ret->clear();
            return false;
        }
        (*ret)[i] = seval_to_type<T>(tmp, ok);
        if (!ok) {
            return false;
        }
    }

    return true;
}

template <typename T>
bool seval_to_Map_string_key(const se::Value &v, cc::Map<std::string, T> *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object *obj = v.toObject();

    std::vector<std::string> allKeys;
    bool                     ok = obj->getAllKeys(&allKeys);
    if (!ok) {
        ret->clear();
        return false;
    }

    se::Value tmp;
    for (const auto &key : allKeys) {
        ok = obj->getProperty(key.c_str(), &tmp);
        if (!ok || !tmp.isObject()) {
            ret->clear();
            return false;
        }

        T nativeObj = static_cast<T>(tmp.toObject()->getPrivateData());
        ret->insert(key, nativeObj);
    }

    return true;
}

// native value -> se value
bool ccvalue_to_seval(const cc::Value &v, se::Value *ret);                   // NOLINT(readability-identifier-naming)
bool ccvaluemap_to_seval(const cc::ValueMap &v, se::Value *ret);             // NOLINT(readability-identifier-naming)
bool ccvaluemapintkey_to_seval(const cc::ValueMapIntKey &v, se::Value *ret); // NOLINT(readability-identifier-naming)
bool ccvaluevector_to_seval(const cc::ValueVector &v, se::Value *ret);       // NOLINT(readability-identifier-naming)

bool ManifestAsset_to_seval(const cc::extension::ManifestAsset &v, se::Value *ret); // NOLINT(readability-identifier-naming)
bool Data_to_seval(const cc::Data &v, se::Value *ret);                              // NOLINT(readability-identifier-naming)
bool DownloadTask_to_seval(const cc::network::DownloadTask &v, se::Value *ret);     // NOLINT(readability-identifier-naming)

// TODO(minggo): should add these functions if only bind gfx.
// gfx_color_attachment_to_seval
// gfx_depth_stecil_attachment_to_seval
// sub_pass_info_to_seval

#if USE_GFX_RENDERER
#endif

template <typename T>
typename std::enable_if<!std::is_base_of<cc::Ref, T>::value, bool>::type
native_ptr_to_seval(T *v_c, se::Value *ret, bool *isReturnCachedValue = nullptr) { // NOLINT(readability-identifier-naming)
    using DecayT = typename std::decay<typename std::remove_const<T>::type>::type;
    auto *v      = const_cast<DecayT *>(v_c);
    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        // CC_LOG_DEBUGWARN("WARNING: non-Ref type: (%s) isn't catched!", typeid(*v).name());
        se::Class *cls = JSBClassType::findClass<T>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
    } else {
        obj = iter->second;
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

//handle reference
template <typename T>
typename std::enable_if<!std::is_base_of<cc::Ref, T>::value && !std::is_pointer<T>::value, bool>::type
native_ptr_to_seval(T &v_ref, se::Value *ret, bool *isReturnCachedValue = nullptr) { // NOLINT(readability-identifier-naming)
    using DecayT = typename std::decay<typename std::remove_const<decltype(v_ref)>::type>::type;
    auto *v      = const_cast<DecayT *>(&v_ref);

    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        // CC_LOG_DEBUGWARN("WARNING: non-Ref type: (%s) isn't catched!", typeid(*v).name());
        se::Class *cls = JSBClassType::findClass<DecayT>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
    } else {
        obj = iter->second;
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template <typename T>
bool native_ptr_to_rooted_seval( // NOLINT(readability-identifier-naming)
    typename std::enable_if<!std::is_base_of<cc::Ref, T>::value, T>::type *v,
    se::Value *ret, bool *isReturnCachedValue = nullptr) {
    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(reinterpret_cast<void *>(v));
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        se::Class *cls = JSBClassType::findClass<T>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        obj->root();
        obj->setPrivateData(reinterpret_cast<void *>(v));

        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
        // CC_LOG_DEBUGWARN("WARNING: non-Ref type: (%s) isn't catched!", typeid(*v).name());
    } else {
        obj = iter->second;
        assert(obj->isRooted());
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        // CC_LOG_DEBUG("return cached object: %s, se::Object:%p, native: %p", typeid(*v).name(), obj, v);
    }

    ret->setObject(obj);
    return true;
}

template <typename T>
typename std::enable_if<!std::is_base_of<cc::Ref, T>::value, bool>::type
native_ptr_to_seval(T *vp, se::Class *cls, se::Value *ret, bool *isReturnCachedValue = nullptr) { // NOLINT(readability-identifier-naming)
    using DecayT = typename std::decay<typename std::remove_const<T>::type>::type;
    auto *v      = const_cast<DecayT *>(vp);
    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
                                                   //        CC_LOG_DEBUGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);

        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
    } else {
        obj = iter->second;
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

//handle ref
template <typename T>
typename std::enable_if<!std::is_base_of<cc::Ref, T>::value, bool>::type
native_ptr_to_seval(T &v_ref, se::Class *cls, se::Value *ret, bool *isReturnCachedValue = nullptr) { // NOLINT(readability-identifier-naming)
    using DecayT = typename std::decay<typename std::remove_const<decltype(v_ref)>::type>::type;
    auto *v      = const_cast<DecayT *>(&v_ref);

    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        //        CC_LOG_DEBUGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);

        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
    } else {
        obj = iter->second;
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template <typename T>
bool native_ptr_to_rooted_seval( // NOLINT(readability-identifier-naming)
    typename std::enable_if<!std::is_base_of<cc::Ref, T>::value, T>::type *v,
    se::Class *cls, se::Value *ret, bool *isReturnCachedValue = nullptr) {
    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        obj->root();
        obj->setPrivateData(v);

        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
        // CC_LOG_DEBUGWARN("WARNING: non-Ref type: (%s) isn't catched, se::Object:%p, native: %p", typeid(*v).name(), obj, v);
    } else {
        obj = iter->second;
        assert(obj->isRooted());
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        // CC_LOG_DEBUG("return cached object: %s, se::Object:%p, native: %p", typeid(*v).name(), obj, v);
    }

    ret->setObject(obj);
    return true;
}

template <typename T>
typename std::enable_if<std::is_base_of<cc::Ref, T>::value, bool>::type
native_ptr_to_seval(T *vp, se::Value *ret, bool *isReturnCachedValue = nullptr) { // NOLINT(readability-identifier-naming)
    using DecayT = typename std::decay<typename std::remove_const<T>::type>::type;
    auto *v      = const_cast<DecayT *>(vp);
    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
                                                   //        CC_LOG_DEBUGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        se::Class *cls = JSBClassType::findClass<T>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        v->retain(); // Retain the native object to unify the logic in finalize method of js object.
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
    } else {
        obj = iter->second;
        //        CC_LOG_DEBUG("INFO: Found Ref type: (%s, native: %p, se: %p) from cache!", typeid(*v).name(), v, obj);
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template <typename T>
typename std::enable_if<std::is_base_of<cc::Ref, T>::value, bool>::type
native_ptr_to_seval(T *vp, se::Class *cls, se::Value *ret, bool *isReturnCachedValue = nullptr) { // NOLINT(readability-identifier-naming)
    using DecayT = typename std::decay<typename std::remove_const<T>::type>::type;
    auto *v      = const_cast<DecayT *>(vp);
    assert(ret != nullptr);
    if (v == nullptr) {
        ret->setNull();
        return true;
    }

    se::Object *obj  = nullptr;
    auto        iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end()) { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
                                                   //        CC_LOG_DEBUGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        v->retain(); // Retain the native object to unify the logic in finalize method of js object.
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = false;
        }
    } else {
        obj = iter->second;
        if (isReturnCachedValue != nullptr) {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template <typename T>
bool std_vector_to_seval(const std::vector<T> &v, se::Value *ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    bool             ok = true;
    se::HandleObject obj(se::Object::createArrayObject(v.size()));

    uint32_t  i = 0;
    se::Value tmp;
    for (const auto &e : v) {
        native_ptr_to_seval(e, &tmp);
        obj->setArrayElement(i, tmp);
        ++i;
    }

    ret->setObject(obj, true);

    return ok;
}

template <typename T>
bool seval_to_reference(const se::Value &v, T **ret) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    assert(v.isObject());
    *ret = static_cast<T *>(v.toObject()->getPrivateData());
    return true;
}

/////////////////////////////////// helpers //////////////////////////////////////////////////////////

////////////////////////// is jsb object ///////////////////////////

template <typename T>
struct is_jsb_object : std::false_type {}; // NOLINT(readability-identifier-naming)

template <typename T>
constexpr bool is_jsb_object_v = is_jsb_object<typename std::remove_const<T>::type>::value; // NOLINT(readability-identifier-naming)

#define JSB_REGISTER_OBJECT_TYPE(T) \
    template <>                     \
    struct is_jsb_object<T> : std::true_type {}

template <typename Out, typename In>
constexpr inline typename std::enable_if<std::is_same<Out, In>::value, Out>::type &
holder_convert_to(In &input) { // NOLINT(readability-identifier-naming)
    return input;
}

template <typename Out, typename In>
constexpr inline typename std::enable_if<std::is_pointer<Out>::value && std::is_same<Out, typename std::add_pointer<In>::type>::value, Out>::type &
holder_convert_to(In &input) { // NOLINT(readability-identifier-naming)
    return static_cast<Out>(&input);
}

template <typename Out, typename In>
constexpr inline typename std::enable_if<std::is_pointer<In>::value && std::is_same<Out, typename std::remove_pointer<In>::type>::value, Out>::type &
holder_convert_to(In &input) { // NOLINT(readability-identifier-naming)
    return *input;
}

template <typename T, bool is_reference>
struct HolderType {
    using type       = typename std::remove_const<T>::type;
    using local_type = typename std::conditional_t<is_reference && is_jsb_object_v<T>, std::add_pointer_t<type>, type>;
    local_type             data;
    type *                 ptr = nullptr;
    constexpr inline type &value() {
        if (ptr) return *ptr;
        return holder_convert_to<type, local_type>(data);
    }
    ~HolderType() {
        delete ptr;
    }
};

template <>
struct HolderType<const char *, false> {
    using type       = const char *;
    using local_type = std::string;
    local_type                 data;
    std::remove_const_t<type> *ptr = nullptr;
    inline type                value() const { return data.c_str(); }
};

#define HOLD_UNBOUND_TYPE(FromType, IsReference)                         \
    template <>                                                          \
    struct HolderType<FromType, IsReference> {                           \
        using type       = FromType;                                     \
        using local_type = typename std::remove_pointer<FromType>::type; \
        std::remove_const_t<local_type> data;                            \
        std::remove_const_t<type> *     ptr = nullptr;                   \
        inline type                     value() { return &data; }        \
    }

HOLD_UNBOUND_TYPE(cc::Vec3 *, false);
HOLD_UNBOUND_TYPE(cc::Quaternion *, false);
HOLD_UNBOUND_TYPE(const cc::Mat4 *, false);
HOLD_UNBOUND_TYPE(cc::Color *, false);
HOLD_UNBOUND_TYPE(cc::geometry::Frustum *, false);

template <>
struct HolderType<cc::ArrayBuffer, true> {
    using type       = cc::ArrayBuffer;
    using local_type = cc::ArrayBuffer;
    local_type                 data;
    std::remove_const_t<type> *ptr = nullptr;
    inline type &              value() { return data; /* TODO(PatriceJiang): use std::move() */ }
};

template <typename R, typename... ARGS>
struct HolderType<std::function<R(ARGS...)>, true> {
    using type       = std::function<R(ARGS...)>;
    using local_type = std::function<R(ARGS...)>;
    local_type                 data;
    std::remove_const_t<type> *ptr = nullptr;
    inline type                value() { return data; }
};

template <typename T>
struct HolderType<std::optional<T>, true> {
    using NonconstT  = typename std::remove_const<T>::type;
    using type       = std::optional<NonconstT>;
    using local_type = NonconstT;
    local_type                 data;
    std::remove_const_t<type> *ptr = nullptr;
    inline type                value() { return std::make_optional<T>(data); }
};

///////////////////////////////////convertion//////////////////////////////////////////////////////////

////////////////// optional
template <typename T, typename Enable = void>
struct is_optional : std::false_type {}; // NOLINT

template <typename T>
struct is_optional<std::optional<T>> : std::true_type {}; // NOLINT

template <typename... Args>
struct is_variant : std::false_type {}; // NOLINT
template <typename... Args>
struct is_variant<std::variant<Args...>> : std::true_type {}; // NOLINT

template <typename T>
inline typename std::enable_if_t<!std::is_enum<T>::value && !std::is_pointer<T>::value, bool>
sevalue_to_native(const se::Value & /*from*/, T * /*to*/, se::Object * /*unused*/) { // NOLINT(readability-identifier-naming)
    SE_LOGE("Can not convert type ???\n - [[ %s ]]\n", typeid(T).name());
    CC_STATIC_ASSERT(!is_variant<T>::value, "should not match std::variant");
    CC_STATIC_ASSERT(std::is_same<T, void>::value, "sevalue_to_native not implemented for T");
    return false;
}

template <typename T>
inline typename std::enable_if_t<std::is_enum<T>::value, bool>
sevalue_to_native(const se::Value &from, T *to, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    typename std::underlying_type_t<T> tmp;
    bool                               ret = sevalue_to_native(from, &tmp, ctx);
    if (ret) *to = static_cast<T>(tmp);
    return ret;
}

//////////////////////////////// forward declaration : sevalue_to_native ////////////////////////////////

// std::variant<...>>ss
template <typename... Args>
bool sevalue_to_native(const se::Value &from, std::variant<Args...> *to, se::Object *ctx); // NOLINT(readability-identifier-naming)

template <>
bool sevalue_to_native(const se::Value &from, cc::MacroValue *to, se::Object *ctx);
template <>
bool sevalue_to_native(const se::Value &from, cc::IPreCompileInfoValueType *to, se::Object * /*ctx*/);

template <typename T>
bool sevalue_to_native(const se::Value &from, std::optional<T> *to, se::Object *ctx); // NOLINT(readability-identifier-naming)
/// std::unordered_map<std::string, V>
template <typename V>
bool sevalue_to_native(const se::Value &from, std::unordered_map<std::string, V> *to, se::Object *ctx); //NOLINT(readability-identifier-naming)
// std::tuple
template <typename... Args>
constexpr bool sevalue_to_native(const se::Value &from, std::tuple<Args...> *to, se::Object *ctx); // NOLINT(readability-identifier-naming)
// std::shared_ptr
template <typename T>
bool sevalue_to_native(const se::Value &from, std::shared_ptr<T> *out, se::Object *ctx); // NOLINT(readability-identifier-naming)
// std::vector
template <typename T, typename Allocator>
bool sevalue_to_native(const se::Value &from, std::vector<T, Allocator> *to, se::Object *ctx); // NOLINT(readability-identifier-naming)
// std::vector
template <typename T, size_t N>
bool sevalue_to_native(const se::Value &from, std::array<T, N> *to, se::Object *ctx); // NOLINT(readability-identifier-naming)
// std::any
template <>
bool sevalue_to_native(const se::Value &from, std::any *to, se::Object *ctx); //NOLINT(readability-identifier-naming)
////////////////// ArrayBuffer
template <>
bool sevalue_to_native(const se::Value &from, cc::ArrayBuffer *to, se::Object * /*ctx*/);
///////////////// std::shared_ptr<cc::ArrayBuffer>
template <>
bool sevalue_to_native(const se::Value &from, std::shared_ptr<cc::ArrayBuffer> *out, se::Object *ctx);

//////////////////// std::array

template <typename T, size_t CNT>
bool sevalue_to_native(const se::Value &from, std::array<T, CNT> *to, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    assert(from.toObject());
    se::Object *array = from.toObject();
    assert(array->isArray());
    uint32_t len = 0;
    array->getArrayLength(&len);
    se::Value tmp;
    assert(len >= CNT);
    for (uint32_t i = 0; i < CNT; i++) {
        array->getArrayElement(i, &tmp);
        sevalue_to_native(tmp, &(*to)[i], ctx);
    }
    return true;
}

template <size_t CNT>
bool sevalue_to_native(const se::Value &from, std::array<uint8_t, CNT> *to, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    assert(from.toObject());
    se::Object *array = from.toObject();
    assert(array->isArray() || array->isArrayBuffer() || array->isTypedArray());
    if (array->isTypedArray()) {
        uint8_t *data = nullptr;
        size_t   size = 0;
        array->getTypedArrayData(&data, &size);
        for (size_t i = 0; i < std::min(size, CNT); i++) {
            (*to)[i] = data[i];
        }
    } else if (array->isArrayBuffer()) {
        uint8_t *data = nullptr;
        size_t   size = 0;
        array->getArrayBufferData(&data, &size);
        for (size_t i = 0; i < std::min(size, CNT); i++) {
            (*to)[i] = data[i];
        }
    } else if (array->isArray()) {
        uint32_t len = 0;
        array->getArrayLength(&len);
        se::Value tmp;
        assert(len >= CNT);
        for (size_t i = 0; i < CNT; i++) {
            array->getArrayElement(static_cast<uint32_t>(i), &tmp);
            sevalue_to_native(tmp, &(*to)[i], ctx);
        }
    } else {
        return false;
    }
    return true;
}

template <>
bool sevalue_to_native(const se::Value &from, std::vector<cc::MacroRecord> *to, se::Object * /*ctx*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::MaterialProperty *to, se::Object * /*ctx*/);

template <typename T>
bool sevalue_to_native(const se::Value &from, std::variant<T, std::vector<T>> *to, se::Object *ctx) {
    se::Object *array = from.toObject();
    if (array->isArray()) {
        std::vector<T> result;
        sevalue_to_native(from, &result, ctx);
        *to = std::move(result);
    } else {
        T result;
        sevalue_to_native(from, &result, ctx);
        *to = result;
    }
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, std::string *to, se::Object * /*ctx*/) {
    *to = from.toString();
    return true;
}

///// integers
template <>
inline bool sevalue_to_native(const se::Value &from, bool *to, se::Object * /*ctx*/) {
    *to = from.isNullOrUndefined() ? false : (from.isNumber() ? from.toDouble() != 0 : from.toBoolean());
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, int32_t *to, se::Object * /*ctx*/) {
    *to = from.toInt32();
    return true;
}
template <>
inline bool sevalue_to_native(const se::Value &from, uint32_t *to, se::Object * /*ctx*/) {
    *to = from.toUint32();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, int16_t *to, se::Object * /*ctx*/) {
    *to = from.toInt16();
    return true;
}
template <>
inline bool sevalue_to_native(const se::Value &from, uint16_t *to, se::Object * /*ctx*/) {
    *to = from.toUint16();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, int8_t *to, se::Object * /*ctx*/) {
    *to = from.toInt8();
    return true;
}
template <>
inline bool sevalue_to_native(const se::Value &from, uint8_t *to, se::Object * /*ctx*/) {
    *to = from.toUint8();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, uint64_t *to, se::Object * /*ctx*/) {
    *to = from.toUint64();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, int64_t *to, se::Object * /*ctx*/) {
    *to = from.toInt64();
    return true;
}

#if CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX
template <>
inline bool sevalue_to_native(const se::Value &from, unsigned long *to, se::Object * /*ctx*/) {
    *to = static_cast<unsigned long>(from.toDouble());
    return true;
}
#endif

template <>
inline bool sevalue_to_native(const se::Value &from, float *to, se::Object * /*ctx*/) {
    *to = from.toFloat();
    return true;
}
inline bool sevalue_to_native(const se::Value &from, double *to, se::Object * /*unused*/) {
    *to = from.toDouble();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value & /*from*/, void * /*to*/, se::Object * /*ctx*/) {
    assert(false); // void not supported
    return false;
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::Data *to, se::Object * /*ctx*/) {
    return seval_to_Data(from, to);
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::Value *to, se::Object * /*unused*/) {
    return seval_to_ccvalue(from, to);
}

template <>
inline bool sevalue_to_native(const se::Value &from, se::Value *to, se::Object * /*unused*/) {
    *to = from;
    return true;
}

template <>
bool sevalue_to_native(const se::Value &from, cc::Vec4 *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Mat3 *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Mat4 *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Vec3 *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Vec2 *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Size *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Quaternion *to, se::Object * /*unused*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::Color *to, se::Object * /*unused*/);

template <>
inline bool sevalue_to_native(const se::Value &from, std::vector<se::Value> *to, se::Object * /*unused*/) {
    if (from.isNullOrUndefined()) {
        to->clear();
        return true;
    }
    assert(from.isObject() && from.toObject()->isArray());
    auto *array = from.toObject();
    to->clear();
    uint32_t size;
    array->getArrayLength(&size);
    for (uint32_t i = 0; i < size; i++) {
        se::Value ele;
        array->getArrayElement(i, &ele);
        to->emplace_back(ele);
    }
    return true;
}

//////////////////  std::any
template <>
inline bool sevalue_to_native(const se::Value &from, std::any *to, se::Object *ctx) {
    assert(false);
    //TODO(PatriceJiang): convert any to specific types
    return false;
}

////////////////// TypedArray

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, bool>::type inline sevalue_to_native(const se::Value &from, cc::TypedArrayTemp<T> *to, se::Object * /*ctx*/) {
    to->setJSTypedArray(from.toObject());
    return true;
}

template <>
bool sevalue_to_native(const se::Value &from, cc::TypedArray *to, se::Object * /*ctx*/);

template <>
bool sevalue_to_native(const se::Value &from, cc::IBArray *to, se::Object * /*ctx*/);

////////////////// pointer types

template <typename T>
typename std::enable_if_t<std::is_pointer<T>::value && !std::is_pointer<typename std::remove_pointer<T>::type>::value, bool>
sevalue_to_native(const se::Value &from, T to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    CC_STATIC_ASSERT(is_jsb_object_v<std::remove_pointer_t<T>>, "Only JSB object are accepted!");
    if (from.isNullOrUndefined()) {
        //const std::string stack = se::ScriptEngine::getInstance()->getCurrentStackTrace();
        //SE_LOGE("[ERROR] sevalue_to_native jsval is null/undefined: %s\nstack: %s", typeid(T).name(), stack.c_str());
        *to = nullptr;
        return true;
    }
    *to = static_cast<T *>(from.toObject()->getPrivateData());
    return true;
}

template <typename T>
typename std::enable_if_t<std::is_pointer<T>::value && std::is_pointer<typename std::remove_pointer<T>::type>::value, bool>
sevalue_to_native(const se::Value &from, T to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    using Value = typename std::remove_pointer<typename std::remove_pointer<T>::type>::type;
    CC_STATIC_ASSERT(is_jsb_object_v<Value> || std::is_arithmetic<Value>::value, "Only JSB object or arithmetic types are supported");

    if CC_CONSTEXPR (is_jsb_object_v<Value>) {
        if (from.isNullOrUndefined()) {
            //const std::string stack = se::ScriptEngine::getInstance()->getCurrentStackTrace();
            //SE_LOGE("[ERROR] sevalue_to_native jsval is null/undefined: %s\nstack: %s", typeid(T).name(), stack.c_str());
            *to = nullptr;
            return true;
        }
        *to = static_cast<typename std::remove_pointer<T>::type>(from.toObject()->getPrivateData());
        return true;
    } else if CC_CONSTEXPR (std::is_arithmetic<Value>::value) {
        se::Object *array = from.toObject();
        if (array->isTypedArray()) {
            uint8_t *data = nullptr;
            array->getTypedArrayData(&data, nullptr);
            *to = reinterpret_cast<Value *>(data);
        } else if (array->isArrayBuffer()) {
            uint8_t *data = nullptr;
            array->getArrayBufferData(&data, nullptr);
            *to = reinterpret_cast<Value *>(data);
        } else {
            assert(false);
            return false;
        }
        return true;
    }
}

template <typename T>
typename std::enable_if_t<!std::is_pointer<T>::value && is_jsb_object_v<T>, bool>
sevalue_to_native(const se::Value &from, T **to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    if (from.isNullOrUndefined()) {
        //const std::string stack = se::ScriptEngine::getInstance()->getCurrentStackTrace();
        //SE_LOGE("[ERROR] sevalue_to_native jsval is null/undefined: %s\nstack: %s", typeid(T).name(), stack.c_str());
        *to = nullptr;
        return true;
    }
    *to = static_cast<T *>(from.toObject()->getPrivateData());
    return true;
}

template <typename T>
typename std::enable_if_t<!std::is_pointer<T>::value && is_jsb_object_v<T>, bool>
sevalue_to_native(const se::Value &from, T ***to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    if (from.isNullOrUndefined()) {
        //const std::string stack = se::ScriptEngine::getInstance()->getCurrentStackTrace();
        //SE_LOGE("[ERROR] sevalue_to_native jsval is null/undefined: %s\nstack: %s", typeid(T).name(), stack.c_str());
        *to = nullptr;
        return true;
    }
    **to = static_cast<T *>(from.toObject()->getPrivateData());
    return true;
}

template <typename T, typename allocator>
bool sevalue_to_native(const se::Value &from, std::vector<T, allocator> *to, se::Object *ctx) { // NOLINT(readability-identifier-naming)

    if (from.isNullOrUndefined()) {
        to->clear();
        return true;
    }

    assert(from.toObject());
    se::Object *array = from.toObject();

    if (array->isArray()) {
        uint32_t len = 0;
        array->getArrayLength(&len);
        to->resize(len);
        se::Value tmp;
        for (uint32_t i = 0; i < len; i++) {
            array->getArrayElement(i, &tmp);
            if (!sevalue_to_native(tmp, to->data() + i, ctx)) {
                SE_LOGE("vector %s convert error at %d\n", typeid(T).name(), i);
            }
        }
        return true;
    }

    if (array->isTypedArray()) {
        assert(std::is_arithmetic<T>::value);
        uint8_t *data    = nullptr;
        size_t   dataLen = 0;
        array->getTypedArrayData(&data, &dataLen);
        to->assign(reinterpret_cast<T *>(data), reinterpret_cast<T *>(data + dataLen));
        return true;
    }

    SE_LOGE("[warn] failed to convert to std::vector\n");
    return false;
}

//template<>
//bool sevalue_to_native(const se::Value &from, cc::gfx::Context **to, se::Object*) {
//    assert(from.isObject());
//    *to = (cc::gfx::Context*)from.toObject()->getPrivateData();
//    return true;
//}

template <>
inline bool sevalue_to_native(const se::Value &from, void **to, se::Object * /*ctx*/) {
    SE_LOGE("[warn] don't know how to convert to void *\n");
    *to = from.toObject()->getPrivateData();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, std::string **to, se::Object * /*ctx*/) {
    **to = from.toString();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::ValueMap *to, se::Object * /*ctx*/) {
    return seval_to_ccvaluemap(from, to);
}

template <>
bool sevalue_to_native(const se::Value &from, std::vector<bool> *to, se::Object * /*ctx*/);

template <>
bool sevalue_to_native(const se::Value &from, std::vector<unsigned char> *to, se::Object * /*ctx*/);

///////////////////// TypedArray

template <typename R, typename... Args>
inline bool sevalue_to_native(const se::Value &from, std::function<R(Args...)> *func, se::Object *self) { // NOLINT(readability-identifier-naming)
    if (from.isObject() && from.toObject()->isFunction()) {
        se::Object *callback = from.toObject();
        self->attachObject(callback);
        *func = [callback, self](Args... inargs) {
            se::AutoHandleScope hs;
            bool                ok = true;
            se::ValueArray      args;
            int                 idx = 0;
            args.resize(sizeof...(Args));
            nativevalue_to_se_args_v(args, inargs...);
            se::Value rval;
            bool      succeed = callback->call(args, self, &rval);
            if (!succeed) {
                se::ScriptEngine::getInstance()->clearException();
            }
            if CC_CONSTEXPR (!std::is_same<R, void>::value) {
                R rawRet = {};
                sevalue_to_native(rval, &rawRet, self);
                return rawRet;
            }
        };
    } else {
        return false;
    }
    return true;
}

//////////////////////// std::variant

template <>
bool sevalue_to_native(const se::Value &from, std::variant<std::vector<float>, std::string> *to, se::Object *ctx);

template <typename... Args>
inline bool sevalue_to_native(const se::Value &from, std::variant<Args...> *to, se::Object *ctx) {
    static_assert(sizeof...(Args) == 0); //TODO(PatriceJiang): should not pass variant from js -> native
    assert(false);
    return false;
}

template <>
inline bool sevalue_to_native(const se::Value &from, std::monostate *to, se::Object *ctx) {
    // nothing todo
    return false;
}

template <>
bool sevalue_to_native(const se::Value &from, std::variant<std::monostate, cc::MaterialProperty, cc::MaterialPropertyList> *to, se::Object *ctx);

#if HAS_CONSTEXPR
template <typename T, bool is_reference>
inline bool sevalue_to_native(const se::Value &from, HolderType<T, is_reference> *holder, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    if CC_CONSTEXPR (is_reference && is_jsb_object_v<T>) {
    #if 1 // TODO(PatriceJiang): allow pure js value to struct
        void *ptr = from.toObject()->getPrivateData();
        if (ptr) {
            holder->data = static_cast<T *>(ptr);
            return true;
        }
        holder->ptr = new T;
        return sevalue_to_native(from, holder->ptr, ctx);
    #else
        void *ptr = from.toObject()->getPrivateData();
        assert(ptr); // pure js object is not acceptable
        holder->data = static_cast<T *>(ptr);
        return true;
    #endif

    } else if CC_CONSTEXPR (is_jsb_object_v<T>) {
        void *ptr = from.toObject()->getPrivateData();
        if (ptr) {
            holder->data = *static_cast<T *>(ptr);
            return true;
        }
        return sevalue_to_native(from, &(holder->data), ctx);

    } else {
        return sevalue_to_native(from, &(holder->data), ctx);
    }
}

#else
template <typename T>
inline typename std::enable_if<is_jsb_object_v<T>, bool>::type sevalue_to_native(const se::Value &from, HolderType<T, true> *holder, se::Object *ctx) {
    void *ptr = from.toObject()->getPrivateData();
    if (ptr) {
        holder->data = static_cast<T *>(ptr);
        return true;
    } else {
        holder->ptr = new T;
        return sevalue_to_native(from, holder->ptr, ctx);
    }
}

template <typename T>
inline typename std::enable_if<!is_jsb_object_v<T>, bool>::type sevalue_to_native(const se::Value &from, HolderType<T, true> *holder, se::Object *ctx) {
    return sevalue_to_native(from, &(holder->data), ctx);
}

template <typename T>
inline typename std::enable_if<is_jsb_object_v<T>, bool>::type sevalue_to_native(const se::Value &from, HolderType<T, false> *holder, se::Object *ctx) {
    void *ptr = from.toObject()->getPrivateData();
    if (ptr) {
        holder->data = *static_cast<T *>(ptr);
        return true;
    } else {
        return sevalue_to_native(from, &(holder->data), ctx);
    }
}

template <typename T>
inline typename std::enable_if<!is_jsb_object_v<T>, bool>::type sevalue_to_native(const se::Value &from, HolderType<T, false> *holder, se::Object *ctx) {
    return sevalue_to_native(from, &(holder->data), ctx);
}

#endif // HAS_CONSTEXPR

#if HAS_CONSTEXPR
template <typename T, typename allocator>
inline bool sevalue_to_native(const se::Value &from, HolderType<std::vector<T, allocator>, true> *holder, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    if CC_CONSTEXPR (is_jsb_object_v<T> && std::is_pointer<T>::value) {
        auto &vec = holder->data;
        return sevalue_to_native(from, &vec, ctx);
    } else if CC_CONSTEXPR (is_jsb_object_v<T>) {
        return sevalue_to_native(from, static_cast<std::vector<T, allocator> *>(&(holder->data)), ctx);
    } else {
        return sevalue_to_native(from, &(holder->data), ctx);
    }
}

#else
template <typename T, typename allocator>
inline typename std::enable_if<is_jsb_object_v<T> && std::is_pointer<T>::value, bool>::type
sevalue_to_native(const se::Value &from, HolderType<std::vector<T, allocator>, true> *holder, se::Object *ctx) {
    auto &vec = holder->data;
    return sevalue_to_native(from, &vec, ctx);
}
template <typename T, typename allocator>
inline typename std::enable_if<is_jsb_object_v<T> && !std::is_pointer<T>::value, bool>::type
sevalue_to_native(const se::Value &from, HolderType<std::vector<T, allocator>, true> *holder, se::Object *ctx) {
    return sevalue_to_native(from, (std::vector<T, allocator> *)/* clang/xcode needs this */ &(holder->data), ctx);
}

template <typename T, typename allocator>
inline typename std::enable_if<!is_jsb_object_v<T>, bool>::type
sevalue_to_native(const se::Value &from, HolderType<std::vector<T, allocator>, true> *holder, se::Object *ctx) {
    return sevalue_to_native(from, &(holder->data), ctx);
}

#endif // HAS_CONSTEXPR

/////////////////// std::shared_ptr

template <typename T>
bool sevalue_to_native(const se::Value &from, std::shared_ptr<T> *out, se::Object *ctx) {
    T *  tmp = new T;
    bool ok  = sevalue_to_native<T>(from, tmp, ctx);
    out->reset(tmp);
    //TODO(PatriceJiang): should not mix smart pointers with raw pointers.
    return ok;
}

template <typename T>
inline
    typename std::enable_if<std::is_arithmetic<T>::value, bool>::type
    sevalue_to_native(const se::Value &from, std::shared_ptr<cc::TypedArrayTemp<T>> *out, se::Object *ctx) {
    *out = std::make_shared<cc::TypedArrayTemp<T>>();
    sevalue_to_native<T>(from, out->get(), ctx);
    //TODO(PatriceJiang): should not mix smart pointers with raw pointers.
    return true;
}

/////////////////// std::tuple
template <typename T, T... S, typename F>
constexpr void se_for_each(std::integer_sequence<T, S...> index, F &&f) {
    (static_cast<void>(f(std::integral_constant<T, S>{})), ...);
}

template <typename... Args>
constexpr bool sevalue_to_native(const se::Value &from, std::tuple<Args...> *to, se::Object *ctx) {
    constexpr size_t ARGSIZE = std::tuple_size<std::tuple<Args...>>::value;
    bool             result  = true;
    se_for_each(std::make_index_sequence<ARGSIZE>{}, [&](auto i) {
        se::Value tmp;
        from.toObject()->getArrayElement(i, &tmp);
        result &= sevalue_to_native(tmp, &std::get<i>(*to), ctx);
    });
    return result;
}

////////////// std::unorderd_map
template <typename V>
bool sevalue_to_native(const se::Value &from, std::unordered_map<std::string, V> *to, se::Object *ctx) { //NOLINT
    se::Object *             jsmap = from.toObject();
    std::vector<std::string> allKeys;
    jsmap->getAllKeys(&allKeys);
    bool      ret = true;
    se::Value property;
    for (auto &it : allKeys) {
        if (jsmap->getProperty(it.c_str(), &property)) {
            auto &output = (*to)[it];
            ret &= sevalue_to_native(property, &output, jsmap);
        }
    }
    return true;
}

///////////////// std::optional
template <typename T>
bool sevalue_to_native(const se::Value &from, std::optional<T> *to, se::Object *ctx) { //NOLINT
    static_assert(!is_optional<T>::value, "bad match ?");
    if (from.isNullOrUndefined()) {
        to->reset();
        return true;
    }
    T    tmp{};
    bool ret = sevalue_to_native(from, &tmp, ctx);
    if constexpr (std::is_move_assignable<T>::value) {
        *to = std::move(tmp);
    } else {
        *to = tmp;
    }
    return ret;
}
//////////////////////  shoter form
template <typename T>
inline bool sevalue_to_native(const se::Value &from, T to) { // NOLINT(readability-identifier-naming)
    return sevalue_to_native(from, to, static_cast<se::Object *>(nullptr));
}

//////////////////////// scene info
template <>
bool sevalue_to_native(const se::Value &from, cc::scene::FogInfo *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::scene::ShadowsInfo *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::scene::SkyboxInfo *, se::Object * /*ctx*/);

/////////////////////// geometry

template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::AABB *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Capsule *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Line *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Ray *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Sphere *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Triangle *, se::Object * /*ctx*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Plane *to, se::Object * /*unused*/);
template <>
bool sevalue_to_native(const se::Value &from, cc::geometry::Frustum *to, se::Object * /*unused*/);

///////////////////////////////////////////////////////////////////
//////////////////  nativevalue_to_se   ///////////////////////////
///////////////////////////////////////////////////////////////////
template <typename T>
inline bool nativevalue_to_se(T &&from, se::Value &to); // NOLINT(readability-identifier-naming)

#if HAS_CONSTEXPR

template <typename T>
inline bool nativevalue_to_se(const T &from, se::Value &to, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    if CC_CONSTEXPR (std::is_enum<T>::value) {
        to.setInt32(static_cast<int32_t>(from));
        return true;
    } else if CC_CONSTEXPR (std::is_pointer<T>::value) {
        return native_ptr_to_seval(from, &to);
    } else if CC_CONSTEXPR (is_jsb_object_v<T>) {
        return native_ptr_to_seval(from, &to);
    } else if CC_CONSTEXPR (std::is_same<T, int64_t>::value || std::is_same<T, uint64_t>::value) {
        to.setInt64(static_cast<int64_t>(from));
        return true;
    } else if CC_CONSTEXPR (std::is_arithmetic<T>::value) {
        to.setDouble(static_cast<double>(from));
        return true;
    } else {
        static_assert(!std::is_const<T>::value, "Only non-const value accepted here");
        return nativevalue_to_se<typename std::conditional_t<std::is_const<T>::value, T, typename std::add_const<T>::type>>(from, to, ctx);
    }
}

#else

template <typename T>
inline typename std::enable_if<std::is_enum<T>::value, bool>::type
nativevalue_to_se(const T &from, se::Value &to, se::Object *ctx) {
    to.setInt32(static_cast<int32_t>(from));
    return true;
}

template <typename T>
inline typename std::enable_if<std::is_pointer<T>::value, bool>::type
nativevalue_to_se(const T &from, se::Value &to, se::Object *ctx) {
    return native_ptr_to_seval(from, &to);
}

template <typename T>
inline typename std::enable_if<is_jsb_object_v<T>, bool>::type
nativevalue_to_se(const T &from, se::Value &to, se::Object *ctx) {
    return native_ptr_to_seval(from, &to);
}

template <typename T>
inline typename std::enable_if<!std::is_enum<T>::value && !std::is_pointer<T>::value && !is_jsb_object_v<T>, bool>::type
nativevalue_to_se(const T &from, se::Value &to, se::Object *ctx) {
    return nativevalue_to_se<typename std::conditional_t<std::is_const<T>::value, T, typename std::add_const<T>::type>>(from, to, ctx);
}

#endif // HAS_CONSTEXPR

//////////////////////////////// forward declaration: nativevalue_to_se ////////////////////////////////

template <typename T>
inline bool nativevalue_to_se(const std::shared_ptr<T> &from, se::Value &to, se::Object *ctx); // NOLINT

template <typename T>
bool nativevalue_to_se(const std::reference_wrapper<T> ref, se::Value &to, se::Object *ctx); // NOLINT

//template <>
//bool nativevalue_to_se(const cc::TypedArray &typedArray, se::Value &to, se::Object * /*ctx*/); // NOLINT

template <>
bool nativevalue_to_se(const cc::ArrayBuffer &arrayBuffer, se::Value &to, se::Object * /*ctx*/); // NOLINT

template <typename... ARGS>
bool nativevalue_to_se(const std::variant<ARGS...> &from, se::Value &to, se::Object *ctx); // NOLINT

template <typename... ARGS>
bool nativevalue_to_se(const std::tuple<ARGS...> &from, se::Value &to, se::Object *ctx); // NOLINT

template <typename T, typename A>
inline bool nativevalue_to_se(const std::vector<T, A> &from, se::Value &to, se::Object *ctx); // NOLINT

template <typename K, typename V>
inline bool nativevalue_to_se(const std::unordered_map<K, V> &from, se::Value &to, se::Object *ctx); // NOLINT

/// nativevalue_to_se std::optional
template <typename T>
bool nativevalue_to_se(const std::optional<T> &from, se::Value &to, se::Object *ctx) { // NOLINT
    if (!from.has_value()) {
        to.setUndefined();
        return true;
    }
    return nativevalue_to_se(from.value(), to, ctx);
}

template <typename T>
inline bool nativevalue_to_se(const cc::TypedArrayTemp<T> &typedArray, se::Value &to, se::Object *ctx) {
    to.setObject(typedArray.getJSTypedArray());
    return true;
}

template <typename T, typename A>
inline bool nativevalue_to_se(const std::vector<T, A> &from, se::Value &to, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    se::HandleObject array(se::Object::createArrayObject(from.size()));
    se::Value        tmp;
    for (size_t i = 0; i < from.size(); i++) {
        nativevalue_to_se(from[i], tmp, ctx);
        array->setArrayElement(static_cast<uint32_t>(i), tmp);
    }
    to.setObject(array, true);
    return true;
}

template <>
inline bool nativevalue_to_se(const std::vector<int8_t> &from, se::Value &to, se::Object * /*ctx*/) {
    se::Object *array = se::Object::createTypedArray(se::Object::TypedArrayType::INT8, from.data(), from.size());
    to.setObject(array);
    array->decRef();
    return true;
}

template <>
inline bool nativevalue_to_se(const std::vector<uint8_t> &from, se::Value &to, se::Object * /*ctx*/) {
    se::Object *array = se::Object::createTypedArray(se::Object::TypedArrayType::UINT8, from.data(), from.size());
    to.setObject(array);
    array->decRef();
    return true;
}

template <typename A>
inline bool nativevalue_to_se(const std::vector<bool, A> &from, se::Value &to, se::Object * /*ctx*/) {
    se::HandleObject array(se::Object::createArrayObject(from.size()));
    for (auto i = 0; i < from.size(); i++) {
        array->setArrayElement(i, se::Value(from[i]));
    }
    to.setObject(array);
    return true;
}

template <typename K, typename V>
inline bool nativevalue_to_se(const std::unordered_map<K, V> &from, se::Value &to, se::Object *ctx) { // NOLINT
    se::Object *ret = se::Object::createPlainObject();
    se::Value   value;
    bool        ok = true;
    for (auto &it : from) {
        ok &= nativevalue_to_se(it.second, value, ctx);
        if CC_CONSTEXPR (std::is_convertible<K, std::string>::value) {
            ret->setProperty(it.first, value);
        } else {
            ret->setProperty(std::to_string(it.first), value);
        }
    }
    to.setObject(ret);
    ret->decRef();
    return true;
}

template <typename T, size_t N>
inline bool nativevalue_to_se(const std::array<T, N> &from, se::Value &to, se::Object *ctx) { // NOLINT(readability-identifier-naming)
    se::Object *array = se::Object::createArrayObject(N);
    se::Value   tmp;
    for (size_t i = 0; i < N; i++) {
        nativevalue_to_se(from[i], tmp, ctx);
        array->setArrayElement(static_cast<uint32_t>(i), tmp);
    }
    to.setObject(array);
    array->decRef();
    return true;
}

template <size_t N>
inline bool nativevalue_to_se(const std::array<uint8_t, N> &from, se::Value &to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    se::Object *array = se::Object::createTypedArray(se::Object::TypedArrayType::UINT8, from.data(), N);
    to.setObject(array);
    array->decRef();
    return true;
}

template <size_t N>
inline bool nativevalue_to_se(const std::array<uint16_t, N> &from, se::Value &to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    se::Object *array = se::Object::createTypedArray(se::Object::TypedArrayType::INT16, from.data(), N * sizeof(uint16_t));
    to.setObject(array);
    array->decRef();
    return true;
}

template <size_t N>
inline bool nativevalue_to_se(const std::array<float, N> &from, se::Value &to, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    se::Object *array = se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, from.data(), N * sizeof(float));
    to.setObject(array);
    array->decRef();
    return true;
}

template <>
inline bool nativevalue_to_se(const int64_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setInt64(from);
    return true;
}

template <>
inline bool nativevalue_to_se(const uint64_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setUint64(from);
    return true;
}

template <>
inline bool nativevalue_to_se(const int32_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setInt32(from);
    return true;
}

template <>
inline bool nativevalue_to_se(const uint32_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setUint32(from);
    return true;
}
template <>
inline bool nativevalue_to_se(const int16_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setInt16(from);
    return true;
}
template <>
inline bool nativevalue_to_se(const uint16_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setUint16(from);
    return true;
}

template <>
inline bool nativevalue_to_se(const int8_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setInt8(from);
    return true;
}

template <>
inline bool nativevalue_to_se(const uint8_t &from, se::Value &to, se::Object * /*ctx*/) {
    to.setUint8(from);
    return true;
}

template <>
inline bool nativevalue_to_se(const std::string &from, se::Value &to, se::Object * /*ctx*/) {
    to.setString(from);
    return true;
}
template <>
inline bool nativevalue_to_se(const float &from, se::Value &to, se::Object * /*ctx*/) {
    to.setFloat(from);
    return true;
}
template <>
inline bool nativevalue_to_se(const double &from, se::Value &to, se::Object * /*ctx*/) {
    to.setFloat(static_cast<float>(from));
    return true;
}
template <>
inline bool nativevalue_to_se(const bool &from, se::Value &to, se::Object * /*ctx*/) {
    to.setBoolean(from);
    return true;
}

// template <>
// bool nativevalue_to_se(const cc::Color &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::NativeDep &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Mat3 &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Mat4 &from, se::Value &to, se::Object *ctx);

template <typename R, typename... Args>
inline bool nativevalue_to_se(std::function<R(Args...)> & /*from*/, se::Value & /*to*/, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    SE_LOGE("Can not convert C++ lambda to JS object");                                                         // TODO(jiangzhan)
    return false;
}

template <typename R, typename... Args>
inline bool nativevalue_to_se(const std::function<R(Args...)> & /*from*/, se::Value & /*to*/, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    SE_LOGE("Can not convert C++ const lambda to JS object");                                                         // TODO(jiangzhan)
    return false;
}

///////////////////////// function ///////////////////////

template <int i, typename T>
bool nativevalue_to_se_args(se::ValueArray &array, T &x) { // NOLINT(readability-identifier-naming)
    return nativevalue_to_se(x, array[i], nullptr);
}
template <int i, typename T, typename... Args>
bool nativevalue_to_se_args(se::ValueArray &array, T &x, Args &...args) { // NOLINT(readability-identifier-naming)
    return nativevalue_to_se_args<i, T>(array, x) && nativevalue_to_se_args<i + 1, Args...>(array, args...);
}

template <typename... Args>
bool nativevalue_to_se_args_v(se::ValueArray &array, Args &...args) { // NOLINT(readability-identifier-naming)
    return nativevalue_to_se_args<0, Args...>(array, args...);
}

/////////////////////// FIXME: remove all code bellow
///////////////// gfx type
namespace cc {
class GFXContext;
class Data;
class Value;
class Vec4;
class Size;
} // namespace cc
//template<>

// JSB_REGISTER_OBJECT_TYPE(cc::network::DownloaderHints);

template <>
bool nativevalue_to_se(const cc::Data &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Value &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const std::unordered_map<std::string, cc::Value> &from, se::Value &to, se::Object *ctx);

// template <>
// bool nativevalue_to_se(const cc::Vec2 &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Vec3 &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Vec4 &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Size &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Quaternion &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::extension::ManifestAsset &from, se::Value &to, se::Object *ctx);

template <>
bool nativevalue_to_se(const cc::Rect &from, se::Value &to, se::Object *ctx);

template <>
inline bool nativevalue_to_se(const cc::network::DownloadTask &from, se::Value &to, se::Object * /*ctx*/) {
    return DownloadTask_to_seval(from, &to);
}

#if __clang__
    #pragma clang diagnostic pop
#endif

// Spine conversions
#if USE_SPINE

template <>
bool sevalue_to_native(const se::Value &, spine::String *, se::Object *);

template <typename T>
bool nativevalue_to_se(const spine::Vector<T> &v, se::Value &ret, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    se::HandleObject obj(se::Object::createArrayObject(v.size()));
    bool             ok = true;

    spine::Vector<T> tmpv = v;

    auto size = static_cast<uint32_t>(tmpv.size());
    for (uint32_t i = 0; i < size; ++i) {
        se::Value tmp;
        ok = nativevalue_to_se(tmpv[i], tmp, nullptr);
        if (!ok || !obj->setArrayElement(i, tmp)) {
            ok = false;
            ret.setUndefined();
            break;
        }
    }

    if (ok) {
        ret.setObject(obj);
    }

    return ok;
}

template <typename T>
bool nativevalue_to_se(const spine::Vector<T *> &v, se::Value &ret, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    se::HandleObject obj(se::Object::createArrayObject(v.size()));
    bool             ok = true;

    spine::Vector<T *> tmpv = v;

    auto size = static_cast<uint32_t>(tmpv.size());
    for (uint32_t i = 0; i < size; ++i) {
        se::Value tmp;
        ok = native_ptr_to_rooted_seval<T>(tmpv[i], &tmp);
        if (!ok || !obj->setArrayElement(i, tmp)) {
            ok = false;
            ret.setUndefined();
            break;
        }
    }

    if (ok) ret.setObject(obj);
    return ok;
}

template <typename T>
bool sevalue_to_native(const se::Value &v, spine::Vector<T *> *ret, se::Object * /*ctx*/) { // NOLINT(readability-identifier-naming)
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object *obj = v.toObject();
    assert(obj->isArray());

    bool     ok  = true;
    uint32_t len = 0;
    ok           = obj->getArrayLength(&len);
    if (!ok) {
        ret->clear();
        return false;
    }

    se::Value tmp;
    for (uint32_t i = 0; i < len; ++i) {
        ok = obj->getArrayElement(i, &tmp);
        if (!ok || !tmp.isObject()) {
            ret->clear();
            return false;
        }

        T *nativeObj = static_cast<T *>(tmp.toObject()->getPrivateData());
        ret->add(nativeObj);
    }

    return true;
}

template <>
bool nativevalue_to_se(const spine::Vector<spine::String> &v, se::Value &ret, se::Object *ctx);

template <>
bool nativevalue_to_se(const spine::String &from, se::Value &to, se::Object *ctx);

template <>
bool sevalue_to_native(const se::Value &v, spine::Vector<spine::String> *ret, se::Object *ctx);

template <>
bool seval_to_Map_string_key(const se::Value &v, cc::Map<std::string, cc::middleware::Texture2D *> *ret);
#endif //USE_SPINE

#if USE_MIDDLEWARE
template <>
inline bool nativevalue_to_se(const se_object_ptr &from, se::Value &to, se::Object * /*ctx*/) {
    to.setObject(const_cast<se::Object *>(from));
    return true;
}
#endif //USE_MIDDLEWARE

/////////////////// shorter form
template <typename T>
inline bool nativevalue_to_se(T &&from, se::Value &to) { // NOLINT(readability-identifier-naming)
    return nativevalue_to_se(std::forward<typename std::add_const<T>::type>(from), to, nullptr);
}

template <typename... ARGS>
bool nativevalue_to_se(const std::variant<ARGS...> &from, se::Value &to, se::Object *ctx) {
    bool ok = false;
    se_for_each(std::make_index_sequence<sizeof...(ARGS)>{}, [&](auto i) {
        if (i != from.index()) {
            return;
        }
        ok = nativevalue_to_se(std::get<i>(from), to, ctx);
    });
    return ok;
}

template <>
inline bool nativevalue_to_se(const std::monostate &from, se::Value &to, se::Object *ctx) { //NOLINT
    to.setUndefined();
    return true;
}

template <>
inline bool nativevalue_to_se(const std::any &from, se::Value &to, se::Object *ctx) { //NOLINT
    assert(false);
    //TODO(PatriceJiang): // should not convert std::any
    return true;
}

template <typename T>
inline bool nativevalue_to_se(const std::shared_ptr<T> &from, se::Value &to, se::Object *ctx) { //NOLINT
    if (!from) {
        to.setNull(); // or undefined ?
        return true;
    }
    return nativevalue_to_se(*from, to, ctx);
}

template <typename... ARGS>
bool nativevalue_to_se(const std::tuple<ARGS...> &from, se::Value &to, se::Object *ctx) {
    bool        ok = true;
    se::Value   tmp;
    se::Object *array = se::Object::createArrayObject(sizeof...(ARGS));
    se_for_each(std::make_index_sequence<sizeof...(ARGS)>{}, [&](auto i) {
        ok &= nativevalue_to_se(std::get<i>(from), tmp, ctx);
        array->setArrayElement(i, tmp);
    });
    to.setObject(array);
    return ok;
}

template <typename T>
bool nativevalue_to_se(const std::reference_wrapper<T> ref, se::Value &to, se::Object *ctx) { // NOLINT
    return nativevalue_to_se(ref.get(), to, ctx);
}
