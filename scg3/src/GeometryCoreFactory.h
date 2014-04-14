/**
 * \file GeometryCoreFactory.h
 * \brief A factory to create geometry cores.
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

#ifndef GEOMETRYCOREFACTORY_H_
#define GEOMETRYCOREFACTORY_H_

#include <string>
#include <vector>
#include "scg_glew.h"
#include "scg_glm.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A factory to create geometry cores.
 */
class GeometryCoreFactory {

public:

  /**
   * Constructor.
   */
  GeometryCoreFactory();

  /**
   * Constructor with one or more file paths to be searched for model files.
   * More than one file paths can be defined using ';' or ',' as delimiter.
   *
   * Example: addFilePath("../models1;../models2")
   */
  GeometryCoreFactory(const std::string& filePath);

  /**
   * Destructor.
   */
  virtual ~GeometryCoreFactory();

  /**
   * Add one or more file paths to be searched for model files.
   * More than one file paths can be defined using ';' or ',' as delimiter.
   *
   * Example: addFilePath("../textures1;../textures2")
   */
  void addFilePath(const std::string& filePath);

  /**
   * Load model from OBJ Wavefront file.
   *
   * Only the follwoing OBJ tags are used: v, vt, vn, f.
   * If normals are not definied explicitly, they are created separately for each triangle
   * (as in the case of flat shading); no smoothing of normals is applied.
   *
   * \param fileName file name to be searched for in known file paths
   */
  GeometryCoreSP createModelFromOBJFile(const std::string& fileName);

  /**
   * Create rectangle in xy plane with normals, tangents, binormals, and
   * texture coordinates (2 triangles).
   *
   * \param sizeXY edge length in xy directions
   */
  GeometryCoreSP createRectangle(glm::vec2 sizeXY);

  /**
   * Create cube with normals, tangents, binormals, and texture coordinates
   * (12 triangles).
   *
   * \param size edge length
   */
  GeometryCoreSP createCube(GLfloat size);

  /**
   * Create cuboid with normals, tangents, binormals, and texture coordinates
   * (12 triangles).
   *
   * \param sizeXYZ edge length in xyz directions
   */
  GeometryCoreSP createCuboid(glm::vec3 sizeXYZ);

  /**
   * Create sphere centered at origin with normals, tangents,
   * binormals, and texture coordinates
   * (2 * nSlices * nStacks triangles).
   *
   * \param radius sphere radius
   * \param nSlices number of slices, i.e., rectangular faces in longitudinal direction
   * \param nStacks number of stacks, i.e., rectangular faces in latitudinal direction
   */
  GeometryCoreSP createSphere(GLfloat radius, int nSlices, int nStacks);

  /**
   * Create cone along z axis and centered at origin with normals, tangents,
   * binormals, and texture coordinates
   * (2 * nSlices * nStacks triangles for lateral surface plus nSlices triangles for cap).
   *
   * \param radius base radius in xy plane
   * \param height height in z direction
   * \param nSlices number of slices, i.e., rectangular faces in circumference direction
   * \param nStacks number of stacks, i.e., rectangular faces in height direction
   * \param hasCap true if base cap shall be modeled (default: true)
   */
  GeometryCoreSP createCone(GLfloat radius, GLfloat height,
      int nSlices, int nStacks, bool hasCap = true);

  /**
   * Create cylinder along z axis and centered at origin with normals, tangents,
   * binormals, and texture coordinates
   * (2 * nSlices * nStacks triangles for lateral surface plus nSlices triangles per cap).
   *
   * \param radius radius in xy plane
   * \param height height in z direction
   * \param nSlices number of slices, i.e., rectangular faces in circumference direction
   * \param nStacks number of stacks, i.e., rectangular faces in height direction
   * \param hasCaps true if base and top caps shall be modeled (default: true)
   */
  GeometryCoreSP createCylinder(GLfloat radius, GLfloat height,
      int nSlices, int nStacks, bool hasCaps = true);

  /**
   * Create conical frustum (or cylinder for baseRadius = topRadius) along z axis and
   * centered at origin with normals, tangents, binormals, and texture coordinates
   * (2 * nSlices * nStacks triangles for lateral surface plus nSlices triangles per cap).
   * Called by createCone() and createCylinder().
   *
   * \param baseRadius base radius in x and y direction
   * \param topRadius top radius in x and y direction (must be <= baseRadius)
   * \param height height in z direction
   * \param nSlices number of slices, i.e., rectangular faces in circumference direction
   * \param nStacks number of stacks, i.e., rectangular faces in height direction
   * \param hasCaps true if base and top caps shall be modeled (default: true)
   */
  GeometryCoreSP createConicalFrustum(GLfloat baseRadius, GLfloat topRadius,
      GLfloat height, int nSlices, int nStacks, bool hasCaps = true);

  /**
   * Create Utah teapot along z axis and centered at origin with normals, tangents,
   * binormals, and texture coordinates
   * (1024 triangles).
   *
   * Data source: https://cvs.khronos.org/svn/repos/registry/trunk/public/webgl/sdk/demos/google/shiny-teapot/index.html
   *
   * \param size approximate diameter
   */
  GeometryCoreSP createTeapot(GLfloat size);

  /**
   * Create Utah teapot along z axis and centered at origin with normals and texture coordinates
   * (1024 triangles), using a fixed normal per triangle optimal for flat shading.
   *
   * Data source: https://cvs.khronos.org/svn/repos/registry/trunk/public/webgl/sdk/demos/google/shiny-teapot/index.html
   *
   * \param size approximate diameter
   */
  GeometryCoreSP createTeapotFlat(GLfloat size);

  /**
   * Create xyz coordinate axes with vertex colors
   * (3 lines).
   *
   * \param size line length
   */
  GeometryCoreSP createXYZAxes(GLfloat size);

  /**
   * Create RGB cube with vertex colors
   * (12 triangles).
   *
   * \param size edge length
   */
  GeometryCoreSP createRGBCube(GLfloat size);

protected:

  /**
   * A vertex entry of a face definition of an OBJ file.
   */
  struct FaceEntry {
    FaceEntry()
        : vertex(0), texCoord(0), normal(0) {
    }
    int vertex;
    int texCoord;
    int normal;
  };

  /**
   * A face definition of an OBJ file.
   */
  struct Face{
    Face()
        : nTriangles(0) {
    }
    int nTriangles;
    std::vector<FaceEntry> entries;
  };

  /**
   * A model stored in an OBJ file.
   */
  struct OBJModel {
    OBJModel()
        : nVertices(0), nTriangles(0) {
    }
    int nVertices;
    int nTriangles;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<Face> faces;
  };

  /**
   * Load and parse an OBJ Wavefront file and create a model.
   *
   * Only the follwoing OBJ tags are used: v, vt, vn, f.
   * If normals are not definied explicitly, they are created separately for each triangle
   * (as in the case of flat shading); no smoothing of normals is applied.
   */
  int loadOBJFile_(const std::string& fileName, OBJModel& model) const;

protected:

  std::vector<std::string> filePaths_;

};


} /* namespace scg */

#endif /* GEOMETRYCOREFACTORY_H_ */
