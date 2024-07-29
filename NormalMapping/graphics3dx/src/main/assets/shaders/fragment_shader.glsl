precision mediump float;
uniform sampler2D texture;
varying vec2 textureCord;
varying vec3 diffuseLighting;
varying vec3 ambientLighting;
varying vec3 specularLighting;
void main()
{

    vec4 textureColor = texture2D(texture, textureCord);

    vec4 finalColor = vec4(0.0);
    finalColor += vec4(diffuseLighting, 1.0) * textureColor;
    finalColor += vec4(ambientLighting, 1.0) * textureColor;
    finalColor += vec4(specularLighting, 1.0) * textureColor;
    finalColor = clamp(finalColor, 0.0, 1.0);

    gl_FragColor = finalColor;

}


