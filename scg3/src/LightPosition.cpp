/**
 * \file LightPosition.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "LightPosition.h"
#include "Traverser.h"

namespace scg {


LightPosition::LightPosition(LightSP light)
    : light_(light) {
}


LightPosition::~LightPosition() {
}


LightPositionSP LightPosition::create(LightSP light) {
  return std::make_shared<LightPosition>(light);
}


LightSP LightPosition::getLight() {
  return light_;
}


LightPosition* LightPosition::setLight(LightSP light) {
  light_ = light;
  return this;
}


void LightPosition::accept(Traverser* traverser) {
  traverser->visitLightPosition(this);
}


} /* namespace scg */
