/**
 * \file MaterialCore.h
 * \brief A core to set material properties for lighting to be applied
 *    to subsequent geometry.
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

#ifndef MATERIALCORE_H_
#define MATERIALCORE_H_

#include "scg_glew.h"
#include "Core.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A core to set material properties for lighting to be applied
 *    to subsequent geometry.
 *
 * The material properties are stored in a uniform buffer object (UBO),
 * which is bound in render().
 */
class MaterialCore: public Core {

public:

  /**
   * Constructor.
   */
  MaterialCore();

  /**
   * Destructor.
   */
  virtual ~MaterialCore();

  /**
   * Create shared pointer.
   */
  static MaterialCoreSP create();

  /**
   * Set emissive RGBA color.
   * \return this pointer for method chaining
   */
  MaterialCore* setEmission(const glm::vec4& color);

  /**
   * Set ambient RGBA color.
   * \return this pointer for method chaining
   */
  MaterialCore* setAmbient(const glm::vec4& color);

  /**
   * Set ambient and diffuse RGBA colors.
   * \return this pointer for method chaining
   */
  MaterialCore* setAmbientAndDiffuse(const glm::vec4& color);

  /**
   * Set diffuse RGBA color.
   * \return this pointer for method chaining
   */
  MaterialCore* setDiffuse(const glm::vec4& color);

  /**
   * Set specular RGBA color.
   * \return this pointer for method chaining
   */
  MaterialCore* setSpecular(const glm::vec4& color);

  /**
   * Set shininess (i.e., specular exponent).
   * \return this pointer for method chaining
   */
  MaterialCore* setShininess(GLfloat shininess);

  /**
   * Initialize material, i.e., create uniform buffer object (UBO).
   */
  void init();

  /**
   * Render material, i.e., bind uniform buffer object (UBO).
   */
  virtual void render(RenderState* renderState);

  /**
   * Render material after traversing sub-tree, i.e., restore previous material state.
   */
  virtual void renderPost(RenderState* renderState);

public:

  // parameters for uniform buffer object (UBO)
  static const size_t FLOAT_SIZE = 4;
  static const size_t VEC4_SIZE = 16;
  static const size_t EMISSION_OFFSET = 0;
  static const size_t AMBIENT_OFFSET = 16;
  static const size_t DIFFUSE_OFFSET = 32;
  static const size_t SPECULAR_OFFSET = 48;
  static const size_t SHININESS_OFFSET = 64;
  static const size_t BUFFER_SIZE = 80;

protected:

  GLuint ubo_;          // uniform buffer object
  GLint uboOld_;
  glm::vec4 emission_;
  glm::vec4 ambient_;
  glm::vec4 diffuse_;
  glm::vec4 specular_;
  GLfloat shininess_;

};


} /* namespace scg */

#endif /* MATERIALCORE_H_ */
