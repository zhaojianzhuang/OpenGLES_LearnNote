//
//  scene.cpp
//  OpenGLES_Note01
//
//  Created by jianzhuangzhao on 2018/6/19.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "scene.h"
#include "ggl.h"
#include "utils.h"
GLuint vbo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
void init()
{
    //    cpu数据
    //
    float data[] = {
        -0.2f, -0.2f, -0.6f, 1.0f,
        0.2f, -0.2f, -0.6f, 1.0f,
        0.0f, 0.2f, -0.6f, 1.0f
    };
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    
    int fileSize = 0 ;
    unsigned char *shaderCode = loadFileContent("res/test.fs", fileSize);
    
    GLuint fsShader = compileShader(GL_FRAGMENT_SHADER, (char *)shaderCode);
    shaderCode = loadFileContent("res/test.vs", fileSize);
    GLuint vsShader = compileShader(GL_VERTEX_SHADER, (char *)shaderCode);
    program = createProgram(vsShader, fsShader);
    positionLocation = glGetAttribLocation(program, "position");
    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
    viewMatrixLocation  = glGetUniformLocation(program, "ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
}

void draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program);
    //    设置uniform
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    //     设置attribute 
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);
    
}

void setViewPortSize(float width, float height)
{
    projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}


