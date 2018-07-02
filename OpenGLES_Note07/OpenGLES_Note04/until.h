//
//  until.h
//  ES
//
//  Created by jianzhuangzhao on 2018/5/26.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#pragma once
#include "ggl.h"


///  load file's content from path
///  get the binary system content
///  path is the path of file. fileSize is a quote, that will be fileSize after load
unsigned char *loadFileContent(const char *path, int &fileSize);

///  create a texture
///  data、width and height must corrted
GLuint createTexture2D(unsigned char *data, int width, int height, GLenum type);

///  create a bmp texture with imagePath
///  packaging decodeBMP() and createTexture2D()
///  we can use this more convenience to get a texture
GLuint createTextureFromBMP(const char *imagePath);

///  create a vbo
///  data can be nullptr, that you must call glBufferSubData() function before draw
GLuint createBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data=nullptr);

///  deocde a bmp file data
///  width and height is a quote after fucntion completed the width and height can be correct
///  because bmp file data format is bgr, so the decoded's data is rgb format
unsigned char *decodeBMP(unsigned char *bmpFileData, int &width, int &height);

///  compile shader with shader's type and shader's code
///  the shader's code (shaderCode) that can from function loadFileContent()
///  the shader's type (shaderType) that can be GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
GLuint complileShader(GLenum shaderType, const char *shaderCode);

///  create a program with vs and fs
///  vs and fs must be compiled
GLuint createProgram(GLuint vsShader, GLuint fsShader);

///  get frames
float getFrameTime();


/// create a texure with no data 
GLuint createProduceTexture(int size);






