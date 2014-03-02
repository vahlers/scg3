/**
 * \file gouraud_vert.glsl
 * \brief Gouraud vertex shader, uses external function applyLighting().
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

smooth out vec4 emissionAmbientDiffuse;
smooth out vec4 specular;
smooth out vec4 texCoord0;


// --- declarations ---


void applyLighting(const in vec3 ecVertex, const in vec3 ecNormal, 
    out vec4 emissionAmbientDiffuse, out vec4 specular);


// --- implementations ---


void main() {
  
  // transform vertex position and normal into eye coordinates 
  vec3 ecVertex = (modelViewMatrix * vVertex).xyz;
  vec3 ecNormal = normalMatrix * vNormal;
      
  // apply lighting model (to be defined in separate shader)
  applyLighting(ecVertex, ecNormal, emissionAmbientDiffuse, specular);
  
  // set output values
  gl_Position = mvpMatrix * vVertex;
  texCoord0 = textureMatrix * vTexCoord0;
}
