precision mediump float;
uniform sampler2D texture;
varying vec2 textureCord;
varying vec3 lighting;
void main()
{

    vec4 textureColor = texture2D(texture, textureCord);
    gl_FragColor = textureColor * vec4(lighting, 1.0);

}


