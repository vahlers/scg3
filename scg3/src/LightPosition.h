/**
 * \file LightPosition.h
 * \brief A light position node to define the position of an associated light
 *    within the scene graph (leaf node).
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

#ifndef LIGHTPOSITION_H_
#define LIGHTPOSITION_H_


#include "Leaf.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A light position node to define the position of an associated light
 *    within the scene graph (leaf node).
 *
 * Light defines the logical position of a light source (i.e., which sub-tree
 * of the scene graph the light is applied to), while LightPosition defines its
 * physical position within the transformation hierarchy.
 */
class LightPosition: public Leaf {

public:

  /**
   * Constructor with associated Light.
   */
  LightPosition(LightSP light);

  /**
   * Destructor.
   */
  virtual ~LightPosition();

  /**
   * Create shared pointer.
   */
  static LightPositionSP create(LightSP light);

  /**
   * Get associated Light.
   */
  LightSP getLight();

  /**
   * Set associated Light.
   * \return this pointer for method chaining
   */
  LightPosition* setLight(LightSP light);

  /**
   * Accept traverser (visitor pattern).
   */
  void accept(Traverser* traverser);

protected:

  LightSP light_;

};


} /* namespace scg */

#endif /* LIGHTPOSITION_H_ */
