/**
 * \file StereoCamera.h
 * \brief A perspective stereo camera (leaf node).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef STEREOCAMERA_H_
#define STEREOCAMERA_H_

#include "../src/scg_glew.h"
#include "../src/Camera.h"
#include "../src/scg_glm.h"
#include "scg_ext_internals.h"

namespace scg {


/**
 * \brief A perspective stereo camera (composite node).
 *
 * Initial parameters (Bourke method):\n
 * - eye factor: -1 (left eye, direction of eye shift on x-axis)\n
 * - vertical field of view: 60 deg\n
 * - near distance: 0.01\n
 * - far distance: 1000.0\n
 * - screen distance: 1.5\n
 * - ratio interocular distance / screen distance: 0.02\n
 */
class StereoCamera: public Camera {

public:

  /**
   * Constructor.
   */
  StereoCamera();

  /**
   * Destructor.
   */
  virtual ~StereoCamera();

  /**
   * Create shared pointer.
   */
  static StereoCameraSP create();

  /**
   * Initialize perspective stereo projection from screen dimensions.
   * Aspect ratio is determined in updateProjection() from current viewport dimensions.
   *
   * \param near near distance
   * \param far far distance
   * \param screenDist screen distance (zero parallax plane)
   * \param screenHeight screen height
   * \param interOcularDist interocular distance
   */
  void init(GLfloat near, GLfloat far, GLfloat screenDist, GLfloat screenHeight,
      GLfloat interOcularDist);

  /**
   * Initialize perspective stereo projection according to Bourke method.
   * Aspect ratio is determined in updateProjection() from current viewport dimensions.
   *
   * Source (modified):\n
   * http://paulbourke.net/miscellaneous/stereographics/stereorender/
   *
   * \param fovyDeg vertical field of view angle (degrees)
   * \param near near distance
   * \param far far distance
   * \param screenDist screen distance (zero parallax plane)
   * \param interOcularFactor ratio interocular distance / screen distance
   */
  void initBourke(GLfloat fovyDeg, GLfloat near, GLfloat far, GLfloat screenDist,
      GLfloat interOcularFactor);

  /**
   * Get projection matrix for current (left or right) eye.
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
  virtual void updateProjection();

  /**
   * Render node, i.e., switch between left and right eye.
   * Calls Camera::render().
   */
  virtual void render(RenderState* renderState);

protected:

  GLint eyeFactor_;
  GLfloat near_;
  GLfloat far_;
  GLfloat screenDist_;
  GLfloat screenHalfWidth_;
  GLfloat screenHalfHeight_;
  GLfloat interOcularHalfDist_;

};


} /* namespace scg */

#endif /* STEREOCAMERA_H_ */
