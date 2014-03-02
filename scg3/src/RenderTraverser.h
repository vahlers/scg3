/**
 * \file RenderTraverser.h
 * \brief A traverser that renders the scene graph (visitor pattern).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef RENDERTRAVERSER_H_
#define RENDERTRAVERSER_H_

#include "Traverser.h"

namespace scg {


class Appearance;
class Camera;
class Shape;
class Light;
class RenderState;


/**
 * \brief A traverser that renders the scene graph (visitor pattern).
 */
class RenderTraverser: public Traverser {

public:

  /**
   * Constructor.
   */
  RenderTraverser(RenderState* renderState);

  /**
   * Destructor.
   */
  virtual ~RenderTraverser();

  // leaf nodes

  /**
   * Visit Shape node: render cores.
   */
  virtual void visitShape(Shape* node);

  // composite nodes

  /**
   * Visit Camera node: apply camera transformation, update model-view
   * matrix of RenderState, render cores.
   */
  virtual void visitCamera(Camera* node);

  /**
   * Visit Camera node after traversing sub-tree: restore model-view
   * matrix of RenderState.
   */
  virtual void visitPostCamera(Camera* node);

  /**
   * Visit Group node: render cores.
   */
  virtual void visitGroup(Group* node);

  /**
   * Visit Group node after traversing sub-tree: restore state.
   */
  virtual void visitPostGroup(Group* node);

  /**
   * Visit Light node: enable light.
   */
  virtual void visitLight(Light* node);

  /**
   * Visit Light node after traversing sub-tree: disable light.
   */
  virtual void visitPostLight(Light* node);

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

#endif /* RENDERTRAVERSER_H_ */
