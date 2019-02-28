/**
 * \file texture_no_lighting_vert.glsl
 * \brief Vertex shader for texture without lighting.
 */

#version 150

in vec4 vVertex;
in vec4 vTexCoord0;

uniform mat4 mvpMatrix;
uniform mat4 textureMatrix;

smooth out vec4 texCoord0;


// --- implementations ---


void main() {
  
  // set output values
  gl_Position = mvpMatrix * vVertex;
  texCoord0 = textureMatrix * vTexCoord0;
}
