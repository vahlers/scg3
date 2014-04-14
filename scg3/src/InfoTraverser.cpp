/**
 * \file InfoTraverser.cpp
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

#include "InfoTraverser.h"
#include "Camera.h"
#include "Group.h"
#include "Light.h"
#include "LightPosition.h"
#include "Shape.h"
#include "Transformation.h"

namespace scg {


InfoTraverser::InfoTraverser(RenderState* renderState)
    : Traverser(renderState), nNodes_(0), nCores_(0), nTriangles_(0) {
}


InfoTraverser::~InfoTraverser() {
}


void InfoTraverser::clear() {
  nNodes_ = nCores_ = nTriangles_ = 0;
}


int InfoTraverser::getNNodes() const {
  return nNodes_;
}


int InfoTraverser::getNCores() const {
  return nCores_;
}


int InfoTraverser::getNTriangles() const {
  return nTriangles_;
}


void InfoTraverser::visitLightPosition(LightPosition* node) {
  nNodes_++;
  nCores_ += node->getNCores();
}


void InfoTraverser::visitShape(Shape* node) {
  nNodes_++;
  nCores_ += node->getNCores();
  nTriangles_ += node->getNTriangles();
}


void InfoTraverser::visitCamera(Camera* node) {
  nNodes_++;
  nCores_ += node->getNCores();
}


void InfoTraverser::visitGroup(Group* node) {
  nNodes_++;
  nCores_ += node->getNCores();
}


void InfoTraverser::visitLight(Light* node) {
  nNodes_++;
  nCores_ += node->getNCores();
}


void InfoTraverser::visitTransformation(Transformation* node) {
  nNodes_++;
  nCores_ += node->getNCores();
}


} /* namespace scg */
