/**
 * \file color_vert.glsl
 * \brief Simple color vertex shader.
 */

#version 150

in vec4 vVertex;
in vec4 vColor;

uniform mat4 mvpMatrix;

smooth out vec4 color;


void main() {
  gl_Position = mvpMatrix * vVertex;
  color = vColor;
}
