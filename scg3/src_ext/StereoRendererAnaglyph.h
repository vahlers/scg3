/**
 * \file StereoRendererAnaglyph.h
 * \brief A renderer for anaglyph stereo (left: red, right: cyan).
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

#ifndef STEREORENDERERANAGLYPH_H_
#define STEREORENDERERANAGLYPH_H_

#include "../src/scg_internals.h"
#include "scg_ext_internals.h"
#include "StereoRenderer.h"

namespace scg {


/**
 * \brief A renderer for anaglyph stereo (left eye: red, right eye: cyan).
 *
 * Decorator pattern, render() calls concreteRenderer->render().
 */
class StereoRendererAnaglyph: public StereoRenderer {

public:

  /**
   * Constructor.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  StereoRendererAnaglyph(RendererSP concreteRenderer);

  /**
   * Destructor.
   */
  virtual ~StereoRendererAnaglyph();

  /**
   * Create shared pointer.
   *
   * \param concreteRenderer concrete renderer to be called by render() (decorator pattern)
   */
  static StereoRendererAnaglyphSP create(RendererSP concreteRenderer);

  /**
   * Render the scene, called by Viewer::startMainLoop().
   * Calls concreteRenderer->render().
   */
  virtual void render();

};


} /* namespace scg */

#endif /* STEREORENDERERANAGLYPH_H_ */
