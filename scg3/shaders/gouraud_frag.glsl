/**
 * \file gouraud_frag.glsl
 * \brief Gouraud fragment shader, use external function applyTexture().
 */

#version 150

smooth in vec4 emissionAmbientDiffuse;
smooth in vec4 specular;
smooth in vec4 texCoord0;

uniform mat4 colorMatrix;

out vec4 fragColor;


// --- declarations ---


vec4 applyTexture(const in vec4 texCoord, const in vec4 emissionAmbientDiffuse,
    const in vec4 specular);


// --- implementations ---


void main(void) {
  
  // apply texture and determine color (to be defined in separate shader)
  vec4 color = applyTexture(texCoord0, emissionAmbientDiffuse, specular);
  
  // transform color by color matrix
  vec4 transformedColor = colorMatrix * vec4(color.rgb, 1.);
  transformedColor /= transformedColor.a;   // perspective division
  
  // set final fragment color
  fragColor = clamp(vec4(transformedColor.rgb, color.a), 0., 1.);
}
