/**
 * \file RenderTraverser.h
 * \brief A traverser that renders the scene graph (visitor pattern).
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
