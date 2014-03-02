/**
 * \file texture2d_modulate.glsl
 * \brief Determine fragment color with 2D texture modulation,
 *    provides external function applyTexture() to fragment shader.
 */

#version 150

uniform sampler2D texture0;


vec4 applyTexture(const in vec4 texCoord, const in vec4 emissionAmbientDiffuse,
    const in vec4 specular) {
  vec4 texColor = texture(texture0, texCoord.st);
  return clamp(emissionAmbientDiffuse * texColor + specular, 0., 1.);
}
