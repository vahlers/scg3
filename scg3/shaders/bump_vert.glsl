/**
 * \file bump_vert.glsl
 * \brief Bump mapping vertex shader.
 */

#version 150

in vec4 vVertex;
in vec3 vNormal;
in vec4 vTexCoord0;
in vec3 vTangent;
in vec3 vBinormal;

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

uniform int nLights;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;
uniform mat4 textureMatrix;

smooth out vec3 ecVertex;
smooth out vec4 texCoord0;
smooth out vec3 tcView;
smooth out vec3 tcSource[MAX_NUMBER_OF_LIGHTS];

void main() {
  
  // transform vertex position, normal, tangent, and binormal into eye coordinates 
  ecVertex = (modelViewMatrix * vVertex).xyz;
  vec3 ecNormal = normalMatrix * vNormal;
  vec3 ecTangent = normalMatrix * vTangent;
  vec3 ecBinormal = normalMatrix * vBinormal;
      
  // create transformation to tangent space 
  vec3 ecN = normalize(ecNormal);
  vec3 ecT = normalize(ecTangent);
  vec3 ecB = normalize(ecBinormal);
  mat3 ec2tcTrans = mat3(
      ecT.x, ecB.x, ecN.x,
      ecT.y, ecB.y, ecN.y,
      ecT.z, ecB.z, ecN.z );

  // transform view direction to tangent space
  tcView = ec2tcTrans * (-ecVertex);
   
  // transform light source directions to tangent space
  for (int i = 0; i < nLights; ++i) {
    if (lights[i].position.w < 0.001) {
      // directional light
      tcSource[i] = ec2tcTrans * lights[i].position.xyz;
    }
    else {
      // point or spot light
      tcSource[i] = ec2tcTrans * (lights[i].position.xyz - ecVertex);
    }
  }
  
  // set output values
  gl_Position = mvpMatrix * vVertex;
  texCoord0 = textureMatrix * vTexCoord0;
}
