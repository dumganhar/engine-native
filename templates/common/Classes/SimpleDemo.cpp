/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

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

#include "SimpleDemo.h"
#include "3d/framework/MeshRenderer.h"
#include "3d/misc/CreateMesh.h"
#include "base/Log.h"
#include "core/assets/AssetsModuleHeader.h"
#include "core/assets/Texture2D.h"
#include "core/builtin/BuiltinResMgr.h"
#include "core/components/CameraComponent.h"
#include "core/scene-graph/Node.h"

#include "renderer/GFXDeviceManager.h"
#include "scene/Pass.h"

#include "3d/lights/DirectionalLightComponent.h"
#include "3d/lights/SphereLightComponent.h"
#include "3d/lights/SpotLightComponent.h"
#include "core/scene-graph/Layers.h"
#include "platform/Image.h"
#include "primitive/Primitive.h"

#include "core/data/deserializer/AssetDeserializerFactory.h"
#include "core/utils/ImageUtils.h"
#include "platform/FileUtils.h"
#include "terrain/Terrain.h"
#include "terrain/TerrainAsset.h"

//#include "platform/View.h"

using namespace cc;
using namespace cc::gfx;

class MyComponent1 : public Component {
public:
    COMPONENT_EXECUTION_ORDER(MyComponent1, 200)
    void onLoad() override {
        CC_LOG_DEBUG("MyComponent1::onLoad");
    }

    void update(float dt) override {
        //        CC_LOG_DEBUG("MyComponent1::update(%f)", dt);
    }

    void lateUpdate(float dt) override {
        //        CC_LOG_DEBUG("MyComponent1::lateUpdate(%f)", dt);
    }

    void __preload() override {
        CC_LOG_DEBUG("MyComponent1::__preload");
    }

    void start() override {
        CC_LOG_DEBUG("MyComponent1::start");
    }

    void onEnable() override {
        CC_LOG_DEBUG("MyComponent1::onEnable");
    }

    void onDisable() override {
        CC_LOG_DEBUG("MyComponent1::onDisable");
    }

    void onDestroy() override {
        CC_LOG_DEBUG("MyComponent1::onDestroy");
    }
};

class MyComponent2 : public Component {
public:
    COMPONENT_EXECUTION_ORDER(MyComponent2, 106)
    void onLoad() override {
        CC_LOG_DEBUG("MyComponent2::onLoad");
    }

    void update(float dt) override {
        //        CC_LOG_DEBUG("MyComponent2::update(%f)", dt);
    }

    void lateUpdate(float dt) override {
        //        CC_LOG_DEBUG("MyComponent2::lateUpdate(%f)", dt);
    }

    void __preload() override {
        CC_LOG_DEBUG("MyComponent2::__preload");
    }

    void start() override {
        CC_LOG_DEBUG("MyComponent2::start");
    }

    void onEnable() override {
        CC_LOG_DEBUG("MyComponent2::onEnable");
    }

    void onDisable() override {
        CC_LOG_DEBUG("MyComponent2::onDisable");
    }

