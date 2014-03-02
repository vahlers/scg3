/**
 * \file PreTraverser.h
 * \brief A traverser that searches Camera and LightPosition nodes in the scene graph (visitor pattern).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef PRETRAVERSER_H_
#define PRETRAVERSER_H_

#include "scg_internals.h"
#include "Traverser.h"

namespace scg {


/**
 * \brief A traverser that searches Camera and LightPosition nodes in the scene graph (visitor pattern).
 */
class PreTraverser: public Traverser {

public:

  /**
   * Constructor.
   */
  PreTraverser(RenderState* renderState);

  /**
   * Destructor.
   */
  virtual ~PreTraverser();

  // leaf nodes

  /**
   * Visit LightPosition node: set model tranformation of associated Light.
   */
  virtual void visitLightPosition(LightPosition* node);

  // composite nodes

  /**
   * Visit Camera node: apply camera transformation, update model-view
   * matrix of RenderState, save projection and view tranformation.
   */
  virtual void visitCamera(Camera* node);

  /**
   * Visit Camera node after traversing sub-tree: restore model-view
   * matrix of RenderState.
   */
  virtual void visitPostCamera(Camera* node);

  /**
   * Visit Transformation node: update model-view matrix of RenderState.
   */
  virtual void visitTransformation(Transformation* node);

  /**
   * Visit Transformation node after traversing sub-tree: restore model-view
   * matrix of RenderState.
   */
  virtual void visitPostTransformation(Transformation* node);

};


} /* namespace scg */

#endif /* PRETRAVERSER_H_ */
