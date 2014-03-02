/**
 * \file simple_flat_frag.glsl
 * \brief Minimal lighting fragment shader, using Gouraud shading.
 */

#version 150

flat in vec4 color;

out vec4 fragColor;


// --- implementations ---


void main(void) {
  
  // set final fragment color
  fragColor = clamp(color, 0., 1.);
}
