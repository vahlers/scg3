/**
 * \file ColorCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "ColorCore.h"
#include "RenderState.h"

namespace scg {


ColorCore::ColorCore()
    : isColorSet_(false) {
}


ColorCore::~ColorCore() {
}


ColorCoreSP ColorCore::create() {
  return std::make_shared<ColorCore>();
}


ColorCore* ColorCore::setColor(glm::vec4 color) {
  if (color.w < -0.001f) {
    // unset vertex color
    isColorSet_ = false;
  }
  else {
    // set vertex color
    color_ = color;
    isColorSet_ = true;
  }
  return this;
}


ColorCore* ColorCore::setMatrix(glm::mat4 matrix) {
  matrix_ = matrix;
  return this;
}


void ColorCore::render(RenderState* renderState) {
  // post-multiply current color matrix by local color matrix
  renderState->colorStack.pushMatrix();
  renderState->colorStack.multMatrix(matrix_);

  // set vertex color (if set)
  if (isColorSet_) {
    colorCoreOld_ = renderState->getColor();
    renderState->setColor(this);
    glVertexAttrib4fv(OGLConstants::COLOR.location, glm::value_ptr(color_));
  }
}


void ColorCore::renderPost(RenderState* renderState) {
  // restore color matrix
  renderState->colorStack.popMatrix();

  // restore vertex color (if set)
  if (isColorSet_) {
    renderState->setColor(colorCoreOld_);
    if (colorCoreOld_) {
      if (colorCoreOld_->isColorSet_) {
        glVertexAttrib4fv(OGLConstants::COLOR.location, glm::value_ptr(colorCoreOld_->color_));
      }
    }
  }
}


} /* namespace scg */
