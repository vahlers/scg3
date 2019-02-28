/**
 * \file scg_utilities.h
 * \brief Utility functions that are used by different classes.
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

#ifndef SCG_UTILITIES_H_
#define SCG_UTILITIES_H_

#include <string>
#include <vector>
#include "scg_glew.h"
#include <GLFW/glfw3.h>

namespace scg {


/**
 * Pi constant.
 */
const float PI = 3.141592654f;


/**
 * \brief Check if an OpenGL error has occured since last call of checkGLError().
 *
 * Can be used via assert(!checkGLError()) in order to get information on code file and line.
 *
 * \return 0 for no error, 1 for error
 */
int checkGLError();


/**
 * \brief Check if an active OpenGL context exists.
 *
 * Should be used in destructors to check for an active context before calling OpenGL functions.
 * Otherwise exceptions thrown without an active context will cause errors.
 *
 * \return true if active OpenGL context exists
 */
bool isGLContextActive();


/**
 * \brief Get cursor (mouse pointer) position in pixels, as opposed to screen coordinates.
 *
 * Wrapper function for glfwGetCursorPos, which returns screen coordinates.
 * The factor for converting from screen coordinates to pixels may change at runtime, e.g.
 * by moving a window from a low-resolution to a high-resolution ("retina") display.
 */
void getCursorPosPixels(GLFWwindow* window, double& xPixels, double& yPixels);


/**
 * \brief Set cursor (mouse pointer) position in pixels, as opposed to screen coordinates.
 *
 * Wrapper function for glfwSetCursorPos, which returns screen coordinates.
 * The factor for converting from screen coordinates to pixels may change at runtime, e.g.
 * by moving a window from a low-resolution to a high-resolution ("retina") display.
 */
void setCursorPosPixels(GLFWwindow* window, double xPixels, double yPixels);


/**
 * \brief Replace backslashes by slashes and ensure that the last character is a slash.
 */
void formatFilePath(std::string& filePath);


/**
 * \brief Try to find file name in a list of file paths.
 *
 * The local directory is searched first.
 *
 * \return full file name including path, empty string if the file has not been found
 */
std::string getFullFileName(const std::vector<std::string>& filePaths, const std::string& fileName);


/**
 * \brief Print information about uniform blocks in shaders.
 */
void printUniformBlockInformation(GLuint program, int nMembers, const GLchar** uniformNames);


/**
 * \brief Split string containing one or more file paths into a vector of single paths.
 *
 * Allowed delimiters: ';' and ','.
 *
 * For each split path formatFilePath() is called.
 */
void splitFilePath(const std::string& filePath, std::vector<std::string>& splitPaths);


} /* namespace scg */

#endif /* SCG_UTILITIES_H_ */
