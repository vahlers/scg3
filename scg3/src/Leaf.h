/**
 * \file Leaf.h
 * \brief Base class for all leaf nodes, i.e., nodes without children (composite pattern, abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef LEAF_H_
#define LEAF_H_

#include "Node.h"

namespace scg {


/**
 * \brief Base class for all leaf nodes, i.e., nodes without children (composite pattern, abstract).
 */
class Leaf: public Node {

public:

  /**
   * Constructor.
   */
  Leaf();

  /**
   * Destructor.
   */
  virtual ~Leaf() = 0;

  /**
   * Traverse node tree (depth-first, pre-order) with given traverser.
   */
  virtual void traverse(Traverser* traverser);

};


} /* namespace scg */

#endif /* LEAF_H_ */
