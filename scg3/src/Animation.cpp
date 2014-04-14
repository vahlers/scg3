/**
 * \file Animation.cpp
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
