/**
 * \file KeyboardController.h
 * \brief A camera controller using keyboard input.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
