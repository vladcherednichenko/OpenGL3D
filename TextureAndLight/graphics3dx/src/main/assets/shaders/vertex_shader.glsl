attribute vec4 vertexPosition;
attribute vec2 vertexTextureCord;
attribute vec3 vertexNormal;
uniform mat4 projection;
uniform mat4 modelView;

varying vec2 textureCord;
varying vec3 diffuseLighting;
varying vec3 ambientLighting;
varying vec3 specularLighting;


void main()
{

    /* [Setup scene vectors.] */
    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));
    vec3 fragColour = vec3(0.0);
    /* [Setup scene vectors.] */

    /* [Calculate the diffuse component.] */
    float diffuse = 0.5;
    vec3 diffuseLightIntensity = vec3(diffuse);
    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));
    diffuseLighting = normalDotLight * diffuseLightIntensity;
    /* [Calculate the diffuse component.] */

    /* [Calculate the ambient component.] */
    float ambient = 0.1;
    vec3 ambientLightIntensity = vec3(ambient);
    ambientLighting = ambientLightIntensity;
    /* [Calculate the ambient component.] */

    /* [Calculate the specular component.] */
    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));
    float specular = 1.0;
    vec3 specularLightIntensity = vec3(specular);
    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);
    float shininess = 2.0;
    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);
    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
    specularLighting = pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;
    /* [Calculate the specular component.] */


    gl_Position = projection * modelView * vertexPosition;
    textureCord = vertexTextureCord;

}