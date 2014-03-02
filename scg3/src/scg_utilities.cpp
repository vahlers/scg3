/**
 * \file scg_utilities.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "scg_glew.h"
#include <GLFW/glfw3.h>
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


void formatFilePath(std::string& filePath) {
#ifdef SCG_CPP11_RANGE_BASED_FOR
  for (char& c : filePath) {
#else
  // iterator fallback
  for (auto it = filePath.begin(); it != filePath.end(); ++it) {
    char& c = *it;
#endif
    if (c == '\\') {
      c = '/';
    }
  }
  if (filePath.back() != '/') {
     filePath += '/';
   }
}


bool isGLContextActive() {
  return glfwGetCurrentContext() != NULL;
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
#ifdef SCG_CPP11_RANGE_BASED_FOR
    for (auto filePath : filePaths) {
#else
    // iterator fallback
    for (auto it = filePaths.begin(); it != filePaths.end(); ++it) {
      auto filePath = *it;
#endif
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

