precision mediump float;
uniform sampler2D texture;
varying vec2 textureCord;
varying vec3 varyingColor;
varying vec3 inverseLightDirection;
varying vec3 inverseEyeDirection;
varying vec3 transformedVertexNormal;
void main()
{
   vec3 fragColor = vec3(0.0,0.0,0.0); 
   vec3 normal = texture2D(texture, textureCord).xyz;
   normal = normalize(normal * 2.0 -1.0);
// Calculate the diffuse component. *
   vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);
   float normalDotLight = max(0.0, dot(normal, inverseLightDirection));
   fragColor += normalDotLight * varyingColor *diffuseLightIntensity;
// Calculate the ambient component. *
   vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);
   fragColor +=  ambientLightIntensity * varyingColor;
// Calculate the specular component. *
   vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);
   vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);
   float shininess = 2.0;
   vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, normal);
   float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
   fragColor += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;
   /* Make sure the fragment colour is between 0 and 1. */
   clamp(fragColor, 0.0, 1.0);
   gl_FragColor = vec4(fragColor,1.0);
}