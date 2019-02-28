/**
 * \file texture_no_lighting_frag.glsl
 * \brief Fragment shader for texture without lighting.
 */

#version 150

smooth in vec4 texCoord0;

uniform sampler2D texture0;
uniform mat4 colorMatrix;

out vec4 fragColor;


// --- implementations ---


void main(void) {
  
  // apply texture and determine color
  vec4 color = texture(texture0, texCoord0.st);
  
  // transform color by color matrix
  vec4 transformedColor = colorMatrix * vec4(color.rgb, 1.);
  transformedColor /= transformedColor.a;   // perspective division
  
  // set final fragment color
  fragColor = clamp(vec4(transformedColor.rgb, color.a), 0., 1.);
}
