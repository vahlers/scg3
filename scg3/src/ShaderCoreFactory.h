/**
 * \file ShaderCoreFactory.h
 * \brief A factory to create shader cores.
 *
 * Defines struct:
 *   ShaderFile
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

#ifndef SHADERCOREFACTORY_H_
#define SHADERCOREFACTORY_H_

#include <string>
#include <vector>
#include "scg_glew.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A shader file consisting of a file name and a shader type (GL_VERTEX_SHADER,
   *    GL_FRAGMENT_SHADER, or GL_GEOMETRY_SHADER), to be used by ShaderCoreFactory.
 */
struct ShaderFile {
  ShaderFile(const std::string& fileName0, GLenum shaderType0) :
    fileName(fileName0), shaderType(shaderType0) {
  }

  std::string fileName;
  GLenum shaderType;
};


/**
 * \brief A factory to create shader cores.
 */
class ShaderCoreFactory {

public:

  /**
   * Constructor.
   */
  ShaderCoreFactory();

  /**
   * Constructor with one or more file paths to be searched for shader files.
   * More than one file paths can be defined using ';' or ',' as delimiter.
   *
   * Example: addFilePath("../shaders1;../shaders2")
   */
  ShaderCoreFactory(const std::string& filePath);

  /**
   * Destructor.
   */
  virtual ~ShaderCoreFactory();

  /**
   * Add one or more file paths to be searched for shader files.
   * More than one file paths can be defined using ';' or ',' as delimiter.
   *
   * Example: addFilePath("../shaders1;../shaders2")
   */
  void addFilePath(const std::string& filePath);

  /**
   * Create a simple shader program without lighting.
   *
   * attributes: vVertex, vColor\n
   * uniforms: mvpMatrix
   */
  ShaderCoreSP createColorShader();

  /**
   * Create a simple shader program with Gouraud shading for a single light
   * without texturing.
   *
   * attributes: vVertex, vNormal\n
   * uniforms: modelViewMatrix, projectionMatrix, mvpMatrix, normalMatrix\n
   * UBOs: LightBlock, MaterialBlock
   */
  ShaderCoreSP createGouraudShader();

  /**
   * Load shaders from source files, compile, and link to create a shader program.
   * \param shaderFiles vector of shader files, each consisting of a file name (to be
   *    searched for in known file paths) and a shader type (GL_VERTEX_SHADER,
   *    GL_FRAGMENT_SHADER, or GL_GEOMETRY_SHADER).
   */
  ShaderCoreSP createShaderFromSourceFiles(
      const std::vector<ShaderFile>& shaderFiles);

  /**
   * Load shaders from source files, compile, and link to create a shader program.
   * \param shaderFiles vector of shader files, each consisting of a file name (to be
   *    searched for in known file paths) and a shader type (GL_VERTEX_SHADER,
   *    GL_FRAGMENT_SHADER, or GL_GEOMETRY_SHADER).
   */
  ShaderCoreSP createShaderFromSourceFiles(
      std::vector<ShaderFile>&& shaderFiles);

protected:

  /**
   * Load shader from source file.
   *
   * \param shader index the shader shall be attached to
   * \param fileName file name to be searched for in known file paths
   */
  int loadSourceFile_(GLuint shader, const std::string& fileName) const;

protected:

  std::vector<std::string> filePaths_;

};


} /* namespace scg */

#endif /* SHADERCOREFACTORY_H_ */
