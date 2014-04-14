/**
 * \file StereoRendererPassive.h
 * \brief A renderer for passive stereo (e.g., polarized projection).
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

#ifndef STEREORENDERERPASSIVE_H_
#define STEREORENDERERPASSIVE_H_

#include <string>
#include "../src/scg_internals.h"
#include "scg_ext_internals.h"
#include "StereoRenderer.h"

namespace scg {


/**
 * \brief A renderer for passive stereo (e.g., polarized projection).
 *
 * Decorator pattern, render() calls concreteRenderer->render().
 */
class StereoRendererPassive: public StereoRenderer {

public:

  /**
   * Constructor.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  StereoRendererPassive(RendererSP concreteRenderer);

  /**
   * Destructor.
   */
  virtual ~StereoRendererPassive();

  /**
   * Create shared pointer.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  static StereoRendererPassiveSP create(RendererSP concreteRenderer);

  /**
   * Render the scene, called by Viewer::startMainLoop().
   * Calls concreteRenderer->render().
   */
  virtual void render();

};


} /* namespace scg */

#endif /* STEREORENDERERPASSIVE_H_ */
