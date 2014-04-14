/**
 * \file TextureCore.h
 * \brief Base class for all texture cores (abstract).
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

#ifndef TEXTURECORE_H_
#define TEXTURECORE_H_

#include "scg_glew.h"
#include "Core.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief Base class for all texture cores (abstract).
 */
class TextureCore: public Core {

public:

  /**
   * Constructor.
   */
  TextureCore();

  /**
   * Destructor.
   */
  virtual ~TextureCore() = 0;

  /**
   * Rotate texture (post-multiply local texture matrix by transformation).
   * \param angleDeg rotation angle (degrees)
   * \param axis rotation axis
   * \return this pointer for method chaining
   */
  TextureCore* rotate(GLfloat angleDeg, glm::vec3 axis);

  /**
   * Scale texture (post-multiply local texture matrix by transformation).
   * \param scaling scaling factors in s, t, and u directions
   * \return this pointer for method chaining
   */
  TextureCore* scale(glm::vec3 scaling);

  /**
   * Set texture matrix.
   * \return this pointer for method chaining
   */
  TextureCore* setMatrix(glm::mat4 matrix);

  /**
   * Render core, i.e., post-multiply current texture matrix by local texture matrix.
   * Note: Derived classes must call this function at the beginning of their render() function.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render core after traversing sub-tree, i.e., restore previous texture matrix.
   * Note: Derived classes must call this function at the end of their render() function.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  GLuint tex_;
  GLint texOld_;
  glm::mat4 matrix_;
};


} /* namespace scg */

#endif /* TEXTURECORE_H_ */
