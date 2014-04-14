/**
 * \file Renderer.h
 * \brief Base class for all renderers (abstract).
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

#ifndef RENDERER_H_
#define RENDERER_H_

#include <memory>
#include <string>
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


struct FrameBufferSize;
class Camera;
class Node;
class Viewer;


/**
 * \brief Base class for all renderers (abstract).
 */
class Renderer {

public:

  /**
   * Constructor.
   */
  Renderer();

  /**
   * Destructor.
   */
  virtual ~Renderer() = 0;

  /**
   * Initialize viewer properties before an OpenGL context has been created.
   *
   * \param viewer viewer that uses the renderer
   * \param frameBufferSize frame buffer size to be used by viewer to create OpenGL context
   *    (cf. FrameBufferSize), can be modified for specific requirements (e.g., stencil buffer)
   */
  virtual void initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize) = 0;

  /**
   * Initialize render state after an OpenGL context has been created.
   */
  virtual void initRenderState();

  /**
   * Destroy scene graph.
   */
  void destroyScene();

  /**
   * Get scene.
   */
  NodeSP getScene();

  /**
   * Set scene.
   */
  void setScene(NodeSP scene);

  /**
   * Get camera.
   */
  CameraSP getCamera();

  /**
   * Set camera.
   */
  void setCamera(CameraSP camera);

  /**
   * Enable or disable lighting of render state.
   *
   * Default: enabled
   */
  void setLighting(bool isLightingEnabled);


  /**
   * Check if lighting is enabled.
   */
  bool isLightingEnabled() const;


  /**
   * Set global ambient light of render state.
   */
  void setGlobalAmbientLight(const glm::vec4& globalAmbientLight);

  /**
   * Get information about the scene graph (e.g., number of triangles).
   */
  virtual std::string getInfo();

  /**
   * Render the scene, called by Viewer::startMainLoop().
   */
  virtual void render() = 0;

protected:

  Viewer* viewer_;
  NodeSP scene_;
  CameraSP camera_;
  RenderStateUP renderState_;

};


} /* namespace scg */

#endif /* RENDERER_H_ */
