/**
 * \file CubeMapCore.cpp
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

#include <cassert>
#include "CubeMapCore.h"
#include "RenderState.h"
#include "scg_utilities.h"
#include "ShaderCore.h"

namespace scg {


CubeMapCore::CubeMapCore()
    : TextureCore() {
}


CubeMapCore::~CubeMapCore() {
  if (isGLContextActive()) {
    glDeleteTextures(1, &tex_);
  }
}


CubeMapCoreSP CubeMapCore::create() {
  return std::make_shared<CubeMapCore>();
}


void CubeMapCore::setCubeMap(GLsizei width, GLsizei height, const std::vector<unsigned char*>& rgbaData) {
  assert(rgbaData.size() == 6);
  glDeleteTextures(1, &tex_);
  glGenTextures(1, &tex_);
  glBindTexture(GL_TEXTURE_CUBE_MAP, tex_);
  assert(glIsTexture(tex_));
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // use anisotropic filtering
  GLfloat maxAnisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

  // transfer textures to GPU memory
  const GLenum cubeMapTexNames[] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  };
  for (int i = 0; i < 6; ++i) {
    assert(rgbaData[i]);
    glTexImage2D(cubeMapTexNames[i], 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData[i]);
  }
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  assert(!checkGLError());
}


void CubeMapCore::render(RenderState* renderState) {
  // multiply current texture matrix by local texture matrix
  TextureCore::render(renderState);

  // save texture binding
  glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &texOld_);

  // bind texture
  assert(glIsTexture(tex_));
  glBindTexture(GL_TEXTURE_CUBE_MAP, tex_);

  // pass inverse view matrix and skybox matrix (i.e., model-view-projection matrix
  // without camera translation) to shader program
  glm::mat4 viewMatrix = renderState->getViewTransform();
  renderState->getShader()->setUniformMatrix4fv("invViewMatrix", 1, glm::value_ptr(glm::inverse(viewMatrix)));
  viewMatrix[3] = glm::vec4(0.f, 0.f, 0.f, 1.f);
  glm::mat4 skyboxMatrix = renderState->projectionStack.getMatrix() * viewMatrix * renderState->getModelMatrix();
  renderState->getShader()->setUniformMatrix4fv("skyboxMatrix", 1, glm::value_ptr(skyboxMatrix));

  assert(!checkGLError());
}


void CubeMapCore::renderPost(RenderState* renderState) {
  // restore texture binding
  glBindTexture(GL_TEXTURE_CUBE_MAP, texOld_);

  // restore texture matrix
  TextureCore::renderPost(renderState);

  assert(!checkGLError());
}


} /* namespace scg */
