/**
 * \file texture_none.glsl
 * \brief Determine fragment color without texture,
 *    provides external function applyTexture() to fragment shader.
 */

#version 150


vec4 applyTexture(const in vec4 texCoord, const in vec4 emissionAmbientDiffuse,
    const in vec4 specular) {
  return clamp(emissionAmbientDiffuse + specular, 0., 1.);
}
