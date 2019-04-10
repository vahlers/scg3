/**
 * \file ShaderCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014-2019 Volker Ahlers
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

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "scg_glew.h"
#include <GLFW/glfw3.h>
#include "RenderState.h"
#include "scg_internals.h"
#include "scg_utilities.h"
#include "ShaderCore.h"

namespace scg {


ShaderCore::ShaderCore(GLuint program, const std::vector<ShaderID>& shaderIDs)
    : program_(program), shaderIDs_(shaderIDs), shaderCoreOld_(nullptr) {
}


ShaderCore::~ShaderCore() {
  clear();
}


void ShaderCore::clear() {
  if (isGLContextActive()) {
    glUseProgram(0);
    for (auto shaderID : shaderIDs_) {
      glDeleteShader(shaderID.shader);
    }
    glDeleteProgram(program_);
  }
  shaderIDs_.clear();
  program_ = 0;
}


ShaderCoreSP ShaderCore::create(GLuint program, const std::vector<ShaderID>& shaderIDs) {
  return std::make_shared<ShaderCore>(program, shaderIDs);
}


void ShaderCore::init() const {
  assert(glIsProgram(program_));
  for (auto shaderID : shaderIDs_) {
    assert(glIsShader(shaderID.shader));
    glCompileShader(shaderID.shader);
    checkCompileError_(shaderID);
    glAttachShader(program_, shaderID.shader);
  }
  glLinkProgram(program_);
  checkLinkError_(program_);

  assert(!checkGLError());
}


GLuint ShaderCore::getProgram() const {
  return program_;
}


void ShaderCore::render(RenderState* renderState) {
  shaderCoreOld_ = renderState->getShader();
  renderState->setShader(this);
  assert(glIsProgram(program_));
  glUseProgram(program_);
  setUniform1f(OGLConstants::TIME, static_cast<GLfloat>(glfwGetTime()));
}


void ShaderCore::renderPost(RenderState* renderState) {
  renderState->setShader(shaderCoreOld_);
  if (shaderCoreOld_) {
    glUseProgram(shaderCoreOld_->program_);
  }
  else {
    glUseProgram(0);
  }
}


void ShaderCore::checkCompileError_(const ShaderID& shaderID) const {
  GLint status = GL_TRUE;
  glGetShaderiv(shaderID.shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    const size_t maxLogLength = 1000;
    GLchar infoLog[maxLogLength];
    glGetShaderInfoLog(shaderID.shader, maxLogLength, NULL, infoLog);
    std::stringstream stream;
    stream << "Compilation of shader " << shaderID.shader << " ("
        << shaderID.name << ") failed [ShaderCoreFactory::checkCompileError_()]" << std::endl
        << infoLog << std::ends;
    throw std::runtime_error(stream.str());
  }
}


void ShaderCore::checkLinkError_(GLuint program) const {
  GLint status = GL_TRUE;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    const size_t maxLogLength = 1000;
    GLchar infoLog[maxLogLength];
    glGetProgramInfoLog(program, maxLogLength, NULL, infoLog);
    std::stringstream stream;
    stream << "Linking of program " << program
        << " failed [ShaderCoreFactory::checkLinkError_()]" << std::endl << infoLog << std::ends;
    throw std::runtime_error(stream.str());
  }
}


} /* namespace scg */
