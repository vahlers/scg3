/**
 * \file ShaderCore.h
 * \brief A core to set a shader program to be applied to subsequent nodes.
 *
 * Defines struct:
 *   ShaderID
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

#ifndef SHADERCORE_H_
#define SHADERCORE_H_

#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>
#include "scg_glew.h"
#include "Core.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A shader ID to identify shaders in error messages.
 * An arbitrary name can be added to the OpnGL shader index, e.g., a file name.
 */
struct ShaderID {

  ShaderID()
      : shader(0) {
  }

  ShaderID(GLuint shader0, const std::string& name0)
      : shader(shader0), name(name0) {
  }

  GLuint shader;
  std::string name;

};


/**
 * \brief A core to set a shader program to be applied to subsequent nodes.
 *
 * A few member functions are defined in the header file to allow inlining.
 * Method chaining (via returning this pointers) is not supported to ensure maximum
 * performance.
 */
class ShaderCore: public Core {

public:

  /**
   * Constructor with given program and shaders.
   */
  ShaderCore(GLuint program, const std::vector<ShaderID>& shaderIDs);

  /**
   * Destructor.
   */
  virtual ~ShaderCore();

  /**
   * Delete shaders and program.
   */
  void clear();

  /**
   * Create shared pointer.
   */
  static ShaderCoreSP create(GLuint program, const std::vector<ShaderID>& shaderIDs);

  /**
   * Initialize shader core, i.e., compile shaders and link program,
   * to be called by ShaderCoreFactory or by application after binding
   * custom attribute and fragment data locations.
   */
  void init() const;

  /**
   * Get shader program.
   */
  GLuint getProgram() const;

  /**
   * Get location of uniform variable.
   */
  GLint getUniformLoc(const std::string& name) const {
    assert(program_ != 0);
    auto it = uniformLocMap_.find(name);
    if (it == uniformLocMap_.end()) {
      it = uniformLocMap_.insert(it,
          std::make_pair(name, glGetUniformLocation(program_, name.c_str())));
    }
    return it->second;
  }

  /**
   * Set uniform variable.
   */
  void setUniform1i(const std::string& name, GLint value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform1i(getUniformLoc(name), value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniform1iv(const std::string& name, GLsizei count, const GLint* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform1iv(getUniformLoc(name), count, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniform1f(const std::string& name, GLfloat value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform1f(getUniformLoc(name), value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniform1fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform1fv(getUniformLoc(name), count, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniform2fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform2fv(getUniformLoc(name), count, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniform3fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform3fv(getUniformLoc(name), count, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniform4fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniform4fv(getUniformLoc(name), count, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniformMatrix2fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniformMatrix2fv(getUniformLoc(name), count, GL_FALSE, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniformMatrix3fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniformMatrix3fv(getUniformLoc(name), count, GL_FALSE, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Set uniform variable.
   */
  void setUniformMatrix4fv(const std::string& name, GLsizei count, const GLfloat* value) const {
    // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
    SCG_SAVE_AND_SWITCH_PROGRAM(program_, programOld);
    glUniformMatrix4fv(getUniformLoc(name), count, GL_FALSE, value);
    SCG_RESTORE_PROGRAM(program_, programOld);
  }

  /**
   * Render shader, i.e., bind shader program.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render shader after traversing sub-tree, i.e., restore previous shader program.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  /**
   * Check for compile errors and print error messages.
   */
  void checkCompileError_(const ShaderID& shaderID) const;

  /**
   * Check for link errors and print error messages.
   */
  void checkLinkError_(GLuint program) const;

protected:

  GLuint program_;
  std::vector<ShaderID> shaderIDs_;
  ShaderCore* shaderCoreOld_;
  mutable std::unordered_map<std::string, GLint> uniformLocMap_;

};


} /* namespace scg */

#endif /* SHADERCORE_H_ */
