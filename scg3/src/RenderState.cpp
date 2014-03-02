/**
 * \file RenderState.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "scg_internals.h"
#include "scg_utilities.h"
#include "Light.h"
#include "RenderState.h"
#include "ShaderCore.h"

namespace scg {


RenderState::RenderState()
    : colorCore_(nullptr), shaderCore_(nullptr), isLightingEnabled_(true),
      nLights_(0), lightUBO_(0), globalAmbientLight_(0.f, 0.f, 0.f, 1.f) {
}


RenderState::~RenderState() {
  if (isGLContextActive()) {
    glDeleteBuffers(1, &lightUBO_);
  }
}


void RenderState::init() {
  glGenBuffers(1, &lightUBO_);
  const size_t bufferSize = OGLConstants::MAX_NUMBER_OF_LIGHTS * Light::BUFFER_SIZE;
  GLubyte* buffer = new GLubyte[bufferSize];
  std::memset(buffer, 0, bufferSize);
  glBindBuffer(GL_UNIFORM_BUFFER, lightUBO_);
  assert(glIsBuffer(lightUBO_));
  glBufferData(GL_UNIFORM_BUFFER, bufferSize, buffer, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  delete [] buffer;
  buffer = nullptr;
  glBindBufferBase(GL_UNIFORM_BUFFER, OGLConstants::LIGHT.bindingPoint, lightUBO_);

  assert(!checkGLError());
}


void RenderState::setLighting(bool isLightingEnabled) {
  isLightingEnabled_ = isLightingEnabled;
}


bool RenderState::isLightingEnabled() const {
  return isLightingEnabled_;
}


int RenderState::getNLights() const {
  return nLights_;
}


GLuint RenderState::getLightUBO() const {
  return lightUBO_;
}


ColorCore* RenderState::getColor() {
  return colorCore_;
}


void RenderState::setColor(ColorCore* core) {
  colorCore_ = core;
}


ShaderCore* RenderState::getShader() {
  return shaderCore_;
}


void RenderState::setShader(ShaderCore* core) {
  shaderCore_ = core;
}


void RenderState::addLight() {
  assert(nLights_ < OGLConstants::MAX_NUMBER_OF_LIGHTS);
  ++nLights_;
}

void RenderState::removeLight() {
  assert(nLights_ > 0);
  --nLights_;
}


void RenderState::setGlobalAmbientLight(const glm::vec4& globalAmbientLight) {
  globalAmbientLight_ = globalAmbientLight;
}


void RenderState::applyProjectionViewTransform() {
  projectionStack.setMatrix(projection_);
  modelViewStack.multMatrix(viewTransform_);
}


void RenderState::passToShader() {
  assert(shaderCore_ != nullptr);
  shaderCore_->setUniformMatrix4fv(OGLConstants::MODEL_VIEW_MATRIX, 1,
      glm::value_ptr(modelViewStack.getMatrix()));
  shaderCore_->setUniformMatrix4fv(OGLConstants::PROJECTION_MATRIX, 1,
      glm::value_ptr(projectionStack.getMatrix()));
  shaderCore_->setUniformMatrix4fv(OGLConstants::MVP_MATRIX, 1,
      glm::value_ptr(projectionStack.getMatrix() * modelViewStack.getMatrix()));
  // compute 3x3 normal matrix from 4x4 model-view matrix
  shaderCore_->setUniformMatrix3fv(OGLConstants::NORMAL_MATRIX, 1,
      glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(modelViewStack.getMatrix())))));
  shaderCore_->setUniformMatrix4fv(OGLConstants::TEXTURE_MATRIX, 1,
      glm::value_ptr(textureStack.getMatrix()));
  shaderCore_->setUniformMatrix4fv(OGLConstants::COLOR_MATRIX, 1,
      glm::value_ptr(colorStack.getMatrix()));
  if (isLightingEnabled_) {
    shaderCore_->setUniform1i(OGLConstants::N_LIGHTS, nLights_);
    shaderCore_->setUniform4fv(OGLConstants::GLOBAL_AMBIENT_LIGHT, 1, glm::value_ptr(globalAmbientLight_));
  }
  else {
    const glm::vec4 black(0.f, 0.f, 0.f, 1.f);
    shaderCore_->setUniform1i(OGLConstants::N_LIGHTS, 0);
    shaderCore_->setUniform4fv(OGLConstants::GLOBAL_AMBIENT_LIGHT, 1, glm::value_ptr(black));
  }
}


} /* namespace scg */
