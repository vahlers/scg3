/**
 * \file Viewer.h
 * \brief Central viewer managing window, controllers, animations, and main loop.
 *
 * Defines structs:
 *   OGLConfig
 *   FrameBufferSize
 *
 * Requires OpenGL 3.2 (or higher), GLEW (included in scg3), and GLFW 3.2.0 (or higher).
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

#ifndef VIEWER_H_
#define VIEWER_H_

#include <vector>
#include "scg_glew.h"
#include <GLFW/glfw3.h>
#include "scg_internals.h"

namespace scg {


/**
 * \brief Profile definitions for OGLConfig.
 */
enum class OGLProfile: int {
  NONE = 0,
  CORE = GLFW_OPENGL_CORE_PROFILE,
  COMPATIBILITY = GLFW_OPENGL_COMPAT_PROFILE
};


/**
 * \brief OpenGL configuration, may be set by user before calling Viewer::init().
 *
 * Default parameters:
 * - OpenGL 3.2
 * - forward-compatible context
 * - core profile
 * - bright gray background color
 */
struct OGLConfig {

  OGLConfig()
      : versionMajor(3), versionMinor(2), forwardCompatible(GL_TRUE), profile(OGLProfile::CORE),
        clearColor(glm::vec4(0.15f, 0.15f, 0.15f, 1.0f)) {
  }

  OGLConfig(int versionMajor0, int versionMinor0, GLboolean forwardCompatible0,
      OGLProfile profile0, glm::vec4 clearColor0)
      : versionMajor(versionMajor0), versionMinor(versionMinor0),
        forwardCompatible(forwardCompatible0), profile(profile0), clearColor(clearColor0) {
  }

  int versionMajor, versionMinor;
  GLboolean forwardCompatible;  // GL_TRUE requires OpenGL 3.0 or higher
  OGLProfile profile;        // CORE or COMPATIBILITY require OpenGL 3.2 or higher
  glm::vec4 clearColor;

};


/**
 * \brief Frame buffer size, to be set by renderer in Renderer::initViewer(), called by Viewer::init().
 *
 * Default parameters:
 * - RGBA channels: 8 bit each
 * - depth buffer: 24 bit
 * - stencil buffer: 8 bit
 */
struct FrameBufferSize {

  FrameBufferSize()
      : redbits(8), greenbits(8), bluebits(8), alphabits(8), depthbits(24), stencilbits(8) {
  }

  int redbits, greenbits, bluebits, alphabits;
  int depthbits;
  int stencilbits;

};


/**
 * \brief Central viewer managing window, controllers, animations, and main loop.
 *
 * A few static functions are required for GLFW callbacks.
 */
class Viewer {

public:

  /**
   * Constructor.
   */
  Viewer();

  /**
   * Destructor.
   */
  virtual ~Viewer();

  /**
   * Create shared pointer.
   */
  static ViewerSP create();

  /**
   * Initialize GLFW with given renderer.
   * \return this pointer for method chaining
   */
  Viewer* init(RendererSP renderer);

  /**
   * Initialize viewer with default renderer, Gouraud shader, perspective camera,
   * and empty scene (with child node camera).
   *
   * \param camera unallocated pointer
   * \param scene unallocated pointer
   * \return this pointer for method chaining
   */
  Viewer* initSimpleRenderer(CameraSP& camera, GroupSP& scene);

  /**
   * Initialize viewer with default renderer, Gouraud shader, perspective camera,
   * directed light, and empty scene (with child nodes camera and light).
   *
   * \param camera unallocated pointer
   * \param scene unallocated pointer
   * \param light unallocated pointer
   * \return this pointer for method chaining
   */
  Viewer* initSimpleRenderer(CameraSP& camera, GroupSP& scene, LightSP& light);

  /**
   * Set OpenGL configuration.
   * In order to take effect, this method has to be called before init().
   *
   * \return this pointer for method chaining
   */
  Viewer* setOpenGLConfig(const OGLConfig& oglConfig);

  /**
   * Add controller to be checked in main loop, e.g., a camera controller.
   * \return this pointer for method chaining
   */
  Viewer* addController(ControllerSP controller);

  /**
   * Add controllers to be checked in main loop, e.g., a camera controller.
   * \return this pointer for method chaining
   */
  Viewer* addControllers(const std::vector<ControllerSP>& controllers);

  /**
   * Add controllers to be checked in main loop, e.g., a camera controller.
   * \return this pointer for method chaining
   */
  Viewer* addControllers(std::vector<ControllerSP>&& controllers);

  /**
   * Add animation to be updated in main loop.
   * \return this pointer for method chaining
   */
  Viewer* addAnimation(AnimationSP animation);

  /**
   * Add animations to be updated in main loop.
   * \return this pointer for method chaining
   */
  Viewer* addAnimations(const std::vector<AnimationSP>& animations);

  /**
   * Add animations to be updated in main loop.
   * \return this pointer for method chaining
   */
  Viewer* addAnimations(std::vector<AnimationSP>&& animations);

  /**
   * Start all animations.
   * \return this pointer for method chaining
   */
  Viewer* startAnimations();

  /**
   * Get current window dimensions.
   */
  void getWindowSize(int& width, int& height) const;

  /**
   * Set window dimensions.
   * \return this pointer for method chaining
   */
  Viewer* setWindowSize(int width, int height);

  /**
   * Check if window has been resized since last call of this method.
   * The internal resize flag is cleared afterwards.
   */
  bool isWindowResized();

  /**
   * Set window title.
   * \return this pointer for method chaining
   */
  Viewer* setWindowTitle(const char* title);

  /**
   * Create OpenGL context, open window with given title and dimensions,
   * and initialize GLEW.
   * \return this pointer for method chaining
   */
  Viewer* createWindow(const char* title, int width, int height);

  /**
   * Create OpenGL context, open fullscreen window with given title,
   * hide mouse cursor, and initialize GLEW.
   * \return this pointer for method chaining
   */
  Viewer* createFullscreenWindow(const char* title);

  /**
   * Start main loop, periodically check input devices and render scene.
   */
  void startMainLoop();

protected:

  /**
   * Create OpenGL context, open window with given title, dimensions, and
   * fullscreen mode, and initialize GLEW.
   * Called by createWindow() and createFullscrennWindow().
   */
  void createWindow_(const char* title, int width, int height, bool fullscreenMode);

  /**
   * Check controllers for input, called by startMainLoop().
   */
  void processControllers_();

  /**
   * Update animations, called by startMainLoop().
   */
  void processAnimations_();

  /**
   * GLFW error callback function.
   */
  static void errorCB_(int error, const char* description);

  /**
   * GLFW callback function for framebuffer resize event.
   * Note: Use glfwSetFramebufferSizeCallback() instead of glfwSetWindowSizeCallback()
   * to correctly handle Mac Retina display
   */
  static void framebufferSizeCB_(GLFWwindow* window, int width, int height);

private:

  /**
   * Disallow copy constructor and assignment operator.
   */
  SCG_DISALLOW_COPY_AND_ASSIGN(Viewer);

protected:

  static bool isInstantiated_;
  static bool isWindowResized_;
  GLFWwindow* window_;
  ViewStateUP viewState_;
  OGLConfig oglConfig_;
  int oglVersion_;
  RendererSP renderer_;
  std::vector<AnimationSP> animations_;
  std::vector<ControllerSP> controllers_;
  FrameBufferSize frameBufferSize_;
  GLbitfield frameBufferClearMask_;

};


} /* namespace scg */

#endif /* VIEWER_H_ */
