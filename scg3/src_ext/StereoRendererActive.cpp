/**
 * \file StereoRendererActive.cpp
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
