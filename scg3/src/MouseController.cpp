/**
 * \file MouseController.cpp
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

#include <iostream>
#include "scg_glew.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "MouseController.h"
#include "scg_glm.h"
#include "scg_utilities.h"
#include "ViewState.h"

namespace scg {


MouseController::MouseController(CameraSP camera)
    : CameraController(camera) {
  moveVelocity_ = 0.01f;
  rotateVelocity_ = 0.05f;

  std::cout << "Mouse camera control enabled" << std::endl;
  std::cout << "- left button (fly/examine): move forward/backward, rotate around yaw/azimuth axis" << std::endl;
  std::cout << "  + alt: dolly in/out (relative to center point), rotate around yaw/azimuth axis" << std::endl;
  std::cout << "- right button (fly/examine): rotate around roll and pitch/elevation axes" << std::endl;
  std::cout << "  + alt: rotate around yaw/azimuth and pitch/elevation axes" << std::endl;
  std::cout << "- middle button or right button + cmd: toggle fly/examine mode" << std::endl;
  std::cout << std::endl;
}


MouseController::~MouseController() {
}


MouseControllerSP MouseController::create(CameraSP camera) {
  return std::make_shared<MouseController>(camera);
}


void MouseController::checkInput(ViewState* viewState) {
  // initialize controller state
  static bool toggleMouseButton(false);
  GLFWwindow* window = viewState->getWindow();
  double mouseX, mouseY;
  // get cursor position in screen coordinates, initialize saved cursor position
  glfwGetCursorPos(window, &mouseX, &mouseY);
  static double mouseXOld(mouseX), mouseYOld(mouseY);

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    // left mouse button pressed: camera movement and rotation
    // free cursor from restricted window area
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // move forward/backward or dolly
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
      camera_->dolly(-moveVelocity_ * static_cast<GLfloat>(mouseY - mouseYOld));
    }
    else {
      camera_->translate(glm::vec3(0.0f, 0.0f, moveVelocity_ * (mouseY - mouseYOld)));
    }

    // rotate around yaw/azimuth axis
    if (isFlyMode_) {
      camera_->rotateYaw(-rotateVelocity_ * static_cast<GLfloat>(mouseX - mouseXOld));
    }
    else {  // examine mode
      camera_->rotateAzimuth(rotateVelocity_ * static_cast<GLfloat>(mouseX - mouseXOld));
    }
    toggleMouseButton = true;
  }
  else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
      ! (glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
          glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS)) {
    // right mouse button pressed: camera rotation
    // free cursor from restricted window area
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // rotate around roll or yaw/azimuth axis
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
      if (isFlyMode_) {
        camera_->rotateYaw(-rotateVelocity_ * static_cast<GLfloat>(mouseX - mouseXOld));
      }
      else {  // examine mode
        camera_->rotateAzimuth(rotateVelocity_ * static_cast<GLfloat>(mouseX - mouseXOld));
      }
    }
    else {
      camera_->rotateRoll(rotateVelocity_ * static_cast<GLfloat>(mouseX - mouseXOld));
    }

    // rotate around pitch/elevation axis
    if (isFlyMode_) {
      camera_->rotatePitch(rotateVelocity_ * static_cast<GLfloat>(mouseY - mouseYOld));
    }
    else {  // examine mode
      camera_->rotateElevation(-rotateVelocity_ * static_cast<GLfloat>(mouseY - mouseYOld));
    }

    toggleMouseButton = true;
  }
  else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS ||
      (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
          (glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
              glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS))) {
    // middle mouse button pressed: toggle fly/examine mode
    if (!toggleMouseButton) {
      static bool prevDrawCenterMode = false;
      isFlyMode_ = !isFlyMode_;
      if (isFlyMode_) {
        // fly mode: restore previous draw center point mode
        camera_->setDrawCenter(prevDrawCenterMode);
      }
      else {
        // examine mode: draw center point, saving current mode
        prevDrawCenterMode = camera_->isDrawCenter();
        camera_->setDrawCenter(true);
      }
    }
    toggleMouseButton = true;
  }
  else {
    // no mouse button pressed: restore mouse cursor (position is restored automatically)
    if (viewState->isMouseCursorVisible()) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    toggleMouseButton = false;
  }
  // save current cursor position
  mouseXOld = mouseX;
  mouseYOld = mouseY;
}


} /* namespace scg */
