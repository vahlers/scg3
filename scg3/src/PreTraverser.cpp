/**
 * \file PreTraverser.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "Camera.h"
#include "Light.h"
#include "LightPosition.h"
#include "PreTraverser.h"
#include "RenderState.h"
#include "Transformation.h"
#include "scg_glm.h"

namespace scg {


PreTraverser::PreTraverser(RenderState* renderState)
    : Traverser(renderState) {
}


PreTraverser::~PreTraverser() {
}


void PreTraverser::visitCamera(Camera* node) {
  // apply camera transformation, but do not render coordinate axes
  node->Transformation::render(renderState_);

  // save projection and view transformation
  renderState_->setProjection(node->getProjection());
  renderState_->setViewTransform(node->getViewTransform(renderState_));
}


void PreTraverser::visitPostCamera(Camera* node) {
  node->renderPost(renderState_);
}


void PreTraverser::visitLightPosition(LightPosition* node) {
  node->getLight()->setModelTransform(renderState_->modelViewStack.getMatrix());
}


void PreTraverser::visitTransformation(Transformation* node) {
  node->render(renderState_);
}


void PreTraverser::visitPostTransformation(Transformation* node) {
  node->renderPost(renderState_);
}


} /* namespace scg */
