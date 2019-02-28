/**
 * \file SpaceMouseController.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <iostream>
#include "../scg3/src/Camera.h"
#include "../scg3/src/scg_glm.h"
#include "../scg3/src/ViewState.h"
#include "SpaceMouseController.h"

namespace scg {


SpaceMouseController::SpaceMouseController(CameraSP camera, const std::string& deviceName)
  : CameraController(camera), sensitivity_(0.1f), navigatorMode_(NavigatorMode::ALL),
    deviceName_(deviceName) {
  moveVelocity_ = 30.0f;
  rotateVelocity_ = 1000.0f;

  // pass this pointer to static callback functions for access to member variables
  navigatorAnalog_ = new vrpn_Analog_Remote(deviceName_.c_str());
  navigatorAnalog_->register_change_handler(this, (vrpn_ANALOGCHANGEHANDLER) analogFunc_);
  navigatorButton_ = new vrpn_Button_Remote(deviceName_.c_str());
  navigatorButton_->register_change_handler(this, (vrpn_BUTTONCHANGEHANDLER) buttonFunc_);

  std::cout << "Space mouse camera control enabled" << std::endl;
  std::cout << "- 3D mouse: move and rotate" << std::endl;
  std::cout << "  + alt: dolly in/out (relative to center point)" << std::endl;
  std::cout << "- left button: toggle navigator mode (all/translate/rotate)" << std::endl;
  std::cout << "- right button: toggle fly/examine mode" << std::endl;
  std::cout << std::endl;
}


SpaceMouseController::~SpaceMouseController() {
}


SpaceMouseControllerSP SpaceMouseController::create(CameraSP camera, const std::string& deviceName) {
  return std::make_shared<SpaceMouseController>(camera, deviceName);
}


void SpaceMouseController::checkInput(ViewState* viewState) {
  window_ = viewState->getWindow();
  navigatorAnalog_->mainloop();
  navigatorButton_->mainloop();
}


// transfer function for channel data
inline float transferFunc(float x, float sensitivity) {
  float result;
  if (fabs(x) <= sensitivity) {
    result = 0.0f;
  }
  else {
    float xSensAbs = fabs(x) - sensitivity;
    result = (x < 0 ? -1 : 1) * xSensAbs * xSensAbs;  //  x -> sgn(x) * (|x| - sensitivity)^2
  }
  return result;
}


void VRPN_CALLBACK SpaceMouseController::analogFunc_(void* userData, vrpn_ANALOGCB analogData) {
  // initialize controller state
  static double lastTime(glfwGetTime());
  SpaceMouseController* controller = reinterpret_cast<SpaceMouseController*>(userData);

  // determine time difference
  double currTime = glfwGetTime();
  GLfloat diffTime = static_cast<GLfloat>(currTime - lastTime);
  lastTime = currTime;

  if (controller->navigatorMode_ != NavigatorMode::ROTATE) {
    if (fabs(analogData.channel[0]) > controller->sensitivity_) {
      controller->camera_->translate(
          glm::vec3(controller->moveVelocity_ * transferFunc(analogData.channel[0], controller->sensitivity_), 0.0f, 0.0f) * diffTime);
    }
    if (fabs(analogData.channel[1]) > controller->sensitivity_) {
      if (glfwGetKey(controller->window_, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
          glfwGetKey(controller->window_, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
        controller->camera_->dolly(
            -controller->moveVelocity_ * transferFunc(analogData.channel[1], controller->sensitivity_) * diffTime);
      }
      else{
        controller->camera_->translate(
            glm::vec3(0.0f, 0.0f, controller->moveVelocity_ * transferFunc(analogData.channel[1], controller->sensitivity_) * diffTime));
      }
    }
    if (fabs(analogData.channel[2]) > controller->sensitivity_) {
      controller->camera_->translate(
          glm::vec3(0.0f, -controller->moveVelocity_ * transferFunc(analogData.channel[2], controller->sensitivity_) * diffTime, 0.0f));
    }
  }
  if (controller->navigatorMode_ != NavigatorMode::TRANSLATE) {
    if (fabs(analogData.channel[3]) > controller->sensitivity_) {
      if (controller->isFlyMode_) {
        controller->camera_->rotatePitch(
            controller->rotateVelocity_ * transferFunc(analogData.channel[3], controller->sensitivity_) * diffTime);
      }
      else {  // examine mode
        controller->camera_->rotateElevation(
            -controller->rotateVelocity_ * transferFunc(analogData.channel[3], controller->sensitivity_) * diffTime);
      }
    }
    if (fabs(analogData.channel[4]) > controller->sensitivity_) {
      controller->camera_->rotateRoll(
          controller->rotateVelocity_ * transferFunc(analogData.channel[4], controller->sensitivity_) * diffTime);
    }
    if (fabs(analogData.channel[5]) > controller->sensitivity_) {
      if (controller->isFlyMode_) {
        controller->camera_->rotateYaw(
            -controller->rotateVelocity_ * transferFunc(analogData.channel[5], controller->sensitivity_) * diffTime);
      }
      else {  // examine mode
        controller->camera_->rotateAzimuth(
            -controller->rotateVelocity_ * transferFunc(analogData.channel[5], controller->sensitivity_) * diffTime);
      }
    }
  }
}


void VRPN_CALLBACK SpaceMouseController::buttonFunc_(void* userData, vrpn_BUTTONCB buttonData) {
  SpaceMouseController* controller = reinterpret_cast<SpaceMouseController*>(userData);
  // switch mode at left button release
  if (buttonData.button == 0 && buttonData.state == 0) {
    controller->navigatorMode_ = static_cast<NavigatorMode>(
        (static_cast<int>(controller->navigatorMode_) + 1) % static_cast<int>(NavigatorMode::COUNT));
  }
  if (buttonData.button == 1 && buttonData.state == 0) {
    static bool prevDrawCenterMode = false;
    controller->isFlyMode_ = !controller->isFlyMode_;
    if (controller->isFlyMode_) {
      // fly mode: restore previous draw center point mode
      controller->camera_->setDrawCenter(prevDrawCenterMode);
    }
    else {
      // examine mode: draw center point, saving current mode
      prevDrawCenterMode = controller->camera_->isDrawCenter();
      controller->camera_->setDrawCenter(true);
    }
  }
}


} /* namespace scg */
