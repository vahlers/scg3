/**
 * \file StereoRenderer.cpp
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
#include "StereoRenderer.h"

namespace scg {


StereoRenderer::StereoRenderer(RendererSP concreteRenderer)
    : Renderer(), concreteRenderer_(concreteRenderer) {
}


StereoRenderer::~StereoRenderer() {
}


void StereoRenderer::initRenderState() {
  assert(concreteRenderer_);
  concreteRenderer_->initRenderState();
}


void StereoRenderer::initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize) {
  assert(concreteRenderer_);
  concreteRenderer_->initViewer(viewer, frameBufferSize);
  // leave OpenGL mode unchanged, no extension required
}


std::string StereoRenderer::getInfo() {
  assert(concreteRenderer_);
  return concreteRenderer_->getInfo();
}



} /* namespace scg */
