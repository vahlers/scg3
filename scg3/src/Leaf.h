/**
 * \file Leaf.h
 * \brief Base class for all leaf nodes, i.e., nodes without children (composite pattern, abstract).
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
