/**
 * \file cube_map_frag.glsl
 * \brief Cube map fragment shader without shading.
 */

#version 150

smooth in vec3 texCoord0;

uniform mat4 colorMatrix;
uniform samplerCube texture0;

out vec4 fragColor;


void main(void) {
  
  // apply cube map and determine color
  vec4 color = texture(texture0, texCoord0);
  
  // transform color by color matrix
  vec4 transformedColor = colorMatrix * vec4(color.rgb, 1.);
  transformedColor /= transformedColor.a;   // perspective division
  
  // set final fragment color
  fragColor = clamp(vec4(transformedColor.rgb, color.a), 0., 1.);
}
