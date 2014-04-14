/**
 * \file Light.h
 * \brief A light to be applied to all nodes of its sub-tree (composite node).
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

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Composite.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A light to be applied to all nodes of its sub-tree (composite node).
 *
 * The light is applied to all nodes of its sub-tree, its location within
 * the scene graph is thus logical, not physical.
 * The light position is given by the member variable position_, which is
 * multiplied by the current view transformation (but not by the model
 * transformation).
 * A light position according to a location within the scene graph can be
 * defined by means of a LightPosition node.
 *
 * Default parameters:\n
 *   position_ = (0,0,0,1) (point light)\n
 *   ambient_ = (0,0,0,1)\n
 *   diffuse_ = (0,0,0,1)\n
 *   specular = (0,0,0,1)\n
 *   spotCosCutoff = 0 (no spotlight)\n
 *   spotExponent = 0
 */
class Light: public Composite {

public:

  /**
   * Constructor.
   */
  Light();

  /**
   * Destructor.
   */
  virtual ~Light();

  /**
   * Create shared pointer.
   */
  static LightSP create();

  /**
   * Set light position.
   * \param position
   *    light position, with w = 0 for directional light and w = 1 for point light
   * \return this pointer for method chaining
   */
  Light* setPosition(const glm::vec4& position);

  /**
   * Set ambient RGBA color.
   * \return this pointer for method chaining
   */
  Light* setAmbient(const glm::vec4& color);

  /**
   * Set diffuse RGBA color.
   * \return this pointer for method chaining
   */
  Light* setDiffuse(const glm::vec4& color);

  /**
   * Set specular RGBA color.
   * \return this pointer for method chaining
   */
  Light* setSpecular(const glm::vec4& color);

  /**
   * Set diffuse and specular RGBA colors.
   * \return this pointer for method chaining
   */
  Light* setDiffuseAndSpecular(const glm::vec4& color);

  /**
   * Set spot parameters.
   * Note: For the spot to be enabled the light has to be a point light (position_.w = 1.0).
   * \param direction
   *    spot direction vector (need not be normalized)
   * \param cutoffDeg
   *    cutoff angle, half cone opening angle (0 to 90 degrees)
   * \param exponent
   *    attenuation exponent
   * \return this pointer for method chaining
   */
  Light* setSpot(const glm::vec3& direction, float cutoffDeg, float exponent);

  /**
   * Set model transformation from scene graph location,
   * to be called by PreTraverser.
   */
  void setModelTransform(const glm::mat4 modelTransform);

  /**
   * Initialize light, i.e., create UBO.
   */
  void init();

  /**
   * Accept traverser.
   */
  virtual void accept(Traverser* traverser);

  /**
   * Accept traverser after traversing sub-tree.
   */
  virtual void acceptPost(Traverser* traverser);

  /**
   * Render light, i.e., add light to render state and bind UBO.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render light after traversing sub-tree, i.e., remove light from render state.
   */
  virtual void renderPost(RenderState* renderState);

public:

  // parameters for uniform buffer object (UBO)
  static const size_t FLOAT_SIZE = 4;
  static const size_t VEC4_SIZE = 16;
  static const size_t POSITION_OFFSET = 0;
  static const size_t AMBIENT_OFFSET = 16;
  static const size_t DIFFUSE_OFFSET = 32;
  static const size_t SPECULAR_OFFSET = 48;
  static const size_t HALF_VECTOR_OFFSET = 64;
  static const size_t SPOT_DIRECTION_OFFSET = 80;
  static const size_t SPOT_COS_CUTOFF_OFFSET = 96;
  static const size_t SPOT_EXPONENT_OFFSET = 100;
  static const size_t BUFFER_SIZE = 112;

protected:

  GLuint ubo_;          // uniform buffer object
  glm::vec4 position_;
  glm::vec4 ambient_;
  glm::vec4 diffuse_;
  glm::vec4 specular_;
  glm::vec4 spotDirection_;
  float spotCosCutoff_;
  float spotExponent_;
  glm::mat4 modelTransform_;

};


} /* namespace scg */

#endif /* LIGHT_H_ */
