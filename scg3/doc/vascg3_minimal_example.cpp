// scg3 minimal example application

#include <scg3.h>

using namespace scg;

int main() {

  // create viewer with default renderer, camera, and light
  auto viewer = Viewer::create();
  CameraSP camera;
  GroupSP scene;
  LightSP light;
  viewer->initSimpleRenderer(camera, scene, light);

  // define red material
  auto matRed = MaterialCore::create();
  matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  // add teapot shape to scene graph
  GeometryCoreFactory geometryFactory;
  auto teapot = Shape::create();
  teapot->addCore(matRed)
        ->addCore(geometryFactory.createTeapot(1.f));
  light->addChild(teapot);

  // move camera backwards, enter main loop
  camera->translate(glm::vec3(0.f, 0.f, 1.f))
        ->dolly(-1.f);
  viewer->startMainLoop();

  return 0;
}
