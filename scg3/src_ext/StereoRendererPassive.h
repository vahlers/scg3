/**
 * \file StereoRendererPassive.h
 * \brief A renderer for passive stereo (e.g., polarized projection).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef STEREORENDERERPASSIVE_H_
#define STEREORENDERERPASSIVE_H_

#include <string>
#include "../src/scg_internals.h"
#include "scg_ext_internals.h"
#include "StereoRenderer.h"

namespace scg {


/**
 * \brief A renderer for passive stereo (e.g., polarized projection).
 *
 * Decorator pattern, render() calls concreteRenderer->render().
 */
class StereoRendererPassive: public StereoRenderer {

public:

  /**
   * Constructor.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  StereoRendererPassive(RendererSP concreteRenderer);

  /**
   * Destructor.
   */
  virtual ~StereoRendererPassive();

  /**
   * Create shared pointer.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  static StereoRendererPassiveSP create(RendererSP concreteRenderer);

  /**
   * Render the scene, called by Viewer::startMainLoop().
   * Calls concreteRenderer->render().
   */
  virtual void render();

};


} /* namespace scg */

#endif /* STEREORENDERERPASSIVE_H_ */
