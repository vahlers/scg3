/**
 * \file skybox_vert.glsl
 * \brief Skybox vertex shader.
 */

#version 150

in vec4 vVertex;

uniform mat4 skyboxMatrix;

smooth out vec3 texCoord0;


void main() {
  gl_Position = skyboxMatrix * vVertex;
  texCoord0 = vVertex.xyz;
}
