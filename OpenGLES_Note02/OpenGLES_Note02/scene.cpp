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
/// vbo
GLuint vbo;

/// program
GLuint program;

/// shader's locaiton
GLint positionLocation, colorLocation,  modelMatrixLocation,
      viewMatrixLocation, projectionMatrixLocation;

/// shader's texutre location
GLuint texcoordLocation, textureLocation, textureLocation2;

/// photo's texture
GLuint texture, texture2;

/// mvp
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;

void init()
{
    //    cpu data
    //
    float data[] = {
        -0.2f, -0.2f, -0.6f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.2f, -0.2f, -0.6f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.2f, -0.6f, 1.0f,    0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f,
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
    colorLocation = glGetAttribLocation(program, "color");
    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
    viewMatrixLocation  = glGetUniformLocation(program, "ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
    texcoordLocation = glGetAttribLocation(program, "texcoord");
    textureLocation = glGetUniformLocation(program, "U_Texture");
    textureLocation2 = glGetUniformLocation(program, "U_Texture2");
    
    texture = createTextureFromBMP("res/test.bmp");
    texture2 = createTextureFromBMP("res/niutou.bmp");
}

void draw()
{
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program);
    
    
    //    set uniform
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    //     set attribute
//    single texture
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glUniform1i(textureLocation, 0);
    
//    more texture
    glActiveTexture(GL_TEXTURE0+0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
    
    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(textureLocation2, 1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void *)(sizeof(float) * 4));
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void *)(sizeof(float) * 8));
    //    draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);
    
}

void setViewPortSize(float width, float height)
{
    projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}



