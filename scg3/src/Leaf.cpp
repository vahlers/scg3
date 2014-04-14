/**
 * \file Leaf.cpp
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
