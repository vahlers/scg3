/**
 * \file Renderer.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "Node.h"
#include "Renderer.h"
#include "RenderState.h"


namespace scg {


Renderer::Renderer()
    : renderState_(new RenderState) {
}


Renderer::~Renderer() {
}


void Renderer::initRenderState() {
  renderState_->init();
}


void Renderer::destroyScene() {
  if (scene_) {
    scene_->destroy();
    scene_.reset();
  }
}


NodeSP Renderer::getScene() {
  return scene_;
}


void Renderer::setScene(NodeSP scene) {
  assert(scene);
  scene_ = scene;
}


CameraSP Renderer::getCamera() {
  return camera_;
}


void Renderer::setCamera(CameraSP camera) {
  assert(camera);
  camera_ = camera;
}


void Renderer::setLighting(bool isLightingEnabled) {
  renderState_->setLighting(isLightingEnabled);
}


bool Renderer::isLightingEnabled() const {
  return renderState_->isLightingEnabled();
}


void Renderer::setGlobalAmbientLight(const glm::vec4& globalAmbientLight) {
  renderState_->setGlobalAmbientLight(globalAmbientLight);
}


std::string Renderer::getInfo() {
  // return empty string by default
  return std::string();
}


} /* namespace scg */
