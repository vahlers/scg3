/**
 * \file SpaceMouseController.h
 * \brief A camera controller using 3D mouse input via VRPN.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef SPACEMOUSECONTROLLER_H_
#define SPACEMOUSECONTROLLER_H_

#include <string>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../scg3/src/CameraController.h"
#include "../scg3/src/scg_internals.h"

namespace scg {


SCG_DECLARE_CLASS(SpaceMouseController);



/**
 * \brief A camera controller using 3D mouse input via VRPN.
 *
 * See implementation of constructor SpaceMouseController::SpaceMouseController(),
 * which prints a list of control actions.
 */
class SpaceMouseController: public CameraController {

public:

  /**
   * Active degrees of freedom: all, translate only, or rotate only.
   */
#ifdef SCG_CPP11_STRONGLY_TYPED_ENUMS
  enum class NavigatorMode: int {
    ALL,
    TRANSLATE,
    ROTATE,
    COUNT
  };
#else
  enum NavigatorMode {
    ALL,
    TRANSLATE,
    ROTATE,
    COUNT
  };
#if defined(_MSC_VER)
#pragma warning(disable: 4482)
#endif
#endif

  /**
   * Constructor with given camera transformation.
   */
  SpaceMouseController(CameraSP camera, const std::string& deviceName);

  /**
   * Destructor.
   */
  virtual ~SpaceMouseController();

  /**
   * Create shared pointer with given camera transformation.
   */
  static SpaceMouseControllerSP create(CameraSP camera,
      const std::string& deviceName = "navigator@localhost");

  /**
   * Check input devices, called by Viewer::startMainLoop().
   *
   * \param viewState view state managed by Viewer, may be modified by controller
   */
  virtual void checkInput(ViewState* viewState);

protected:

  /**
   * VRPN analog callback function.
   */
  static void VRPN_CALLBACK analogFunc_(void* userData, vrpn_ANALOGCB analogData);

  /**
   * VRPN button callback function.
   */
  static void VRPN_CALLBACK buttonFunc_(void* userData, vrpn_BUTTONCB buttonData);

protected:

  float sensitivity_;
  NavigatorMode navigatorMode_;
  std::string deviceName_;
  GLFWwindow* window_;
  vrpn_Analog_Remote* navigatorAnalog_;
  vrpn_Button_Remote* navigatorButton_;

};


} /* namespace scg */

#endif /* SPACEMOUSECONTROLLER_H_ */
