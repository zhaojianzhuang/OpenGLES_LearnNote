//
//  shader.h
//  ES
//
//  Created by jianzhuangzhao on 2018/5/31.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#pragma once
#include "ggl.h"

/// texture
struct UniformTexture
{
    GLuint mLocation;
    GLuint mTexture;
    
    UniformTexture ()
    {
        mLocation = -1;
        mTexture = 0 ;
    }
};

/// vec4
struct UniformVector4f
{
    GLuint mLocation;
    float v[4];
    UniformVector4f()
    {
        mLocation = 0;
        memset(v, 0, sizeof(float) * 4);
    }
};


class Shader
{
public:
    ///  UniformTexture mTexture
    std::map<std::string, UniformTexture *> mUniformTextures;
    ///  UniformVec4 mUiformVec4s
    std::map<std::string, UniformVector4f *> mUiformVec4s;
    ///     program
    GLuint mProgram;
    /// mvp matrix
    GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMatrixLocation;
    ///  normal slot
    GLint mPositionLocation, mColorLocation, mTexcoordLocation, mNormalLocation;
    
    
    ///  init with .vs's path and .fs's path
    ///  init property 
    void init(const char*vs, const char*fs);
    
    
    ///  bind mvp matrix
    ///  assignment the data to opengl
    void bind(float *M, float *V, float*P);
    
    
    ///  set texture
    ///  name is the slot, path is the image's path
    void setTexture(const char *name,const char *path);
    
    
    /// set shader's vec4 value
    /// name is shader's key, x, y, z, w is the value
    void setVec4(const char *name, float x, float y, float z,float w);
};

