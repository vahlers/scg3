/**
 * \file PickController.h
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef PICKCONTROLLER_H_
#define PICKCONTROLLER_H_

#include "../scg3/src/Controller.h"
#include "../scg3/src/scg_internals.h"
#include "../scg3/src/Transformation.h"

namespace scg {


SCG_DECLARE_CLASS(PickController);


/**
 * \brief Experimental picking controller, creating a translation to the picking location.
 */
class PickController: public Controller, public Transformation {

public:

  /**
   * Constructor.
   */
  PickController();

  /**
   * Destructor.
   */
  virtual ~PickController();

  /**
   * Create shared pointer.
   */
  static PickControllerSP create();

  /**
   * Check input devices, called by Viewer::startMainLoop().
   *
   * \param viewState view state managed by Viewer, may be modified by controller
   */
  virtual void checkInput(ViewState* viewState);

  /**
   * Render transformation, i.e., post-multiply current model-view matrix by
   * local matrix.
   */
  virtual void render(RenderState* renderState);

protected:

  bool isPicked_;
  double mouseX_, mouseY_;

};


} /* namespace scg */

#endif /* PICKCONTROLLER_H_ */
