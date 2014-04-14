/**
 * \file CubeMapCore.h
 * \brief Cube map texture core.
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

#ifndef CUBEMAPCORE_H_
#define CUBEMAPCORE_H_

#include <vector>
#include "scg_internals.h"
#include "TextureCore.h"

namespace scg {


/**
 * \brief Cube map textue core.
 *
 * To be used in conjunction with cube map or skybox shader.
 */
class CubeMapCore: public TextureCore {

public:

  /**
   * Constructor.
   */
  CubeMapCore();

  /**
   * Destructor.
   */
  virtual ~CubeMapCore();

  /**
   * Create shared pointer.
   */
  static CubeMapCoreSP create();

  /**
   * Create cube map texture from RGBA images with given parameters.
   *
   * \param width texture width
   * \param height texture height
   * \param rgbaData vector of 6 arrays of RGBA values for textures in directions
   *     +x, -x, +y, -y, +z, -z
   */
  void setCubeMap(GLsizei width, GLsizei height, const std::vector<unsigned char*>& rgbaData);

  /**
   * Render core, i.e., bind texture and post-multiply current texture matrix
   * by local texture matrix.
   * Pass inverse view matrix and skybox matrix (i.e., model-view-projection matrix
   * without camera translation) to shader program.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render core after traversing sub-tree, i.e., restore previous texture matrix
   * and bind previous texture.
   */
  virtual void renderPost(RenderState* renderState);

};


} /* namespace scg */

#endif /* CUBEMAPCORE_H_ */
