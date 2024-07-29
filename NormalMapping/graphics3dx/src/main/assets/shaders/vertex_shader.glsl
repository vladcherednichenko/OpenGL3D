attribute vec4 vertexPosition;
attribute vec2 vertexTextureCord;
attribute vec3 vertexNormal;
attribute vec3 vertexColor; 
attribute vec3 vertexTangent;
attribute vec3 vertexBiNormal;
varying vec2 textureCord;
varying vec3 varyingColor; 
varying vec3 inverseLightDirection;
varying vec3 inverseEyeDirection;
uniform mat4 projection;
uniform mat4 modelView;
void main()
{
   vec3 worldSpaceVertex =(modelView * vertexPosition).xyz;
   vec3 transformedVertexNormal = normalize((modelView *  vec4(vertexNormal, 0.0)).xyz);
   inverseLightDirection = normalize(vec3(0.0, 0.0, 1.0));
   inverseEyeDirection = normalize((vec3(0.0, 0.0, 1.0)- worldSpaceVertex ).xyz);
   gl_Position = projection * modelView * vertexPosition;
   textureCord = vertexTextureCord;
   varyingColor = vertexColor;
   vec3 transformedTangent = normalize((modelView * vec4(vertexTangent, 0.0)).xyz);
   vec3 transformedBinormal = normalize((modelView * vec4(vertexBiNormal, 0.0)).xyz);
   mat3 tangentMatrix = mat3(transformedTangent, transformedBinormal, transformedVertexNormal);
   inverseLightDirection =inverseLightDirection * tangentMatrix;
   inverseEyeDirection = inverseEyeDirection * tangentMatrix;
}