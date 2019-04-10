/**
 * \file scg_utilities.cpp
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
#include <iostream>
#include <map>
#include "scg_internals.h"
#include "scg_utilities.h"

namespace scg {


int checkGLError() {
  int result = 0;
  std::map<GLenum, std::string> messages;
  messages[GL_INVALID_ENUM] = "invalid enum";
  messages[GL_INVALID_VALUE] = "invalid value";
  messages[GL_INVALID_OPERATION] = "invalid operation";
  messages[GL_STACK_OVERFLOW] = "stack overflow";
  messages[GL_STACK_UNDERFLOW] = "stack underflow";
  messages[GL_OUT_OF_MEMORY] = "out of memory";
  messages[GL_INVALID_FRAMEBUFFER_OPERATION] = "invalid framebuffer operation";

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << std::endl << "GL error: " << messages[error] << std::endl;
    result = 1;
  }
  return result;
}


bool isGLContextActive() {
  return glfwGetCurrentContext() != NULL;
}


void getCursorPosPixels(GLFWwindow* window, double& xPixels, double& yPixels) {
  // get window size (screen coords) and framebuffer size (pixels)
  int wScreen, hScreen, wPixels, hPixels;
  glfwGetWindowSize(window, &wScreen, &hScreen);
  glfwGetFramebufferSize(window, &wPixels, &hPixels);
  // get cursor position (screen coords) and transform to pixels
  double xScreen, yScreen;
  glfwGetCursorPos(window, &xScreen, &yScreen);
  xPixels = (xScreen * wPixels) / wScreen;
  yPixels = (yScreen * hPixels) / hScreen;
}


void setCursorPosPixels(GLFWwindow* window, double xPixels, double yPixels) {
  // get window size (screen coords) and framebuffer size (pixels)
  int wScreen, hScreen, wPixels, hPixels;
  glfwGetWindowSize(window, &wScreen, &hScreen);
  glfwGetFramebufferSize(window, &wPixels, &hPixels);
  // set cursor position transformed from pixels to screen coords
  glfwSetCursorPos(window, (xPixels * wScreen) / wPixels, (yPixels * hScreen) / hPixels);
}


void formatFilePath(std::string& filePath) {
  for (char& c : filePath) {
    if (c == '\\') {
      c = '/';
    }
  }
  if (filePath.back() != '/') {
     filePath += '/';
   }
}


std::string getFullFileName(const std::vector<std::string>& filePaths, const std::string& fileName) {
  // first try to open local file, then search known paths
  std::string result;
  std::ifstream istr(fileName.c_str());
  if (istr.is_open()) {
    istr.close();
    result = fileName;
  }
  else {
    for (auto filePath : filePaths) {
      istr.open((filePath + fileName).c_str());
      if (istr.is_open()) {
        istr.close();
        result = filePath + fileName;
        break;
      }
    }
  }
  return result;
}


void printUniformBlockInformation(GLuint program, int nMembers, const GLchar** uniformNames) {
  GLuint* uniformIndices = new GLuint[nMembers];
  glGetUniformIndices(program, nMembers, uniformNames, uniformIndices);
  if (uniformIndices[0] != GL_INVALID_INDEX) {
    GLint* uniformOffsets = new GLint[nMembers];
    glGetActiveUniformsiv(program, nMembers, uniformIndices, GL_UNIFORM_OFFSET, uniformOffsets);
    std::cout << "Uniform block member: index / offset" << std::endl;
    for (int i = 0; i < nMembers; ++i) {
      std::cout << "  " << uniformNames[i] << ": " << uniformIndices[i] << " / " << uniformOffsets[i] << std::endl;
    }
    std::cout << std::endl;
    delete [] uniformOffsets;
    uniformOffsets = nullptr;
  }
  delete [] uniformIndices;
  uniformIndices = nullptr;
}


void splitFilePath(const std::string& filePath, std::vector<std::string>& splitPaths) {
  std::string path;
  size_t length = filePath.length();
  size_t startPos = 0;
  size_t endPos = length;
  while (startPos < length) {
    endPos = filePath.find_first_of(";,", startPos);
    if (endPos == std::string::npos) {
      endPos = length;
    }
    path = filePath.substr(startPos, endPos - startPos);
    formatFilePath(path);
    splitPaths.push_back(path);
    startPos = endPos + 1;
  }
}


} /* namespace scg */

