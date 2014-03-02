/**
 * \file RenderTraverser.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "Camera.h"
#include "Group.h"
#include "Light.h"
#include "RenderState.h"
#include "RenderTraverser.h"
#include "Shape.h"
#include "Transformation.h"

namespace scg {


RenderTraverser::RenderTraverser(RenderState* renderState)
    : Traverser(renderState) {
}


RenderTraverser::~RenderTraverser() {
}


void RenderTraverser::visitShape(Shape* node) {
  node->render(renderState_);
}


void RenderTraverser::visitCamera(Camera* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostCamera(Camera* node) {
  node->renderPost(renderState_);
}


void RenderTraverser::visitGroup(Group* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostGroup(Group* node) {
  node->renderPost(renderState_);
}


void RenderTraverser::visitLight(Light* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostLight(Light* node) {
  node->renderPost(renderState_);
}


void RenderTraverser::visitTransformation(Transformation* node) {
  node->render(renderState_);
}


void RenderTraverser::visitPostTransformation(Transformation* node) {
  node->renderPost(renderState_);
}


} /* namespace scg */
