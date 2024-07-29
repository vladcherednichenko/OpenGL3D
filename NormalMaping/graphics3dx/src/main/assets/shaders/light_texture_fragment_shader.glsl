precision mediump float;

uniform sampler2D texture;
varying vec2 textureCoord;
varying vec3 lightingEffect;

void main() {
    vec4 textureColor = texture2D(texture, textureCoord);
    gl_FragColor = textureColor * vec4(lightingEffect, 1.0);
}
