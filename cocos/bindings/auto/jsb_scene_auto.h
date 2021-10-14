#pragma once
#include "base/Config.h"
#include <type_traits>
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/auto/jsb_gfx_auto.h"
#include "cocos/bindings/auto/jsb_geometry_auto.h"
#include "cocos/bindings/auto/jsb_assets_auto.h"
#include "cocos/core/scene-graph/Node.h"
#include "cocos/scene/Light.h"
#include "cocos/scene/DirectionalLight.h"
#include "cocos/scene/SpotLight.h"
#include "cocos/scene/SphereLight.h"
#include "cocos/scene/Model.h"
#include "cocos/scene/SubModel.h"
#include "cocos/scene/Pass.h"
#include "cocos/scene/RenderScene.h"
#include "cocos/scene/DrawBatch2D.h"
#include "cocos/scene/Camera.h"
#include "cocos/scene/RenderWindow.h"
#include "cocos/scene/Camera.h"
#include "cocos/scene/Define.h"
#include "cocos/scene/Ambient.h"

extern se::Object *__jsb_cc_BaseNode_proto; // NOLINT
extern se::Class * __jsb_cc_BaseNode_class; // NOLINT

bool js_register_cc_BaseNode(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::BaseNode);
SE_DECLARE_FUNC(js_scene_BaseNode_addChild);
SE_DECLARE_FUNC(js_scene_BaseNode_destroy);
SE_DECLARE_FUNC(js_scene_BaseNode_destroyAllChildren);
SE_DECLARE_FUNC(js_scene_BaseNode_emit);
SE_DECLARE_FUNC(js_scene_BaseNode_getChangedFlags);
SE_DECLARE_FUNC(js_scene_BaseNode_getChildByName);
SE_DECLARE_FUNC(js_scene_BaseNode_getChildByPath);
SE_DECLARE_FUNC(js_scene_BaseNode_getChildByUuid);
SE_DECLARE_FUNC(js_scene_BaseNode_getChildren);
SE_DECLARE_FUNC(js_scene_BaseNode_getDirtyFlag);
SE_DECLARE_FUNC(js_scene_BaseNode_getName);
SE_DECLARE_FUNC(js_scene_BaseNode_getParent);
SE_DECLARE_FUNC(js_scene_BaseNode_getPersistNode);
SE_DECLARE_FUNC(js_scene_BaseNode_getPosition);
SE_DECLARE_FUNC(js_scene_BaseNode_getRotation);
SE_DECLARE_FUNC(js_scene_BaseNode_getScale);
SE_DECLARE_FUNC(js_scene_BaseNode_getScene);
SE_DECLARE_FUNC(js_scene_BaseNode_getSiblingIndex);
SE_DECLARE_FUNC(js_scene_BaseNode_getUUid);
SE_DECLARE_FUNC(js_scene_BaseNode_getWorldMatrix);
SE_DECLARE_FUNC(js_scene_BaseNode_getWorldRotation);
SE_DECLARE_FUNC(js_scene_BaseNode_hasEventListener);
SE_DECLARE_FUNC(js_scene_BaseNode_insertChild);
SE_DECLARE_FUNC(js_scene_BaseNode_isActive);
SE_DECLARE_FUNC(js_scene_BaseNode_isActiveInHierarchy);
SE_DECLARE_FUNC(js_scene_BaseNode_isChildOf);
SE_DECLARE_FUNC(js_scene_BaseNode_off);
SE_DECLARE_FUNC(js_scene_BaseNode_on);
SE_DECLARE_FUNC(js_scene_BaseNode_onPostActivated);
SE_DECLARE_FUNC(js_scene_BaseNode_once);
SE_DECLARE_FUNC(js_scene_BaseNode_removeAllChildren);
SE_DECLARE_FUNC(js_scene_BaseNode_removeChild);
SE_DECLARE_FUNC(js_scene_BaseNode_removeFromParent);
SE_DECLARE_FUNC(js_scene_BaseNode_setActive);
SE_DECLARE_FUNC(js_scene_BaseNode_setChangedFlags);
SE_DECLARE_FUNC(js_scene_BaseNode_setDirtyFlag);
SE_DECLARE_FUNC(js_scene_BaseNode_setLayer);
SE_DECLARE_FUNC(js_scene_BaseNode_setName);
SE_DECLARE_FUNC(js_scene_BaseNode_setParent);
SE_DECLARE_FUNC(js_scene_BaseNode_setPersistNode);
SE_DECLARE_FUNC(js_scene_BaseNode_setSiblingIndex);
SE_DECLARE_FUNC(js_scene_BaseNode_targetOff);
SE_DECLARE_FUNC(js_scene_BaseNode_updateSiblingIndex);
SE_DECLARE_FUNC(js_scene_BaseNode_updateWorldTransform);
SE_DECLARE_FUNC(js_scene_BaseNode_walk);
SE_DECLARE_FUNC(js_scene_BaseNode_instantiate);
SE_DECLARE_FUNC(js_scene_BaseNode_setScene);
SE_DECLARE_FUNC(js_scene_BaseNode_getIdxOfChild);
SE_DECLARE_FUNC(js_scene_BaseNode_BaseNode);

extern se::Object *__jsb_cc_Node_proto; // NOLINT
extern se::Class * __jsb_cc_Node_class; // NOLINT

