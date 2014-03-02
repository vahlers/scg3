// scg3 table scene example application

#include <scg3.h>

using namespace scg;


void createScene(ViewerSP viewer, CameraSP camera, GroupSP& scene);


int main() {

  // create viewer and renderer
  auto viewer = Viewer::create();
  auto renderer = StandardRenderer::create();
  viewer->init(renderer)
        ->createWindow("s c g 3   e x a m p l e", 1024, 768);

  // create camera
  auto camera = PerspectiveCamera::create();
  renderer->setCamera(camera);

  // create scene
  GroupSP scene;
  createScene(viewer, camera, scene);
  renderer->setScene(scene);

  // move camera backwards, enter main loop
  camera->translate(glm::vec3(0.f, 0.5f, 1.f))
        ->dolly(-1.f);
  viewer->startMainLoop();

  return 0;
}


void createScene(ViewerSP viewer, CameraSP camera, GroupSP& scene) {

  ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders");

  // Phong shader
  auto shaderPhong = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Phong shader with texture mapping
  auto shaderPhongTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
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
          ->setSpecular(glm::vec4(0.5f, 0.5f, 0.5f, 1.f))
          ->setShininess(20.f)
          ->init();

  // textures
  TextureCoreFactory textureFactory("../scg3/textures;../../scg3/textures");
  auto texWood = textureFactory.create2DTextureFromFile(
      "wood_256.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

  // floor shape and transformation
  GeometryCoreFactory geometryFactory;
  auto floorCore = geometryFactory.createCuboid(glm::vec3(20.f, 0.05f, 10.f));
  auto floor = Shape::create();
  floor->addCore(matGreen)
       ->addCore(floorCore);
  auto floorTrans = Transformation::create();
  floorTrans->translate(glm::vec3(0.f, -0.5f, 0.f));

  // teapot shape and transformation
  auto teapotCore = geometryFactory.createTeapot(0.35f);
  auto teapot = Shape::create();
  teapot->addCore(matRed)
      ->addCore(teapotCore);
  auto teapotTrans = Transformation::create();
  teapotTrans->translate(glm::vec3(0.f, 0.9f, 0.f))
      ->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));

  // table group and transformation
  auto table = Group::create();
  table->addCore(shaderPhongTex)
       ->addCore(matWhite)
       ->addCore(texWood);
  auto tableTrans = Transformation::create();
  tableTrans->rotate(30.f, glm::vec3(0.f, 1.f, 0.f));

  auto tableTop = Shape::create(geometryFactory.createCuboid(glm::vec3(1.5f, 0.05f, 1.f)));
  auto tableTopTrans = Transformation::create();
  tableTopTrans->translate(glm::vec3(0.f, 0.5f, 0.f));
  table->addChild(tableTopTrans);
  tableTopTrans->addChild(tableTop);

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

  // create scene graph
  scene = Group::create();
  scene->addCore(shaderPhong);
  scene->addChild(camera)
       ->addChild(light);
  light->addChild(floorTrans)
       ->addChild(tableTrans);
  floorTrans->addChild(floor);
  tableTrans->addChild(table)
            ->addChild(teapotTrans);
  teapotTrans->addChild(teapot);
}
