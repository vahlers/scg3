/**
 * \file Transformation.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014-2019 Volker Ahlers
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

#include "RenderState.h"
#include "Transformation.h"
#include "Traverser.h"

namespace scg {


Transformation::Transformation()
    : matrix_(1.0f) {
}


Transformation::~Transformation() {
}


TransformationSP Transformation::create() {
  return std::make_shared<Transformation>();
}


const glm::mat4& Transformation::getMatrix() const {
  return matrix_;
}


Transformation* Transformation::setMatrix(const glm::mat4& matrix) {
  matrix_ = matrix;
  return this;
}


Transformation* Transformation::translate(glm::vec3 translation) {
  matrix_ = glm::translate(matrix_, translation);
  return this;
}



Transformation* Transformation::rotateRad(GLfloat angleRad, glm::vec3 axis) {
  matrix_ = glm::rotate(matrix_, angleRad, axis);
  return this;
}


Transformation* Transformation::scale(glm::vec3 scaling) {
  matrix_ = glm::scale(matrix_, scaling);
  return this;
}


void Transformation::accept(Traverser *traverser) {
  traverser->visitTransformation(this);
}


void Transformation::acceptPost(Traverser *traverser) {
  traverser->visitPostTransformation(this);
}


void Transformation::render(RenderState* renderState) {
  renderState->modelViewStack.pushMatrix();
  renderState->modelViewStack.multMatrix(matrix_);
}


void Transformation::renderPost(RenderState* renderState) {
  renderState->modelViewStack.popMatrix();
}


} /* namespace scg */
