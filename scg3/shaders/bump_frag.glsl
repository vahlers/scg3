/**
 * \file bump_frag.glsl
 * \brief Bump mapping fragment shader, uses external function applyTexture().
 */

#version 150

const int MAX_NUMBER_OF_LIGHTS = 10;

smooth in vec3 ecVertex;
smooth in vec4 texCoord0;
smooth in vec3 tcView;
smooth in vec3 tcSource[MAX_NUMBER_OF_LIGHTS];

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
uniform mat4 colorMatrix;
uniform sampler2D texture1;   // normal map

out vec4 fragColor;


// --- declarations ---


void applyLighting(out vec4 emissionAmbientDiffuse, out vec4 specular);

void pointOrDirectionalLight(const in int idx, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular);

void spotLight(const in int idx, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular);

vec4 applyTexture(const in vec4 texCoord, const in vec4 emissionAmbientDiffuse, const in vec4 specular);


// --- implementations ---


void main(void) {
  
  // apply lighting model
  vec4 emissionAmbientDiffuse, specular;
  applyLighting(emissionAmbientDiffuse, specular);
  
  // apply texture and determine color (to be defined in separate shader)
  vec4 color = applyTexture(texCoord0, emissionAmbientDiffuse, specular);

  // transform color by color matrix
  vec4 transformedColor = colorMatrix * vec4(color.rgb, 1.);
  transformedColor /= transformedColor.a;   // perspective division
    
  // set final fragment color
  fragColor = clamp(vec4(transformedColor.rgb, color.a), 0., 1.);
}


void applyLighting(out vec4 emissionAmbientDiffuse, out vec4 specular) {
  
  // normalized view direction
  vec3 v = normalize(tcView);
   
  // determine normal from normal map
  vec3 n = normalize(texture(texture1, texCoord0.st).rgb * 2. - 1.);
  
  // add contributions of light sources
  vec4 ambient = vec4(0., 0., 0., 0.);
  vec4 diffuse = vec4(0., 0., 0., 0.);
  specular = vec4(0., 0., 0., 0.);
  for (int i = 0; i < nLights; ++i) {    
    if (lights[i].spotCosCutoff < 0.001) {
      pointOrDirectionalLight(i, v, n, ambient, diffuse, specular);
    }
    else {
      spotLight(i, v, n, ambient, diffuse, specular);
    }
  }
  
  // multiply with material parameters, add emission and global ambient light
  emissionAmbientDiffuse = material.emission 
      + material.ambient * (globalAmbientLight + ambient) 
      + material.diffuse * diffuse;
  specular *= material.specular;  
}


void pointOrDirectionalLight(const in int idx, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular) {
  
  // normalized light source direction and half vector
  vec3 s = normalize(tcSource[idx]);
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


void spotLight(const in int idx, const in vec3 v, const in vec3 n, 
    inout vec4 ambient, inout vec4 diffuse, inout vec4 specular) {

  // normalized light source direction and half vector
  vec3 s = normalize(tcSource[idx]);
  vec3 h = normalize(v + s);

  // check if surface point is inside spotlight cone
  float dirDotS = dot(lights[idx].spotDirection.xyz, 
      normalize(ecVertex - lights[idx].position.xyz));
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
