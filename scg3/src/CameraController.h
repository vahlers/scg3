/**
 * \file CameraController.h
 * \brief Base class for all camera controllers, acting on a Camera node (abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include "scg_glew.h"
#include "Controller.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief Base class for all camera controllers, acting on a Camera node (abstract).
 *
 * A typical CameraController offers actions for camera movement and rotation,
 * and potentially for continuous flight of camera.
 * It may further be possible to toggle between fly mode (free camera movement in space)
 * and examine mode (camera movement relative to center point).
 */
class CameraController: public Controller {

public:

  /**
   * Constructor with given camera transformation.
   */
  CameraController(CameraSP camera);

  /**
   * Destructor.
   */
  virtual ~CameraController() = 0;

  /**
   * Set camera transformation to act on.
   */
  void setCamera(CameraSP camera);

  /**
   * Set velocity for camera movement.
   */
  void setMoveVelocity(GLfloat moveVelocity);

  /**
   * Set velocity for camera rotation.
   */
  void setRotateVelocity(GLfloat rotateVelocity);

  /**
   * Set velocity for continuous flight of camera.
   */
  void setFlightVelocity(GLfloat flightVelocity);

  /**
   * Set step for changing flight velocity.
   */
  void setFlightVelocityStep(GLfloat flightVelocityStep);

  /**
   * Check input devices, called by Viewer::startMainLoop().
   *
   * \param viewState view state managed by Viewer, may be modified by controller
   */
  virtual void checkInput(ViewState* viewState) = 0;

protected:

  CameraSP camera_;
  GLfloat moveVelocity_;
  GLfloat rotateVelocity_;
  GLfloat flightVelocity_;
  GLfloat flightVelocityStep_;
  bool isFlyMode_;    /**< true: fly mode, false: examination mode */

};


} /* namespace scg */

#endif /* CAMERACONTROLLER_H_ */
