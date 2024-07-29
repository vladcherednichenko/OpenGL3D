attribute vec4 vertexPosition;
attribute vec2 vertexTextureCord;
attribute vec3 vertexNormal;
uniform mat4 projection;
uniform mat4 modelView;

varying vec2 textureCord;
varying vec3 lighting;

void main()
{

    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));
    vec3 fragColour = vec3(0.0);

    vec3 diffuseLightIntensity = vec3(0.5, 0.5, 0.5);
    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));
    fragColour += normalDotLight * diffuseLightIntensity;

    float ambientLight = 0.1;
    vec3 ambientLightIntensity = vec3(ambientLight, ambientLight, ambientLight);
    fragColour += ambientLightIntensity;

    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));
    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);
    float shininess = 2.0;
    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);
    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
    fragColour += pow(normalDotReflection, shininess) * specularLightIntensity;


    lighting = clamp(fragColour, 0.0, 1.0);

    gl_Position = projection * modelView * vertexPosition;
    textureCord = vertexTextureCord;

}