/**
 * \file TextureCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "RenderState.h"
#include "TextureCore.h"

namespace scg {


TextureCore::TextureCore()
    : tex_(0), texOld_(0) {
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
