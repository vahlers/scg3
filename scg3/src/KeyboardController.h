/**
 * \file KeyboardController.h
 * \brief A camera controller using keyboard input.
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

#ifndef KEYBOARDCONTROLLER_H_
#define KEYBOARDCONTROLLER_H_

#include "scg_glew.h"
#include "CameraController.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A camera controller using keyboard input.
 *
 * See implementation of constructor KeyboardController::KeyboardController(),
 * which prints a list of control actions.
 */
class KeyboardController: public CameraController {

public:

  /**
   * Constructor with given camera transformation.
   */
  KeyboardController(CameraSP camera);

  /**
   * Destructor.
   */
  virtual ~KeyboardController();

  /**
   * Create shared pointer with given camera transformation.
   */
  static KeyboardControllerSP create(CameraSP camera);

  /**
   * Check input devices, called by Viewer::startMainLoop().
   *
   * \param viewState view state managed by Viewer, may be modified by controller
   */
  virtual void checkInput(ViewState* viewState);

};


} /* namespace scg */

#endif /* KEYBOARDCONTROLLER_H_ */
