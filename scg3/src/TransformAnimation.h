/**
 * \file TransformAnimation.h
 * \brief An animation that creates a transformation to be applied to ist sub-tree (composite node).
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

#ifndef TRANSFORMANIMATION_H_
#define TRANSFORMANIMATION_H_

#include <functional>
#include "scg_glew.h"
#include "Animation.h"
#include "scg_glm.h"
#include "scg_internals.h"
#include "Transformation.h"

namespace scg {


/**
 * \brief An animation that creates a transformation to be applied to its sub-tree (composite node).
 *
 * The update function can be set as a function object for a global function, a member function
 * (method) of a class, or a lambda function.
 *
 * Example (lambda function):
 *
 * \code
 * auto myAnimation = TransformAnimation::create();
 * float angularVel = 50.f;
 * glm::vec3 axis(1.f, 0.f, 0.f);
 * myAnimation->setUpdateFunc(
 *     [angularVel, axis](TransformAnimation* animation,
 *                        double currTime, double diffTime, double totalTime) {
 *       animation->rotate(angularVel * static_cast<GLfloat>(diffTime), axis);
 *     });
 *
 * aNode->addChild(myAnimation);
 * myAnimation->addChild(anotherNode);
 *
 * myViewer.addAnimation(myAnimation);
 * myViewer.startAnimations();
 * \endcode
 */
class TransformAnimation: public Animation, public Transformation {

public:

  /**
   * Constructor.
   */
  TransformAnimation();

  /**
   * Destructor.
   */
  virtual ~TransformAnimation();

  /**
   * Create shared pointer.
   */
  static TransformAnimationSP create();

  /**
   * Get parameter.
   */
  GLfloat getFloatParam() const;

  /**
   * Set parameter to be used by animation function.
   * \return this pointer for method chaining
   */
  TransformAnimation* setFloatParam(GLfloat param);

  /**
   * Get parameter.
   */
  const glm::vec3& getVec3Param() const;

  /**
   * Set parameter to be used by animation function.
   * \return this pointer for method chaining
   */
  TransformAnimation* setVec3Param(const glm::vec3& param);

  /**
   * Get parameter.
   */
  const glm::mat4& getMat4Param() const;

  /**
   * Set parameter to be used by animation function.
   * \return this pointer for method chaining
   */
  TransformAnimation* setMat4Param(const glm::mat4& param);

  /**
   * Set start function f_start that is called when the animation is started as
   * f(this).
   * \param startFunc function object with signature void f(TransformAnimation*).
   * \return this pointer for method chaining
   */
  TransformAnimation* setStartFunc(std::function<void(TransformAnimation*)> startFunc);

  /**
   * Set update function that is called when the animation is updated as
   * f(this, currTime, diffTime, totalTime) (cf. Animation).
   * \param updateFunc function object with signature
   *    void f(TransformAnimation*, double, double, double).
   * \return this pointer for method chaining
   */
  TransformAnimation* setUpdateFunc(std::function<void(TransformAnimation*, double, double, double)> updateFunc);

  /**
   * Start or restart animation with given time, call start function (if defined).
   *
   * \param currTime current time (seconds)
   */
  virtual void start(double currTime);

  /**
   * Update animation with given time, call update function (if defined).
   *
   * \param currTime current time (seconds)
   */
  virtual void update(double currTime);

protected:

  GLfloat floatParam_;
  glm::vec3 vec3Param_;
  glm::mat4 mat4Param_;
  std::function<void(TransformAnimation*)> startFunc_;
  std::function<void(TransformAnimation*, double, double, double)> updateFunc_;

};

} /* namespace scg */

#endif /* TRANSFORMANIMATION_H_ */
