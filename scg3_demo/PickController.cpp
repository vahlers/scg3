/**
 * \file PickController.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../scg3/src/RenderState.h"
#include "../scg3/src/scg_glm.h"
#include "../scg3/src/ViewState.h"
#include "PickController.h"


namespace scg {


PickController::PickController()
    : isPicked_(false) {
}


PickController::~PickController() {
}


PickControllerSP PickController::create() {
  return std::make_shared<PickController>();
}


void PickController::checkInput(ViewState* viewState) {
  GLFWwindow* window = viewState->getWindow();

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    // right mouse button pressed: picking
    isPicked_ = true;
    glfwGetCursorPos(window, &mouseX_, &mouseY_);
  }
  else {
    isPicked_ = false;
  }
}


void PickController::render(RenderState* renderState) {
  renderState->modelViewStack.pushMatrix();

  if (isPicked_) {
    // transform picking location to object coordinates
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    // transform to normalized device coordinates
    // (x,y,z in [-1,1], mirror y coordinate)
    glm::vec4 devCoord(
        2.f * (static_cast<GLint>(mouseX_) - viewport[0]) / (viewport[2] - 1.f) - 1.f,
        1.f - 2.f * (static_cast<GLint>(mouseY_) - viewport[1]) / (viewport[3] - 1.f),
        -0.9f,
        1.f);
    // transform to 4D object coordinates
    glm::vec4 objCoord4 = glm::inverse(renderState->getMVPMatrix()) * devCoord;
    // perspective division to 3D object coordinates
    glm::vec3 objCoord(objCoord4);
    float perDivFactor = 1.f / objCoord4.w;
    objCoord *= perDivFactor;

    // set translation to picking location
    setMatrix(glm::mat4());
    translate(objCoord);

    renderState->modelViewStack.multMatrix(matrix_);
  }
}


} /* namespace scg */