    void onDestroy() override {
        CC_LOG_DEBUG("MyComponent2::onDestroy");
    }
};
namespace {
void setMaterialFromJsonContent(Material *material, const std::string &materialJson, const std::string &effectName = "standard") {
    std::string materialJsonContent = FileUtils::getInstance()->getStringFromFile(materialJson);

    rapidjson::Document materialDoc;
    materialDoc.Parse(materialJsonContent.c_str());
    auto deserializer = AssetDeserializerFactory::createAssetDeserializer(DeserializeAssetType::MATERIAL);
    deserializer->deserialize(materialDoc, material);
    material->setEffectAsset(EffectAsset::get(effectName));
    material->update(); // need update if not using initialize
}

void createTextureForMaterial(const std::string &texJsonFile, Material *material, const std::string &propName) {
    auto *      texture2DExportedFromEditor = new Texture2D();
    std::string texture2DJsonContent        = FileUtils::getInstance()->getStringFromFile(texJsonFile);
    {
        rapidjson::Document texture2DDoc;
        texture2DDoc.Parse(texture2DJsonContent.c_str());
        auto deserializer = AssetDeserializerFactory::createAssetDeserializer(DeserializeAssetType::TEXTURE2D);
        deserializer->deserialize(texture2DDoc, texture2DExportedFromEditor);
    }
    // setImageForMaterial
    auto *image = new Image();
    bool  ret   = image->initWithImageFile(texture2DExportedFromEditor->getMipmapsUuids()[0] + ".png"); // TODO(xwx): HACK
    ImageUtils::convert2RGBA(image);                                                                    // TODO(xwx): HACK: image file is RGB8 and Metal do not support
    if (ret) {
        auto *imgAsset = new ImageAsset(); //cjh shared_ptr ?
        imgAsset->setNativeAsset(image);   //cjh HOW TO RELEASE?

        texture2DExportedFromEditor->setImage(imgAsset);
        texture2DExportedFromEditor->onLoaded();
        material->setProperty(propName, texture2DExportedFromEditor);
    }
    image->release();
}

void setMeshFromJson(Mesh *mesh, const std::string &meshJson, const std::string &meshBinary) {
    std::string         meshJsonContent = FileUtils::getInstance()->getStringFromFile(meshJson);
    rapidjson::Document meshDoc;
    meshDoc.Parse(meshJsonContent.c_str());
    auto deserializer = AssetDeserializerFactory::createAssetDeserializer(DeserializeAssetType::MESH);
    deserializer->deserialize(meshDoc, mesh);

    Data              meshData = FileUtils::getInstance()->getDataFromFile(meshBinary);
    Mesh::ICreateInfo meshInfo;
    meshInfo.structInfo = mesh->getStruct();
    auto meshBuffer     = std::make_shared<ArrayBuffer>(static_cast<uint32_t>(meshData.getSize()));
    memcpy(const_cast<uint8_t *>(meshBuffer->getData()), meshData.getBytes(), meshData.getSize());
    Uint8Array meshDataArray{meshBuffer, 0};
    meshInfo.data = meshDataArray;
    mesh->reset(meshInfo);
    mesh->initialize();
}

} // namespace

void SimpleDemo::testMeshAndMaterial() {
    Node *corsetNode = new Node("corset");
    corsetNode->setParent(_scene);
    // create mesh from deserializer
    Mesh *meshExportedFromEditor = new Mesh();
    setMeshFromJson(meshExportedFromEditor, "29805fb3-2189-4731-b788-b6b74617a960@d9c96.json", "29805fb3-2189-4731-b788-b6b74617a960@d9c96.bin");
    corsetNode->setScale(100, 100, 100);

    // create mesh renderer
    auto *corsetMeshRenderer = new MeshRenderer();
    corsetMeshRenderer       = corsetNode->addComponent<MeshRenderer>();
    corsetMeshRenderer->setMesh(meshExportedFromEditor);

    // create material from deserializer
    auto *corsetMaterial = new Material();

    setMaterialFromJsonContent(corsetMaterial, "f5345262-68e8-4676-b142-543e3ff75c17@ddb15.json", "standard");

    createTextureForMaterial("f5345262-68e8-4676-b142-543e3ff75c17@3effa.json", corsetMaterial, "mainTexture");
    createTextureForMaterial("f5345262-68e8-4676-b142-543e3ff75c17@221a5.json", corsetMaterial, "metallicRoughnessMap");
    createTextureForMaterial("f5345262-68e8-4676-b142-543e3ff75c17@0089c.json", corsetMaterial, "normalMap");
    createTextureForMaterial("f5345262-68e8-4676-b142-543e3ff75c17@221a5.json", corsetMaterial, "occlusionMap");

    corsetMeshRenderer->setMaterial(corsetMaterial);
}

