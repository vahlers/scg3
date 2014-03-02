/**
 * \file CubeMapCore.h
 * \brief Cube map texture core.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef CUBEMAPCORE_H_
#define CUBEMAPCORE_H_

#include <vector>
#include "scg_internals.h"
#include "TextureCore.h"

namespace scg {


/**
 * \brief Cube map textue core.
 *
 * To be used in conjunction with cube map or skybox shader.
 */
class CubeMapCore: public TextureCore {

public:

  /**
   * Constructor.
   */
  CubeMapCore();

  /**
   * Destructor.
   */
  virtual ~CubeMapCore();

  /**
   * Create shared pointer.
   */
  static CubeMapCoreSP create();

  /**
   * Create cube map texture from RGBA images with given parameters.
   *
   * \param width texture width
   * \param height texture height
   * \param rgbaData vector of 6 arrays of RGBA values for textures in directions
   *     +x, -x, +y, -y, +z, -z
   */
  void setCubeMap(GLsizei width, GLsizei height, const std::vector<unsigned char*>& rgbaData);

  /**
   * Render core, i.e., bind texture and post-multiply current texture matrix
   * by local texture matrix.
   * Pass inverse view matrix and skybox matrix (i.e., model-view-projection matrix
   * without camera translation) to shader program.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render core after traversing sub-tree, i.e., restore previous texture matrix
   * and bind previous texture.
   */
  virtual void renderPost(RenderState* renderState);

};


} /* namespace scg */

#endif /* CUBEMAPCORE_H_ */