bool js_register_cc_Node(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Node);
SE_DECLARE_FUNC(js_scene_Node_getAngle);
SE_DECLARE_FUNC(js_scene_Node_getEulerAngles);
SE_DECLARE_FUNC(js_scene_Node_getForward);
SE_DECLARE_FUNC(js_scene_Node_getLayer);
SE_DECLARE_FUNC(js_scene_Node_getRight);
SE_DECLARE_FUNC(js_scene_Node_getUp);
SE_DECLARE_FUNC(js_scene_Node_getWorldPosition);
SE_DECLARE_FUNC(js_scene_Node_getWorldRS);
SE_DECLARE_FUNC(js_scene_Node_getWorldRT);
SE_DECLARE_FUNC(js_scene_Node_getWorldScale);
SE_DECLARE_FUNC(js_scene_Node_invalidateChildren);
SE_DECLARE_FUNC(js_scene_Node_inverseTransformPoint);
SE_DECLARE_FUNC(js_scene_Node_lookAt);
SE_DECLARE_FUNC(js_scene_Node_pauseSystemEvents);
SE_DECLARE_FUNC(js_scene_Node_resumeSystemEvents);
SE_DECLARE_FUNC(js_scene_Node_rotate);
SE_DECLARE_FUNC(js_scene_Node_setAngle);
SE_DECLARE_FUNC(js_scene_Node_setEulerAngles);
SE_DECLARE_FUNC(js_scene_Node_setForward);
SE_DECLARE_FUNC(js_scene_Node_setPosition);
SE_DECLARE_FUNC(js_scene_Node_setRTS);
SE_DECLARE_FUNC(js_scene_Node_setRotation);
SE_DECLARE_FUNC(js_scene_Node_setRotationFromEuler);
SE_DECLARE_FUNC(js_scene_Node_setScale);
SE_DECLARE_FUNC(js_scene_Node_setWorldPosition);
SE_DECLARE_FUNC(js_scene_Node_setWorldRotation);
SE_DECLARE_FUNC(js_scene_Node_setWorldRotationFromEuler);
SE_DECLARE_FUNC(js_scene_Node_setWorldScale);
SE_DECLARE_FUNC(js_scene_Node_translate);
SE_DECLARE_FUNC(js_scene_Node_setDirtyNode);
SE_DECLARE_FUNC(js_scene_Node_getDirtyNode);
SE_DECLARE_FUNC(js_scene_Node_resetChangedFlags);
SE_DECLARE_FUNC(js_scene_Node_clearNodeArray);
SE_DECLARE_FUNC(js_scene_Node_Node);

extern se::Object *__jsb_cc_scene_Light_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Light_class; // NOLINT

bool js_register_cc_scene_Light(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Light);
SE_DECLARE_FUNC(js_scene_Light_attachToScene);
SE_DECLARE_FUNC(js_scene_Light_destroy);
SE_DECLARE_FUNC(js_scene_Light_detachFromScene);
SE_DECLARE_FUNC(js_scene_Light_getName);
SE_DECLARE_FUNC(js_scene_Light_getScene);
SE_DECLARE_FUNC(js_scene_Light_initialize);
SE_DECLARE_FUNC(js_scene_Light_isBaked);
SE_DECLARE_FUNC(js_scene_Light_isUseColorTemperature);
SE_DECLARE_FUNC(js_scene_Light_setBaked);
SE_DECLARE_FUNC(js_scene_Light_setColor);
SE_DECLARE_FUNC(js_scene_Light_setColorTemperature);
SE_DECLARE_FUNC(js_scene_Light_setColorTemperatureRGB);
SE_DECLARE_FUNC(js_scene_Light_setName);
SE_DECLARE_FUNC(js_scene_Light_setNode);
SE_DECLARE_FUNC(js_scene_Light_setUseColorTemperature);
SE_DECLARE_FUNC(js_scene_Light_update);
SE_DECLARE_FUNC(js_scene_Light_nt2lm);

extern se::Object *__jsb_cc_scene_DirectionalLight_proto; // NOLINT
extern se::Class * __jsb_cc_scene_DirectionalLight_class; // NOLINT

bool js_register_cc_scene_DirectionalLight(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::DirectionalLight);
SE_DECLARE_FUNC(js_scene_DirectionalLight_setDirection);
SE_DECLARE_FUNC(js_scene_DirectionalLight_setIlluminance);
SE_DECLARE_FUNC(js_scene_DirectionalLight_DirectionalLight);

extern se::Object *__jsb_cc_scene_SpotLight_proto; // NOLINT
extern se::Class * __jsb_cc_scene_SpotLight_class; // NOLINT

bool js_register_cc_scene_SpotLight(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::SpotLight);
SE_DECLARE_FUNC(js_scene_SpotLight_getLuminance);
SE_DECLARE_FUNC(js_scene_SpotLight_setAspect);
SE_DECLARE_FUNC(js_scene_SpotLight_setFrustum);
SE_DECLARE_FUNC(js_scene_SpotLight_setLuminance);
SE_DECLARE_FUNC(js_scene_SpotLight_setRange);
SE_DECLARE_FUNC(js_scene_SpotLight_setSize);
SE_DECLARE_FUNC(js_scene_SpotLight_setSpotAngle);
SE_DECLARE_FUNC(js_scene_SpotLight_SpotLight);

extern se::Object *__jsb_cc_scene_SphereLight_proto; // NOLINT
extern se::Class * __jsb_cc_scene_SphereLight_class; // NOLINT

bool js_register_cc_scene_SphereLight(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::SphereLight);
SE_DECLARE_FUNC(js_scene_SphereLight_getLuminance);
SE_DECLARE_FUNC(js_scene_SphereLight_setLuminance);
SE_DECLARE_FUNC(js_scene_SphereLight_setPosition);
SE_DECLARE_FUNC(js_scene_SphereLight_setRange);
SE_DECLARE_FUNC(js_scene_SphereLight_setSize);
SE_DECLARE_FUNC(js_scene_SphereLight_SphereLight);

extern se::Object *__jsb_cc_scene_Model_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Model_class; // NOLINT

