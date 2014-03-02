/**
 * \file InfoTraverser.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
