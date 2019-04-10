/**
 * \file ShaderCoreFactory.cpp
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

#include <fstream>
#include <stdexcept>
#include "scg_internals.h"
#include "ShaderCore.h"
#include "ShaderCoreFactory.h"
#include "scg_utilities.h"

namespace scg {


ShaderCoreFactory::ShaderCoreFactory() {
}


ShaderCoreFactory::ShaderCoreFactory(const std::string& filePath) {
  addFilePath(filePath);
}


ShaderCoreFactory::~ShaderCoreFactory() {
}


void ShaderCoreFactory::addFilePath(const std::string& filePath) {
  assert(!filePath.empty());
  splitFilePath(filePath, filePaths_);
}


ShaderCoreSP ShaderCoreFactory::createColorShader() {
  // create program and shader vector
  GLuint program = glCreateProgram();
  assert(glIsProgram(program));
  std::vector<ShaderID> shaderIDs;

  // create vertex shader
  const char* sourceVert = "\
      #version 150 \n\
      in vec4 vVertex; \n\
      in vec4 vColor; \n\
      uniform mat4 mvpMatrix; \n\
      smooth out vec4 color; \n\
      void main() { \n\
        gl_Position = mvpMatrix * vVertex; \n\
        color = vColor; \n\
      } \n\
      ";

  GLuint shaderVert = glCreateShader(GL_VERTEX_SHADER);
  assert(glIsShader(shaderVert));
  shaderIDs.push_back(ShaderID(shaderVert, "color vertex shader"));
  glShaderSource(shaderVert, 1, &sourceVert, 0);

  // create fragment shader
  const char* sourceFrag = "\
      #version 150 \n\
      smooth in vec4 color; \n\
      out vec4 fragColor; \n\
      void main(void) { \n\
        fragColor = color; \n\
      } \n\
      ";

  GLuint shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
  assert(glIsShader(shaderFrag));
  shaderIDs.push_back(ShaderID(shaderFrag, "color fragment shader"));
  glShaderSource(shaderFrag, 1, &sourceFrag, 0);

  // bind standard attribute and fragment data locations
  OGLConstants::bindAttribFragDataLocations(program);

  // compile shaders and link program
  auto core = ShaderCore::create(program, shaderIDs);
  core ->init();

  assert(!checkGLError());

  return core;
}


ShaderCoreSP ShaderCoreFactory::createGouraudShader() {
  // create program and shader vector
  GLuint program = glCreateProgram();
  assert(glIsProgram(program));
  std::vector<ShaderID> shaderIDs;

  // create vertex shader
  const char* sourceVert = "\
      #version 150 \n\
      in vec4 vVertex; \n\
      in vec3 vNormal; \n\
      uniform mat4 modelViewMatrix; \n\
      uniform mat4 projectionMatrix; \n\
      uniform mat4 mvpMatrix; \n\
      uniform mat3 normalMatrix; \n\
      const int MAX_NUMBER_OF_LIGHTS = 10; \n\
      struct Light { \n\
        vec4 position; \n\
        vec4 ambient; \n\
        vec4 diffuse; \n\
        vec4 specular; \n\
        vec4 halfVector; \n\
        vec4 spotDirection; \n\
        float spotCosCutoff; \n\
        float spotExponent; \n\
      }; \n\
      layout(std140) uniform LightBlock { \n\
        Light lights[MAX_NUMBER_OF_LIGHTS]; \n\
      }; \n\
      struct Material { \n\
        vec4 emission; \n\
        vec4 ambient; \n\
        vec4 diffuse; \n\
        vec4 specular; \n\
        float shininess; \n\
      }; \n\
      layout(std140) uniform MaterialBlock { \n\
        Material material; \n\
      }; \n\
      smooth out vec4 color; \n\
      void main() { \n\
        vec3 ecVertex = (modelViewMatrix * vVertex).xyz; \n\
        vec3 ecNormal = normalMatrix * vNormal; \n\
        vec3 v = normalize(-ecVertex); \n\
        vec3 n = normalize(ecNormal); \n\
        vec3 s = normalize(lights[0].position.xyz - ecVertex); \n\
        vec3 h = normalize(v + s); \n\
        color = material.emission + material.ambient * lights[0].ambient; \n\
        float sDotN = max(0., dot(s, n)); \n\
        color += material.diffuse * lights[0].diffuse * sDotN; \n\
        float hDotN = dot(h, n); \n\
        if (hDotN > 0.) { \n\
          color += material.specular * lights[0].specular * pow(hDotN, material.shininess); \n\
        } \n\
        gl_Position = mvpMatrix * vVertex; \n\
      } \n\
      ";

  GLuint shaderVert = glCreateShader(GL_VERTEX_SHADER);
  assert(glIsShader(shaderVert));
  shaderIDs.push_back(ShaderID(shaderVert, "Gouraud vertex shader"));
  glShaderSource(shaderVert, 1, &sourceVert, 0);

  // create fragment shader
  const char* sourceFrag = "\
      #version 150 \n\
      smooth in vec4 color; \n\
      out vec4 fragColor; \n\
      void main(void) { \n\
        fragColor = clamp(color, 0., 1.); \n\
      } \n\
      ";

  GLuint shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
  assert(glIsShader(shaderFrag));
  shaderIDs.push_back(ShaderID(shaderFrag, "Gouraud fragment shader"));
  glShaderSource(shaderFrag, 1, &sourceFrag, 0);

  // bind standard attribute and fragment data locations
  OGLConstants::bindAttribFragDataLocations(program);

  // compile shaders and link program
  auto core = ShaderCore::create(program, shaderIDs);
  core ->init();

  // bind standard uniform blocks
  OGLConstants::bindUniformBlocks(program);

  assert(!checkGLError());

  return core;
}


ShaderCoreSP ShaderCoreFactory::createShaderFromSourceFiles(
    const std::vector<ShaderFile>& shaderFiles) {
  // create program and shader vector
  GLuint program = glCreateProgram();
  assert(glIsProgram(program));
  std::vector<ShaderID> shaderIDs;

  // load shaders from source files
  for (auto shaderFile : shaderFiles) {
    GLuint shader = glCreateShader(shaderFile.shaderType);
    assert(glIsShader(shader));
    shaderIDs.push_back(ShaderID(shader, shaderFile.fileName));
    int error = loadSourceFile_(shader, shaderFile.fileName);
    if (error != 0) {
      throw std::runtime_error("cannot open file " + shaderFile.fileName
          + " [ShaderCoreFactory::createShaderFromSourceFiles()]");
    }
  }

  // bind standard attribute and fragment data locations
  OGLConstants::bindAttribFragDataLocations(program);

  // compile shaders and link program
  auto core = ShaderCore::create(program, shaderIDs);
  core ->init();

  // bind standard uniform blocks and sampler texture units
  OGLConstants::bindUniformBlocks(program);
  OGLConstants::bindSamplers(program);

  assert(!checkGLError());

  return core;
}


ShaderCoreSP ShaderCoreFactory::createShaderFromSourceFiles(
    std::vector<ShaderFile>&& shaderFiles) {
  std::vector<ShaderFile> shaderFilesVec = std::move(shaderFiles);
  return createShaderFromSourceFiles(shaderFilesVec);
}


int ShaderCoreFactory::loadSourceFile_(GLuint shader, const std::string& fileName) const {
  int error = 0;

  do {
    // try to find file
    std::string fullFileName = getFullFileName(filePaths_, fileName);
    if (fullFileName.empty()) {
      error = 1;
      break;
    }
    std::ifstream istr(fullFileName);
    if (!istr.is_open()) {
      error = 1;
      break;
    }

    // read shader source
    char line[1024];
    std::vector<std::string> sourceVec;
    while (istr.getline(line, 1024)) {
      sourceVec.push_back(std::string(line) + '\n');
    }
    istr.close();

    // pass shader source to OpenGL
    const GLchar** source = new const GLchar*[sourceVec.size()];
    for (unsigned int i = 0; i < sourceVec.size(); i++) {
      source[i] = reinterpret_cast<const GLchar*>(sourceVec[i].c_str());
    }
    assert(glIsShader(shader));
    glShaderSource(shader, sourceVec.size(), source, NULL);
    delete[] source;
    source = 0;
  } while (false);

  return error;
}


} /* namespace scg */
