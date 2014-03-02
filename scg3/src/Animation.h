/**
 * \file Animation.h
 * \brief Base class for all animations (abstract), providing general functionality.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
