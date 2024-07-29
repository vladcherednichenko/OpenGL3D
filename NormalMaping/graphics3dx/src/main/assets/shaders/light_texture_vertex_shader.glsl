attribute vec4 vertexPosition;
attribute vec2 vertexTextureCoord;
attribute vec3 vertexNormal;

varying vec2 textureCoord;
varying vec3 lightingEffect;

uniform mat4 projection;
uniform mat4 modelView;

void main() {
    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));
    vec3 fragColour = vec3(0.0);

    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);
    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));
    fragColour += normalDotLight * diffuseLightIntensity;

    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);
    fragColour += ambientLightIntensity;

    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));
    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);
    float shininess = 2.0;
    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);
    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
    fragColour += pow(normalDotReflection, shininess) * specularLightIntensity;

    lightingEffect = clamp(fragColour, 0.0, 1.0);

    gl_Position = projection * modelView * vertexPosition;
    textureCoord = vertexTextureCoord;
}
