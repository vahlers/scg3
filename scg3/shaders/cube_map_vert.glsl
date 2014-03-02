/**
 * \file cube_map_vert.glsl
 * \brief Cube map vertex shader without shading.
 */

#version 150

in vec4 vVertex;
in vec3 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;
uniform mat4 invViewMatrix;

smooth out vec3 texCoord0;


void main() {
  
  // transform vertex position and normal into eye coordinates 
  vec3 ecVertex = (modelViewMatrix * vVertex).xyz;
  vec3 ecNormal = normalMatrix * vNormal;
      
  // compute reflection for cube mapping
  vec4 ecReflection = vec4(reflect(normalize(ecVertex), normalize(ecNormal)), 0.);
  
  // set output values
  gl_Position = mvpMatrix * vVertex;
  texCoord0 = (invViewMatrix * ecReflection).stp;
}
