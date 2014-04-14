/**
 * \file TextureCoreFactory.h
 * \brief A factory to create textures.
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

#ifndef TEXTURECOREFACTORY_H_
#define TEXTURECOREFACTORY_H_

#include <string>
#include <vector>
#include "scg_glew.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A factory to create textures.
 */
class TextureCoreFactory {

public:

  /**
   * Constructor.
   */
  TextureCoreFactory();

  /**
   * Constructor with one or more file paths to be searched for texture files.
   * More than one file paths can be defined using ';' or ',' as delimiter.
   *
   * Example: addFilePath("../textures1;../textures2")
   */
  TextureCoreFactory(const std::string& filePath);

  /**
   * Destructor.
   */
  virtual ~TextureCoreFactory();

  /**
   * Add one or more file paths to be searched for texture files.
   * More than one file paths can be defined using ';' or ',' as delimiter.
   *
   * Example: addFilePath("../textures1;../textures2")
   */
  void addFilePath(const std::string& filePath);

  /**
   * Load texture image from source file and create a 2D texture with given parameters.
   * If minFilter is GL_*_MIPMAP_* (see below), a mipmap is created from the
   * given image.
   *
   * \param fileName file name to be searched for in known file paths
   * \param wrapModeS GL_CLAMP, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
   *    GL_MIRRORED_REPEAT, or GL_REPEAT
   * \param wrapModeT see wrapModeS
   * \param minFilter GL_NEAREST, GL_LINEAR,\n
   *    GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
   *    GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR
   * \param magFilter GL_NEAREST or GL_LINEAR
   */
  Texture2DCoreSP create2DTextureFromFile(const std::string& fileName,
      GLenum wrapModeS, GLenum wrapModeT, GLenum minFilter, GLenum magFilter);

  /**
   * Load texture (optional) and normal map images from source files and create a bump map
   * with given parameters.
   * If minFilter is GL_*_MIPMAP_* (see below), mipmaps are created from the
   * given images.
   *
   * \param texFileName texture file name to be searched for in known file paths
   * \param normalFileName normal map file name to be searched for in known file paths
   * \param wrapModeS GL_CLAMP, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
   *    GL_MIRRORED_REPEAT, or GL_REPEAT
   * \param wrapModeT see wrapModeS
   * \param minFilter GL_NEAREST, GL_LINEAR,\n
   *    GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
   *    GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR
   * \param magFilter GL_NEAREST or GL_LINEAR
   */
  BumpMapCoreSP createBumpMapFromFiles(const std::string& texFileName,
      const std::string& normalFileName, GLenum wrapModeS, GLenum wrapModeT,
      GLenum minFilter, GLenum magFilter);

  /**
   * Load texture images from source files and create a cube map.
   * \param fileNames 6 texture file names for directions +x, -x, +y, -y, +z, -z
   *     to be searched for in known file paths
   */
  CubeMapCoreSP createCubeMapFromFiles(const std::vector<std::string>& fileNames);

  /**
   * Load texture images from source files and create a cube map.
   * \param fileNames 6 texture file names for directions +x, -x, +y, -y, +z, -z
   *     to be searched for in known file paths
   */
  CubeMapCoreSP createCubeMapFromFiles(std::vector<std::string>&& fileNames);

protected:

  std::vector<std::string> filePaths_;

};


} /* namespace scg */

#endif /* TEXTURECOREFACTORY_H_ */
