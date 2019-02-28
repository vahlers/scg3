/**
 * \file StandardRenderer.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <sstream>
#include "../scg3/src/Camera.h"
#include "../scg3/src/Node.h"
#include "../scg3/src/InfoTraverser.h"
#include "../scg3/src/PreTraverser.h"
#include "../scg3/src/RenderState.h"
#include "../scg3/src/RenderTraverser.h"
#include "../scg3/src/Viewer.h"
#include "RenderToTextureRenderer.h"

namespace scg {


GLuint renderToTextureTex = 0;


RenderToTextureRenderer::RenderToTextureRenderer()
    : fbo_(0), rbo_(0),
      infoTraverser_(new InfoTraverser(renderState_.get())),
      preTraverser_(new PreTraverser(renderState_.get())),
      renderTraverser_(new RenderTraverser(renderState_.get())) {
}


RenderToTextureRenderer::~RenderToTextureRenderer() {
}


RenderToTextureRendererSP RenderToTextureRenderer::create() {
  return std::make_shared<RenderToTextureRenderer>();
}


void RenderToTextureRenderer::initViewer(Viewer *viewer, FrameBufferSize *fbSize) {
  viewer_ = viewer;
  // enable stencil buffer, to be used by projection shadows
  fbSize->stencilbits = 8;
}


void RenderToTextureRenderer::initRenderState() {
  Renderer::initRenderState();

  // Render to texture code based on Wolff 2011
  // create FBO
  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  // create texture object
  glGenTextures(1, &renderToTextureTex);
  glActiveTexture(GL_TEXTURE0); // texture unit 0
  glBindTexture(GL_TEXTURE_2D, renderToTextureTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // bind texture to FBO color attachment
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderToTextureTex, 0);

  // create RBO for depth buffer
  glGenRenderbuffers(1, &rbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);

  // bind RBO to FBO depth attachment
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_);

  // set target for fragment shader output
  GLenum drawBuffer[] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers(1, drawBuffer);

  // unbind FBO, revert to default framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


std::string RenderToTextureRenderer::getInfo() {
  assert(scene_);
  scene_->traverse(infoTraverser_.get());
  std::stringstream stream;
  stream << "No. of nodes: " << infoTraverser_->getNNodes() << std::endl
      << "No. of core pointers: " << infoTraverser_->getNCores() << std::endl
      << "No. of triangles (approx.): " << infoTraverser_->getNTriangles() << std::endl
      << std::ends;
  return stream.str();
}


void RenderToTextureRenderer::render() {
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

  // save viewport
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  // bind texture FBO
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glViewport(0, 0, 512, 512);      // viewport for texture
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // pass 2: render scene
  scene_->traverse(renderTraverser_.get());

  // unbind texture FBO, revert to default framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // restore viewport
  glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

  // pass 2: render scene
  scene_->traverse(renderTraverser_.get());

  // restore projection and modelview matrices
  renderState_->modelViewStack.popMatrix();
  renderState_->projectionStack.popMatrix();
}


} /* namespace scg */
