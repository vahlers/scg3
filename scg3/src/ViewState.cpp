/**
 * \file ViewState.cpp
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

#include <cfloat>
#include <iomanip>
#include <iostream>
#include "scg_glew.h"
#include <GLFW/glfw3.h>
#include "ViewState.h"

namespace scg {


ViewState::ViewState()
    : isMouseCursorVisible_(true), isAnimationLocked_(false),
      isFrameRateOutput_(false), frameRateInterval_(3.), frameRate_(0.) {
}


ViewState::~ViewState() {
}


GLFWwindow* ViewState::getWindow() const {
  return window_;
}


void ViewState::setWindow(GLFWwindow* window) {
  window_ = window;
}


bool ViewState::isMouseCursorVisible() const {
  return isMouseCursorVisible_;
}


void ViewState::setMouseCursorVisible(bool isVisible) {
  isMouseCursorVisible_ = isVisible;
}


bool ViewState::isAnimationLocked() const {
  return isAnimationLocked_;
}


void ViewState::setAnimationLocked(bool isLocked) {
  isAnimationLocked_ = isLocked;
}


bool ViewState::isFrameRateOutput() const {
  return isFrameRateOutput_;
}


void ViewState::setFrameRateOutput(bool isOutput) {
  isFrameRateOutput_ = isOutput;
}


void ViewState::setFrameRateInterval(double intervalSeconds) {
  frameRateInterval_ = intervalSeconds;
}


double ViewState::getFrameRate() const {
  return frameRate_;
}


void ViewState::updateFrameRate() {
  if (frameRateInterval_ > DBL_EPSILON) {
    static int nFrames = 0;
    static double lastTime = glfwGetTime();
    ++nFrames;
    double currTime = glfwGetTime();
    double diffTime = currTime - lastTime;
    if (diffTime > frameRateInterval_) {
      frameRate_ = nFrames / diffTime;
      nFrames = 0;
      lastTime = currTime;
      if (isFrameRateOutput_) {
        std::cout << "Frame rate: " << std::fixed << std::setw(6) << std::setprecision(1)
            << frameRate_ << " FPS" << std::endl;
      }
    }
  }
}


} /* namespace scg */
