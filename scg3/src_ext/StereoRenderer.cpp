/**
 * \file StereoRenderer.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "StereoRenderer.h"

namespace scg {


StereoRenderer::StereoRenderer(RendererSP concreteRenderer)
    : concreteRenderer_(concreteRenderer) {
}


StereoRenderer::~StereoRenderer() {
}


void StereoRenderer::initRenderState() {
  assert(concreteRenderer_);
  concreteRenderer_->initRenderState();
}


void StereoRenderer::initViewer(Viewer* viewer, FrameBufferSize* frameBufferSize) {
  assert(concreteRenderer_);
  concreteRenderer_->initViewer(viewer, frameBufferSize);
  // leave OpenGL mode unchanged, no extension required
}


std::string StereoRenderer::getInfo() {
  assert(concreteRenderer_);
  return concreteRenderer_->getInfo();
}



} /* namespace scg */
