attribute vec4 vertexPosition;
attribute vec3 vertexColour;
/* [Add a vertex normal attribute.] */
attribute vec3 vertexNormal;
/* [Add a vertex normal attribute.] */
varying vec3 fragColour;
uniform mat4 projection;
uniform mat4 modelView;
void main()
{
/* [Setup scene vectors.] */
    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));
    fragColour = vec3(0.0);
/* [Setup scene vectors.] */

/* [Calculate the diffuse component.] */
    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 vertexDiffuseReflectionConstant = vertexColour;
    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));
    fragColour += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;
/* [Calculate the diffuse component.] */

/* [Calculate the ambient component.] */
    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);
    vec3 vertexAmbientReflectionConstant = vertexColour;
    fragColour += vertexAmbientReflectionConstant * ambientLightIntensity;
/* [Calculate the ambient component.] */

/* [Calculate the specular component.] */
    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));
    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);
    float shininess = 2.0;
    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);
    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
    fragColour += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;
/* [Calculate the specular component.] */

    /* Make sure the fragment colour is between 0 and 1. */
    clamp(fragColour, 0.0, 1.0);

    gl_Position = projection * modelView * vertexPosition;
}


