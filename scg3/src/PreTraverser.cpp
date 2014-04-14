/**
 * \file PreTraverser.cpp
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

#include "Camera.h"
#include "Light.h"
#include "LightPosition.h"
#include "PreTraverser.h"
#include "RenderState.h"
#include "Transformation.h"
#include "scg_glm.h"

namespace scg {


PreTraverser::PreTraverser(RenderState* renderState)
    : Traverser(renderState) {
}


PreTraverser::~PreTraverser() {
}


void PreTraverser::visitCamera(Camera* node) {
  // apply camera transformation, but do not render coordinate axes
  node->Transformation::render(renderState_);

  // save projection and view transformation
  renderState_->setProjection(node->getProjection());
  renderState_->setViewTransform(node->getViewTransform(renderState_));
}


void PreTraverser::visitPostCamera(Camera* node) {
  node->renderPost(renderState_);
}


void PreTraverser::visitLightPosition(LightPosition* node) {
  node->getLight()->setModelTransform(renderState_->modelViewStack.getMatrix());
}


void PreTraverser::visitTransformation(Transformation* node) {
  node->render(renderState_);
}


void PreTraverser::visitPostTransformation(Transformation* node) {
  node->renderPost(renderState_);
}


} /* namespace scg */
