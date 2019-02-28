/**
 * \file PerspectiveCamera.h
 * \brief A camera with perspective projection (leaf node).
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

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "scg_glew.h"
#include "Camera.h"

namespace scg {


/**
 * \brief A camera with perspective projection (composite node).
 *
 * See Camera base class for further information.
 *
 * Initial parameters:\n
 * - vertical field of view: 60 deg\n
 * - near distance: 0.01\n
 * - far distance: 1000.0\n
 */
class PerspectiveCamera: public Camera {

public:

  /**
   * Constructor.
   */
  PerspectiveCamera();

  /**
   * Destructor.
   */
  virtual ~PerspectiveCamera();

  /**
   * Create shared pointer.
   */
  static PerspectiveCameraSP create();

  /**
   * Initialize perspective projection.
   * Aspect ratio is determined in updateProjection() from current viewport dimensions.
   *
   * \param fovyDeg vertical field of view angle (degrees)
   * \param near near distance
   * \param far far distance
   */
  void init(GLfloat fovyDeg, GLfloat near, GLfloat far);

  /**
   * Update projection matrix from current viewport dimensions,
   * called by Renderer::render() (or derived class) if window has been resized.
   */
  virtual void updateProjection();

protected:

  GLfloat fovyRad_;
  GLfloat near_;
  GLfloat far_;

};


} /* namespace scg */

#endif /* PERSPECTIVECAMERA_H_ */