bool js_register_cc_scene_Model(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Model);
SE_DECLARE_FUNC(js_scene_Model_attachToScene);
SE_DECLARE_FUNC(js_scene_Model_createBoundingShape);
SE_DECLARE_FUNC(js_scene_Model_destroy);
SE_DECLARE_FUNC(js_scene_Model_detachFromScene);
SE_DECLARE_FUNC(js_scene_Model_getCastShadow);
SE_DECLARE_FUNC(js_scene_Model_getInstMatWorldIdx);
SE_DECLARE_FUNC(js_scene_Model_getInstanceAttributes);
SE_DECLARE_FUNC(js_scene_Model_getInstancedAttributeBlock);
SE_DECLARE_FUNC(js_scene_Model_getInstancedBuffer);
SE_DECLARE_FUNC(js_scene_Model_getInstancedBufferSize);
SE_DECLARE_FUNC(js_scene_Model_getLocalData);
SE_DECLARE_FUNC(js_scene_Model_getMacroPatches);
SE_DECLARE_FUNC(js_scene_Model_getNode);
SE_DECLARE_FUNC(js_scene_Model_getReceiveShadow);
SE_DECLARE_FUNC(js_scene_Model_getScene);
SE_DECLARE_FUNC(js_scene_Model_getSubModels);
SE_DECLARE_FUNC(js_scene_Model_getTransform);
SE_DECLARE_FUNC(js_scene_Model_getTransformUpdated);
SE_DECLARE_FUNC(js_scene_Model_getUpdateStamp);
SE_DECLARE_FUNC(js_scene_Model_getVisFlags);
SE_DECLARE_FUNC(js_scene_Model_initSubModel);
SE_DECLARE_FUNC(js_scene_Model_initialize);
SE_DECLARE_FUNC(js_scene_Model_isDynamicBatching);
SE_DECLARE_FUNC(js_scene_Model_isEnabled);
SE_DECLARE_FUNC(js_scene_Model_isInited);
SE_DECLARE_FUNC(js_scene_Model_isInstancingEnabled);
SE_DECLARE_FUNC(js_scene_Model_onGlobalPipelineStateChanged);
SE_DECLARE_FUNC(js_scene_Model_onMacroPatchesStateChanged);
SE_DECLARE_FUNC(js_scene_Model_setBounds);
SE_DECLARE_FUNC(js_scene_Model_setCastShadow);
SE_DECLARE_FUNC(js_scene_Model_setDynamicBatching);
SE_DECLARE_FUNC(js_scene_Model_setEnabled);
SE_DECLARE_FUNC(js_scene_Model_setInstMatWorldIdx);
SE_DECLARE_FUNC(js_scene_Model_setLocalBuffer);
SE_DECLARE_FUNC(js_scene_Model_setNode);
SE_DECLARE_FUNC(js_scene_Model_setReceiveShadow);
SE_DECLARE_FUNC(js_scene_Model_setSubModelMaterial);
SE_DECLARE_FUNC(js_scene_Model_setSubModelMesh);
SE_DECLARE_FUNC(js_scene_Model_setTransform);
SE_DECLARE_FUNC(js_scene_Model_setVisFlags);
SE_DECLARE_FUNC(js_scene_Model_updateInstancedAttributes);
SE_DECLARE_FUNC(js_scene_Model_updateLightingmap);
SE_DECLARE_FUNC(js_scene_Model_updateTransform);
SE_DECLARE_FUNC(js_scene_Model_updateUBOs);
SE_DECLARE_FUNC(js_scene_Model_updateWorldBound);
SE_DECLARE_FUNC(js_scene_Model_Model);

extern se::Object *__jsb_cc_scene_AmbientInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_AmbientInfo_class; // NOLINT

bool js_register_cc_scene_AmbientInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::AmbientInfo);
SE_DECLARE_FUNC(js_scene_AmbientInfo_getGroundAlbedo);
SE_DECLARE_FUNC(js_scene_AmbientInfo_getSkyColor);
SE_DECLARE_FUNC(js_scene_AmbientInfo_getSkyIllum);
SE_DECLARE_FUNC(js_scene_AmbientInfo_setGroundAlbedo);
SE_DECLARE_FUNC(js_scene_AmbientInfo_setSkyColor);
SE_DECLARE_FUNC(js_scene_AmbientInfo_setSkyIllum);
SE_DECLARE_FUNC(js_scene_AmbientInfo_AmbientInfo);

extern se::Object *__jsb_cc_scene_Ambient_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Ambient_class; // NOLINT

bool js_register_cc_scene_Ambient(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Ambient);
SE_DECLARE_FUNC(js_scene_Ambient_getAlbedoArray);
SE_DECLARE_FUNC(js_scene_Ambient_getColorArray);
SE_DECLARE_FUNC(js_scene_Ambient_getGroundAlbedo);
SE_DECLARE_FUNC(js_scene_Ambient_getSkyColor);
SE_DECLARE_FUNC(js_scene_Ambient_getSkyIllum);
SE_DECLARE_FUNC(js_scene_Ambient_initialize);
SE_DECLARE_FUNC(js_scene_Ambient_isEnabled);
SE_DECLARE_FUNC(js_scene_Ambient_setEnabled);
SE_DECLARE_FUNC(js_scene_Ambient_setGroundAlbedo);
SE_DECLARE_FUNC(js_scene_Ambient_setSkyColor);
SE_DECLARE_FUNC(js_scene_Ambient_setSkyIllum);
SE_DECLARE_FUNC(js_scene_Ambient_Ambient);

extern se::Object *__jsb_cc_scene_FogInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_FogInfo_class; // NOLINT

bool js_register_cc_scene_FogInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::FogInfo);
SE_DECLARE_FUNC(js_scene_FogInfo_activate);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogAtten);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogColor);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogDensity);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogEnd);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogRange);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogStart);
SE_DECLARE_FUNC(js_scene_FogInfo_getFogTop);
SE_DECLARE_FUNC(js_scene_FogInfo_getType);
SE_DECLARE_FUNC(js_scene_FogInfo_isEnabled);
SE_DECLARE_FUNC(js_scene_FogInfo_setEnabled);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogAtten);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogColor);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogDensity);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogEnd);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogRange);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogStart);
SE_DECLARE_FUNC(js_scene_FogInfo_setFogTop);
SE_DECLARE_FUNC(js_scene_FogInfo_setType);

extern se::Object *__jsb_cc_scene_Fog_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Fog_class; // NOLINT

