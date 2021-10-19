#pragma once
#include "base/Config.h"
#include <type_traits>
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/auto/jsb_gfx_auto.h"
#include "cocos/bindings/auto/jsb_pipeline_auto.h"
#include "cocos/core/assets/AssetsModuleHeader.h"
#include "cocos/3d/assets/Mesh.h"
#include "cocos/3d/assets/Morph.h"
#include "cocos/3d/assets/MorphRendering.h"
#include "cocos/3d/assets/Skeleton.h"

extern se::Object *__jsb_cc_BoundingBox_proto; // NOLINT
extern se::Class * __jsb_cc_BoundingBox_class; // NOLINT

bool js_register_cc_BoundingBox(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::BoundingBox *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::BoundingBox);

extern se::Object *__jsb_cc_VertexIdChannel_proto; // NOLINT
extern se::Class * __jsb_cc_VertexIdChannel_class; // NOLINT

bool js_register_cc_VertexIdChannel(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::VertexIdChannel *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::VertexIdChannel);

extern se::Object *__jsb_cc_Asset_proto; // NOLINT
extern se::Class * __jsb_cc_Asset_class; // NOLINT

bool js_register_cc_Asset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Asset);
SE_DECLARE_FUNC(js_assets_Asset_addRef);
SE_DECLARE_FUNC(js_assets_Asset_createNode);
SE_DECLARE_FUNC(js_assets_Asset_decRef);
SE_DECLARE_FUNC(js_assets_Asset_deserialize);
SE_DECLARE_FUNC(js_assets_Asset_destroy);
SE_DECLARE_FUNC(js_assets_Asset_getNativeAsset);
SE_DECLARE_FUNC(js_assets_Asset_getNativeDep);
SE_DECLARE_FUNC(js_assets_Asset_getRefCount);
SE_DECLARE_FUNC(js_assets_Asset_initDefault);
SE_DECLARE_FUNC(js_assets_Asset_isDefault);
SE_DECLARE_FUNC(js_assets_Asset_onLoaded);
SE_DECLARE_FUNC(js_assets_Asset_serialize);
SE_DECLARE_FUNC(js_assets_Asset_setNativeAsset);
SE_DECLARE_FUNC(js_assets_Asset_toString);
SE_DECLARE_FUNC(js_assets_Asset_validate);

extern se::Object *__jsb_cc_BufferAsset_proto; // NOLINT
extern se::Class * __jsb_cc_BufferAsset_class; // NOLINT

bool js_register_cc_BufferAsset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::BufferAsset);
SE_DECLARE_FUNC(js_assets_BufferAsset_getBuffer);

extern se::Object *__jsb_cc_TextureBase_proto; // NOLINT
extern se::Class * __jsb_cc_TextureBase_class; // NOLINT

bool js_register_cc_TextureBase(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::TextureBase);
SE_DECLARE_FUNC(js_assets_TextureBase_getAnisotropy);
SE_DECLARE_FUNC(js_assets_TextureBase_getGFXSampler);
SE_DECLARE_FUNC(js_assets_TextureBase_getGFXTexture);
SE_DECLARE_FUNC(js_assets_TextureBase_getHash);
SE_DECLARE_FUNC(js_assets_TextureBase_getHeight);
SE_DECLARE_FUNC(js_assets_TextureBase_getId);
SE_DECLARE_FUNC(js_assets_TextureBase_getPixelFormat);
SE_DECLARE_FUNC(js_assets_TextureBase_getSamplerHash);
SE_DECLARE_FUNC(js_assets_TextureBase_getWidth);
SE_DECLARE_FUNC(js_assets_TextureBase_isCompressed);
SE_DECLARE_FUNC(js_assets_TextureBase_setAnisotropy);
SE_DECLARE_FUNC(js_assets_TextureBase_setFilters);
SE_DECLARE_FUNC(js_assets_TextureBase_setMipFilter);
SE_DECLARE_FUNC(js_assets_TextureBase_setWrapMode);

