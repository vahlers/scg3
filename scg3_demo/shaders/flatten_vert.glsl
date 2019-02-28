/**
 * \file flatten_vert.glsl
 * \brief Flatten vertex shader, uses external function applyLighting().
 * 
 * To be used with fragment shader color_frag.glsl.
 */

#version 150

in vec4 vVertex;
in vec3 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;

smooth out vec4 color;


// --- declarations ---


void applyLighting(const in vec3 ecVertex, const in vec3 ecNormal, 
    out vec4 emissionAmbientDiffuse, out vec4 specular);


// --- implementations ---


void main() {
  
  // scale vertex in y-direction
  vec4 modVertex = vVertex * vec4(1.0, 0.01, 1.0, 1.0);
  
  // transform vertex position and normal into eye coordinates 
  vec3 ecVertex = (modelViewMatrix * modVertex).xyz;
  vec3 ecNormal = normalMatrix * vNormal;
      
  // apply lighting model (to be defined in separate shader)
  vec4 emissionAmbientDiffuse;
  vec4 specular;
  applyLighting(ecVertex, ecNormal, emissionAmbientDiffuse, specular);
  
  // set output values
  gl_Position = mvpMatrix * modVertex;
  color = emissionAmbientDiffuse + specular;
}