bool js_register_cc_scene_Fog(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Fog);
SE_DECLARE_FUNC(js_scene_Fog_activate);
SE_DECLARE_FUNC(js_scene_Fog_getColorArray);
SE_DECLARE_FUNC(js_scene_Fog_getFogAtten);
SE_DECLARE_FUNC(js_scene_Fog_getFogColor);
SE_DECLARE_FUNC(js_scene_Fog_getFogDensity);
SE_DECLARE_FUNC(js_scene_Fog_getFogEnd);
SE_DECLARE_FUNC(js_scene_Fog_getFogRange);
SE_DECLARE_FUNC(js_scene_Fog_getFogStart);
SE_DECLARE_FUNC(js_scene_Fog_getFogTop);
SE_DECLARE_FUNC(js_scene_Fog_getType);
SE_DECLARE_FUNC(js_scene_Fog_initialize);
SE_DECLARE_FUNC(js_scene_Fog_isEnabled);
SE_DECLARE_FUNC(js_scene_Fog_setEnabled);
SE_DECLARE_FUNC(js_scene_Fog_setFogAtten);
SE_DECLARE_FUNC(js_scene_Fog_setFogColor);
SE_DECLARE_FUNC(js_scene_Fog_setFogDensity);
SE_DECLARE_FUNC(js_scene_Fog_setFogEnd);
SE_DECLARE_FUNC(js_scene_Fog_setFogStart);
SE_DECLARE_FUNC(js_scene_Fog_setFogTop);
SE_DECLARE_FUNC(js_scene_Fog_setType);
SE_DECLARE_FUNC(js_scene_Fog_setfogRange);
SE_DECLARE_FUNC(js_scene_Fog_Fog);

extern se::Object *__jsb_cc_IPassStates_proto; // NOLINT
extern se::Class * __jsb_cc_IPassStates_class; // NOLINT

bool js_register_cc_IPassStates(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IPassStates *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IPassStates);

extern se::Object *__jsb_cc_IPassInfo_proto; // NOLINT
extern se::Class * __jsb_cc_IPassInfo_class; // NOLINT

bool js_register_cc_IPassInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IPassInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IPassInfo);

extern se::Object *__jsb_cc_IPassInfoFull_proto; // NOLINT
extern se::Class * __jsb_cc_IPassInfoFull_class; // NOLINT

bool js_register_cc_IPassInfoFull(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::IPassInfoFull *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::IPassInfoFull);

extern se::Object *__jsb_cc_scene_IMacroPatch_proto; // NOLINT
extern se::Class * __jsb_cc_scene_IMacroPatch_class; // NOLINT

bool js_register_cc_scene_IMacroPatch(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::scene::IMacroPatch *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::scene::IMacroPatch);

extern se::Object *__jsb_cc_scene_ShadowInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_ShadowInfo_class; // NOLINT

bool js_register_cc_scene_ShadowInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::ShadowInfo);
SE_DECLARE_FUNC(js_scene_ShadowInfo_activate);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getBias);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getDistance);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getFar);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getMaxReceived);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getNear);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getNormal);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getNormalBias);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getOrthoSize);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getPcf);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getSaturation);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getShadowColor);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getShadowMapSize);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getSize);
SE_DECLARE_FUNC(js_scene_ShadowInfo_getType);
SE_DECLARE_FUNC(js_scene_ShadowInfo_isAutoAdapt);
SE_DECLARE_FUNC(js_scene_ShadowInfo_isEnabled);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setAutoAdapt);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setBias);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setDistance);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setEnabled);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setFar);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setMaxReceived);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setNear);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setNormal);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setNormalBias);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setOrthoSize);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setPcf);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setPlaneFromNode);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setSaturation);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setShadowMapSize);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setType);
SE_DECLARE_FUNC(js_scene_ShadowInfo_setshadowColor);

extern se::Object *__jsb_cc_scene_Shadow_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Shadow_class; // NOLINT

bool js_register_cc_scene_Shadow(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Shadow);
SE_DECLARE_FUNC(js_scene_Shadow_activate);
SE_DECLARE_FUNC(js_scene_Shadow_destroy);
SE_DECLARE_FUNC(js_scene_Shadow_getBias);
SE_DECLARE_FUNC(js_scene_Shadow_getDistance);
SE_DECLARE_FUNC(js_scene_Shadow_getFar);
SE_DECLARE_FUNC(js_scene_Shadow_getInstancingMaterial);
SE_DECLARE_FUNC(js_scene_Shadow_getMatLight);
SE_DECLARE_FUNC(js_scene_Shadow_getMaterial);
SE_DECLARE_FUNC(js_scene_Shadow_getMaxReceived);
SE_DECLARE_FUNC(js_scene_Shadow_getNear);
SE_DECLARE_FUNC(js_scene_Shadow_getNormal);
SE_DECLARE_FUNC(js_scene_Shadow_getNormalBias);
SE_DECLARE_FUNC(js_scene_Shadow_getOrthoSize);
SE_DECLARE_FUNC(js_scene_Shadow_getPcf);
SE_DECLARE_FUNC(js_scene_Shadow_getPlanarInstanceShader);
SE_DECLARE_FUNC(js_scene_Shadow_getPlanarShader);
SE_DECLARE_FUNC(js_scene_Shadow_getSaturation);
SE_DECLARE_FUNC(js_scene_Shadow_getShadowColor);
SE_DECLARE_FUNC(js_scene_Shadow_getShadowColor4f);
SE_DECLARE_FUNC(js_scene_Shadow_getShadowMapSize);
SE_DECLARE_FUNC(js_scene_Shadow_getSize);
SE_DECLARE_FUNC(js_scene_Shadow_getType);
SE_DECLARE_FUNC(js_scene_Shadow_initialize);
SE_DECLARE_FUNC(js_scene_Shadow_isAutoAdapt);
SE_DECLARE_FUNC(js_scene_Shadow_isEnabled);
SE_DECLARE_FUNC(js_scene_Shadow_isShadowMapDirty);
SE_DECLARE_FUNC(js_scene_Shadow_setAutoAdapt);
SE_DECLARE_FUNC(js_scene_Shadow_setBias);
SE_DECLARE_FUNC(js_scene_Shadow_setDistance);
SE_DECLARE_FUNC(js_scene_Shadow_setEnabled);
SE_DECLARE_FUNC(js_scene_Shadow_setFar);
SE_DECLARE_FUNC(js_scene_Shadow_setMaxReceived);
SE_DECLARE_FUNC(js_scene_Shadow_setNear);
SE_DECLARE_FUNC(js_scene_Shadow_setNormal);
SE_DECLARE_FUNC(js_scene_Shadow_setNormalBias);
SE_DECLARE_FUNC(js_scene_Shadow_setOrthoSize);
SE_DECLARE_FUNC(js_scene_Shadow_setPcf);
SE_DECLARE_FUNC(js_scene_Shadow_setSaturation);
SE_DECLARE_FUNC(js_scene_Shadow_setShadowColor);
SE_DECLARE_FUNC(js_scene_Shadow_setShadowMapDirty);
SE_DECLARE_FUNC(js_scene_Shadow_setShadowMapSize);
SE_DECLARE_FUNC(js_scene_Shadow_setSize);
SE_DECLARE_FUNC(js_scene_Shadow_setType);
SE_DECLARE_FUNC(js_scene_Shadow_Shadow);

