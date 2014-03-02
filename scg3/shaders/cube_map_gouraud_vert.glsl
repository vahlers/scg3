/**
 * \file cube_map_gouraud_vert.glsl
 * \brief Cube map vertex shader with Gouraud shading,
 *     uses external function applyLighting().
 */

#version 150

in vec4 vVertex;
in vec3 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;
uniform mat4 invViewMatrix;

smooth out vec4 emissionAmbientDiffuse;
smooth out vec4 specular;
smooth out vec3 texCoord0;


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
  
  // compute reflection for cube mapping
  vec4 ecReflection = vec4(reflect(normalize(ecVertex), normalize(ecNormal)), 0.);
  
  // set output values
  gl_Position = mvpMatrix * vVertex;
  texCoord0 = (invViewMatrix * ecReflection).stp;
}
