//
//  skybox.h
//  ES
//
//  Created by jianzhuangzhao on 2018/6/17.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#pragma once
#include "vertexbuffer.h"
#include "shader.h"
class SkyBox
{
    /// data
    VertexBuffer *mVertexBuffer;
    /// shader
    Shader *mShader;
    /// model matrix
    glm::mat4 mModelMatrix;
public:
    
    /// init with image dir
    void init(const char *imageDir);
    
    /// init front
    void initFront(const char *imageDir);
    
    /// init back
    void initBack(const char *imageDir);
    
    /// init left
    void initLeft(const char *imageDir);
    
    /// init right
    void initRight(const char *imageDir);
    
    /// init top
    void initTop(const char *imageDir);
    
    /// init bottom
    void initBottom(const char *imageDir);
    
    /// draw with matrix
    /// camera's position that can guarantee in a skybox
    void draw(glm::mat4 &v, glm::mat4 &p, float x, float y, float z);
};
