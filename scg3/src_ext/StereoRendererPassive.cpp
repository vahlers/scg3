/**
 * \file StereoRendererPassive.cpp
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
