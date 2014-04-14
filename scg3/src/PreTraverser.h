/**
 * \file PreTraverser.h
 * \brief A traverser that searches Camera and LightPosition nodes in the scene graph (visitor pattern).
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
