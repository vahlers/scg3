/**
 * \file Texture2DCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "RenderToTexture2DCore.h"
#include "RenderToTextureRenderer.h"

namespace scg {


RenderToTexture2DCore::RenderToTexture2DCore()
    : Texture2DCore() {
}


RenderToTexture2DCoreSP RenderToTexture2DCore::create() {
  return std::make_shared<RenderToTexture2DCore>();
}


void RenderToTexture2DCore::render(RenderState* renderState) {
  tex_ = renderToTextureTex;
  Texture2DCore::render(renderState);
}

} /* namespace scg */
