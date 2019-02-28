/**
 * \file RenderState.h
 * \brief The central render state that collects information about the current
 *    shader, transformations, matrix stacks, light and color properties.
 *
 * Defines helper classes:
 *   MatrixStack
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014-2019 Volker Ahlers
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

#ifndef RENDERSTATE_H_
#define RENDERSTATE_H_

#include <cassert>
#include <stack>
#include "scg_glew.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief Matrix stack to store model-view, projection, texture, and color matrices,
 *    used by RenderState.
 *
 * The member functions are defined in the header file to allow inlining.
 */
class MatrixStack {

public:

  MatrixStack() {
    stack_.push(glm::mat4(1.0f));
  }

  const glm::mat4& getMatrix() const {
    assert(!stack_.empty());
    return stack_.top();
  }

  void setMatrix(const glm::mat4& matrix) {
    assert(!stack_.empty());
    stack_.top() = matrix;
  }

  void setIdentity() {
    assert(!stack_.empty());
    stack_.top() = glm::mat4(1.0f);
  }

  void pushMatrix() {
    assert(!stack_.empty());
    stack_.push(stack_.top());
  }

  void pushMatrix(const glm::mat4& matrix) {
    stack_.push(matrix);
  }

  void popMatrix() {
    assert(!stack_.empty());
    stack_.pop();
  }

  void multMatrix(const glm::mat4& matrix) {
    assert(!stack_.empty());
    stack_.top() *= matrix;
  }

protected:

  std::stack<glm::mat4> stack_;

};


/**
 * \brief The central render state that collects information about the current
 *    shader, transformations, matrix stacks, light and color properties.
 *
 * The light properties are stored in a uniform buffer object (UBO).
 * A few member functions are defined in the header file to allow inlining.
 * The matrix stacks are public member variables that are accessed as, e.g.,
 *
 * RenderState* renderState;
 * renderState->modelViewStack.pushMatrix();
 */
class RenderState {

public:

  /**
   * Constructor.
   */
  RenderState();

  /**
   * Destructor.
   */
  virtual ~RenderState();

  /**
   * Inittailize state, create light uniform buffer object (UBO).
   */
  void init();

  /**
   * Get number of active lights.
   */
  int getNLights() const;

  /**
   * Get light uniforma buffer object (UBO).
   */
  GLuint getLightUBO() const;

  /**
   * Get color core.
   */
  ColorCore* getColor();

  /**
   * Set color core.
   */
  void setColor(ColorCore* core);

  /**
   * Get shader core.
   */
  ShaderCore* getShader();

  /**
   * Set shader core.
   */
  void setShader(ShaderCore* core);

  /**
   * Get view transformation that is applied before rendering the scene.
   */
  const glm::mat4& getViewTransform() const {
    return viewTransform_;
  }

  /**
   * Get view transformation that is applied before rendering the scene.
   */
  void setViewTransform(const glm::mat4& viewTransform) {
    viewTransform_ = viewTransform;
  }

  /**
   * Get camera projection that is applied before rendering the scene.
   */
  const glm::mat4& getProjection() const {
    return projection_;
  }

  /**
   * Set camera projection that is applied before rendering the scene.
   */
  void setProjection(const glm::mat4& projection) {
    projection_ = projection;
  }

  /**
   * Get current model-view-projection matrix.
   */
  const glm::mat4& getMVPMatrix() const {
    return tempMatrix_ = projectionStack.getMatrix() * modelViewStack.getMatrix();
  }

  /**
   * Get current model matrix.
   */
  const glm::mat4& getModelMatrix() const {
    return tempMatrix_ = glm::inverse(viewTransform_) * modelViewStack.getMatrix();
  }


  /**
   * Enable or disable lighting (light sources and global ambient light).
   *
   * Default: enabled
   */
  void setLighting(bool isLightingEnabled);


  /**
   * Check if lighting is enabled.
   */
  bool isLightingEnabled() const;


  /**
   * Add light, i.e., increase the number of lights.
   */
  void addLight();

  /**
   * Remove light, i.e., decrease the number of lights.
   */
  void removeLight();

  /**
   * Set global ambient light intensity to be applied independent of light sources.
   */
  void setGlobalAmbientLight(const glm::vec4& globalAmbientLight);

  /**
   * Apply projection and view transformation before rendering the scene,
   * to be called by Renderer.
   */
  void applyProjectionViewTransform();

  /**
   * Pass current modelview, projection, normal, texture, color matrices to shader,
   * to be called before rendering any geometry.
   */
  void passToShader();

public:

  // public member variables are used for efficiency
  MatrixStack modelViewStack;
  MatrixStack projectionStack;
  MatrixStack textureStack;
  MatrixStack colorStack;

protected:

  ColorCore* colorCore_;
  ShaderCore* shaderCore_;
  glm::mat4 projection_;
  glm::mat4 viewTransform_;
  mutable glm::mat4 tempMatrix_;
  bool isLightingEnabled_;
  GLint nLights_;
  GLuint lightUBO_;
  glm::vec4 globalAmbientLight_;

};


} /* namespace scg */

#endif /* RENDERSTATE_H_ */
