/**
 * \file StereoRendererPassive.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "../src/scg_glew.h"
#include "../src/scg_utilities.h"
#include "StereoRendererPassive.h"

namespace scg {


StereoRendererPassive::StereoRendererPassive(RendererSP concreteRenderer)
    : StereoRenderer(concreteRenderer) {
}


StereoRendererPassive::~StereoRendererPassive() {
}


StereoRendererPassiveSP StereoRendererPassive::create(RendererSP concreteRenderer) {
  assert(concreteRenderer);
  return std::make_shared<StereoRendererPassive>(concreteRenderer);
}


void StereoRendererPassive::render() {
  assert(concreteRenderer_);

  // get viewport dimensions
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  GLint viewportHalfWidth = viewport[2] / 2;
  GLint viewportHeight = viewport[3];

  // left eye: render scene in left half of viewport using concrete renderer
  glViewport(0, 0, viewportHalfWidth, viewportHeight);
  concreteRenderer_->render();

  // right eye: render scene in right half of viewport using concrete renderer
  glViewport(viewportHalfWidth, 0, viewportHalfWidth, viewportHeight);
  concreteRenderer_->render();

  // restore viewport
  glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

  assert(!checkGLError());
}


} /* namespace scg */
