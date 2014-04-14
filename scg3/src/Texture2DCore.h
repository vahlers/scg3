/**
 * \file Texture2DCore.h
 * \brief 2D texture core.
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

#ifndef TEXTURE2DCORE_H_
#define TEXTURE2DCORE_H_

#include "scg_glew.h"
#include "scg_glm.h"
#include "scg_internals.h"
#include "TextureCore.h"

namespace scg {


/**
 * \brief 2D texture core.
 */
class Texture2DCore: public TextureCore {

public:

  /**
   * Constructor.
   */
  Texture2DCore();

  /**
   * Destructor.
   */
  virtual ~Texture2DCore();

  /**
   * Create shared pointer.
   */
  static Texture2DCoreSP create();

  /**
   * Create texture from RGBA image with given parameters.
   * If minFilter is GL_*_MIPMAP_* (see below), a mipmap is created from the
   * given image.
   *
   * \param width texture width
   * \param height texture height
   * \param rgbaData array of RGBA values
   * \param wrapModeS GL_CLAMP, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
   *    GL_MIRRORED_REPEAT, or GL_REPEAT
   * \param wrapModeT see wrapModeS
   * \param minFilter GL_NEAREST, GL_LINEAR,\n
   *    GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
   *    GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR
   * \param magFilter GL_NEAREST or GL_LINEAR
   */
  void setTexture(GLsizei width, GLsizei height, const unsigned char* rgbaData,
      GLenum wrapModeS, GLenum wrapModeT, GLenum minFilter, GLenum magFilter);

  /**
   * Rotate texture around (0,0,1) axis
   * (post-multiply local texture matrix by transformation).
   *
   * \param angleDeg rotation angle (degrees)
   */
  void rotate2D(GLfloat angleDeg);

  /**
   * Scale texture in s and t direction
   * (post-multiply local texture matrix by transformation).
   *
   * \param scaling scaling factors in s and t direction
   */
  void scale2D(glm::vec2 scaling);

  /**
   * Render core, i.e., bind texture and post-multiply current texture matrix
   * by local texture matrix.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render core after traversing sub-tree, i.e., restore previous texture matrix
   * and bind previous texture.
   */
  virtual void renderPost(RenderState* renderState);

};


} /* namespace scg */

#endif /* TEXTURE2DCORE_H_ */
