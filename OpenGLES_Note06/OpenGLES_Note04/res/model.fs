#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D U_Texture;
uniform vec4 U_LightPos;
uniform vec4 U_LightAmbient;
uniform vec4 U_LightSpecular;
uniform vec4 U_LightDiffuse;
uniform vec4 U_SpecularMaterial;
uniform vec4 U_DiffuseMaterial;
uniform vec4 U_AmbientMaterial;
uniform vec4 U_CameraPos;
uniform vec4 U_LightOpt;
varying vec4 V_Texcoord;
varying vec4 V_Color;
varying vec4 V_Normal;
varying vec4 V_WorldPos;
void main()
{
    vec4 color=vec4(0.0,0.0,0.0,0.0);
    vec4 ambientColor=U_LightAmbient*U_AmbientMaterial;
    vec3 lightPos=U_LightPos.xyz;
    vec3 L=lightPos;
    L=normalize(L);
    vec3 n=normalize(V_Normal.xyz);
    float diffuseIntensity=max(0.0,dot(L,n));
    vec4 diffuseColor=U_LightDiffuse*U_DiffuseMaterial*diffuseIntensity;
    vec4 specularColor=vec4(0.0,0.0,0.0,0.0);
    if(diffuseIntensity!=0.0){
        vec3 reflectDir=normalize(reflect(-L,n));
        vec3 viewDir=normalize(U_CameraPos.xyz-V_WorldPos.xyz);
        specularColor=U_LightSpecular*U_SpecularMaterial*pow(max(0.0,dot(viewDir,reflectDir)),U_LightOpt.x);
    }
    color=ambientColor+diffuseColor*texture2D(U_Texture,V_Texcoord.xy)+specularColor;
    gl_FragColor=color;
}
//镜面反射
//#ifdef GL_ES
//precision mediump float;
//#endif
//uniform sampler2D U_Texture;
//uniform vec4 U_LightPos; 点光源
//uniform vec4 U_LightAmbient;
//uniform vec4 U_LightDiffuse;
//uniform vec4 U_DiffuseMaterial;
//uniform vec4 U_AmbientMaterial;
//varying vec4 V_Texcoord;
//varying vec4 V_Color;
//varying vec4 V_Normal;
//void main()
//{
//    vec4 color=vec4(0.0,0.0,0.0,0.0);
//    vec4 ambientColor=U_LightAmbient*U_AmbientMaterial;
//    vec3 lightPos=U_LightPos.xyz;
//    vec3 L=lightPos;
//    L=normalize(L);
//    vec3 n=normalize(V_Normal.xyz);
//    float diffuseIntensity=max(0.0,dot(L,n));
//    vec4 diffuseColor=U_LightDiffuse*U_DiffuseMaterial*diffuseIntensity;
//    color=ambientColor+diffuseColor;
//    gl_FragColor=color+texture2D(U_Texture,V_Texcoord.xy);
//}
// 环境光
//#ifdef GL_ES
//precision mediump float;
//#endif
//uniform sampler2D U_Texture;
//uniform vec4 U_LightAmbient;
//uniform vec4 U_AmbientMaterial;
//varying vec4 V_Texcoord;
//void main()
//{
//    vec4 color=vec4(0.0,0.0,0.0,0.0);
//    vec4 ambientColor=U_LightAmbient*U_AmbientMaterial;
//    color=ambientColor;
//    gl_FragColor=color+texture2D(U_Texture,V_Texcoord.xy);
//}
