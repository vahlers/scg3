/**
 * \file scg_internals.cpp
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
#include <sstream>
#include "scg_internals.h"
#include "scg_utilities.h"

namespace scg {


const OGLAttrib OGLConstants::VERTEX = { "vVertex", 0 };
const OGLAttrib OGLConstants::COLOR = { "vColor", 1 };
const OGLAttrib OGLConstants::NORMAL = { "vNormal", 2 };
const OGLAttrib OGLConstants::TEX_COORD_0 = { "vTexCoord0", 3 };
const OGLAttrib OGLConstants::TEX_COORD_1 = { "vTexCoord1", 4 };
const OGLAttrib OGLConstants::TANGENT = { "vTangent", 5 };
const OGLAttrib OGLConstants::BINORMAL = { "vBinormal", 6 };

const OGLFragData OGLConstants::FRAG_COLOR = { "fragColor", 0 };

const OGLUniformBlock OGLConstants::LIGHT = { "LightBlock", 0 };
const OGLUniformBlock OGLConstants::MATERIAL = { "MaterialBlock", 1 };

const char* OGLConstants::MODEL_VIEW_MATRIX = "modelViewMatrix";
const char* OGLConstants::PROJECTION_MATRIX = "projectionMatrix";
const char* OGLConstants::MVP_MATRIX = "mvpMatrix";
const char* OGLConstants::NORMAL_MATRIX = "normalMatrix";
const char* OGLConstants::TEXTURE_MATRIX = "textureMatrix";
const char* OGLConstants::COLOR_MATRIX = "colorMatrix";
const char* OGLConstants::N_LIGHTS = "nLights";
const char* OGLConstants::GLOBAL_AMBIENT_LIGHT = "globalAmbientLight";
const char* OGLConstants::TIME = "time";

const OGLSampler OGLConstants::TEXTURE0 = { "texture0", 0 };
const OGLSampler OGLConstants::TEXTURE1 = { "texture1", 1 };


void OGLConstants::bindAttribFragDataLocations(GLuint program) {
  glBindAttribLocation(program, VERTEX.location, VERTEX.name);
  glBindAttribLocation(program, COLOR.location, COLOR.name);
  glBindAttribLocation(program, NORMAL.location, NORMAL.name);
  glBindAttribLocation(program, TEX_COORD_0.location, TEX_COORD_0.name);
  glBindAttribLocation(program, TEX_COORD_1.location, TEX_COORD_1.name);
  glBindAttribLocation(program, TANGENT.location, TANGENT.name);
  glBindAttribLocation(program, BINORMAL.location, BINORMAL.name);

  glBindFragDataLocation(program, FRAG_COLOR.location, FRAG_COLOR.name);

  assert(!checkGLError());
}


void OGLConstants::bindUniformBlocks(GLuint program) {
  GLuint lightIndex = glGetUniformBlockIndex(program, LIGHT.name);
  if (lightIndex != GL_INVALID_INDEX) {
    glUniformBlockBinding(program, lightIndex, LIGHT.bindingPoint);
  }
  GLuint materialIndex = glGetUniformBlockIndex(program, MATERIAL.name);
  if (materialIndex != GL_INVALID_INDEX) {
    glUniformBlockBinding(program, materialIndex, MATERIAL.bindingPoint);
  }

  assert(!checkGLError());
}


void OGLConstants::bindSamplers(GLuint program) {
  // glProgramUniform() is not used in order to keep OpenGL 3.2 compatibility
  SCG_SAVE_AND_SWITCH_PROGRAM(program, programOld);
  glUniform1i(glGetUniformLocation(program, TEXTURE0.name), TEXTURE0.texUnit);
  glUniform1i(glGetUniformLocation(program, TEXTURE1.name), TEXTURE1.texUnit);
  SCG_RESTORE_PROGRAM(program, programOld);

  assert(!checkGLError());
}


}
