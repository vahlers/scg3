/**
 * \file GeometryCore.h
 * \brief A core that contains geometry information to be rendered.
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

#ifndef GEOMETRYCORE_H_
#define GEOMETRYCORE_H_

#include <functional>
#include <vector>
#include "scg_glew.h"
#include "Core.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief Draw mode for vertex buffer objects.
 */
enum class DrawMode {
  ARRAYS,
  ELEMENTS
};


/**
 * \brief A core that contains geometry information to be rendered.
 *
 * Vertices and indices are stored in vertex buffer objects (VBOs).
 * Each geometry core has its own vertex array object (VAO) that is used to
 * store attribute and element index bindings.
 */
class GeometryCore: public Core {

public:

  /**
   * Constructor.
   *
   * \param primitiveType GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
   *    GL_TRIANGLES, GL_TRIANGLE_STRIP, or GL_TRIANGLE_FAN
   * \param drawMode DrawMode::ARRAYS or DrawMode::ELEMENTS
   */
  GeometryCore(GLenum primitiveType, DrawMode drawMode);

  /**
   * Destructor.
   */
  virtual ~GeometryCore();

  /**
   * Create shared pointer.
   */
  static GeometryCoreSP create(GLenum primitiveType, DrawMode drawMode);

  /**
   * Add vertex attribute data that is stored in its own vertex buffer object (VBO).
   * \param location attribute location the VBO is bound to
   * \param data attribute data
   * \param size buffer size in bytes
   * \param dim dimension of each attribute value, e.g., 3 for xyz vertices
   * \param usage GL_STATIC_DRAW, GL_DYNAMIC_DRAW, or GL_STREAM_DRAW
   * \return this pointer for method chaining
   */
  GeometryCore* addAttributeData(GLuint location, const GLfloat* data, GLsizeiptr size, GLint dim, GLenum usage);

  /**
   * Set element index data that is stored in its own vertex buffer object (VBO).
   *
   * \param data element data
   * \param size buffer size in bytes
   * \param usage GL_STATIC_DRAW, GL_DYNAMIC_DRAW, or GL_STREAM_DRAW
   * \return this pointer for method chaining
   */
  GeometryCore* setElementIndexData(const GLuint* data, GLsizeiptr size, GLenum usage);

  /**
   * Get approximate number of triangles, called by Shape::getNTriangles().
   */
  int getNTriangles() const;

  /**
   * Render geometry.
   */
  virtual void render(RenderState* renderState);

protected:

  GLenum primitiveType_;
  DrawMode drawMode_;
  std::function<void(GLenum, GLsizei)> drawFunc_;
  GLuint vao_;
  std::vector<GLuint> vboAttributes_;
  GLuint vboIndex_;
  GLsizei nElements_;

};


} /* namespace scg */

#endif /* GEOMETRYCORE_H_ */
