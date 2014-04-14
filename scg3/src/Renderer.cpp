/**
 * \file Renderer.cpp
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
