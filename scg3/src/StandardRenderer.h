/**
 * \file StandardRenderer.h
 * \brief A standard renderer that uses a PreTraverser, a RenderTraverser, and an
 *    InfoTraverser.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014 Volker Ahlers
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STANDARDRENDERER_H_
#define STANDARDRENDERER_H_

#include "Renderer.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A standard renderer that uses a PreTraverser, a RenderTraverser, and an
 *    InfoTraverser.
 *
 * The stencil buffer is activated for later use in projection shadows and planar
 * reflections.
 */
class StandardRenderer: public Renderer {

public:

  /**
   * Constructor.
   */
  StandardRenderer();

  /**
   * Destructor.
   */
  virtual ~StandardRenderer();

  /**
   * Create shared pointer.
   */
  static StandardRendererSP create();

  /**
   * Initialize viewer properties before an OpenGL context has been created.
   * Activate the stencil buffer for later use in projection shadows and planar reflections.
   *
   * \param viewer viewer that uses the renderer
   * \param frameBufferSize frame buffer size to be used by viewer to create OpenGL context
   *    (cf. FrameBufferSize), modified to activate the stencil buffer
   */
  virtual void initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize);

  /**
   * Get information about the scene graph (e.g., number of triangles).
   */
  virtual std::string getInfo();

  /**
   * Render the scene, called by Viewer::startMainLoop().
   */
  virtual void render();

protected:

  InfoTraverserUP infoTraverser_;
  PreTraverserUP preTraverser_;
  RenderTraverserUP renderTraverser_;

};


} /* namespace scg */

#endif /* STANDARDRENDERER_H_ */
