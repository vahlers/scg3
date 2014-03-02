/**
 * \file Transformation.h
 * \brief A transformation node to be used to appy a transformation to the sub-tree (composite node).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
   * \param angleDeg rotation angle (degrees)
   * \param axis rotaton axis
   * \return this pointer for method chaining
   */
  virtual Transformation* rotate(GLfloat angleDeg, glm::vec3 axis);

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