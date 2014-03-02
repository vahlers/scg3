/**
 * \file Animation.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <ctime>
#include "Animation.h"
#include "scg_internals.h"

namespace scg {


Animation::Animation()
    : isStarted_(false), isRunning_(false), lastTime_(0.0), diffTime_(0.0), totalTime_(0.0) {
}


Animation::~Animation() {
}


bool Animation::isStarted() const {
  return isStarted_;
}


bool Animation::isRunning() const {
  return isRunning_;
}


void Animation::start(double currTime) {
  lastTime_ = currTime;
  isStarted_ = true;
  isRunning_ = true;
}


void Animation::stop() {
  isRunning_ = false;
}


void Animation::reset() {
  isStarted_ = false;
  isRunning_ = false;
  lastTime_ = 0.0;
  diffTime_ = 0.0;
  totalTime_ = 0.0;
}


void Animation::update(double currTime) {
  if (isRunning_) {
    diffTime_ = currTime - lastTime_;
    totalTime_ += diffTime_;
    lastTime_ = currTime;
  }
}


} /* namespace scg */
