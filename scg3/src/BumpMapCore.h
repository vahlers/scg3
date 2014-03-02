/**
 * \file BumpMapCore.h
 * \brief Bump map core storing a texture (optional) and a normal map.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef BUMPMAPCORE_H_
#define BUMPMAPCORE_H_

#include "scg_internals.h"
#include "Texture2DCore.h"

namespace scg {


/**
 * \brief 2D bump map core storing a texture (optional) and a normal map.
 */
class BumpMapCore: public Texture2DCore {

public:

  /**
   * Contructor.
   */
  BumpMapCore();

  /**
   * Destructor.
   */
  virtual ~BumpMapCore();

  /**
   * Create shared pointer.
   */
  static BumpMapCoreSP create();

  /**
   * Create normal map from RGBA image with given parameters.
   * If minFilter is GL_*_MIPMAP_* (see below), a mipmap is created from the
   * given image.
   *
   * \param width normal map width
   * \param height normal map height
   * \param rgbaData array of RGBA values
   * \param wrapModeS GL_CLAMP, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
   *    GL_MIRRORED_REPEAT, or GL_REPEAT
   * \param wrapModeT see wrapModeS
   * \param minFilter GL_NEAREST, GL_LINEAR,\n
   *    GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
   *    GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR
   * \param magFilter GL_NEAREST or GL_LINEAR
   */
  void setNormalMap(GLsizei width, GLsizei height, const unsigned char* rgbaData,
      GLenum wrapModeS, GLenum wrapModeT, GLenum minFilter, GLenum magFilter);

  /**
   * Render core, i.e., bind texture and normal map, and post-multiply current texture matrix
   * by local texture matrix.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render core after traversing sub-tree, i.e., restore previous texture matrix
   * and bind previous texture and normal map.
   */
  virtual void renderPost(RenderState* renderState);

protected:

  GLuint texNormal_;
  GLint texNormalOld_;

};


} /* namespace scg */

#endif /* BUMPMAPCORE_H_ */