extern se::Object *__jsb_cc_IGeometricInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IGeometricInfo_class; // NOLINT

bool js_register_cc_IGeometricInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IGeometricInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IGeometricInfo);

extern se::Object *__jsb_cc_IFlatBuffer_proto; // NOLINT
extern se::Class * __jsb_cc_IFlatBuffer_class; // NOLINT

bool js_register_cc_IFlatBuffer(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IFlatBuffer *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IFlatBuffer);

extern se::Object *__jsb_cc_RenderingSubMesh_proto; // NOLINT
extern se::Class * __jsb_cc_RenderingSubMesh_class; // NOLINT

bool js_register_cc_RenderingSubMesh(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::RenderingSubMesh);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_enableVertexIdChannel);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_genFlatBuffers);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_geometricInfo);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getAttributes);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getFlatBuffers);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getIaInfo);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getIndexBuffer);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getJointMappedBuffers);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getMesh);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getPrimitiveMode);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getSubMeshIdx);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_getVertexBuffers);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_indirectBuffer);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_setFlatBuffers);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_setMesh);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_setSubMeshIdx);
SE_DECLARE_FUNC(js_assets_RenderingSubMesh_RenderingSubMesh);

extern se::Object *__jsb_cc_IMemoryImageSource_proto; // NOLINT
extern se::Class * __jsb_cc_IMemoryImageSource_class; // NOLINT

bool js_register_cc_IMemoryImageSource(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IMemoryImageSource *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IMemoryImageSource);

extern se::Object *__jsb_cc_ImageAsset_proto; // NOLINT
extern se::Class * __jsb_cc_ImageAsset_class; // NOLINT

bool js_register_cc_ImageAsset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::ImageAsset);
SE_DECLARE_FUNC(js_assets_ImageAsset_isCompressed);
SE_DECLARE_FUNC(js_assets_ImageAsset_ImageAsset);

extern se::Object *__jsb_cc_SimpleTexture_proto; // NOLINT
extern se::Class * __jsb_cc_SimpleTexture_class; // NOLINT

bool js_register_cc_SimpleTexture(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::SimpleTexture);
SE_DECLARE_FUNC(js_assets_SimpleTexture_assignImage);
SE_DECLARE_FUNC(js_assets_SimpleTexture_checkTextureLoaded);
SE_DECLARE_FUNC(js_assets_SimpleTexture_mipmapLevel);
SE_DECLARE_FUNC(js_assets_SimpleTexture_updateImage);
SE_DECLARE_FUNC(js_assets_SimpleTexture_updateMipmaps);
SE_DECLARE_FUNC(js_assets_SimpleTexture_uploadData);

extern se::Object *__jsb_cc_ITexture2DSerializeData_proto; // NOLINT
extern se::Class * __jsb_cc_ITexture2DSerializeData_class; // NOLINT

bool js_register_cc_ITexture2DSerializeData(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ITexture2DSerializeData *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ITexture2DSerializeData);

extern se::Object *__jsb_cc_ITexture2DCreateInfo_proto; // NOLINT
extern se::Class * __jsb_cc_ITexture2DCreateInfo_class; // NOLINT

bool js_register_cc_ITexture2DCreateInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ITexture2DCreateInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ITexture2DCreateInfo);

extern se::Object *__jsb_cc_Texture2D_proto; // NOLINT
extern se::Class * __jsb_cc_Texture2D_class; // NOLINT

