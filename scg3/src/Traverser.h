/**
 * \file Traverser.h
 * \brief Base class for all traversers (visitor pattern, abstract).
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

#ifndef TRAVERSER_H_
#define TRAVERSER_H_

#include "scg_internals.h"

namespace scg {


/**
 * \brief Base class for all traversers (visitor pattern, abstract).
 */
class Traverser {

public:

  /**
   * Constructor.
   */
  Traverser(RenderState* renderState);

  /**
   * Destructor.
   */
  virtual ~Traverser() = 0;

  // leaf nodes

  /**
   * Visit LightPosition node.
   */
  virtual void visitLightPosition(LightPosition* node);

  /**
   * Visit Shape node.
   */
  virtual void visitShape(Shape* node);

  // composite nodes

  /**
   * Visit Camera node.
   */
  virtual void visitCamera(Camera* node);

  /**
   * Visit Camera node after traversing sub-tree.
   */
  virtual void visitPostCamera(Camera* node);

  /**
   * Visit Group node.
   */
  virtual void visitGroup(Group* node);

  /**
   * Visit Group node after traversing sub-tree.
   */
  virtual void visitPostGroup(Group* node);

  /**
   * Visit Light node.
   */
  virtual void visitLight(Light* node);

  /**
   * Visit Light node after traversing sub-tree.
   */
  virtual void visitPostLight(Light* node);

  /**
   * Visit Transformation node.
   */
  virtual void visitTransformation(Transformation* node);

  /**
   * Visit Transformation node after traversing sub-tree.
   */
  virtual void visitPostTransformation(Transformation* node);

protected:

  RenderState* renderState_;

};


} /* namespace scg */

#endif /* TRAVERSER_H_ */