extern se::Object *__jsb_cc_scene_SkyboxInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_SkyboxInfo_class; // NOLINT

bool js_register_cc_scene_SkyboxInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::SkyboxInfo);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_activate);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_getEnvamp);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_isEnabled);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_isRGBE);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_isUseIBL);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_setEnabled);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_setEnvmap);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_setRGBE);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_setUseIBL);
SE_DECLARE_FUNC(js_scene_SkyboxInfo_SkyboxInfo);

extern se::Object *__jsb_cc_scene_Skybox_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Skybox_class; // NOLINT

bool js_register_cc_scene_Skybox(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Skybox);
SE_DECLARE_FUNC(js_scene_Skybox_activate);
SE_DECLARE_FUNC(js_scene_Skybox_getEnvmap);
SE_DECLARE_FUNC(js_scene_Skybox_getModel);
SE_DECLARE_FUNC(js_scene_Skybox_initialize);
SE_DECLARE_FUNC(js_scene_Skybox_isEnabled);
SE_DECLARE_FUNC(js_scene_Skybox_isRGBE);
SE_DECLARE_FUNC(js_scene_Skybox_isUseIBL);
SE_DECLARE_FUNC(js_scene_Skybox_setEnabled);
SE_DECLARE_FUNC(js_scene_Skybox_setEnvmap);
SE_DECLARE_FUNC(js_scene_Skybox_setIsRGBE);
SE_DECLARE_FUNC(js_scene_Skybox_setUseIBL);
SE_DECLARE_FUNC(js_scene_Skybox_Skybox);

extern se::Object *__jsb_cc_scene_IRenderWindowInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_IRenderWindowInfo_class; // NOLINT

bool js_register_cc_scene_IRenderWindowInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::scene::IRenderWindowInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::scene::IRenderWindowInfo);

extern se::Object *__jsb_cc_scene_RenderWindow_proto; // NOLINT
extern se::Class * __jsb_cc_scene_RenderWindow_class; // NOLINT

bool js_register_cc_scene_RenderWindow(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::RenderWindow);
SE_DECLARE_FUNC(js_scene_RenderWindow_attachCamera);
SE_DECLARE_FUNC(js_scene_RenderWindow_clearCameras);
SE_DECLARE_FUNC(js_scene_RenderWindow_destroy);
SE_DECLARE_FUNC(js_scene_RenderWindow_detachCamera);
SE_DECLARE_FUNC(js_scene_RenderWindow_extractRenderCameras);
SE_DECLARE_FUNC(js_scene_RenderWindow_getCamera);
SE_DECLARE_FUNC(js_scene_RenderWindow_getFramebuffer);
SE_DECLARE_FUNC(js_scene_RenderWindow_getHeight);
SE_DECLARE_FUNC(js_scene_RenderWindow_getWidth);
SE_DECLARE_FUNC(js_scene_RenderWindow_hasOffScreenAttachments);
SE_DECLARE_FUNC(js_scene_RenderWindow_hasOnScreenAttachments);
SE_DECLARE_FUNC(js_scene_RenderWindow_initialize);
SE_DECLARE_FUNC(js_scene_RenderWindow_resize);
SE_DECLARE_FUNC(js_scene_RenderWindow_shouldSyncSizeWithSwapchain);
SE_DECLARE_FUNC(js_scene_RenderWindow_sortCameras);
SE_DECLARE_FUNC(js_scene_RenderWindow_RenderWindow);

extern se::Object *__jsb_cc_scene_ICameraInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_ICameraInfo_class; // NOLINT

bool js_register_cc_scene_ICameraInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::scene::ICameraInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::scene::ICameraInfo);

extern se::Object *__jsb_cc_scene_Camera_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Camera_class; // NOLINT