bool js_register_cc_Texture2D(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Texture2D);
SE_DECLARE_FUNC(js_assets_Texture2D_create);
SE_DECLARE_FUNC(js_assets_Texture2D_description);
SE_DECLARE_FUNC(js_assets_Texture2D_getGfxTextureCreateInfo);
SE_DECLARE_FUNC(js_assets_Texture2D_getHtmlElementObj);
SE_DECLARE_FUNC(js_assets_Texture2D_getImage);
SE_DECLARE_FUNC(js_assets_Texture2D_getMipmaps);
SE_DECLARE_FUNC(js_assets_Texture2D_getMipmapsUuids);
SE_DECLARE_FUNC(js_assets_Texture2D_initialize);
SE_DECLARE_FUNC(js_assets_Texture2D_releaseTexture);
SE_DECLARE_FUNC(js_assets_Texture2D_reset);
SE_DECLARE_FUNC(js_assets_Texture2D_setImage);
SE_DECLARE_FUNC(js_assets_Texture2D_setMipmaps);
SE_DECLARE_FUNC(js_assets_Texture2D_Texture2D);

extern se::Object *__jsb_cc_IPropertyInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IPropertyInfo_class; // NOLINT

bool js_register_cc_IPropertyInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IPropertyInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IPropertyInfo);

extern se::Object *__jsb_cc_ITechniqueInfo_proto; // NOLINT
extern se::Class * __jsb_cc_ITechniqueInfo_class; // NOLINT

bool js_register_cc_ITechniqueInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ITechniqueInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ITechniqueInfo);

extern se::Object *__jsb_cc_IBlockInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IBlockInfo_class; // NOLINT

bool js_register_cc_IBlockInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IBlockInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IBlockInfo);

extern se::Object *__jsb_cc_ISamplerTextureInfo_proto; // NOLINT
extern se::Class * __jsb_cc_ISamplerTextureInfo_class; // NOLINT

bool js_register_cc_ISamplerTextureInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ISamplerTextureInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ISamplerTextureInfo);

extern se::Object *__jsb_cc_IAttributeInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IAttributeInfo_class; // NOLINT

bool js_register_cc_IAttributeInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IAttributeInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IAttributeInfo);

extern se::Object *__jsb_cc_IDefineInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IDefineInfo_class; // NOLINT

bool js_register_cc_IDefineInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IDefineInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IDefineInfo);

extern se::Object *__jsb_cc_IBuiltin_proto; // NOLINT
extern se::Class * __jsb_cc_IBuiltin_class; // NOLINT

bool js_register_cc_IBuiltin(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IBuiltin *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IBuiltin);

extern se::Object *__jsb_cc_IBuiltinInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IBuiltinInfo_class; // NOLINT

bool js_register_cc_IBuiltinInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IBuiltinInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IBuiltinInfo);

extern se::Object *__jsb_cc_IBuiltins_proto; // NOLINT
extern se::Class * __jsb_cc_IBuiltins_class; // NOLINT

bool js_register_cc_IBuiltins(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IBuiltins *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IBuiltins);

extern se::Object *__jsb_cc_IShaderSource_proto; // NOLINT
extern se::Class * __jsb_cc_IShaderSource_class; // NOLINT

bool js_register_cc_IShaderSource(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IShaderSource *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IShaderSource);

extern se::Object *__jsb_cc_IShaderInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IShaderInfo_class; // NOLINT

bool js_register_cc_IShaderInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IShaderInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IShaderInfo);
SE_DECLARE_FUNC(js_assets_IShaderInfo_getSource);

extern se::Object *__jsb_cc_EffectAsset_proto; // NOLINT
extern se::Class * __jsb_cc_EffectAsset_class; // NOLINT

bool js_register_cc_EffectAsset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::EffectAsset);
SE_DECLARE_FUNC(js_assets_EffectAsset_registerAsset);
SE_DECLARE_FUNC(js_assets_EffectAsset_remove);
SE_DECLARE_FUNC(js_assets_EffectAsset_get);
SE_DECLARE_FUNC(js_assets_EffectAsset_getAll);
SE_DECLARE_FUNC(js_assets_EffectAsset_EffectAsset);

extern se::Object *__jsb_cc_JsonAsset_proto; // NOLINT
extern se::Class * __jsb_cc_JsonAsset_class; // NOLINT

bool js_register_cc_JsonAsset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::JsonAsset);
SE_DECLARE_FUNC(js_assets_JsonAsset_JsonAsset);

