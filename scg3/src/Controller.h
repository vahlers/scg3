/**
 * \file Controller.h
 * \brief Base class for all controllers (abstract).
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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "scg_internals.h"

namespace scg {


/**
 * \brief Base class for all controllers (abstract).
 */
class Controller {

public:

  /**
   * Constructor.
   */
  Controller();

  /**
   * Destructor.
   */
  virtual ~Controller() = 0;

  /**
   * Check input devices, called by Viewer::startMainLoop().
   *
   * \param viewState view state managed by Viewer, may be modified by controller
   */
  virtual void checkInput(ViewState* viewState) = 0;

};


} /* namespace scg */

#endif /* CONTROLLER_H_ */
