/**
 * \file KeyboardController.cpp
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

#include <iostream>
#include "scg_glew.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "KeyboardController.h"
#include "scg_glm.h"
#include "ViewState.h"

namespace scg {


KeyboardController::KeyboardController(CameraSP camera)
    : CameraController(camera) {
  moveVelocity_ = 1.0f;
  rotateVelocity_ = 45.0f;
  flightVelocityStep_ = 0.2f;

  std::cout << "Keyboard camera control enabled" << std::endl;
  std::cout << "- space: toggle fly/examine mode" << std::endl;
  std::cout << "- arrow keys (fly mode/default): rotate around yaw and pitch axes" << std::endl;
  std::cout << "  + alt: rotate around roll and pitch axes" << std::endl;
  std::cout << "- arrow keys (examine mode): rotate around azimuth and elevation axes" << std::endl;
  std::cout << "  + alt: rotate around roll and elevation axes" << std::endl;
  std::cout << "- w/s: move forward/backward" << std::endl;
  std::cout << "  + alt: dolly in/out (relative to center point)" << std::endl;
  std::cout << "- a/d/x/z: move left/right/up/down (a/d/x/y on German keyboard)" << std::endl;
  std::cout << "- page up/down: increase/decrease continuous flight velocity" << std::endl;
  std::cout << "- h: toggle frame rate output (to console)" << std::endl;
  std::cout << "- j: toggle center point visibility" << std::endl;
  std::cout << "- k: toggle mouse cursor visibility" << std::endl;
  std::cout << "- l: toggle polygon mode (fill/line)" << std::endl;
  std::cout << std::endl;
}


KeyboardController::~KeyboardController() {
}


KeyboardControllerSP KeyboardController::create(CameraSP camera) {
  return std::make_shared<KeyboardController>(camera);
}


void KeyboardController::checkInput(ViewState* viewState) {
  // initialize controller state
  static double lastTime(glfwGetTime());
  GLFWwindow* window = viewState->getWindow();

  // determine time difference
  double currTime = glfwGetTime();
  GLfloat diffTime = static_cast<GLfloat>(currTime - lastTime);
  lastTime = currTime;

  // camera movement
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
      camera_->dolly(moveVelocity_ * diffTime);
    }
    else {
      camera_->translate(glm::vec3(0.0f, 0.0f, -moveVelocity_ * diffTime));
    }
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
      camera_->dolly(-moveVelocity_ * diffTime);
    }
    else {
      camera_->translate(glm::vec3(0.0f, 0.0f, moveVelocity_ * diffTime));
    }
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera_->translate(glm::vec3(-moveVelocity_ * diffTime, 0.0f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera_->translate(glm::vec3(moveVelocity_ * diffTime, 0.0f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
    camera_->translate(glm::vec3(0.0f, moveVelocity_ * diffTime, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
    camera_->translate(glm::vec3(0.0f, -moveVelocity_ * diffTime, 0.0f));
  }

  // camera rotation
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
      camera_->rotateRoll(-rotateVelocity_ * diffTime);
    }
    else {
      if (isFlyMode_) {
        camera_->rotateYaw(rotateVelocity_ * diffTime);
      }
      else {
        camera_->rotateAzimuth(-rotateVelocity_ * diffTime);
      }
    }
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
      camera_->rotateRoll(rotateVelocity_ * diffTime);
    }
    else {
      if (isFlyMode_) {
        camera_->rotateYaw(-rotateVelocity_ * diffTime);
      }
      else {
        camera_->rotateAzimuth(rotateVelocity_ * diffTime);
      }
    }
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    if (isFlyMode_) {
      camera_->rotatePitch(-rotateVelocity_ * diffTime);
    }
    else {
      camera_->rotateElevation(rotateVelocity_ * diffTime);
    }
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    if (isFlyMode_) {
      camera_->rotatePitch(rotateVelocity_ * diffTime);
    }
    else {
      camera_->rotateElevation(-rotateVelocity_ * diffTime);
    }
  }

  // continuous flight velocity
  static bool toggleKeyPageUp = false;
  if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS && !toggleKeyPageUp) {
    flightVelocity_ -= flightVelocityStep_;
    toggleKeyPageUp = true;
  }
  if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_RELEASE) {
    toggleKeyPageUp = false;
  }
  static bool toggleKeyPageDown = false;
  if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS && !toggleKeyPageDown) {
    flightVelocity_ += flightVelocityStep_;
    toggleKeyPageDown = true;
  }
  if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE) {
    toggleKeyPageDown = false;
  }

  // toggle fly/examine mode
  static bool toggleKeySpace = false;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !toggleKeySpace) {
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
    toggleKeySpace = true;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    toggleKeySpace = false;
  }

  // toggle frame rate output
  static bool toggleKeyH = false;
  if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !toggleKeyH) {
    viewState->setFrameRateOutput(!viewState->isFrameRateOutput());
    toggleKeyH = true;
  }
  if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE) {
    toggleKeyH = false;
  }

  // toggle draw center point mode
  static bool toggleKeyJ = false;
  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && !toggleKeyJ) {
    camera_->setDrawCenter(!camera_->isDrawCenter());
    toggleKeyJ = true;
  }
  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
    toggleKeyJ = false;
  }

  // toggle visibility of mouse cursor
  static bool toggleKeyK = false;
  static double mouseXOld(0), mouseYOld(0);
  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && !toggleKeyK) {
    viewState->setMouseCursorVisible(!viewState->isMouseCursorVisible());
    if (viewState->isMouseCursorVisible()) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      glfwSetCursorPos(window, mouseXOld, mouseYOld);
    }
    else {
      glfwGetCursorPos(window, &mouseXOld, &mouseYOld);
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    toggleKeyK = true;
  }
  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) {
    toggleKeyK = false;
  }

  // toggle line/fill mode
  static bool toggleKeyL = false;
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !toggleKeyL) {
    static bool isLineMode = false;
    isLineMode = !isLineMode;
    isLineMode ?
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    toggleKeyL = true;
  }
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
    toggleKeyL = false;
  }

  // continuous flight action
  camera_->translate(glm::vec3(0.0f, 0.0f, flightVelocity_ * diffTime));
}


} /* namespace scg */
