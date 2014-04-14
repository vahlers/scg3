/**
 * \file MouseController.h
 * \brief A camera controller using mouse input.
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

#ifndef MOUSECONTROLLER_H_
#define MOUSECONTROLLER_H_

#include "CameraController.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A camera controller using mouse input.
 *
 * See implementation of constructor MouseController::MouseController(),
 * which prints a list of control actions.
 */
class MouseController: public CameraController {

public:

  /**
   * Constructor with given camera transformation.
   */
  MouseController(CameraSP camera);

  /**
   * Destructor.
   */
  virtual ~MouseController();

  /**
   * Create shared pointer with given camera transformation.
   */
  static MouseControllerSP create(CameraSP camera);

  /**
   * Check input devices, called by Viewer::startMainLoop().
   *
   * \param viewState view state managed by Viewer, may be modified by controller
   */
  virtual void checkInput(ViewState* viewState);

};


} /* namespace scg */

#endif /* MOUSECONTROLLER_H_ */
