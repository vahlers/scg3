/**
 * \file Texture2DCore.cpp
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

#include <cassert>
#include "RenderState.h"
#include "scg_utilities.h"
#include "Texture2DCore.h"

namespace scg {


Texture2DCore::Texture2DCore()
    : TextureCore() {
}


Texture2DCore::~Texture2DCore() {
  if (isGLContextActive()) {
    glDeleteTextures(1, &tex_);
  }
}


Texture2DCoreSP Texture2DCore::create() {
  return std::make_shared<Texture2DCore>();
}


void Texture2DCore::setTexture(GLsizei width, GLsizei height, const unsigned char* rgbaData,
    GLenum wrapModeS, GLenum wrapModeT, GLenum minFilter, GLenum magFilter) {
  assert(rgbaData);
  glDeleteTextures(1, &tex_);
  glGenTextures(1, &tex_);
  glBindTexture(GL_TEXTURE_2D, tex_);
  assert(glIsTexture(tex_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

  // use anisotropic filtering
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

  assert(!checkGLError());
}


void Texture2DCore::rotate2D(GLfloat angleDeg) {
  rotate(angleDeg, glm::vec3(0.f, 0.f, 1.f));
}


void Texture2DCore::scale2D(glm::vec2 scaling) {
  scale(glm::vec3(scaling, 1.f));
}


void Texture2DCore::render(RenderState* renderState) {
  // multiply current texture matrix by local texture matrix
  TextureCore::render(renderState);

  // save texture binding
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &texOld_);

  // bind texture
  assert(glIsTexture(tex_));
  glBindTexture(GL_TEXTURE_2D, tex_);

  assert(!checkGLError());
}


void Texture2DCore::renderPost(RenderState* renderState) {
  // restore texture binding
  glBindTexture(GL_TEXTURE_2D, texOld_);

  // restore texture matrix
  TextureCore::renderPost(renderState);

  assert(!checkGLError());
}


} /* namespace scg */
