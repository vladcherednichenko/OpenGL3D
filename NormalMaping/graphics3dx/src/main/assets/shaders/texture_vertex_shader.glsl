attribute vec4 vertexPosition;
attribute vec2 vertexTextureCord;
varying vec2 textureCord;
uniform mat4 projection;
uniform mat4 modelView;
void main()
{
    gl_Position = projection * modelView * vertexPosition;
    textureCord = vertexTextureCord;
}