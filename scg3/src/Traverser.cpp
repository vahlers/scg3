/**
 * \file Traverser.cpp
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

#include "Traverser.h"

namespace scg {


Traverser::Traverser(RenderState* renderState)
    : renderState_(renderState) {
}


Traverser::~Traverser() {
}


void Traverser::visitLightPosition(LightPosition* node) {
  // do nothing by default
}


void Traverser::visitShape(Shape* node) {
  // do nothing by default
}


void Traverser::visitCamera(Camera* node) {
  // do nothing by default
}


void Traverser::visitPostCamera(Camera* node) {
  // do nothing by default
}


void Traverser::visitGroup(Group* node) {
  // do nothing by default
}


void Traverser::visitPostGroup(Group* node) {
  // do nothing by default
}


void Traverser::visitLight(Light* node) {
  // do nothing by default
}


void Traverser::visitPostLight(Light* node) {
  // do nothing by default
}


void Traverser::visitTransformation(Transformation* node) {
  // do nothing by default
}


void Traverser::visitPostTransformation(Transformation* node) {
  // do nothing by default
}


} /* namespace scg */
