/**
 * \file StereoRendererAnaglyph.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014 Volker Ahlers
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
