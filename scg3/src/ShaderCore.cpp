/**
 * \file ShaderCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
#ifdef SCG_CPP11_RANGE_BASED_FOR
    for (auto shaderID : shaderIDs_) {
#else
    // iterator fallback
    for (auto it = shaderIDs_.begin(); it < shaderIDs_.end(); ++it) {
      auto shaderID = *it;
#endif
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
#ifdef SCG_CPP11_RANGE_BASED_FOR
  for (auto shaderID : shaderIDs_) {
#else
  // iterator fallback
  for (auto it = shaderIDs_.begin(); it != shaderIDs_.end(); ++it) {
    auto shaderID = *it;
#endif
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
