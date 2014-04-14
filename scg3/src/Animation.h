/**
 * \file Animation.h
 * \brief Base class for all animations (abstract), providing general functionality.
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

#ifndef ANIMATION_H_
#define ANIMATION_H_

namespace scg {


/**
 * \brief Base class for all animations (abstract), providing general functionality.
 */
class Animation {

public:

  /**
   * Constructor.
   */
  Animation();

  /**
   * Destructor.
   */
  virtual ~Animation();

  /**
   * Check if animation has been started at least once.
   */
  bool isStarted() const;

  /**
   * Check if animation is running.
   */
  bool isRunning() const;

  /**
   * Start or restart animation with given time.
   *
   * Note: This method must also be called by derived methods.
   *
   * \param currTime current time (seconds)
   */
  virtual void start(double currTime);

  /**
   * Stop or pause animation.
   *
   * Note: This method must also be called by derived methods.
   */
  virtual void stop();

  /**
   * Reset animation, i.e., set all variables to their initial states.
   *
   * Note: This method must also be called by derived methods.
   */
  virtual void reset();

  /**
   * Update animation with given time.
   *
   * Note: This method must also be called by derived methods.
   *
   * \param currTime current time (seconds)
   */
  virtual void update(double currTime) = 0;

protected:

  bool isStarted_;    /**< true if animation has been started (may be stopped temporarily) */
  bool isRunning_;    /**< true if animation is running */
  double lastTime_;   /**< time of last update (seconds) */
  double diffTime_;   /**< time since last update (seconds) */
  double totalTime_;  /**< time since last reset (seconds) */

};


} /* namespace scg */

#endif /* ANIMATION_H_ */
