/**
 * \file Leaf.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "Leaf.h"

namespace scg {


Leaf::Leaf() {
}


Leaf::~Leaf() {
}


void Leaf::traverse(Traverser* traverser) {
  // check if node is visible
  if (isVisible_) {
    // process node
    accept(traverser);
  }

  // recursively traverse siblings (if any)
  if (rightSibling_) {
    rightSibling_->traverse(traverser);
  }
}


} /* namespace scg */
