/**
 * \file Scg3Test.cpp
 * \brief A simple scg3 test application.
 *
 * Requires C++11 and OpenGL 3.2 (or later versions).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include "PickController.h"
#include "RenderToTexture2DCore.h"
#include "RenderToTextureRenderer.h"
#include "SpaceMouseController.h"
#include "Scg3Demo.h"

using namespace scg;


struct SCGConfiguration {
  static const int sceneType = 3;           // 0: RGB cubes, 1: single shape, 2: multiple shapes, 3: table, 4: test
  // for all scenes:
  static const int stereoMode = 0;          // 0: no, 1: anaglyph, 2: active, 3: passive stereo
  static const bool useOGLConfig = false;
  static const bool useFullscreen = false;
  static const int colorTransformType = 0;  // 0: identity, 1: grayscale, 2: black
  // for single shape scene:
  static const int shapeType = 1;           // 0: sphere, 1: teapot, 2: OBJ model
  static const int shaderType = 3;          // 0: flat, 1: Gouraud, 2: Phong, 3: Gouraud with clipping
  static const std::string modelFileName;   // defined below
  // for multiple shapes scene:
  static const int textureType = 2;         // 0: no texture, 1: wood texture , 2: noise bump map, 3: brick texture bump map
  // for table scene:
  static const bool useBumpMapWall = true;
  static const bool useSkybox = true;
  static const bool useCubeMap = true;
  static const bool usePicking = false;
  static const bool useRenderToTexture = true;
  static const bool useSpaceMouse = false;
  static const std::string spaceMouseDevice;  // defined below
};

const std::string SCGConfiguration::modelFileName = "cessna.obj";
const std::string SCGConfiguration::spaceMouseDevice = "navigator@localhost";


Scg3Demo::Scg3Demo() {
}


Scg3Demo::~Scg3Demo() {
}


void Scg3Demo::run() {
  // create viewer and renderer
  auto viewer = Viewer::create();
  RendererSP renderer;
  if (SCGConfiguration::useRenderToTexture) {
    renderer = RenderToTextureRenderer::create();
  }
  else {
    renderer = StandardRenderer::create();
  }
  StereoRendererSP stereoRenderer;
  switch (SCGConfiguration::stereoMode) {
  case 0:
    // no stereo
    break;
  case 1:
    // anaglyph stereo
    stereoRenderer = StereoRendererAnaglyph::create(renderer);
    break;
  case 2:
    // active stereo, e.g., shutter glasses
    stereoRenderer = StereoRendererActive::create(renderer);
    break;
  case 3:
    // passive stereo, e.g., polarized projection
    stereoRenderer = StereoRendererPassive::create(renderer);
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::stereoMode [Scg3Test::run()]");
  }

  if (SCGConfiguration::useOGLConfig) {
    // set OpenGL configuration, override default parameters
    viewer->setOpenGLConfig(OGLConfig(4, 3, GL_FALSE, OGLProfile::CORE, glm::vec4(0.5f, 0.5f, 0.5f, 1.f)));
  }

  if (stereoRenderer) {
    viewer->init(stereoRenderer);
  }
  else {
    viewer->init(renderer);
  }

  if (SCGConfiguration::useFullscreen) {
    viewer->createFullscreenWindow("s c g 3   d e m o");
  }
  else {
    viewer->createWindow("s c g 3   d e m o", 1450, 1050);
  }

  // create camera
  CameraSP camera;
  if (stereoRenderer) {
    auto stereoCamera = StereoCamera::create();
    stereoCamera->initBourke(60.f, 0.01f, 1000.f, 1.5f, 0.02f);
    camera = stereoCamera;
  }
  else {
    camera = PerspectiveCamera::create();
  }
  renderer->setCamera(camera);

  // create scene
  GroupSP scene;
  switch (SCGConfiguration::sceneType) {
  case 0:
    // RGB scene without lighting
    createRGBScene_(viewer, camera, scene);
    break;
  case 1:
    // single shape with lighting
    createLightedShape_(viewer, camera, scene);
    break;
  case 2:
    // multiple shapes with lighting
    createLightedScene_(viewer, camera, scene);
    break;
  case 3:
    // table and teapot with lighting
    createTableScene_(viewer, camera, scene);
    break;
  case 4:
    // general test scene
    createTestScene_(viewer, camera, scene);
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::sceneType [Scg3Test::run()]");
  }
  renderer->setScene(scene);

  // start animations, enter main loop
  viewer->startAnimations()
        ->startMainLoop();
}


void Scg3Demo::createRGBScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene) {
  // color shader
  ShaderCoreFactory shaderFactory;
  auto shaderCore = shaderFactory.createColorShader();

  // camera controllers
  camera->translate(glm::vec3(0.f, 0.f, 1.f))
        ->dolly(-2.f);
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });

  // random number generator, using Mersenne Twister seeded with current time
  std::mt19937 randEngine(static_cast<std::mt19937::result_type>(std::time(nullptr)));
  auto random = std::bind(std::uniform_real_distribution<float>(0.0f, 1.0f), randEngine);

  // RGB cube shape group
  auto cubes = Group::create();

  GeometryCoreFactory geometryFactory;
  auto cubeCore = geometryFactory.createRGBCube(1.0f);

  const int nCubes = 10;
  for (int i = 0; i < nCubes; ++i) {
    auto cube = Shape::create(cubeCore);

    float scaling = random();
    auto cubeTrans = Transformation::create();
    cubeTrans->translate(glm::vec3(random(), random(), random()) * 2.f - glm::vec3(1.f, 1.f, 1.f))
             ->rotate(360.0f * random(),
                 glm::normalize(glm::vec3(random(), random(), random()) * 2.f - glm::vec3(1.f, 1.f, 1.f)))
             ->scale(glm::vec3(scaling, scaling, scaling));

    auto cubeAnim = TransformAnimation::create();
    float angularVel = 100.0f * random();
    cubeAnim->setUpdateFunc(
        [angularVel](TransformAnimation* anim, double currTime, double diffTime, double totalTime) {
          anim->rotate(angularVel * static_cast<GLfloat>(diffTime), glm::vec3(1.0f, 0.0f, 0.0f));
        });
    viewer->addAnimation(cubeAnim);

    cubes->addChild(cubeTrans);
    cubeTrans->addChild(cubeAnim);
    cubeAnim->addChild(cube);
  }

  // create scene graph
  scene = Group::create();
  scene->addCore(shaderCore);
  scene->addChild(camera)
       ->addChild(cubes);
}


void Scg3Demo::createLightedShape_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene) {
  // flat shader
  ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders;shaders;../shaders");
  auto shaderFlat = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("simple_flat_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("simple_flat_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // Gouraud shader
  auto shaderGouraud = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("simple_gouraud_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("simple_gouraud_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // Phong shader
  auto shaderPhong = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Gouraud shader with clipping
  auto shaderGouraudClipping = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("simple_gouraud_clipping_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("simple_gouraud_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // camera controllers
  camera->translate(glm::vec3(0.f, 0.f, 1.f))
        ->dolly(-1.f);
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });

  // lights
  auto light = Light::create();
  light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
       ->setPosition(glm::vec4(10.f, 10.f, 10.f, 1.f))
       ->init();

  // materials
  auto matRed = MaterialCore::create();
  matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  // colors
  auto color = ColorCore::create();
  switch (SCGConfiguration::colorTransformType) {
  case 0:
    // do nothing, use default identity matrix
    break;
  case 1:
    // grayscale color transformation
    color->setMatrix(glm::transpose(glm::mat4(
        0.3f, 0.6f, 0.1f, 0.f,
        0.3f, 0.6f, 0.1f, 0.f,
        0.3f, 0.6f, 0.1f, 0.f,
        0.f,  0.f,  0.f,  1.f )));
    break;
  case 2:
    // black color transformation
    color->setMatrix(glm::transpose(glm::mat4(
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 1.f )));
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::colorTransformType [Scg3Test::createLightedShape_()]");
  }

  // shape and transformation
  GeometryCoreFactory geometryFactory("../scg3/models;../../scg3/models");
  auto shape = Shape::create();
  shape->addCore(matRed);
  auto shapeTrans = Transformation::create();
  switch (SCGConfiguration::shapeType) {
  case 0:
    shape->addCore(geometryFactory.createSphere(0.5f, 20, 10));
    break;
  case 1:
    if (SCGConfiguration::shaderType == 0) {
      shape->addCore(geometryFactory.createTeapotFlat(1.f));
    }
    else {
      shape->addCore(geometryFactory.createTeapot(1.f));
    }
    shapeTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
    break;
  case 2:
    shape->addCore(geometryFactory.createModelFromOBJFile(SCGConfiguration::modelFileName));
    shapeTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f))
        ->scale(glm::vec3(0.05f, 0.05f, 0.05f));
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::shapeType [Scg3Test::createLightedShape_()]");
  }

  // create scene graph
  scene = Group::create();
  switch (SCGConfiguration::shaderType) {
  case 0:
    scene->addCore(shaderFlat);
    break;
  case 1:
    scene->addCore(shaderGouraud);
    break;
  case 2:
    scene->addCore(shaderPhong);
    break;
  case 3:
    scene->addCore(shaderGouraudClipping);
    glEnable(GL_CLIP_DISTANCE0);
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::shaderType [Scg3Test::createLightedShape_()]");
  }
  scene->addCore(color);
  scene->addChild(camera)
       ->addChild(light);
  light->addChild(shapeTrans);
  shapeTrans->addChild(shape);
}


void Scg3Demo::createLightedScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene) {

  // Phong shader
  ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders");
  auto shaderPhong = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Phong shader with 2D texture modulation
  auto shaderPhongTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
      });

  // Bump map shader
  auto shaderBump = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("bump_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("bump_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Bump map shader with 2D texture modulation
  auto shaderBumpTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("bump_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("bump_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
      });

  // camera controllers
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });

  // lights
  auto light = Light::create();
  light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
       ->setPosition(glm::vec4(10.f, 10.f, 10.f, 1.f))
       ->init();

  auto headLight = Light::create();
  headLight->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 0.3f, 1.f))
           ->setPosition(glm::vec4(0.f, 1.f, 0.f, 1.f))
           ->setSpot(glm::vec3(0.f, -0.5f, -1.f), 10.f, 20.f)
           ->init();
  auto headLightPos = LightPosition::create(headLight);

  // materials
  auto matBlue = MaterialCore::create();
  matBlue->setAmbientAndDiffuse(glm::vec4(0.9f, 0.9f, 1.0f, 1.0f))
         ->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
         ->setShininess(20.0f)
         ->init();

  auto matRed = MaterialCore::create();
  matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  // textures
  TextureCoreFactory textureFactory("../scg3/textures;../../scg3/textures");

  auto texWood = textureFactory.create2DTextureFromFile("wood_256.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

  auto bumpBrick = textureFactory.createBumpMapFromFiles("brick_texture.png", "brick_normal.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

  auto bumpNoise = textureFactory.createBumpMapFromFiles("", "noise_normal.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

  // colors
  auto color = ColorCore::create();
  switch (SCGConfiguration::colorTransformType) {
  case 0:
    // do nothing, use default identity matrix
    break;
  case 1:
    // grayscale color transformation
    color->setMatrix(glm::transpose(glm::mat4(
        0.3f, 0.6f, 0.1f, 0.f,
        0.3f, 0.6f, 0.1f, 0.f,
        0.3f, 0.6f, 0.1f, 0.f,
        0.f,  0.f,  0.f,  1.f )));
    break;
  case 2:
    // black color transformation
    color->setMatrix(glm::transpose(glm::mat4(
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 1.f )));
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::colorTransformType [Scg3Test::createLightedScene_()]");
  }

  // floor shape and transformation
  GeometryCoreFactory geometryFactory;
  auto floor = Shape::create();
  floor->addCore(matBlue)
       ->addCore(geometryFactory.createCuboid(glm::vec3(100.f, 0.1f, 100.f)));

  auto floorTrans = Transformation::create();
  floorTrans->translate(glm::vec3(0.f, -2.f, 0.f));

  // random number generator, using Mersenne twister seeded with current time
  std::mt19937 randEngine(static_cast<std::mt19937::result_type>(std::time(nullptr)));
  auto randomUniform = std::bind(std::uniform_real_distribution<float>(0.0f, 1.0f), randEngine);
  auto randomNormal = std::bind(std::normal_distribution<float>(0.f, 1.f), randEngine);

  // random shape groups (textured and non-textured)
  auto shapes = Group::create();
  auto texturedShapes = Group::create();
  switch (SCGConfiguration::textureType) {
  case 0:
    // do nothing, i.e., do not apply any texture
    break;
  case 1:
    // wood texture
    texturedShapes->addCore(shaderPhongTex)
                  ->addCore(texWood);
    break;
  case 2:
    // noise bump map
    texturedShapes->addCore(shaderBump)
                  ->addCore(bumpNoise);
    break;
  case 3:
    // brick bump map
    texturedShapes->addCore(shaderBumpTex)
                  ->addCore(bumpBrick);
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::textureType [Scg3Test::createLightedScene_()]");
  }

  auto cubeCore = geometryFactory.createCube(1.f);
  auto sphereCore = geometryFactory.createSphere(0.5f, 20, 10);
  auto coneCore = geometryFactory.createCone(0.25f, 1.f, 20, 10, true);
  auto cylinderCore = geometryFactory.createCylinder(0.25f, 1.f, 20, 10, true);
  auto teapotCore = geometryFactory.createTeapot(1.f);

  const int nShapes = 500;
  for (int i = 0; i < nShapes; ++i) {
    auto matCore = MaterialCore::create();
    matCore->setAmbientAndDiffuse(glm::vec4(randomUniform(), randomUniform(), randomUniform(), 1.0f))
           ->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
           ->setShininess(20.0f)
           ->init();

    auto shape = Shape::create();
    shape->addCore(matCore);

    float coreChoice = randomUniform();
    if (coreChoice <= 0.2f) {
      shape->addCore(cubeCore);
    }
    else if (coreChoice <= 0.4f) {
      shape->addCore(sphereCore);
    }
    else if (coreChoice <= 0.6f) {
      shape->addCore(coneCore);
    }
    else if (coreChoice <= 0.8f) {
      shape->addCore(cylinderCore);
    }
    else {
      shape->addCore(teapotCore);
    }

    float scaling = randomUniform();
    auto shapeTrans = Transformation::create();
    shapeTrans->translate(glm::vec3(randomNormal(), randomNormal(), randomNormal()) * 10.f)
              ->rotate(360.0f * randomUniform(),
                  glm::normalize(glm::vec3(randomUniform(), randomUniform(), randomUniform())))
              ->scale(glm::vec3(scaling, scaling, scaling));

    float angularVel = 100.0f * randomUniform();
    auto axis = glm::normalize(glm::vec3(randomUniform(), randomUniform(), randomUniform()));
    auto shapeAnim = TransformAnimation::create();
    shapeAnim->setUpdateFunc(
        [angularVel, axis](TransformAnimation* anim, double currTime, double diffTime, double totalTime) {
          anim->rotate(angularVel * static_cast<GLfloat>(diffTime), axis);
        });
    viewer->addAnimation(shapeAnim);

    // let shapes rotate around their center
    float textureChoice = randomUniform();
    if (textureChoice >= 0.5f) {
      shapes->addChild(shapeTrans);
    }
    else {
      texturedShapes->addChild(shapeTrans);
    }
    shapeTrans->addChild(shapeAnim);
    shapeAnim->addChild(shape);
  }

  // create scene graph
  scene = Group::create();
  scene->addCore(shaderPhong)
       ->addCore(color);
  scene->addChild(camera)
       ->addChild(headLight);
  camera->addChild(headLightPos);
  headLight->addChild(light);
  light->addChild(floorTrans)
       ->addChild(shapes)
       ->addChild(texturedShapes);
  floorTrans->addChild(floor);
}


void Scg3Demo::createTableScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene) {
  // Gouraud shader
  ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders;shaders;../shaders");
  auto shaderGouraud = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("gouraud_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("gouraud_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_VERTEX_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Gouraud shader with texture mapping
  auto shaderGouraudTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("gouraud_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("gouraud_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_VERTEX_SHADER),
        ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
      });

  // bump mapping shader
  auto shaderBump = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("bump_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("bump_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // bump mapping shader with texture mapping
  auto shaderBumpTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("bump_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("bump_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
      });

  // Toon shader
  auto shaderToon = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("toon_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Toon shader with texture mapping
  auto shaderToonTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("toon_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
      });

  // flatten shader
  auto shaderFlatten = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("flatten_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("color_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_VERTEX_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // thicken shader
  auto shaderThicken = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("thicken_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("color_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_VERTEX_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // breath shader
  auto shaderBreath = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("breath_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("color_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_VERTEX_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });
  shaderBreath->setUniform1f("angFreq", 3.14159f);

  // skybox shader
  auto shaderSkybox = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("skybox_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("skybox_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // cube map shader
  auto shaderCubeMap = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("cube_map_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("cube_map_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // color shader
  auto shaderColor = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("color_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("color_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // texture shader without lighting
  auto shaderTextureNoLighting = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("texture_no_lighting_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("texture_no_lighting_frag.glsl", GL_FRAGMENT_SHADER)
      });

  // camera controllers
  camera->translate(glm::vec3(0.f, 0.5f, 1.f))
        ->dolly(-1.f);
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });
  if (SCGConfiguration::useSpaceMouse) {
    viewer->addController(SpaceMouseController::create(camera, SCGConfiguration::spaceMouseDevice));
  }

  // lights
  auto light = Light::create();
  light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
       ->setPosition(glm::vec4(10.f, 10.f, 10.f, 1.f))
       ->init();

  // materials
  auto matRed = MaterialCore::create();
  matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  auto matGreen = MaterialCore::create();
  matGreen->setAmbientAndDiffuse(glm::vec4(0.1f, 0.8f, 0.3f, 1.f))
          ->init();

  auto matWhite = MaterialCore::create();
  matWhite->setAmbientAndDiffuse(glm::vec4(1.f, 1.f, 1.f, 1.f))
 //         ->setSpecular(glm::vec4(0.5f, 0.5f, 0.5f, 1.f))
 //         ->setShininess(20.f)
          ->init();

  auto matGray = MaterialCore::create();
  matGray->setAmbientAndDiffuse(glm::vec4(0.5f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  // textures
  TextureCoreFactory textureFactory("../scg3/textures;../../scg3/textures;textures;../textures");

  auto texWood = textureFactory.create2DTextureFromFile("wood_256.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

  auto texBrick = textureFactory.create2DTextureFromFile("brick_texture.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  texBrick->scale(glm::vec3(3.f, 1.5f, 1.f));

  auto bumpBrick = textureFactory.createBumpMapFromFiles("brick_texture.png", "brick_normal.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  bumpBrick->scale(glm::vec3(3.f, 1.5f, 1.f));

  auto bumpNoise = textureFactory.createBumpMapFromFiles("", "noise_normal.png",
      GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  bumpNoise->scale(glm::vec3(6.f, 3.f, 1.f));

  auto cubeSkybox = textureFactory.createCubeMapFromFiles(
      {
        "skybox_xpos.png", "skybox_xneg.png",
        "skybox_ypos.png", "skybox_yneg.png",
        "skybox_zpos.png", "skybox_zneg.png"
      });

  auto texRenderToTexture = RenderToTexture2DCore::create();

  // colors
  auto color = ColorCore::create();
  switch (SCGConfiguration::colorTransformType) {
  case 0:
    // do nothing, use default identity matrix
    break;
  case 1:
    // grayscale color transformation
    color->setMatrix(glm::transpose(glm::mat4(
        0.3f, 0.6f, 0.1f, 0.f,
        0.3f, 0.6f, 0.1f, 0.f,
        0.3f, 0.6f, 0.1f, 0.f,
        0.f,  0.f,  0.f,  1.f )));
    break;
  case 2:
    // black color transformation
    color->setMatrix(glm::transpose(glm::mat4(
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 1.f )));
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::colorTransformType [Scg3Test::createLightedScene_()]");
  }

  // floor shape and transformation
  GeometryCoreFactory geometryFactory;
  auto floorCore = geometryFactory.createCuboid(glm::vec3(20.f, 0.05f, 10.f));
  auto floor = Shape::create();
  if (SCGConfiguration::useBumpMapWall) {
    floor->addCore(shaderBump)
         ->addCore(bumpNoise);
  }
  floor->addCore(matGreen)
       ->addCore(floorCore);
  auto floorTrans = Transformation::create();
  floorTrans->translate(glm::vec3(0.f, -0.5f, 0.f));

  // wall shape and transformation
  auto wallCore = geometryFactory.createCuboid(glm::vec3(20.f, 10.f, 0.05f));
  auto wall = Shape::create();
  if (SCGConfiguration::useBumpMapWall) {
    wall->addCore(shaderBumpTex)
        ->addCore(matWhite)
        ->addCore(bumpBrick)
        ->addCore(wallCore);
  }
  else {
    wall->addCore(shaderGouraudTex)
        ->addCore(matWhite)
        ->addCore(texBrick)
        ->addCore(wallCore);
  }
  auto wallTrans = Transformation::create();
  wallTrans->translate(glm::vec3(0.f, 4.5f, -5.f));

  // render to texture screen shape and transformation
  auto screenCore = geometryFactory.createRectangle(glm::vec2(6.f, 6.f));
  auto screen = Shape::create();
  screen->addCore(shaderTextureNoLighting)
      ->addCore(texRenderToTexture)
      ->addCore(screenCore);
  auto screenTrans = Transformation::create();
  screenTrans->translate(glm::vec3(4.f, 4.f, -4.f));

  // teapot shape and transformation
  auto teapotCore = geometryFactory.createTeapot(0.35f);
  auto teapot = Shape::create();
//  teapot->addCore(shaderFlatten);
//  teapot->addCore(shaderThicken);
//  teapot->addCore(shaderBreath);
  if (SCGConfiguration::useCubeMap) {
    teapot->addCore(shaderCubeMap)
          ->addCore(cubeSkybox);
  }
  teapot->addCore(matRed)
        ->addCore(teapotCore);
  auto teapotTrans = Transformation::create();
  teapotTrans->translate(glm::vec3(0.f, 0.9f, 0.f))
             ->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));

  // table group and transformation
  auto table = Group::create();
  table->addCore(shaderGouraudTex);
//  table->addCore(shaderToonTex);
//  table->addCore(shaderBreath);

  table->addCore(matWhite)
       ->addCore(texWood);
  auto tableTrans = Transformation::create();
  tableTrans->rotate(30.f, glm::vec3(0.f, 1.f, 0.f));

  auto tableTop = Shape::create(geometryFactory.createCuboid(glm::vec3(1.5f, 0.05f, 1.f)));
  auto tableTopTrans = Transformation::create();
  tableTopTrans->translate(glm::vec3(0.f, 0.5f, 0.f))
               ->addChild(tableTop);
  table->addChild(tableTopTrans);

  auto tableLegCore = geometryFactory.createCuboid(glm::vec3(0.1f, 1.f, 0.1f));
  ShapeSP tableLeg[4];
  TransformationSP tableLegTrans[4];
  for (int i = 0; i < 4; ++i) {
    tableLeg[i] = Shape::create(tableLegCore);
    tableLegTrans[i] = Transformation::create();
    table->addChild(tableLegTrans[i]);
    tableLegTrans[i]->addChild(tableLeg[i]);
  }
  tableLegTrans[0]->translate(glm::vec3( 0.6f, 0.f,  0.35f));
  tableLegTrans[1]->translate(glm::vec3( 0.6f, 0.f, -0.35f));
  tableLegTrans[2]->translate(glm::vec3(-0.6f, 0.f, -0.35f));
  tableLegTrans[3]->translate(glm::vec3(-0.6f, 0.f,  0.35f));

  // skybox
  auto skybox = Shape::create();
  if (SCGConfiguration::useSkybox) {
    auto skyboxCore = geometryFactory.createCube(50.f);
    skybox->addCore(shaderSkybox)
          ->addCore(cubeSkybox)
          ->addCore(skyboxCore);
  }

  // create scene graph
  scene = Group::create();
  scene->addCore(shaderGouraud)
//       scene->addCore(shaderToon)
//       ->addCore(shaderBreath)
       ->addCore(color);
  scene->addChild(camera)
       ->addChild(light);
  light->addChild(floorTrans)
       ->addChild(tableTrans)
       ->addChild(wallTrans);
  floorTrans->addChild(floor);
  tableTrans->addChild(table)
            ->addChild(teapotTrans);
  teapotTrans->addChild(teapot);
  wallTrans->addChild(wall);

  if (SCGConfiguration::useSkybox) {
    scene->addChild(skybox);
  }

  if (SCGConfiguration::usePicking) {
    auto pickController = PickController::create();
    viewer->addController(pickController);
    auto picker = Shape::create();
    auto pickerCore = geometryFactory.createSphere(0.0002f, 20, 10);
    picker->addCore(matRed)
          ->addCore(pickerCore);
    light->addChild(pickController);
    pickController->addChild(picker);
  }

  if (SCGConfiguration::useRenderToTexture) {
    light->addChild(screenTrans);
    screenTrans->addChild(screen);
  }
}


void Scg3Demo::createTestScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene) {
  // shader factory; define required shaders below
  ShaderCoreFactory shaderFactory;

  // camera controllers
  camera->translate(glm::vec3(0.f, 0.f, 1.f))
        ->dolly(-2.f);
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });

  // create scene graph; add shader core below
  scene = Group::create();
  scene->addChild(camera);

#if 1
  // test colored lines

  // color shader
  auto colorShader = shaderFactory.createColorShader();

  // red color core
  auto colorRed = ColorCore::create();
  colorRed->setColor(glm::vec4(1.f, 0.f, 0.f, 1.f));

  // lines geometry core
  auto linesCore = GeometryCore::create(GL_LINES, DrawMode::ARRAYS);    // or GL_LINE_STRIP
  const GLfloat vertices[] = {
      0.f, 0.f, 0.f,
      1.f, 0.f, 0.f,
      0.f, 1.f, 0.f,
      1.f, 1.f, 0.f
      // ...
  };
  linesCore->addAttributeData(OGLConstants::VERTEX.location, vertices,
      sizeof(vertices), 3, GL_STATIC_DRAW);

  // lines shape
  auto lines = Shape::create();
  lines->addCore(colorShader)
       ->addCore(colorRed)
       ->addCore(linesCore);

  scene->addChild(lines);
#endif

}
