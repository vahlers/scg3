/**
 * \file Composite.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "Composite.h"

namespace scg {


Composite::Composite() {
}


Composite::~Composite() {
}


void Composite::destroy() {
  // destroy children (if any)
  if (leftChild_) {
    leftChild_->destroy();
  }

  // clear smart pointer
  leftChild_.reset();

  // destroy node
  Node::destroy();
}


Composite* Composite::addChild(NodeSP child) {
  assert(child);
  if (!leftChild_) {
    // no left child yet, add left child
    leftChild_ = child;
    child->parent_ = this;
  }
  else {
    // add new sibling to left child (recursively)
    leftChild_->addSibling_(child);
  }
  return this;
}


Composite* Composite::removeChild(Node* node, bool& result) {
  assert(node);
  result = false;
  if (leftChild_) {
    // check if node to remove is left child
    if (node == leftChild_.get()) {
      // remove left child
      leftChild_ = node->rightSibling_;
      result = true;
    }
    else {
      // search siblings of left child for node to remove (recursively)
      leftChild_->removeSibling_(node, result);
    }
  }
  return this;
}


Composite* Composite::removeChild(Node* node) {
  bool result;
  return removeChild(node, result);
}


void Composite::traverse(Traverser* traverser) {
  // check if node and its sub-tree are visible
  if (isVisible_) {
    // process node
    accept(traverser);

    // recursively traverse children (if any)
    if (leftChild_) {
      leftChild_->traverse(traverser);
    }

    // post-process node
    acceptPost(traverser);
  }

  // recursively traverse siblings (if any)
  if (rightSibling_) {
    rightSibling_->traverse(traverser);
  }
}


void Composite::acceptPost(Traverser* traverser) {
  // do nothing by default
}


void Composite::renderPost(RenderState* renderState) {
  // do nothing by default
}


} /* namespace scg */