extern se::Object *__jsb_cc_IMaterialInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IMaterialInfo_class; // NOLINT

bool js_register_cc_IMaterialInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IMaterialInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IMaterialInfo);

extern se::Object *__jsb_cc_Material_proto; // NOLINT
extern se::Class * __jsb_cc_Material_class; // NOLINT

bool js_register_cc_Material(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Material);
SE_DECLARE_FUNC(js_assets_Material_copy);
SE_DECLARE_FUNC(js_assets_Material_getEffectAsset);
SE_DECLARE_FUNC(js_assets_Material_getEffectName);
SE_DECLARE_FUNC(js_assets_Material_getHash);
SE_DECLARE_FUNC(js_assets_Material_getParent);
SE_DECLARE_FUNC(js_assets_Material_getPasses);
SE_DECLARE_FUNC(js_assets_Material_getProperty);
SE_DECLARE_FUNC(js_assets_Material_getTechniqueIndex);
SE_DECLARE_FUNC(js_assets_Material_initialize);
SE_DECLARE_FUNC(js_assets_Material_overridePipelineStates);
SE_DECLARE_FUNC(js_assets_Material_reset);
SE_DECLARE_FUNC(js_assets_Material_resetUniforms);
SE_DECLARE_FUNC(js_assets_Material_setEffectAsset);
SE_DECLARE_FUNC(js_assets_Material_update);
SE_DECLARE_FUNC(js_assets_Material_getHashForMaterial);
SE_DECLARE_FUNC(js_assets_Material_Material);

extern se::Object *__jsb_cc_Prefab_proto; // NOLINT
extern se::Class * __jsb_cc_Prefab_class; // NOLINT

bool js_register_cc_Prefab(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Prefab);
SE_DECLARE_FUNC(js_assets_Prefab__instantiate);
SE_DECLARE_FUNC(js_assets_Prefab_Prefab);

extern se::Object *__jsb_cc_IRenderTextureCreateInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IRenderTextureCreateInfo_class; // NOLINT

bool js_register_cc_IRenderTextureCreateInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IRenderTextureCreateInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IRenderTextureCreateInfo);

extern se::Object *__jsb_cc_RenderTexture_proto; // NOLINT
extern se::Class * __jsb_cc_RenderTexture_class; // NOLINT

bool js_register_cc_RenderTexture(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::RenderTexture);
SE_DECLARE_FUNC(js_assets_RenderTexture_getHeight);
SE_DECLARE_FUNC(js_assets_RenderTexture_getWidth);
SE_DECLARE_FUNC(js_assets_RenderTexture_getWindow);
SE_DECLARE_FUNC(js_assets_RenderTexture_initWindow);
SE_DECLARE_FUNC(js_assets_RenderTexture_initialize);
SE_DECLARE_FUNC(js_assets_RenderTexture_reset);
SE_DECLARE_FUNC(js_assets_RenderTexture_resize);
SE_DECLARE_FUNC(js_assets_RenderTexture_RenderTexture);

extern se::Object *__jsb_cc_SceneAsset_proto; // NOLINT
extern se::Class * __jsb_cc_SceneAsset_class; // NOLINT

bool js_register_cc_SceneAsset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::SceneAsset);
SE_DECLARE_FUNC(js_assets_SceneAsset_getScene);
SE_DECLARE_FUNC(js_assets_SceneAsset_SceneAsset);

extern se::Object *__jsb_cc_TextAsset_proto; // NOLINT
extern se::Class * __jsb_cc_TextAsset_class; // NOLINT

bool js_register_cc_TextAsset(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::TextAsset);
SE_DECLARE_FUNC(js_assets_TextAsset_TextAsset);

extern se::Object *__jsb_cc_ITextureCubeMipmap_proto; // NOLINT
extern se::Class * __jsb_cc_ITextureCubeMipmap_class; // NOLINT

