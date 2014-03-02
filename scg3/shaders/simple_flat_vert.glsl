/**
 * \file simple_flat_vert.glsl
 * \brief Minimal lighting vertex shader, using a single point light and Gouraud shading.
 */

#version 150

in vec4 vVertex;
in vec3 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;

const int MAX_NUMBER_OF_LIGHTS = 10;

struct Light {
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 halfVector;      // used as vec3, expected as normalized
  vec4 spotDirection;   // used as vec3, expected as normalized
  float spotCosCutoff;
  float spotExponent;   
};

layout(std140) uniform LightBlock {
  Light lights[MAX_NUMBER_OF_LIGHTS];
};

struct Material {
  vec4 emission;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;  
};

layout(std140) uniform MaterialBlock {
  Material material;
};

uniform int nLights;
uniform vec4 globalAmbientLight;

flat out vec4 color;


// --- declarations ---


void applyLighting(const in vec3 ecVertex, const in vec3 ecNormal, out vec4 color);


// --- implementations ---


void main() {
  
  // transform vertex position and normal into eye coordinates 
  vec3 ecVertex = (modelViewMatrix * vVertex).xyz;
  vec3 ecNormal = normalMatrix * vNormal;
      
  // apply lighting model
  applyLighting(ecVertex, ecNormal, color);
  
  // set output values
  gl_Position = mvpMatrix * vVertex;
}


void applyLighting(const in vec3 ecVertex, const in vec3 ecNormal, out vec4 color) {
  
  // normalized view direction and surface normal
  vec3 v = normalize(-ecVertex);
  vec3 n = normalize(ecNormal);
  
  // normalized light source direction and half vector
  vec3 s = normalize(lights[0].position.xyz - ecVertex);
  vec3 h = normalize(v + s);
  
  // emission and global ambient
  color = material.emission + material.ambient * globalAmbientLight; 
  
  if (nLights > 0) {
    // ambient
    color += material.ambient * lights[0].ambient; 
    
    // diffuse
    float sDotN = max(0., dot(s, n));
    color += material.diffuse * lights[0].diffuse * sDotN;
  
    // specular
    float hDotN = dot(h, n);
    if (hDotN > 0.) {
      color += material.specular * lights[0].specular * pow(hDotN, material.shininess);  
    }
  }
}