void SimpleDemo::setup(int width, int height, uintptr_t windowHandle) {
    CC_LOG_INFO("SimpleDemo::%s, width: %d, height: %d", __FUNCTION__, width, height);

    // Initialize Device
    BindingMappingInfo bindingMappingInfo;
    bindingMappingInfo.bufferOffsets  = std::vector<int>{0, pipeline::globalUBOCount + pipeline::localUBOCount, pipeline::globalUBOCount};
    bindingMappingInfo.samplerOffsets = std::vector<int>{-pipeline::globalUBOCount, pipeline::globalSamplerCount + pipeline::localSamplerCount, pipeline::globalSamplerCount - pipeline::localUBOCount};
    bindingMappingInfo.flexibleSet    = 1;

    int pixelWidth  = width * 2;
    int pixelHeight = height * 2;

    DeviceInfo info;
    info.windowHandle       = windowHandle;
    info.width              = pixelWidth;
    info.height             = pixelHeight;
    info.pixelRatio         = 2;
    info.bindingMappingInfo = bindingMappingInfo;
    _device                 = DeviceManager::create(info);

    // Initialize director
    _director = new Director();
    _director->init();
    _director->getRoot()->resize(pixelWidth, pixelHeight);
    _director->getRoot()->setRenderPipeline(nullptr);

    BuiltinResMgr::getInstance()->initBuiltinRes(_device);

    BuiltinResMgr::getInstance()->tryCompileAllPasses();

    // Scene
    _scene = new Scene("myscene");

    //////////// Cube Node
    // add a node to scene
    _cubeNode = new Node("cube");
    // _cubeNode->setPosition(Vec3(10, 0, 10));
    _cubeNode->setParent(_scene);
    // _cubeNode->setPosition(-3.6, 0.5, -2.F);
    // _cubeMeshRenderer = _cubeNode->addComponent<MeshRenderer>();

    // create camera
    auto *cameraNode = new Node("camera");
    cameraNode->setParent(_scene);
    cameraNode->setPosition(-10, 10, -10);
    cameraNode->setEulerAngles(Vec3{-35, -135, 0});

    auto *cameraComp = cameraNode->addComponent<Camera>();
    cameraComp->setProjection(Camera::ProjectionType::PERSPECTIVE);
    cameraComp->setPriority(0);
    cameraComp->setFov(45);
    cameraComp->setFovAxis(Camera::FOVAxis::VERTICAL);
    cameraComp->setOrthoHeight(10);
    cameraComp->setNear(1);
    cameraComp->setFar(1000);
    cameraComp->setClearColor(cc::Color{51, 51, 51, 255});
    cameraComp->setClearDepth(1);
    cameraComp->setClearStencil(0);
    cameraComp->setClearFlags(Camera::ClearFlag::SOLID_COLOR);
    cameraComp->setRect(cc::Rect(0, 0, 1, 1));
    cameraComp->setAperture(Camera::Aperture::F16_0);
    cameraComp->setShutter(Camera::Shutter::D125);
    cameraComp->setIso(Camera::ISO::ISO100);
    cameraComp->setScreenScale(1.0f);
    cameraComp->setVisibility(static_cast<uint32_t>(Layers::LayerList::IGNORE_RAYCAST | Layers::LayerList::UI_3D | Layers::LayerList::DEFAULT));

    // Main Light
    auto *lightNode = new Node("MainLight");
    lightNode->setPosition(-10, 15, 17.5);
    lightNode->setRotationFromEuler(-35, -30, 0); // DirectionalLight
    lightNode->setParent(_scene);
    auto *lightComp = lightNode->addComponent<DirectionalLight>();

    // Sphere Light
    // auto *sphereLightNode = new Node("SphereLight");
    // sphereLightNode->setPosition(3.3, 1.8, -2.7);
    // sphereLightNode->setParent(_scene);
    // auto *sphereLightComp = sphereLightNode->addComponent<SphereLight>();
    // sphereLightComp->setTerm(PhotometricTerm::LUMINOUS_FLUX);
    // sphereLightComp->setColor(cc::Color{0, 255, 255, 255});
    // sphereLightComp->setLuminousFlux(1700);
    // sphereLightComp->setSize(0.15);
    // sphereLightComp->setRange(2);

    // testMeshAndMaterial();
    // testShadow();
    testTerrain();

    _director->runSceneImmediate(_scene, nullptr, nullptr);
}

