// clang-format off
#pragma once
#include "base/Config.h"
#include <type_traits>
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/auto/jsb_gfx_auto.h"
#include "cocos/bindings/auto/jsb_scene_auto.h"
#include "cocos/bindings/auto/jsb_assets_auto.h"
#include "cocos/renderer/pipeline/forward/ForwardPipeline.h"
#include "cocos/renderer/pipeline/forward/ForwardFlow.h"
#include "cocos/renderer/pipeline/forward/ForwardStage.h"
#include "cocos/renderer/pipeline/shadow/ShadowFlow.h"
#include "cocos/renderer/pipeline/shadow/ShadowStage.h"
#include "cocos/renderer/pipeline/RenderPipeline.h"
#include "cocos/renderer/pipeline/RenderFlow.h"
#include "cocos/renderer/pipeline/RenderStage.h"
#include "cocos/renderer/pipeline/Define.h"
#include "cocos/renderer/pipeline/GlobalDescriptorSetManager.h"
#include "cocos/renderer/pipeline/InstancedBuffer.h"
#include "cocos/renderer/pipeline/deferred/DeferredPipeline.h"
#include "cocos/renderer/pipeline/deferred/MainFlow.h"
#include "cocos/renderer/pipeline/deferred/GbufferStage.h"
#include "cocos/renderer/pipeline/deferred/LightingStage.h"
#include "cocos/renderer/pipeline/deferred/BloomStage.h"
#include "cocos/renderer/pipeline/deferred/PostprocessStage.h"
#include "cocos/renderer/pipeline/PipelineSceneData.h"

extern se::Object *__jsb_cc_pipeline_RenderQueueDesc_proto; // NOLINT
extern se::Class * __jsb_cc_pipeline_RenderQueueDesc_class; // NOLINT

bool js_register_cc_pipeline_RenderQueueDesc(se::Object *obj); // NOLINT
bool register_all_pipeline(se::Object *obj);                   // NOLINT

template <>
bool sevalue_to_native(const se::Value &, cc::pipeline::RenderQueueDesc *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cc::pipeline::RenderQueueDesc);

extern se::Object *__jsb_cc_pipeline_GlobalDSManager_proto; // NOLINT
extern se::Class * __jsb_cc_pipeline_GlobalDSManager_class; // NOLINT

bool js_register_cc_pipeline_GlobalDSManager(se::Object *obj); // NOLINT
bool register_all_pipeline(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(cc::pipeline::GlobalDSManager);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_bindBuffer);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_bindSampler);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_bindTexture);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_getDescriptorSetLayout);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_getDescriptorSetMap);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_getGlobalDescriptorSet);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_getLinearSampler);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_getOrCreateDescriptorSet);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_getPointSampler);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_update);
SE_DECLARE_FUNC(js_pipeline_GlobalDSManager_GlobalDSManager);
