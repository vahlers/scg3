/**
 * \file skybox_frag.glsl
 * \brief Skybox fragment shader.
 */

#version 150

smooth in vec3 texCoord0;

uniform samplerCube texture0;
uniform mat4 colorMatrix;

out vec4 fragColor;


void main() {
  vec4 color = texture(texture0, texCoord0);
  
  // transform color by color matrix
  vec4 transformedColor = colorMatrix * vec4(color.rgb, 1.);
  transformedColor /= transformedColor.a;   // perspective division
    
  // set final fragment color
  fragColor = clamp(vec4(transformedColor.rgb, color.a), 0., 1.);
}
