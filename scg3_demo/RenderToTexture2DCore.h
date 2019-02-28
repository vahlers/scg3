/**
 * \file RenderToTexture2DCore.h
 * \brief 2D texture core.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef RENDERTOTEXTURE2DCORE_H_
#define RENDERTOTEXTURE2DCORE_H_

#include "../scg3/src/Texture2DCore.h"

namespace scg {


SCG_DECLARE_CLASS(RenderToTexture2DCore);


/**
 * \brief 2D texture core.
 */
class RenderToTexture2DCore: public Texture2DCore {

public:

  /**
   * Constructor.
   */
  RenderToTexture2DCore();

  /**
   * Create shared pointer.
   */
  static RenderToTexture2DCoreSP create();

  virtual void render(RenderState* renderState);

};


} /* namespace scg */

#endif /* RENDERTOTEXTURE2DCORE_H_ */
