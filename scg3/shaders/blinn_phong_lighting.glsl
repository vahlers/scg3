/**
 * \file blinn_phong_lighting.glsl
 * \brief Blinn Phong lighting shader, provides external function applyLighting()
 *    to vertex or fragment shader.
 */

#version 150

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


// --- declarations ---


void directionalLight(const in int idx, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular);

void pointLight(const in int idx, const in vec3 ecVertex, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular);

void spotLight(const in int idx, const in vec3 ecVertex, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular);


// --- implementations ---

  
void applyLighting(const in vec3 ecVertex, const in vec3 ecNormal, 
    out vec4 emissionAmbientDiffuse, out vec4 specular) {
  
  // normalized view direction and surface normal
  vec3 v = normalize(-ecVertex);
  vec3 n = normalize(ecNormal);
  
  // add contributions of light sources
  vec4 ambient = vec4(0., 0., 0., 0.);
  vec4 diffuse = vec4(0., 0., 0., 0.);
  specular = vec4(0., 0., 0., 0.);
  for (int i = 0; i < nLights; ++i) {
    if (lights[i].position.w < 0.001) {
      directionalLight(i, v, n, ambient, diffuse, specular);
    }
    else {
      if (lights[i].spotCosCutoff < 0.001) {
        pointLight(i, ecVertex, v, n, ambient, diffuse, specular);
      }
      else {
        spotLight(i, ecVertex, v, n, ambient, diffuse, specular);
      }
    }
  }
  
  // multiply with material parameters, add emission and global ambient light
  emissionAmbientDiffuse = material.emission 
      + material.ambient * (globalAmbientLight + ambient) 
      + material.diffuse * diffuse;
  specular *= material.specular;  
}


void directionalLight(const in int idx, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular) {
  
  // normalized light source direction (half vector is provided by application)
  vec3 s = normalize(lights[idx].position.xyz);
  
  // ambient
  ambient += lights[idx].ambient;
  
  // diffuse
  float sDotN = max(0., dot(s, n));
  diffuse += lights[idx].diffuse * sDotN;

  // specular
  float hDotN = dot(lights[idx].halfVector.xyz, n);
  if (hDotN > 0.) {
    specular += lights[idx].specular * pow(hDotN, material.shininess);
  }
}


void pointLight(const in int idx, const in vec3 ecVertex, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular) {

  // normalized light source direction and half vector
  vec3 s = normalize(lights[idx].position.xyz - ecVertex);
  vec3 h = normalize(v + s);
  
  // ambient
  ambient += lights[idx].ambient;
  
  // diffuse
  float sDotN = max(0., dot(s, n));
  diffuse += lights[idx].diffuse * sDotN;

  // specular
  float hDotN = dot(h, n);
  if (hDotN > 0.) {
    specular += lights[idx].specular * pow(hDotN, material.shininess);  
  }
}


void spotLight(const in int idx, const in vec3 ecVertex, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular) {

  // normalized light source direction and half vector
  vec3 s = normalize(lights[idx].position.xyz - ecVertex);
  vec3 h = normalize(v + s);

  // check if surface point is inside spotlight cone
  float dirDotS = dot(lights[idx].spotDirection.xyz, -s);
  if (dirDotS >= lights[idx].spotCosCutoff) {
    
    // spot attenuation from center to edges
    float attenuation = pow(dirDotS, lights[idx].spotExponent);
    
    // ambient
    ambient += attenuation * lights[idx].ambient;
    
    // diffuse
    float sDotN = max(0., dot(s, n));
    diffuse += attenuation * lights[idx].diffuse * sDotN;
    
    // specular
    float hDotN = dot(h, n);
    if (hDotN > 0.) {
      specular += attenuation * lights[idx].specular * pow(hDotN, material.shininess);
    }
  }
}
