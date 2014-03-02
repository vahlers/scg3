/**
 * \file StandardRenderer.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "sstream"
#include "Camera.h"
#include "Node.h"
#include "InfoTraverser.h"
#include "PreTraverser.h"
#include "RenderState.h"
#include "RenderTraverser.h"
#include "StandardRenderer.h"
#include "Viewer.h"

namespace scg {


StandardRenderer::StandardRenderer()
    : infoTraverser_(new InfoTraverser(renderState_.get())),
      preTraverser_(new PreTraverser(renderState_.get())),
      renderTraverser_(new RenderTraverser(renderState_.get())) {
}


StandardRenderer::~StandardRenderer() {
}


StandardRendererSP StandardRenderer::create() {
  return std::make_shared<StandardRenderer>();
}


void StandardRenderer::initViewer(Viewer *viewer, FrameBufferSize *fbSize) {
  viewer_ = viewer;
  // enable stencil buffer, to be used by projection shadows
  fbSize->stencilbits = 8;
}


std::string StandardRenderer::getInfo() {
  assert(scene_);
  scene_->traverse(infoTraverser_.get());
  std::stringstream stream;
  stream << "No. of nodes: " << infoTraverser_->getNNodes() << std::endl
      << "No. of core pointers: " << infoTraverser_->getNCores() << std::endl
      << "No. of triangles (approx.): " << infoTraverser_->getNTriangles() << std::endl
      << std::ends;
  return stream.str();
}


void StandardRenderer::render() {
  assert(viewer_);
  assert(scene_);
  assert(camera_);

  // check if camera projection has to be updated
  if (viewer_->isWindowResized()) {
    camera_->updateProjection();
  }

  // save projection and modelview matrices, set modelview matrix to identity
  renderState_->projectionStack.pushMatrix();
  renderState_->modelViewStack.pushMatrix();
  renderState_->modelViewStack.setIdentity();

  // pass 1: save camera projection and view transformation
  scene_->traverse(preTraverser_.get());

  // apply projection and view transformation as determined in previous frame
  renderState_->applyProjectionViewTransform();

  // pass 2: render scene
  scene_->traverse(renderTraverser_.get());

  // restore projection and modelview matrices
  renderState_->modelViewStack.popMatrix();
  renderState_->projectionStack.popMatrix();
}


} /* namespace scg */
