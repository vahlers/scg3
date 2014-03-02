/**
 * \file MouseController.h
 * \brief A camera controller using mouse input.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
