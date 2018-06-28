attribute vec4 position;
attribute vec4 color;
attribute vec4 texcoord;
attribute vec4 normal;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 IT_ModelMatrix;
varying vec4 V_Normal;
varying vec4 V_Color;
varying vec4 V_Texcoord;
varying vec4 V_WorldPos;
void main()
{
    V_Texcoord=texcoord;
    V_Normal=IT_ModelMatrix*normal;
    V_Color=color;
    V_WorldPos=ModelMatrix*position;
    gl_Position=ProjectionMatrix*ViewMatrix*ModelMatrix*position;
}
