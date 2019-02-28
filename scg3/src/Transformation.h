/**
 * \file Transformation.h
 * \brief A transformation node to be used to appy a transformation to the sub-tree (composite node).
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

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include "scg_glew.h"
#include "Composite.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


class Traverser;


/**
 * \brief A transformation node to be used to appy a transformation to the sub-tree (composite node).
 */
class Transformation: public Composite {

public:

  /**
   * Constructor.
   */
  Transformation();

  /**
   * Destructor.
   */
  virtual ~Transformation();

  /**
   * Create shared pointer.
   */
  static TransformationSP create();

  /**
   * Get transformation matrix.
   */
  const glm::mat4& getMatrix() const;

  /**
   * Set transformation matrix.
   * \return this pointer for method chaining
   */
  virtual Transformation* setMatrix(const glm::mat4& matrix);

  /**
   * Translate subsequent geometry.
   * \param translation tranlation vector
   * \return this pointer for method chaining
   */
  virtual Transformation* translate(glm::vec3 translation);

  /**
   * Rotate subsequent geometry.
   * \param angleDeg rotation angle (radians)
   * \param axis rotaton axis
   * \return this pointer for method chaining
   */
  virtual Transformation* rotateRad(GLfloat angleRad, glm::vec3 axis);

  /**
   * Rotate subsequent geometry.
   * \param angleDeg rotation angle (degrees)
   * \param axis rotaton axis
   * \return this pointer for method chaining
   */
  virtual Transformation* rotate(GLfloat angleDeg, glm::vec3 axis) {
    return rotateRad(glm::radians(angleDeg), axis);
  }

  /**
   * Scale subsequent geometry.
   * \param scaling scale factors in xyz directions
   * \return this pointer for method chaining
   */
  virtual Transformation* scale(glm::vec3 scaling);

  /**
   * Accept traverser (visitor pattern).
   */
  virtual void accept(Traverser* traverser);

  /**
   * Accept traverser after traversing sub-tree (visitor pattern).
   */
  virtual void acceptPost(Traverser* traverser);

  /**
   * Render transformation, i.e., post-multiply current model-view matrix by
   * local matrix.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render transformaton after traversing sub-tree, i.e., restore model-view matrix.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  glm::mat4 matrix_;

};


} /* namespace scg */


#endif /* TRANSFORMATION_H_ */