bool js_register_cc_scene_Camera(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Camera);
SE_DECLARE_FUNC(js_scene_Camera_attachToScene);
SE_DECLARE_FUNC(js_scene_Camera_changeTargetWindow);
SE_DECLARE_FUNC(js_scene_Camera_destroy);
SE_DECLARE_FUNC(js_scene_Camera_detachCamera);
SE_DECLARE_FUNC(js_scene_Camera_detachFromScene);
SE_DECLARE_FUNC(js_scene_Camera_getAperture);
SE_DECLARE_FUNC(js_scene_Camera_getApertureValue);
SE_DECLARE_FUNC(js_scene_Camera_getAspect);
SE_DECLARE_FUNC(js_scene_Camera_getClearColor);
SE_DECLARE_FUNC(js_scene_Camera_getClearDepth);
SE_DECLARE_FUNC(js_scene_Camera_getClearFlag);
SE_DECLARE_FUNC(js_scene_Camera_getClearStencil);
SE_DECLARE_FUNC(js_scene_Camera_getEc);
SE_DECLARE_FUNC(js_scene_Camera_getExposure);
SE_DECLARE_FUNC(js_scene_Camera_getFarClip);
SE_DECLARE_FUNC(js_scene_Camera_getForward);
SE_DECLARE_FUNC(js_scene_Camera_getFov);
SE_DECLARE_FUNC(js_scene_Camera_getFovAxis);
SE_DECLARE_FUNC(js_scene_Camera_getFrustum);
SE_DECLARE_FUNC(js_scene_Camera_getHeight);
SE_DECLARE_FUNC(js_scene_Camera_getIso);
SE_DECLARE_FUNC(js_scene_Camera_getIsoValue);
SE_DECLARE_FUNC(js_scene_Camera_getMatProj);
SE_DECLARE_FUNC(js_scene_Camera_getMatProjInv);
SE_DECLARE_FUNC(js_scene_Camera_getMatView);
SE_DECLARE_FUNC(js_scene_Camera_getMatViewProj);
SE_DECLARE_FUNC(js_scene_Camera_getMatViewProjInv);
SE_DECLARE_FUNC(js_scene_Camera_getName);
SE_DECLARE_FUNC(js_scene_Camera_getNearClip);
SE_DECLARE_FUNC(js_scene_Camera_getNode);
SE_DECLARE_FUNC(js_scene_Camera_getOrthoHeight);
SE_DECLARE_FUNC(js_scene_Camera_getPosition);
SE_DECLARE_FUNC(js_scene_Camera_getPriority);
SE_DECLARE_FUNC(js_scene_Camera_getProjectionType);
SE_DECLARE_FUNC(js_scene_Camera_getScene);
SE_DECLARE_FUNC(js_scene_Camera_getScreenScale);
SE_DECLARE_FUNC(js_scene_Camera_getShutter);
SE_DECLARE_FUNC(js_scene_Camera_getShutterValue);
SE_DECLARE_FUNC(js_scene_Camera_getViewport);
SE_DECLARE_FUNC(js_scene_Camera_getVisibility);
SE_DECLARE_FUNC(js_scene_Camera_getWidth);
SE_DECLARE_FUNC(js_scene_Camera_getWindow);
SE_DECLARE_FUNC(js_scene_Camera_initialize);
SE_DECLARE_FUNC(js_scene_Camera_isEnabled);
SE_DECLARE_FUNC(js_scene_Camera_isWindowSize);
SE_DECLARE_FUNC(js_scene_Camera_resize);
SE_DECLARE_FUNC(js_scene_Camera_screenToWorld);
SE_DECLARE_FUNC(js_scene_Camera_setAperture);
SE_DECLARE_FUNC(js_scene_Camera_setClearColor);
SE_DECLARE_FUNC(js_scene_Camera_setClearDepth);
SE_DECLARE_FUNC(js_scene_Camera_setClearFlag);
SE_DECLARE_FUNC(js_scene_Camera_setClearStencil);
SE_DECLARE_FUNC(js_scene_Camera_setEc);
SE_DECLARE_FUNC(js_scene_Camera_setEnabled);
SE_DECLARE_FUNC(js_scene_Camera_setFarClip);
SE_DECLARE_FUNC(js_scene_Camera_setFixedSize);
SE_DECLARE_FUNC(js_scene_Camera_setForward);
SE_DECLARE_FUNC(js_scene_Camera_setFov);
SE_DECLARE_FUNC(js_scene_Camera_setFovAxis);
SE_DECLARE_FUNC(js_scene_Camera_setFrustum);
SE_DECLARE_FUNC(js_scene_Camera_setIso);
SE_DECLARE_FUNC(js_scene_Camera_setNearClip);
SE_DECLARE_FUNC(js_scene_Camera_setNode);
SE_DECLARE_FUNC(js_scene_Camera_setOrthoHeight);
SE_DECLARE_FUNC(js_scene_Camera_setPosition);
SE_DECLARE_FUNC(js_scene_Camera_setPriority);
SE_DECLARE_FUNC(js_scene_Camera_setProjectionType);
SE_DECLARE_FUNC(js_scene_Camera_setScreenScale);
SE_DECLARE_FUNC(js_scene_Camera_setShutter);
SE_DECLARE_FUNC(js_scene_Camera_setViewport);
SE_DECLARE_FUNC(js_scene_Camera_setVisibility);
SE_DECLARE_FUNC(js_scene_Camera_setWindow);
SE_DECLARE_FUNC(js_scene_Camera_setWindowSize);
SE_DECLARE_FUNC(js_scene_Camera_update);
SE_DECLARE_FUNC(js_scene_Camera_worldMatrixToScreen);
SE_DECLARE_FUNC(js_scene_Camera_worldToScreen);
SE_DECLARE_FUNC(js_scene_Camera_Camera);

extern se::Object *__jsb_cc_scene_DrawBatch2D_proto; // NOLINT
extern se::Class * __jsb_cc_scene_DrawBatch2D_class; // NOLINT

bool js_register_cc_scene_DrawBatch2D(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::scene::DrawBatch2D *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::scene::DrawBatch2D);

extern se::Object *__jsb_cc_scene_IRenderSceneInfo_proto; // NOLINT
extern se::Class * __jsb_cc_scene_IRenderSceneInfo_class; // NOLINT

bool js_register_cc_scene_IRenderSceneInfo(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::scene::IRenderSceneInfo *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::scene::IRenderSceneInfo);

extern se::Object *__jsb_cc_scene_RenderScene_proto; // NOLINT
extern se::Class * __jsb_cc_scene_RenderScene_class; // NOLINT