bool js_register_cc_ITextureCubeMipmap(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ITextureCubeMipmap *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ITextureCubeMipmap);

extern se::Object *__jsb_cc_ITextureCubeSerializeMipmapData_proto; // NOLINT
extern se::Class * __jsb_cc_ITextureCubeSerializeMipmapData_class; // NOLINT

bool js_register_cc_ITextureCubeSerializeMipmapData(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ITextureCubeSerializeMipmapData *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ITextureCubeSerializeMipmapData);

extern se::Object *__jsb_cc_ITextureCubeSerializeData_proto; // NOLINT
extern se::Class * __jsb_cc_ITextureCubeSerializeData_class; // NOLINT

bool js_register_cc_ITextureCubeSerializeData(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::ITextureCubeSerializeData *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::ITextureCubeSerializeData);

extern se::Object *__jsb_cc_TextureCube_proto; // NOLINT
extern se::Class * __jsb_cc_TextureCube_class; // NOLINT

bool js_register_cc_TextureCube(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::TextureCube);
SE_DECLARE_FUNC(js_assets_TextureCube_getGfxTextureCreateInfo);
SE_DECLARE_FUNC(js_assets_TextureCube_getImage);
SE_DECLARE_FUNC(js_assets_TextureCube_getMipmaps);
SE_DECLARE_FUNC(js_assets_TextureCube_initialize);
SE_DECLARE_FUNC(js_assets_TextureCube_releaseTexture);
SE_DECLARE_FUNC(js_assets_TextureCube_reset);
SE_DECLARE_FUNC(js_assets_TextureCube_setImage);
SE_DECLARE_FUNC(js_assets_TextureCube_setMipmaps);
SE_DECLARE_FUNC(js_assets_TextureCube_fromTexture2DArray);
SE_DECLARE_FUNC(js_assets_TextureCube_TextureCube);

extern se::Object *__jsb_cc_IMeshBufferView_proto; // NOLINT
extern se::Class * __jsb_cc_IMeshBufferView_class; // NOLINT

bool js_register_cc_IMeshBufferView(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IMeshBufferView *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IMeshBufferView);

extern se::Object *__jsb_cc_MorphTarget_proto; // NOLINT
extern se::Class * __jsb_cc_MorphTarget_class; // NOLINT

bool js_register_cc_MorphTarget(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::MorphTarget *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::MorphTarget);

extern se::Object *__jsb_cc_SubMeshMorph_proto; // NOLINT
extern se::Class * __jsb_cc_SubMeshMorph_class; // NOLINT

bool js_register_cc_SubMeshMorph(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::SubMeshMorph *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::SubMeshMorph);

extern se::Object *__jsb_cc_Morph_proto; // NOLINT
extern se::Class * __jsb_cc_Morph_class; // NOLINT

bool js_register_cc_Morph(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::Morph *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::Morph);

extern se::Object *__jsb_cc_Mesh_IVertexBundle_proto; // NOLINT
extern se::Class * __jsb_cc_Mesh_IVertexBundle_class; // NOLINT

bool js_register_cc_Mesh_IVertexBundle(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::Mesh::IVertexBundle *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::Mesh::IVertexBundle);

extern se::Object *__jsb_cc_Mesh_ISubMesh_proto; // NOLINT
extern se::Class * __jsb_cc_Mesh_ISubMesh_class; // NOLINT

bool js_register_cc_Mesh_ISubMesh(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::Mesh::ISubMesh *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::Mesh::ISubMesh);

extern se::Object *__jsb_cc_Mesh_IStruct_proto; // NOLINT
extern se::Class * __jsb_cc_Mesh_IStruct_class; // NOLINT

bool js_register_cc_Mesh_IStruct(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::Mesh::IStruct *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::Mesh::IStruct);

extern se::Object *__jsb_cc_Mesh_ICreateInfo_proto; // NOLINT
extern se::Class * __jsb_cc_Mesh_ICreateInfo_class; // NOLINT

