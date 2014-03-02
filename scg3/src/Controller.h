/**
 * \file Controller.h
 * \brief Base class for all controllers (abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
