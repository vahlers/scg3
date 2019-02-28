/**
 * \file StandardRenderer.h
 * \brief A standard renderer that uses a PreTraverser, a RenderTraverser, and an
 *    InfoTraverser.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef RENDERTOTEXTURERENDERER_H_
#define RENDERTOTEXTURERENDERER_H_

#include "../scg3/src/Renderer.h"
#include "../scg3/src/scg_internals.h"

namespace scg {


SCG_DECLARE_CLASS(RenderToTextureRenderer);


extern GLuint renderToTextureTex;


/**
 * \brief A renderer to demonstrate render to texture that uses a PreTraverser, a RenderTraverser, and an
 *    InfoTraverser.
 *
 * The stencil buffer is activated for later use in projection shadows and planar
 * reflections.
 */
class RenderToTextureRenderer: public Renderer {

public:

  /**
   * Constructor.
   */
  RenderToTextureRenderer();

  /**
   * Destructor.
   */
  virtual ~RenderToTextureRenderer();

  /**
   * Create shared pointer.
   */
  static RenderToTextureRendererSP create();

  /**
   * Initialize viewer properties before an OpenGL context has been created.
   * Activate the stencil buffer for later use in projection shadows and planar reflections.
   *
   * \param viewer viewer that uses the renderer
   * \param frameBufferSize frame buffer size to be used by viewer to create OpenGL context
   *    (cf. FrameBufferSize), modified to activate the stencil buffer
   */
  virtual void initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize);

  virtual void initRenderState();

  /**
   * Get information about the scene graph (e.g., number of triangles).
   */
  virtual std::string getInfo();

  /**
   * Render the scene, called by Viewer::startMainLoop().
   */
  virtual void render();

protected:

  GLuint fbo_;
  GLuint rbo_;
  InfoTraverserUP infoTraverser_;
  PreTraverserUP preTraverser_;
  RenderTraverserUP renderTraverser_;

};


} /* namespace scg */

#endif /* RENDERTOTEXTURERENDERER_H_ */
