/**
 * \file Traverser.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "Traverser.h"

namespace scg {


Traverser::Traverser(RenderState* renderState)
    : renderState_(renderState) {
}


Traverser::~Traverser() {
}


void Traverser::visitLightPosition(LightPosition* node) {
  // do nothing by default
}


void Traverser::visitShape(Shape* node) {
  // do nothing by default
}


void Traverser::visitCamera(Camera* node) {
  // do nothing by default
}


void Traverser::visitPostCamera(Camera* node) {
  // do nothing by default
}


void Traverser::visitGroup(Group* node) {
  // do nothing by default
}


void Traverser::visitPostGroup(Group* node) {
  // do nothing by default
}


void Traverser::visitLight(Light* node) {
  // do nothing by default
}


void Traverser::visitPostLight(Light* node) {
  // do nothing by default
}


void Traverser::visitTransformation(Transformation* node) {
  // do nothing by default
}


void Traverser::visitPostTransformation(Transformation* node) {
  // do nothing by default
}


} /* namespace scg */
