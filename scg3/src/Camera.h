/**
 * \file Camera.h
 * \brief Base class for all cameras (leaf node, abstract).
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

#ifndef CAMERA_H_
#define CAMERA_H_

#include "scg_glew.h"
#include "scg_glm.h"
#include "scg_internals.h"
#include "Transformation.h"

namespace scg {


/**
 * \brief Base class for all cameras (composite node, abstract).
 *
 * Camera offers transformation functions (partly inherited from Transformation) to
 * change the position and orientation of the camera.
 * It is possible to add further nodes, including shapes, as children of a camera,
 * which will be transformed the same way as the camera itself.
 *
 * If enabled by setDrawCenterMode(), xyz coordinate axes are drawn at the center point,
 * i.e., the center of examination (x red, y green, z blue).
 *
 * Initial parameters:\n
 * - center point distace: 1.0\n
 * - draw center mode: off
 */
class Camera: public Transformation {

public:

  /**
   * Constructor.
   */
  Camera();

  /**
   * Destructor.
   */
  virtual ~Camera();

  /**
   * Get projection matrix.
   */
  virtual const glm::mat4& getProjection();

  /**
   * Get view transformation matrix according to camera position and orientation.
   */
  virtual const glm::mat4& getViewTransform(RenderState* renderState);

  /**
   * Update projection matrix from current viewport dimensions,
   * called by Renderer::render() (or derived class) if window has been resized.
   */
  virtual void updateProjection() = 0;

  /**
   * Get camera position.
   */
  const glm::vec3& getPosition() const;

  /**
   * Set camera position.
   * \return this pointer for method chaining
   */
  Camera* setPosition(const glm::vec3& position);

  /**
   * Get camera orientation as quaternion.
   */
  const glm::quat& getOrientation() const;

  /**
   * Set camera orientation as quaternion.
   * \return this pointer for method chaining
   */
  Camera* setOrientation(const glm::quat& orientation);

  /**
   * Get view direction.
   */
  const glm::vec3& getViewDirection() const;

  /**
   * Get distance to center point.
   */
  GLfloat getCenterDist() const;

  /**
   * Set camera transformation matrix.
   * \return this pointer for method chaining
   */
  virtual Camera* setMatrix(const glm::mat4& matrix);

  /**
   * Translate camera, move center point accordingly.
   * \return this pointer for method chaining
   */
  virtual Camera* translate(glm::vec3 translation);

  /**
   * Rotate camera around given axis (radians).
   * \return this pointer for method chaining
   */
  virtual Camera* rotateRad(GLfloat angleRad, glm::vec3 axis);

  /**
   * Rotate camera around given axis (degrees).
   * \return this pointer for method chaining
   */
  virtual Camera* rotate(GLfloat angleDeg, glm::vec3 axis) {
    return rotateRad(glm::radians(angleDeg), axis);
  }

  /**
   * Ignore scaling (do nothing) for camera transformation.
   * \return this pointer for method chaining
   */
  virtual Camera* scale(glm::vec3 scaling);

  /**
   * Dolly camera in/out, leave center point fixed.
   * \param distance positive for dolly in/forward
   * \return this pointer for method chaining
   */
  Camera* dolly(GLfloat distance);

  /**
   * Rotate camera around center point in azimuth direction.
   * \param angleDeg rotation angle (radians)
   * \return this pointer for method chaining
   */
  Camera* rotateAzimuthRad(GLfloat angleRad);

  /**
   * Rotate camera around center point in azimuth direction.
   * \param angleDeg rotation angle (degrees)
   * \return this pointer for method chaining
   */
  Camera* rotateAzimuth(GLfloat angleDeg) {
    return rotateAzimuthRad(glm::radians(angleDeg));
  }

  /**
   * Rotate camera around center point in elevation direction.
   * \param angleDeg rotation angle (radians)
   * \return this pointer for method chaining
   */
  Camera* rotateElevationRad(GLfloat angleRad);

  /**
   * Rotate camera around center point in elevation direction.
   * \param angleDeg rotation angle (degrees)
   * \return this pointer for method chaining
   */
  Camera* rotateElevation(GLfloat angleDeg) {
    return rotateElevationRad(glm::radians(angleDeg));
  }

  /**
   * Rotate camera around pitch axis.
   * \param angleDeg rotation angle (radians)
   * \return this pointer for method chaining
   */
  Camera* rotatePitchRad(GLfloat angleRad);

  /**
   * Rotate camera around pitch axis.
   * \param angleDeg rotation angle (degrees)
   * \return this pointer for method chaining
   */
  Camera* rotatePitch(GLfloat angleDeg) {
    return rotatePitchRad(glm::radians(angleDeg));
  }

  /**
   * Rotate camera around roll axis.
   * \param angleDeg rotation angle (radians)
   * \return this pointer for method chaining
   */
  Camera* rotateRollRad(GLfloat angleRad);

  /**
   * Rotate camera around roll axis.
   * \param angleDeg rotation angle (degrees)
   * \return this pointer for method chaining
   */
  Camera* rotateRoll(GLfloat angleDeg) {
    return rotateRollRad(glm::radians(angleDeg));
  }

  /**
   * Rotate camera around yaw axis.
   * \param angleDeg rotation angle (radians)
   * \return this pointer for method chaining
   */
  Camera* rotateYawRad(GLfloat angleRad);

  /**
   * Rotate camera around yaw axis.
   * \param angleDeg rotation angle (degrees)
   * \return this pointer for method chaining
   */
  Camera* rotateYaw(GLfloat angleDeg) {
    return rotateYawRad(glm::radians(angleDeg));
  }

  /**
   * Get mode for drawing coordinate axes at center point.
   */
  bool isDrawCenter() const;

  /**
   * Set mode for drawing coordinate axes at center point.
   * \return this pointer for method chaining
   */
  Camera* setDrawCenter(bool isDrawCenter);

  /**
   * Accept traverser (visitor pattern).
   */
  void accept(Traverser* traverser);

  /**
   * Accept traverser after traversing sub-tree (visitor pattern).
   */
  virtual void acceptPost(Traverser* traverser);

  /**
   * Render node, i.e., update model-view matrix of RenderState,
   * draw center point (if enabled).
   */
  virtual void render(RenderState* renderState);

  /**
   * Render transformaton after traversing sub-tree, i.e., restore model-view matrix.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  /**
   * Update direction vectors, center point, transformation matrix, and camera.
   */
  virtual void update_();

protected:

  glm::mat4 projection_;
  glm::mat4 viewTransform_;
  glm::vec3 eyePt_;
  glm::vec3 centerPt_;
  GLfloat centerDist_;
  glm::vec3 viewDir_;
  glm::vec3 upDir_;
  glm::vec3 rightDir_;
  glm::quat orientation_;
  bool isDrawCenter_;

};


} /* namespace scg */

#endif /* CAMERA_H_ */
