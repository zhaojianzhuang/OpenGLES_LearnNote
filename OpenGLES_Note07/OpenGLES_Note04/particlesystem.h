//
//  particlesystem.h
//  OpenGLES_Note04
//
//  Created by jianzhuangzhao on 2018/7/2.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#pragma once
#include "vertexbuffer.h"
#include "shader.h"
class ParticleSystem {
    /// data
    VertexBuffer *mVertexBuffer;
    
    /// model matrix
    glm::mat4 mModelMatrix;
    
    /// texture
    GLuint mTexture;
public:
    /// handle shader
    Shader *mShader;
    /// init mdoel matrix
    
    void init(float x, float y, float z);
    /// draw
    
    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
    
    /// update 
    void update(float deltaTime);
};
