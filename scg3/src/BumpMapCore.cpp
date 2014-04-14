/**
 * \file BumpMapCore.cpp
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

#include "BumpMapCore.h"
#include "scg_utilities.h"

namespace scg {


BumpMapCore::BumpMapCore()
    : Texture2DCore(), texNormal_(0), texNormalOld_(0) {
}


BumpMapCore::~BumpMapCore() {
  if (isGLContextActive()) {
    glDeleteTextures(1, &texNormal_);
  }
}


BumpMapCoreSP BumpMapCore::create() {
  return std::make_shared<BumpMapCore>();
}


void BumpMapCore::setNormalMap(GLsizei width, GLsizei height, const unsigned char* rgbaData,
    GLenum wrapModeS, GLenum wrapModeT, GLenum minFilter, GLenum magFilter) {
  glActiveTexture(GL_TEXTURE1);
  assert(rgbaData);
  glDeleteTextures(1, &texNormal_);
  glGenTextures(1, &texNormal_);
  glBindTexture(GL_TEXTURE_2D, texNormal_);
  assert(glIsTexture(texNormal_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

  // use anisotropic filtering if supported by graphics driver
  GLfloat maxAnisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

  // transfer texture to GPU memory, generate mipmap if requested, unbind texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);
  if (minFilter == GL_NEAREST_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR ||
      minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_LINEAR_MIPMAP_LINEAR) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);

  assert(!checkGLError());
}


void BumpMapCore::render(RenderState* renderState) {
  // multiply current texture matrix by local texture matrix
  TextureCore::render(renderState);

  if (tex_ != 0) {
    // save texture binding
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &texOld_);

    // bind texture
    assert(glIsTexture(tex_));
    glBindTexture(GL_TEXTURE_2D, tex_);
  }

  // save normal map binding
  glActiveTexture(GL_TEXTURE1);
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &texNormalOld_);

  // bind normal map
  assert(glIsTexture(texNormal_));
  glBindTexture(GL_TEXTURE_2D, texNormal_);
  glActiveTexture(GL_TEXTURE0);

  assert(!checkGLError());
}


void BumpMapCore::renderPost(RenderState* renderState) {
  // restore texture binding
  if (tex_ != 0) {
    glBindTexture(GL_TEXTURE_2D, texOld_);
  }

  // restore normal map binding
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texNormalOld_);
  glActiveTexture(GL_TEXTURE0);

  // restore texture matrix
  TextureCore::renderPost(renderState);

  assert(!checkGLError());
}


} /* namespace scg */
