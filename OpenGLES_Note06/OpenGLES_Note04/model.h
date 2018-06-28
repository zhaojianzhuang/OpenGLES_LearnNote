//
//  model.h
//  OpenGLES_Note04
//
//  Created by jianzhuangzhao on 2018/6/27.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "ggl.h"
#include "vertexbuffer.h"
#include "shader.h"

class Model {
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
    
public:
    Model();
    glm::mat4 mModelMatrix;
    void init(const char *modelPath);
    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMarix, float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setTexture(const char *imagePath);
};
