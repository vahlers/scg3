/**
 * \file Composite.h
 * \brief Base class for all composite nodes, i.e., nodes with children (composite pattern, abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef COMPOSITE_H_
#define COMPOSITE_H_

#include "Node.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief Base class for all composite nodes, i.e., nodes with children (composite pattern, abstract).
 */
class Composite: public Node {

public:

  /**
   * Constructor.
   */
  Composite();

  /**
   * Destructor.
   */
  virtual ~Composite() = 0;

  /**
   * Remove node from scene graph, destroy nodes of sub-tree (if any).
   */
  virtual void destroy();

  /**
   * Add child to composite node.
   * \return this pointer for method chaining
   */
  Composite* addChild(NodeSP child);

  /**
   * Remove child from composite node.
   * \param node pointer to node to be removed
   * \param result true if node has been found and removed
   * \return this pointer for method chaining
   */
  Composite* removeChild(Node* node, bool& result);

  /**
   * Remove child from composite node (ignore result).
   * \return this pointer for method chaining
   */
  Composite* removeChild(Node* node);

  /**
   * Traverse node tree (depth-first, pre-order) with given traverser.
   */
  virtual void traverse(Traverser* traverser);

  /**
   * Accept traverser after traversing sub-tree (visitor pattern).
   */
  virtual void acceptPost(Traverser* traverser);

  /**
   * Render node after traversing sub-tree, e.g., to restore previous state.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  NodeSP leftChild_;

};


} /* namespace scg */

#endif /* COMPOSITE_H_ */