bool js_register_cc_Mesh_ICreateInfo(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::Mesh::ICreateInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::Mesh::ICreateInfo);

extern se::Object *__jsb_cc_Mesh_proto; // NOLINT
extern se::Class * __jsb_cc_Mesh_class; // NOLINT

bool js_register_cc_Mesh(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Mesh);
SE_DECLARE_FUNC(js_assets_Mesh_assign);
SE_DECLARE_FUNC(js_assets_Mesh_copyAttribute);
SE_DECLARE_FUNC(js_assets_Mesh_copyIndices);
SE_DECLARE_FUNC(js_assets_Mesh_destroyRenderingMesh);
SE_DECLARE_FUNC(js_assets_Mesh_getBoneSpaceBounds);
SE_DECLARE_FUNC(js_assets_Mesh_getData);
SE_DECLARE_FUNC(js_assets_Mesh_getHash);
SE_DECLARE_FUNC(js_assets_Mesh_getJointBufferIndices);
SE_DECLARE_FUNC(js_assets_Mesh_getMaxPosition);
SE_DECLARE_FUNC(js_assets_Mesh_getMinPosition);
SE_DECLARE_FUNC(js_assets_Mesh_getRenderingSubMeshes);
SE_DECLARE_FUNC(js_assets_Mesh_getStruct);
SE_DECLARE_FUNC(js_assets_Mesh_getSubMeshCount);
SE_DECLARE_FUNC(js_assets_Mesh_initialize);
SE_DECLARE_FUNC(js_assets_Mesh_merge);
SE_DECLARE_FUNC(js_assets_Mesh_readAttribute);
SE_DECLARE_FUNC(js_assets_Mesh_readIndices);
SE_DECLARE_FUNC(js_assets_Mesh_reset);
SE_DECLARE_FUNC(js_assets_Mesh_validateMergingMesh);
SE_DECLARE_FUNC(js_assets_Mesh_Mesh);

extern se::Object *__jsb_cc_MorphRendering_proto; // NOLINT
extern se::Class * __jsb_cc_MorphRendering_class; // NOLINT

bool js_register_cc_MorphRendering(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::MorphRendering);
SE_DECLARE_FUNC(js_assets_MorphRendering_createInstance);

extern se::Object *__jsb_cc_MorphRenderingInstance_proto; // NOLINT
extern se::Class * __jsb_cc_MorphRenderingInstance_class; // NOLINT

bool js_register_cc_MorphRenderingInstance(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::MorphRenderingInstance);
SE_DECLARE_FUNC(js_assets_MorphRenderingInstance_adaptPipelineState);
SE_DECLARE_FUNC(js_assets_MorphRenderingInstance_destroy);
SE_DECLARE_FUNC(js_assets_MorphRenderingInstance_requiredPatches);
SE_DECLARE_FUNC(js_assets_MorphRenderingInstance_setWeights);

extern se::Object *__jsb_cc_StdMorphRendering_proto; // NOLINT
extern se::Class * __jsb_cc_StdMorphRendering_class; // NOLINT

bool js_register_cc_StdMorphRendering(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::StdMorphRendering);
SE_DECLARE_FUNC(js_assets_StdMorphRendering_StdMorphRendering);

extern se::Object *__jsb_cc_Skeleton_proto; // NOLINT
extern se::Class * __jsb_cc_Skeleton_class; // NOLINT

bool js_register_cc_Skeleton(se::Object *obj); // NOLINT
bool register_all_assets(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Skeleton);
SE_DECLARE_FUNC(js_assets_Skeleton_getBindposes);
SE_DECLARE_FUNC(js_assets_Skeleton_getHash);
SE_DECLARE_FUNC(js_assets_Skeleton_getInverseBindposes);
SE_DECLARE_FUNC(js_assets_Skeleton_getJoints);
SE_DECLARE_FUNC(js_assets_Skeleton_setBindposes);
SE_DECLARE_FUNC(js_assets_Skeleton_setJoints);

