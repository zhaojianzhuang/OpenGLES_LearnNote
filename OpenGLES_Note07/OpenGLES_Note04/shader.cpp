//
//  shader.cpp
//  ES
//
//  Created by jianzhuangzhao on 2018/5/31.
//  Copyright © 2018年 ZJZ. All rights reserved.
//
#include "shader.h"
#include "until.h"
#include "vertexbuffer.h"
void Shader::init(const char*vs, const char*fs)
{
    int nFileSize = 0;
    const char*vsCode = (char*)loadFileContent(vs,nFileSize);
    const char*fsCode = (char*)loadFileContent(fs,nFileSize);
    GLuint vsShader = complileShader(GL_VERTEX_SHADER, vsCode);
    if (vsShader==0)
    {
        return;
    }
    GLuint fsShader = complileShader(GL_FRAGMENT_SHADER, fsCode);
    if (fsShader == 0)
    {
        return;
    }
    mProgram=createProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    if (mProgram!=0)
    {
        mModelMatrixLocation = glGetUniformLocation(mProgram, "ModelMatrix");
        mViewMatrixLocation = glGetUniformLocation(mProgram, "ViewMatrix");
        mProjectionMatrixLocation = glGetUniformLocation(mProgram, "ProjectionMatrix");
        mPositionLocation = glGetAttribLocation(mProgram, "position");
        mColorLocation = glGetAttribLocation(mProgram, "color");
        mTexcoordLocation = glGetAttribLocation(mProgram, "texcoord");
        mNormalLocation = glGetAttribLocation(mProgram, "normal");
    }
}

void Shader::bind(float *M, float *V, float *P)
{
    glUseProgram(mProgram);
    glUniformMatrix4fv(mModelMatrixLocation, 1, GL_FALSE, M);
    glUniformMatrix4fv(mViewMatrixLocation, 1, GL_FALSE, V);
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, P);
    int iIndex = 0;
    for (auto iter = mUniformTextures.begin(); iter != mUniformTextures.end(); ++iter)
    {
        glActiveTexture(GL_TEXTURE0+iIndex);
        glBindTexture(GL_TEXTURE_2D, iter->second->mTexture);
        glUniform1i(iter->second->mLocation, iIndex++);
    }
    
    for (auto iter = mUiformVec4s.begin(); iter != mUiformVec4s.end(); ++iter) {
        glUniform4fv(iter->second->mLocation, 1, iter->second->v);
    }
    glEnableVertexAttribArray(mPositionLocation);
    glVertexAttribPointer(mPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(mColorLocation);
    glVertexAttribPointer(mColorLocation,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float)*4));
    glEnableVertexAttribArray(mTexcoordLocation);
    glVertexAttribPointer(mTexcoordLocation,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float)*8));
    glEnableVertexAttribArray(mNormalLocation);
    glVertexAttribPointer(mNormalLocation,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float)*12));
}


void Shader::setTexture(const char *name,const char *path)
{
    auto iter = mUniformTextures.find(name);
    if (iter == mUniformTextures.end()){
        GLint location = glGetUniformLocation(mProgram, name);
        if (location != -1){
            UniformTexture *t = new UniformTexture;
            t -> mLocation = location;
            t -> mTexture = createTextureFromBMP(path);
            mUniformTextures.insert(std::pair<std::string, UniformTexture *>(name, t));
        }
    } else
    {
        glDeleteTextures(1, &iter->second->mTexture);
        iter->second->mTexture = createTextureFromBMP(path);
    }
}
void Shader::setVec4(const char *name, float x, float y, float z, float w)
{
    auto iter = mUiformVec4s.find(name);
    if (iter == mUiformVec4s.end())
    {
        GLint location = glGetUniformLocation(mProgram, name);
        if (location != -1)
        {
            UniformVector4f *v = new UniformVector4f;
            v->v[0] = x;
            v->v[1] = y;
            v->v[2] = z;
            v->v[3] = w;
            v->mLocation = location;
            mUiformVec4s.insert(std::pair<std::string, UniformVector4f *>(name, v));
            
        }
    }else
    {
        iter->second->v[0] = x;
        iter->second->v[1] = y;
        iter->second->v[2] = z;
        iter->second->v[3] = w;
    }
}
