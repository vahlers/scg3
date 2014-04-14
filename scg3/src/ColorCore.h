/**
 * \file ColorCore.h
 * \brief A core to set a vertex color or a color transformation to be applied
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

#ifndef COLORCORE_H_
#define COLORCORE_H_

#include "Core.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A core to set a vertex color or a color transformation to be applied
 *    to subsequent geometry.
 */
class ColorCore: public Core {

public:

  /**
   * Constructor.
   */
  ColorCore();

  /**
   * Destructor.
   */
  virtual ~ColorCore();

  /**
   * Create shared pointer.
   */
  static ColorCoreSP create();

  /**
   * Set vertex color.
   * \param color vertex color; for color.w < 0, the vertex color is unset
   * \return this pointer for method chaining
   */
  ColorCore* setColor(glm::vec4 color);

  /**
   * Set color matrix.
   * \return this pointer for method chaining
   */
  ColorCore* setMatrix(glm::mat4 matrix);

  /**
   * Render core, i.e., post-multiply current color matrix by local color matrix
   * and set vertex color (if defined).
   */
  virtual void render(RenderState* renderState);

  /**
   * Render core after traversing sub-tree, i.e., restore previous color matrix.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  bool isColorSet_;
  glm::vec4 color_;
  glm::mat4 matrix_;
  ColorCore* colorCoreOld_;

};


} /* namespace scg */

#endif /* COLORCORE_H_ */
