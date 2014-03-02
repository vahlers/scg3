/**
 * \file StereoRendererActive.h
 * \brief A renderer for active stereo (e.g., shutter glasses).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef STEREORENDERERACTIVE_H_
#define STEREORENDERERACTIVE_H_

#include <string>
#include "../src/scg_internals.h"
#include "scg_ext_internals.h"
#include "StereoRenderer.h"

namespace scg {


/**
 * \brief A renderer for active stereo (e.g., shutter glasses).
 *
 * Decorator pattern, render() calls concreteRenderer->render().
 */
class StereoRendererActive: public StereoRenderer {

public:

  /**
   * Constructor.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  StereoRendererActive(RendererSP concreteRenderer);

  /**
   * Destructor.
   */
  virtual ~StereoRendererActive();

  /**
   * Create shared pointer.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  static StereoRendererActiveSP create(RendererSP concreteRenderer);

  /**
   * Initialize viewer properties before an OpenGL context has been created.
   * Request stereo framebuffer.
   *
   * \param viewer viewer that uses the renderer
   * \param frameBufferSize frame buffer size to be used by viewer to create OpenGL context
   *    (cf. FrameBufferSize)
   */
  virtual void initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize);

  /**
   * Render the scene, called by Viewer::startMainLoop().
   * Calls concreteRenderer->render().
   */
  virtual void render();

};


} /* namespace scg */

#endif /* STEREORENDERERACTIVE_H_ */
