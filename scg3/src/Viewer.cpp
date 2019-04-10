/**
 * \file Viewer.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014-2019 Volker Ahlers
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Animation.h"
#include "Camera.h"
#include "Controller.h"
#include "Group.h"
#include "KeyboardController.h"
#include "Light.h"
#include "MouseController.h"
#include "Node.h"
#include "PerspectiveCamera.h"
#include "Renderer.h"
#include "ShaderCore.h"
#include "ShaderCoreFactory.h"
#include "StandardRenderer.h"
#include "scg_glm.h"
#include "scg_utilities.h"
#include "Viewer.h"
#include "ViewState.h"

namespace scg {


Viewer::Viewer()
    : window_(nullptr), viewState_(new ViewState) {
  if (isInstantiated_) {
    throw std::runtime_error("Cannot instantiate more than one Viewer [Viewer::Viewer()]");
  }
  isInstantiated_ = true;
}


Viewer::~Viewer() {
  glfwTerminate();
  glfwSetErrorCallback(nullptr);
}


ViewerSP Viewer::create() {
  return  std::make_shared<Viewer>();
}


Viewer* Viewer::setOpenGLConfig(const OGLConfig& oglConfig) {
  oglConfig_ = oglConfig;
  return this;
}


Viewer* Viewer::init(RendererSP renderer) {
  assert(renderer);
  renderer_ = renderer;

  // initialize GLFW
  glfwSetErrorCallback(errorCB_);
  int retCode = glfwInit();
  if (retCode == GL_FALSE) {
    throw std::runtime_error("glfwInit() failed [Viewer::init()]");
  }

  // set OpenGL configuration
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, oglConfig_.versionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, oglConfig_.versionMinor);
  oglVersion_ = 100 * oglConfig_.versionMajor + oglConfig_.versionMinor;
  if (oglVersion_ >= 300) {   // OpenGL 3.0 or higher
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, oglConfig_.forwardCompatible);
  }
  if (oglVersion_ >= 302) {   // OpenGL 3.2 or higher
    glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(oglConfig_.profile));
  }

  // initialize OpenGL parameters specific for render strategy
  renderer_->initViewer(this, &frameBufferSize_);
  frameBufferClearMask_ = GL_COLOR_BUFFER_BIT;
  if (frameBufferSize_.depthbits > 0) {
    frameBufferClearMask_ |= GL_DEPTH_BUFFER_BIT;
  }
  if (frameBufferSize_.stencilbits > 0) {
    frameBufferClearMask_ |= GL_STENCIL_BUFFER_BIT;
  }

  // Note: checkGLError() is not called here, since OpenGL context does not yet exist.

  return this;
}


Viewer* Viewer::initSimpleRenderer(CameraSP& camera, GroupSP& scene) {

  // create renderer
  auto renderer = StandardRenderer::create();
  this->init(renderer)
      ->createWindow("s c g 3", 1024, 768);

  // create camera and controllers
  camera = PerspectiveCamera::create();
  renderer->setCamera(camera);
  this->addController(KeyboardController::create(camera))
      ->addController(MouseController::create(camera));

  // create Gouraud shader and scene
  ShaderCoreFactory shaderFactory;
  auto shaderGouraud = shaderFactory.createGouraudShader();
  scene = Group::create();
  scene->addCore(shaderGouraud);
  scene->addChild(camera);
  renderer->setScene(scene);

  return this;
}


Viewer* Viewer::initSimpleRenderer(CameraSP& camera, GroupSP& scene, LightSP& light) {

  initSimpleRenderer(camera, scene);

  // white directed light from direction (1, 1, 1)
  light = Light::create();
  light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
      ->setPosition(glm::vec4(1.f, 1.f, 1.f, 0.f))
      ->init();
  scene->addChild(light);

  return this;
}


Viewer* Viewer::addController(ControllerSP controller) {
  assert(controller);
  controllers_.push_back(controller);

  return this;
}


Viewer* Viewer::addControllers(const std::vector<ControllerSP>& controllers) {
  for (auto controller : controllers) {
    addController(controller);
  }
  return this;
}


Viewer* Viewer::addControllers(std::vector<ControllerSP>&& controllers) {
  std::vector<ControllerSP> controllersVec = std::move(controllers);
  addControllers(controllersVec);
  return this;
}


Viewer* Viewer::addAnimation(AnimationSP animation) {
  assert(animation);
  animations_.push_back(animation);
  return this;
}


Viewer* Viewer::addAnimations(const std::vector<AnimationSP>& animations) {
  for (auto animation : animations) {
    addAnimation(animation);
  }
  return this;
}


Viewer* Viewer::addAnimations(std::vector<AnimationSP>&& animations) {
  std::vector<AnimationSP> animationsVec = std::move(animations);
  addAnimations(animationsVec);
  return this;
}


Viewer* Viewer::startAnimations() {
  double currTime = glfwGetTime();

  for (auto animation : animations_) {
    animation->start(currTime);
  }
  return this;
}


void Viewer::getWindowSize(int& width, int& height) const {
  glfwGetWindowSize(window_, &width, &height);
}


Viewer* Viewer::setWindowSize(int width, int height) {
  glfwSetWindowSize(window_, width, height);
  return this;
}



bool Viewer::isWindowResized() {
  bool result = isWindowResized_;
  isWindowResized_ = false;
  return result;
}


Viewer* Viewer::setWindowTitle(const char* title) {
  glfwSetWindowTitle(window_, title);
  return this;
}


Viewer* Viewer::createWindow(const char* title, int width, int height) {
  createWindow_(title, width, height, false);
  return this;
}


Viewer* Viewer::createFullscreenWindow(const char* title) {
  viewState_->setMouseCursorVisible(false);
  const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  createWindow_(title, videoMode->width, videoMode->height, true);
  return this;
}


void Viewer::startMainLoop() {
  if (!renderer_) {
    throw std::runtime_error("Undefined renderer, call Viewer::init() first [Viewer::render()]");
  }
  if (!window_) {
    throw std::runtime_error("No open window, call Viewer::createWindow() first [Viewer::render()]");
  }

  std::cout << renderer_->getInfo() << std::endl;

  // main loop
  while (!glfwWindowShouldClose(window_)) {

    // check controllers for input and update animations
    processControllers_();
    processAnimations_();

    // let renderer display scene
    glClear(frameBufferClearMask_);
    renderer_->render();
    glfwSwapBuffers(window_);

    // update frame rate
    viewState_->updateFrameRate();

    // poll events, e.g., Alt-F4
    glfwPollEvents();

    assert(!checkGLError());
  }
}


void Viewer::createWindow_(const char* title, int width, int height, bool fullscreenMode) {
  if (!renderer_) {
    throw std::runtime_error("Undefined renderer, call Viewer::init() first [Viewer::createWindow_()]");
  }

  // open window and create OpenGL context
  GLFWmonitor* monitorPtr = fullscreenMode ? glfwGetPrimaryMonitor() : nullptr;
  window_ = glfwCreateWindow(width, height, title, monitorPtr, nullptr);
  if (!window_) {
    throw std::runtime_error("glfwCreateWindow() failed [Viewer::createWindow_()]");
  }
  glfwMakeContextCurrent(window_);
  viewState_->setWindow(window_);
  isWindowResized_ = true;    // trigger update of camera projection

  // synchronize frame rate with vertical display frequency
  glfwSwapInterval(1);

  // register callback functions
  glfwSetFramebufferSizeCallback(window_, framebufferSizeCB_);

  // initialize GLEW
  GLenum error = glewInit();
  if (error != GLEW_OK) {
    throw std::runtime_error(std::string("glewInit() failed: ") + (const char*) glewGetErrorString(error)
        + " [Viewer::createWindow_()]");
  }
  glGetError();   // ignore GL error (invalid enum) in glewInit

  // set OpenGL parameters
  glEnable(GL_DEPTH_TEST);
  glClearColor(oglConfig_.clearColor[0], oglConfig_.clearColor[1], oglConfig_.clearColor[2],
      oglConfig_.clearColor[3]);

  // print version information
  std::cout << "s c g 3" << std::endl
       << "-------" << std::endl;
  std::cout << "GL version: " << (const char*) glGetString(GL_VERSION) << std::endl;
  std::cout << "GL vendor: " << (const char*) glGetString(GL_VENDOR) << std::endl;
  std::cout << "GL renderer: " << (const char*) glGetString(GL_RENDERER) << std::endl;
  std::cout << "GLSL version: " << (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
  int major, minor, revision;
  glfwGetVersion(&major, &minor, &revision);
  std::cout << "GLFW version: " << major << "." << minor << "." << revision << std::endl;
  std::cout << "GLM version: " << GLM_VERSION_MAJOR << "." << GLM_VERSION_MINOR << "."
      << GLM_VERSION_PATCH << "." << GLM_VERSION_REVISION << std::endl << std::endl;

  // inititalize renderer
  renderer_->initRenderState();

  assert(!checkGLError());
}


void Viewer::processControllers_() {
  for (auto controller : controllers_) {
    controller->checkInput(viewState_.get());
  }
}


void Viewer::processAnimations_() {
  if (!(animations_.empty() || viewState_->isAnimationLocked())) {
    double currTime = glfwGetTime();

    for (auto animation : animations_) {
      animation->update(currTime);
    }
  }
}


void Viewer::errorCB_(int error, const char* description) {
  std::cerr << std::endl << "GLFW error: " << description << std::endl;
}


void Viewer::framebufferSizeCB_(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  isWindowResized_ = true;

  assert(!checkGLError());
}


bool Viewer::isInstantiated_(false);
bool Viewer::isWindowResized_(false);


} /* namespace scg */
