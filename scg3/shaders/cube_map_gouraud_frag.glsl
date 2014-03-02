/**
 * \file cube_map_gouraud_frag.glsl
 * \brief Cube map fragment shader with Gouraud shading.
 */

#version 150

smooth in vec4 emissionAmbientDiffuse;
smooth in vec4 specular;
smooth in vec3 texCoord0;

uniform mat4 colorMatrix;
uniform samplerCube texture0;

out vec4 fragColor;


void main(void) {
  
  // apply cube map and determine color
  vec4 texColor = texture(texture0, texCoord0);
  vec4 color = clamp(mix(texColor, emissionAmbientDiffuse, 0.5) + specular, 0., 1.);
  
  // transform color by color matrix
  vec4 transformedColor = colorMatrix * vec4(color.rgb, 1.);
  transformedColor /= transformedColor.a;   // perspective division
  
  // set final fragment color
  fragColor = clamp(vec4(transformedColor.rgb, color.a), 0., 1.);
}
