/**
 * \file Core.h
 * \brief Base class for all cores (abstract).
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

#ifndef CORE_H_
#define CORE_H_

namespace scg {


class RenderState;

/**
 * \brief Base class for all cores (abstract).
 */
class Core {

public:

  /**
   * Constructor.
   */
  Core();

  /**
   * Destructor.
   */
  virtual ~Core() = 0;

  /**
   * Render core.
   */
  virtual void render(RenderState* renderState) = 0;

  /**
   * Render core after traversing sub-tree, e.g., to restore previous state.
   */
  virtual void renderPost(RenderState* renderState);

};


} /* namespace scg */

#endif /* CORE_H_ */