void SimpleDemo::testShadow() {
    Node *cubeNode = new Node("cube");
    cubeNode->setParent(_scene);
    cubeNode->setPosition(-3.6, 0.5, -2.F);
    auto *cubeMeshRenderer = cubeNode->addComponent<MeshRenderer>();
    // create mesh asset
    auto *cube = new Primitive(PrimitiveType::BOX);
    cube->onLoaded();

    cubeMeshRenderer->setShadowCastingMode(ModelShadowCastingMode::ON);
    cubeMeshRenderer->setReceiveShadow(ModelShadowReceivingMode::ON);
    cubeMeshRenderer->setMesh(cube);
    // set material
    auto *defaultMaterial = new Material();
    setMaterialFromJsonContent(defaultMaterial, "d3c7820c-2a98-4429-8bc7-b8453bc9ac41.json", "standard");
    cubeMeshRenderer->setMaterial(defaultMaterial);

    // //////////  Torus Node
    Node *torusNode = new Node("torus");
    torusNode->setParent(_scene);
    torusNode->setPosition(0.75, 0.6, -3);
    auto *torusMeshRenderer = torusNode->addComponent<MeshRenderer>();
    auto *torus             = new Primitive(PrimitiveType::TORUS);
    torus->onLoaded();
    torusMeshRenderer->setShadowCastingMode(ModelShadowCastingMode::ON);
    torusMeshRenderer->setReceiveShadow(ModelShadowReceivingMode::ON);
    torusMeshRenderer->setMesh(torus);
    torusMeshRenderer->setMaterial(defaultMaterial);

    // //////////// Plane Node
    // // plane node
    Node *planeNode = new Node("plane");
    planeNode->setParent(_scene);
    // create mesh renderer
    auto *planeMeshRenderer = planeNode->addComponent<MeshRenderer>();
    auto *plane             = new Primitive(PrimitiveType::PLANE);
    plane->onLoaded();
    planeMeshRenderer->setMesh(plane);
    planeMeshRenderer->setMaterial(defaultMaterial);
    planeMeshRenderer->setShadowCastingMode(ModelShadowCastingMode::OFF);
    planeMeshRenderer->setReceiveShadow(ModelShadowReceivingMode::ON);

    auto *shadowInfo = _scene->getSceneGlobal()->getShadowInfo();
    shadowInfo->setEnabled(true);
    // shadowInfo->setType(cc::scene::ShadowType::PLANAR);
    shadowInfo->setType(cc::scene::ShadowType::SHADOW_MAP);
}

void SimpleDemo::testTerrain() {
    // deserialize terrain asset
    auto fileUtils        = FileUtils::getInstance();
    auto terrainAssetJson = fileUtils->getStringFromFile("bb4eed63-fb14-4bf8-a8f3-7c9b271a9f18.json");
    CC_ASSERT(!terrainAssetJson.empty());

    rapidjson::Document doc;
    doc.Parse(terrainAssetJson.c_str());
    auto  deserializer = AssetDeserializerFactory::createAssetDeserializer(DeserializeAssetType::TERRAIN);
    auto *asset        = new TerrainAsset();
    deserializer->deserialize(doc, asset);

    auto             terrainAssetBin   = fileUtils->getDataFromFile("bb4eed63-fb14-4bf8-a8f3-7c9b271a9f18.bin");
    ArrayBuffer::Ptr terrainBinaryData = std::make_shared<ArrayBuffer>(terrainAssetBin.getBytes(), terrainAssetBin.getSize());
    asset->setNativeAsset(terrainBinaryData);
    asset->onLoaded();

    // Create terrain component
    auto *node    = new Node();
    auto *terrain = node->addComponent<Terrain>();
    terrain->setAsset(asset);
    node->setParent(_scene);
}

void SimpleDemo::step(float dt) {
    //    dt = 1.F / 60.F;
    //     CC_LOG_INFO("SimpleDemo::%s, dt: %.06f", __FUNCTION__, dt);
    //    _cubeNode->setAngle(_cubeNode->getAngle() + 10 * dt);
    auto euler = _cubeNode->getEulerAngles();
    euler.y += dt * 1000;
    _cubeNode->setEulerAngles(euler);

    _director->tick(dt);
}

void SimpleDemo::finalize() {
    CC_LOG_INFO("SimpleDemo::%s", __FUNCTION__);
    CC_SAFE_DELETE(_cubeMeshRenderer);
    CC_SAFE_DELETE(_scene);
    CC_SAFE_DELETE(_director);
    DeviceManager::destroy();
}
