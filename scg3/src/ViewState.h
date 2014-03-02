/**
 * \file ViewState.h
 * \brief The view state of the application, managed by Viewer and accessible by
 *    Controller::checkInput() (or derived classes).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef VIEWSTATE_H_
#define VIEWSTATE_H_

#include "scg_glew.h"
#include <GLFW/glfw3.h>

namespace scg {


/**
 * \brief The view state of the application, managed by Viewer and accessible by
 *    Controller::checkInput() (or derived classes).
 */
class ViewState {

public:

  /**
   * Constructor.
   */
  ViewState();

  /**
   * Destructor.
   */
  virtual ~ViewState();

  /**
   * Get window pointer, called by camera controllers.
   */
  GLFWwindow* getWindow() const;

  /**
   * Set window pointer.
   */
  void setWindow(GLFWwindow* window);

  /**
   * Check mouse cursor visibility.
   */
  bool isMouseCursorVisible() const;

  /**
   * Set mouse cursor visibility (default: true/visible).
   */
  void setMouseCursorVisible(bool isVisible);

  /**
   * Check locked state of animations.
   */
  bool isAnimationLocked() const;

  /**
   * Set locked state of animations (default: false/unlocked).
   */
  void setAnimationLocked(bool isLocked);

  /**
   * Check frame output mode.
   */
  bool isFrameRateOutput() const;

  /**
   * Set frame output mode (default: false/disabled).
   */
  void setFrameRateOutput(bool isOutput);

  /**
   * Set interval for frame rate computation (default: 3 sec).
   *
   * \param intervalSec interval (seconds) for frame rate computation;
   *    0 deactivates frame rate computation
   */
  void setFrameRateInterval(double intervalSec);

  /**
   * Get current frame rate (FPS).
   */
  double getFrameRate() const;

  /**
   * Update frame rate, called by Viewer::startMainLoop().
   */
  void updateFrameRate();

protected:

  GLFWwindow* window_;
  bool isMouseCursorVisible_;
  bool isAnimationLocked_;
  bool isFrameRateOutput_;
  double frameRateInterval_;
  double frameRate_;

};

} /* namespace scg */

#endif /* VIEWSTATE_H_ */
