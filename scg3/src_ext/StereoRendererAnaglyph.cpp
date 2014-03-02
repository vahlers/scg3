/**
 * \file StereoRendererAnaglyph.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "../src/scg_glew.h"
#include "../src/scg_utilities.h"
#include "StereoRendererAnaglyph.h"

namespace scg {


StereoRendererAnaglyph::StereoRendererAnaglyph(RendererSP concreteRenderer)
    : StereoRenderer(concreteRenderer) {
}


StereoRendererAnaglyph::~StereoRendererAnaglyph() {
}


StereoRendererAnaglyphSP StereoRendererAnaglyph::create(RendererSP concreteRenderer) {
  assert(concreteRenderer);
  return std::make_shared<StereoRendererAnaglyph>(concreteRenderer);
}


void StereoRendererAnaglyph::render() {
  assert(concreteRenderer_);

  // left eye (red): disable green and blue color channels,
  // render scene using concrete renderer
  glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
  concreteRenderer_->render();

  // right eye (cyan): clear depth buffer only, disable red color channel,
  // render scene using concrete renderer
  glClear(GL_DEPTH_BUFFER_BIT);
  glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
  concreteRenderer_->render();

  // enable all color channels in order to clear the whole frame buffer
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  assert(!checkGLError());
}


} /* namespace scg */