bool js_register_cc_scene_RenderScene(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::RenderScene);
SE_DECLARE_FUNC(js_scene_RenderScene_addBatch);
SE_DECLARE_FUNC(js_scene_RenderScene_addCamera);
SE_DECLARE_FUNC(js_scene_RenderScene_addDirectionalLight);
SE_DECLARE_FUNC(js_scene_RenderScene_addModel);
SE_DECLARE_FUNC(js_scene_RenderScene_addSphereLight);
SE_DECLARE_FUNC(js_scene_RenderScene_addSpotLight);
SE_DECLARE_FUNC(js_scene_RenderScene_destroy);
SE_DECLARE_FUNC(js_scene_RenderScene_generateModelId);
SE_DECLARE_FUNC(js_scene_RenderScene_getBatches);
SE_DECLARE_FUNC(js_scene_RenderScene_getCameras);
SE_DECLARE_FUNC(js_scene_RenderScene_getDrawBatch2Ds);
SE_DECLARE_FUNC(js_scene_RenderScene_getMainLight);
SE_DECLARE_FUNC(js_scene_RenderScene_getModels);
SE_DECLARE_FUNC(js_scene_RenderScene_getName);
SE_DECLARE_FUNC(js_scene_RenderScene_getSphereLights);
SE_DECLARE_FUNC(js_scene_RenderScene_getSpotLights);
SE_DECLARE_FUNC(js_scene_RenderScene_initialize);
SE_DECLARE_FUNC(js_scene_RenderScene_onGlobalPipelineStateChanged);
SE_DECLARE_FUNC(js_scene_RenderScene_removeBatch);
SE_DECLARE_FUNC(js_scene_RenderScene_removeBatches);
SE_DECLARE_FUNC(js_scene_RenderScene_removeCamera);
SE_DECLARE_FUNC(js_scene_RenderScene_removeCameras);
SE_DECLARE_FUNC(js_scene_RenderScene_removeDirectionalLight);
SE_DECLARE_FUNC(js_scene_RenderScene_removeModel);
SE_DECLARE_FUNC(js_scene_RenderScene_removeModels);
SE_DECLARE_FUNC(js_scene_RenderScene_removeSphereLight);
SE_DECLARE_FUNC(js_scene_RenderScene_removeSphereLights);
SE_DECLARE_FUNC(js_scene_RenderScene_removeSpotLight);
SE_DECLARE_FUNC(js_scene_RenderScene_removeSpotLights);
SE_DECLARE_FUNC(js_scene_RenderScene_setMainLight);
SE_DECLARE_FUNC(js_scene_RenderScene_unsetMainLight);
SE_DECLARE_FUNC(js_scene_RenderScene_update);
SE_DECLARE_FUNC(js_scene_RenderScene_RenderScene);

extern se::Object *__jsb_cc_Root_proto; // NOLINT
extern se::Class * __jsb_cc_Root_class; // NOLINT

bool js_register_cc_Root(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::Root);
SE_DECLARE_FUNC(js_scene_Root_activeWindow);
SE_DECLARE_FUNC(js_scene_Root_createCamera);
SE_DECLARE_FUNC(js_scene_Root_createScene);
SE_DECLARE_FUNC(js_scene_Root_createWindow);
SE_DECLARE_FUNC(js_scene_Root_destroy);
SE_DECLARE_FUNC(js_scene_Root_destroyLight);
SE_DECLARE_FUNC(js_scene_Root_destroyModel);
SE_DECLARE_FUNC(js_scene_Root_destroyScene);
SE_DECLARE_FUNC(js_scene_Root_destroyScenes);
SE_DECLARE_FUNC(js_scene_Root_destroyWindow);
SE_DECLARE_FUNC(js_scene_Root_destroyWindows);
SE_DECLARE_FUNC(js_scene_Root_frameMove);
SE_DECLARE_FUNC(js_scene_Root_getBatcher2D);
SE_DECLARE_FUNC(js_scene_Root_getCumulativeTime);
SE_DECLARE_FUNC(js_scene_Root_getCurWindow);
SE_DECLARE_FUNC(js_scene_Root_getDataPoolManager);
SE_DECLARE_FUNC(js_scene_Root_getDevice);
SE_DECLARE_FUNC(js_scene_Root_getFixedFPS);
SE_DECLARE_FUNC(js_scene_Root_getFps);
SE_DECLARE_FUNC(js_scene_Root_getFrameCount);
SE_DECLARE_FUNC(js_scene_Root_getFrameTime);
SE_DECLARE_FUNC(js_scene_Root_getMainWindow);
SE_DECLARE_FUNC(js_scene_Root_getPipeline);
SE_DECLARE_FUNC(js_scene_Root_getScenes);
SE_DECLARE_FUNC(js_scene_Root_getTempWindow);
SE_DECLARE_FUNC(js_scene_Root_getWindows);
SE_DECLARE_FUNC(js_scene_Root_initialize);
SE_DECLARE_FUNC(js_scene_Root_isUsingDeferredPipeline);
SE_DECLARE_FUNC(js_scene_Root_onGlobalPipelineStateChanged);
SE_DECLARE_FUNC(js_scene_Root_resetCumulativeTime);
SE_DECLARE_FUNC(js_scene_Root_resize);
SE_DECLARE_FUNC(js_scene_Root_setCurWindow);
SE_DECLARE_FUNC(js_scene_Root_setFixedFPS);
SE_DECLARE_FUNC(js_scene_Root_setRenderPipeline);
SE_DECLARE_FUNC(js_scene_Root_setTempWindow);
SE_DECLARE_FUNC(js_scene_Root_getInstance);
SE_DECLARE_FUNC(js_scene_Root_Root);

extern se::Object *__jsb_cc_scene_Pass_proto; // NOLINT
extern se::Class * __jsb_cc_scene_Pass_class; // NOLINT

