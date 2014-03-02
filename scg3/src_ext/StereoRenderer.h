/**
 * \file StereoRenderer.h
 * \brief Base class for all stereo renderers (abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef STEREORENDERER_H_
#define STEREORENDERER_H_

#include <string>
#include "../src/Renderer.h"
#include "../src/scg_internals.h"

namespace scg {


/**
 * \brief Base class for all stereo renderers (abstract).
 *
 * Decorator pattern, render() calls concreteRenderer->render().
 */
class StereoRenderer: public Renderer {

public:

  /**
   * Constructor.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  StereoRenderer(RendererSP concreteRenderer);

  /**
   * Destructor.
   */
  virtual ~StereoRenderer() = 0;

  /**
   * Initialize render state after an OpenGL context has been created.
   */
  virtual void initRenderState();

  /**
   * Initialize viewer properties before an OpenGL context has been created.
   *
   * \param viewer viewer that uses the renderer
   * \param frameBufferSize frame buffer size to be used by viewer to create OpenGL context
   *    (cf. FrameBufferSize)
   */
  virtual void initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize);

  /**
   * Get information about the scene graph (e.g., number of triangles).
   * Calls concreteRenderer_->getInfo().
   */
  virtual std::string getInfo();

  /**
   * Render the scene, called by Viewer::startMainLoop().
   * Should call concreteRenderer->render().
   */
  virtual void render() = 0;

protected:

  RendererSP concreteRenderer_;

};


} /* namespace scg */

#endif /* STEREORENDERER_H_ */
