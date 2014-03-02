/**
 * \file Transformation.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "RenderState.h"
#include "Transformation.h"
#include "Traverser.h"

namespace scg {


Transformation::Transformation() {
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



Transformation* Transformation::rotate(GLfloat angleDeg, glm::vec3 axis) {
  matrix_ = glm::rotate(matrix_, angleDeg, axis);
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
