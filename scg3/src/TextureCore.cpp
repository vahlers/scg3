/**
 * \file TextureCore.cpp
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

#include <cassert>
#include "RenderState.h"
#include "TextureCore.h"

namespace scg {


TextureCore::TextureCore()
    : tex_(0), texOld_(0), matrix_(1.0f) {
}


TextureCore::~TextureCore() {
}


TextureCore* TextureCore::rotate(GLfloat angleDeg, glm::vec3 axis) {
  matrix_ = glm::rotate(matrix_, angleDeg, axis);
  return this;
}


TextureCore* TextureCore::scale(glm::vec3 scaling) {
  matrix_ = glm::scale(matrix_, scaling);
  return this;
}


TextureCore* TextureCore::setMatrix(glm::mat4 matrix) {
  matrix_ = matrix;
  return this;
}


void TextureCore::render(RenderState* renderState) {
  // post-multiply current texture matrix by local texture matrix
  renderState->textureStack.pushMatrix();
  renderState->textureStack.multMatrix(matrix_);
}


void TextureCore::renderPost(RenderState* renderState) {
  // restore texture matrix
  renderState->textureStack.popMatrix();
}


} /* namespace scg */
