/**
 * \file phong_vert.glsl
 * \brief Phong vertex shader.
 */

#version 150

in vec4 vVertex;
in vec3 vNormal;
in vec4 vTexCoord0;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;
uniform mat4 textureMatrix;

smooth out vec3 ecVertex;
smooth out vec3 ecNormal;
smooth out vec4 texCoord0;


void main() {
  
  // transform vertex position and normal into eye coordinates 
  ecVertex = (modelViewMatrix * vVertex).xyz;
  ecNormal = normalMatrix * vNormal;
      
  // set output values
  gl_Position = mvpMatrix * vVertex;
  texCoord0 = textureMatrix * vTexCoord0;
}