bool js_register_cc_scene_Pass(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::Pass);
SE_DECLARE_FUNC(js_scene_Pass_beginChangeStatesSilently);
SE_DECLARE_FUNC(js_scene_Pass_bindSampler);
SE_DECLARE_FUNC(js_scene_Pass_bindTexture);
SE_DECLARE_FUNC(js_scene_Pass_destroy);
SE_DECLARE_FUNC(js_scene_Pass_endChangeStatesSilently);
SE_DECLARE_FUNC(js_scene_Pass_getBatchingScheme);
SE_DECLARE_FUNC(js_scene_Pass_getBinding);
SE_DECLARE_FUNC(js_scene_Pass_getBlendState);
SE_DECLARE_FUNC(js_scene_Pass_getBlocks);
SE_DECLARE_FUNC(js_scene_Pass_getDefines);
SE_DECLARE_FUNC(js_scene_Pass_getDepthStencilState);
SE_DECLARE_FUNC(js_scene_Pass_getDescriptorSet);
SE_DECLARE_FUNC(js_scene_Pass_getDevice);
SE_DECLARE_FUNC(js_scene_Pass_getDynamicState);
SE_DECLARE_FUNC(js_scene_Pass_getDynamics);
SE_DECLARE_FUNC(js_scene_Pass_getHandle);
SE_DECLARE_FUNC(js_scene_Pass_getHash);
SE_DECLARE_FUNC(js_scene_Pass_getLocalSetLayout);
SE_DECLARE_FUNC(js_scene_Pass_getPassIndex);
SE_DECLARE_FUNC(js_scene_Pass_getPassInfoFull);
SE_DECLARE_FUNC(js_scene_Pass_getPhase);
SE_DECLARE_FUNC(js_scene_Pass_getPipelineLayout);
SE_DECLARE_FUNC(js_scene_Pass_getPrimitive);
SE_DECLARE_FUNC(js_scene_Pass_getPriority);
SE_DECLARE_FUNC(js_scene_Pass_getProgram);
SE_DECLARE_FUNC(js_scene_Pass_getProperties);
SE_DECLARE_FUNC(js_scene_Pass_getPropertyIndex);
SE_DECLARE_FUNC(js_scene_Pass_getRasterizerState);
SE_DECLARE_FUNC(js_scene_Pass_getRoot);
SE_DECLARE_FUNC(js_scene_Pass_getShaderInfo);
SE_DECLARE_FUNC(js_scene_Pass_getShaderVariant);
SE_DECLARE_FUNC(js_scene_Pass_getStage);
SE_DECLARE_FUNC(js_scene_Pass_initPassFromTarget);
SE_DECLARE_FUNC(js_scene_Pass_initialize);
SE_DECLARE_FUNC(js_scene_Pass_isRootBufferDirty);
SE_DECLARE_FUNC(js_scene_Pass_overridePipelineStates);
SE_DECLARE_FUNC(js_scene_Pass_resetTexture);
SE_DECLARE_FUNC(js_scene_Pass_resetTextures);
SE_DECLARE_FUNC(js_scene_Pass_resetUBOs);
SE_DECLARE_FUNC(js_scene_Pass_resetUniform);
SE_DECLARE_FUNC(js_scene_Pass_setDynamicState);
SE_DECLARE_FUNC(js_scene_Pass_setUniform);
SE_DECLARE_FUNC(js_scene_Pass_setUniformArray);
SE_DECLARE_FUNC(js_scene_Pass_tryCompile);
SE_DECLARE_FUNC(js_scene_Pass_update);
SE_DECLARE_FUNC(js_scene_Pass_getPropertyTypeFromHandle);
SE_DECLARE_FUNC(js_scene_Pass_getTypeFromHandle);
SE_DECLARE_FUNC(js_scene_Pass_getBindingFromHandle);
SE_DECLARE_FUNC(js_scene_Pass_getOffsetFromHandle);
SE_DECLARE_FUNC(js_scene_Pass_fillPipelineInfo);
SE_DECLARE_FUNC(js_scene_Pass_getPassHash);
SE_DECLARE_FUNC(js_scene_Pass_Pass);

extern se::Object *__jsb_cc_scene_SubModel_proto; // NOLINT
extern se::Class * __jsb_cc_scene_SubModel_class; // NOLINT

bool js_register_cc_scene_SubModel(se::Object *obj); // NOLINT
bool register_all_scene(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::scene::SubModel);
SE_DECLARE_FUNC(js_scene_SubModel_destroy);
SE_DECLARE_FUNC(js_scene_SubModel_getPass);
SE_DECLARE_FUNC(js_scene_SubModel_getPasses);
SE_DECLARE_FUNC(js_scene_SubModel_getPatches);
SE_DECLARE_FUNC(js_scene_SubModel_getPlanarInstanceShader);
SE_DECLARE_FUNC(js_scene_SubModel_getPlanarShader);
SE_DECLARE_FUNC(js_scene_SubModel_getPriority);
SE_DECLARE_FUNC(js_scene_SubModel_getShader);
SE_DECLARE_FUNC(js_scene_SubModel_getShaders);
SE_DECLARE_FUNC(js_scene_SubModel_initPlanarShadowInstanceShader);
SE_DECLARE_FUNC(js_scene_SubModel_initPlanarShadowShader);
SE_DECLARE_FUNC(js_scene_SubModel_initialize);
SE_DECLARE_FUNC(js_scene_SubModel_onMacroPatchesStateChanged);
SE_DECLARE_FUNC(js_scene_SubModel_onPipelineStateChanged);
SE_DECLARE_FUNC(js_scene_SubModel_setDescriptorSet);
SE_DECLARE_FUNC(js_scene_SubModel_setInputAssembler);
SE_DECLARE_FUNC(js_scene_SubModel_setPasses);
SE_DECLARE_FUNC(js_scene_SubModel_setPlanarInstanceShader);
SE_DECLARE_FUNC(js_scene_SubModel_setPlanarShader);
SE_DECLARE_FUNC(js_scene_SubModel_setPriority);
SE_DECLARE_FUNC(js_scene_SubModel_setShaders);
SE_DECLARE_FUNC(js_scene_SubModel_setSubMesh);
SE_DECLARE_FUNC(js_scene_SubModel_update);
SE_DECLARE_FUNC(js_scene_SubModel_SubModel);

