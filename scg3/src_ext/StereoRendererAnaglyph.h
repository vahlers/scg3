/**
 * \file StereoRendererAnaglyph.h
 * \brief A renderer for anaglyph stereo (left: red, right: cyan).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef STEREORENDERERANAGLYPH_H_
#define STEREORENDERERANAGLYPH_H_

#include "../src/scg_internals.h"
#include "scg_ext_internals.h"
#include "StereoRenderer.h"

namespace scg {


/**
 * \brief A renderer for anaglyph stereo (left eye: red, right eye: cyan).
 *
 * Decorator pattern, render() calls concreteRenderer->render().
 */
class StereoRendererAnaglyph: public StereoRenderer {

public:

  /**
   * Constructor.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  StereoRendererAnaglyph(RendererSP concreteRenderer);

  /**
   * Destructor.
   */
  virtual ~StereoRendererAnaglyph();

  /**
   * Create shared pointer.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  static StereoRendererAnaglyphSP create(RendererSP concreteRenderer);

  /**
   * Render the scene, called by Viewer::startMainLoop().
   * Calls concreteRenderer->render().
   */
  virtual void render();

};


} /* namespace scg */

#endif /* STEREORENDERERANAGLYPH_H_ */
