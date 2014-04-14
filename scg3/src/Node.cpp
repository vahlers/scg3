/**
 * \file Node.cpp
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

#include <cassert>
#include "Composite.h"
#include "Core.h"
#include "Node.h"

namespace scg {


Node::Node()
  : parent_(nullptr), isVisible_(true) {
}


Node::~Node() {
}


void Node::clear() {
}


void Node::destroy() {
  // remove node from tree
  if(parent_) {
    bool isNodeRemoved = false;
    parent_->removeChild(this, isNodeRemoved);
    assert(isNodeRemoved);
    isNodeRemoved = !isNodeRemoved;   // avoid warning (unused variable) in release build
  }

  // clear (smart) pointers
  rightSibling_.reset();
  parent_ = nullptr;

  // clear node data (if any)
  clear();
}


int Node::getNCores() const {
  return cores_.size();
}


const std::string& Node::getMetaInfo(const std::string& key) const {
  return metaInfo_[key];
}


void Node::setMetaInfo(const std::string& key, const std::string& value) {
  metaInfo_[key] = value;
}


bool Node::isVisible() const{
  return isVisible_;
}


void Node::setVisible(bool isVisible) {
  isVisible_ = isVisible;
}


void Node::accept(Traverser* traverser) {
  // do nothing by default
}


void Node::render(RenderState* renderState) {
  // do nothing by default
}


void Node::addSibling_(NodeSP sibling) {
  assert(sibling);
  if (!rightSibling_) {
    // no right sibling yet, add new sibling
    rightSibling_ = sibling;
    sibling->parent_ = parent_;
  }
  else {
    // add new sibling to right sibling (recursively)
    rightSibling_->addSibling_(sibling);
  }
}


void Node::removeSibling_(Node* node, bool& result) {
  assert(node);
  result = false;
  if (rightSibling_) {
    // check if node to remove is right sibling
    if (node == rightSibling_.get()) {
      // remove right sibling
      rightSibling_ = node->rightSibling_;
      result = true;
    }
    else {
      // search siblings of right sibling for node to remove (recursively)
      rightSibling_->removeSibling_(node, result);
    }
  }
}


void Node::processCores_(RenderState* renderState) {
  // use a forward iterator to access vector from first to last element
  for (auto it = cores_.begin(); it != cores_.end(); ++it) {
    (*it)->render(renderState);
  }
}

void Node::postProcessCores_(RenderState* renderState) {
  // use a reverse iterator to access vector from last to first element
  for (auto rit = cores_.rbegin(); rit != cores_.rend(); ++rit) {
    (*rit)->renderPost(renderState);
  }
}


} /* namespace scg */
