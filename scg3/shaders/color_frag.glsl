/**
 * \file color_frag.glsl
 * \brief Simple color fragment shader.
 */

#version 150

smooth in vec4 color;

out vec4 fragColor;


void main(void) {
  fragColor = clamp(color, 0., 1.);
}
