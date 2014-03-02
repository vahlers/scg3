/**
 * \file StereoRendererActive.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "../src/scg_glew.h"
#include <GLFW/glfw3.h>
#include "../src/scg_utilities.h"
#include "StereoRendererActive.h"

namespace scg {


StereoRendererActive::StereoRendererActive(RendererSP concreteRenderer)
    : StereoRenderer(concreteRenderer) {
}


StereoRendererActive::~StereoRendererActive() {
}


StereoRendererActiveSP StereoRendererActive::create(RendererSP concreteRenderer) {
  assert(concreteRenderer);
  return std::make_shared<StereoRendererActive>(concreteRenderer);
}


void StereoRendererActive::initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize) {
  assert(concreteRenderer_);
  concreteRenderer_->initViewer(viewer, frameBufferSize);
  glfwWindowHint(GLFW_STEREO, GL_TRUE);
}


void StereoRendererActive::render() {
  assert(concreteRenderer_);

  // left eye: enable left buffer, clear frame and depth buffers,
  // render scene using concrete renderer
  glDrawBuffer(GL_BACK_LEFT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  concreteRenderer_->render();

  // right eye: enable right buffer, clear frame and depth buffers,
  // render scene using concrete renderer
  glDrawBuffer(GL_BACK_RIGHT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  concreteRenderer_->render();

  assert(!checkGLError());
}


} /* namespace scg */
