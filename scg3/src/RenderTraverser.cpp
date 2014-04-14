/**
 * \file RenderTraverser.cpp
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
#include "Group.h"
#include "Light.h"
#include "RenderState.h"
#include "RenderTraverser.h"
#include "Shape.h"
#include "Transformation.h"

namespace scg {


RenderTraverser::RenderTraverser(RenderState* renderState)
    : Traverser(renderState) {
}


RenderTraverser::~RenderTraverser() {
}


void RenderTraverser::visitShape(Shape* node) {
  node->render(renderState_);
}


void RenderTraverser::visitCamera(Camera* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostCamera(Camera* node) {
  node->renderPost(renderState_);
}


void RenderTraverser::visitGroup(Group* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostGroup(Group* node) {
  node->renderPost(renderState_);
}


void RenderTraverser::visitLight(Light* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostLight(Light* node) {
  node->renderPost(renderState_);
}


void RenderTraverser::visitTransformation(Transformation* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostTransformation(Transformation* node) {
  node->renderPost(renderState_);
}


} /* namespace scg */
