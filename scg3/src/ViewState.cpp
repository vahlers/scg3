/**
 * \file ViewState.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
