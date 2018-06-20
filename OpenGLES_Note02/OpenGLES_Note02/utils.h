//
//  utils.h
//  OpenGLES_Note02
//
//  Created by jianzhuangzhao on 2018/6/19.
//  Copyright © 2018年 ZJZ. All rights reserved.
//
#include "ggl.h"

/// load file content from path
/// path is where is document
/// filesize document's size quote
unsigned char *loadFileContent(const char *path, int &fileSize);


///  compile shader with shader's type and shader's code
///  the shader's code (shaderCode) that can from function loadFileContent()
///  the shader's type (shaderType) that can be GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
GLuint compileShader(GLenum shaderType, const char *shaderCode);

///  create a program with vs and fs
///  vs and fs must be compiled
GLuint createProgram(GLuint vsShader, GLuint fsShader);


///  deocde a bmp file data
///  width and height is a quote after fucntion completed the width and height can be correct
///  because bmp file data format is bgr, so the decoded's data is rgb format
unsigned char *decodeBMP(unsigned char *bmpFileData, int &width, int &height);

///  create a texture
///  data width height must corrted
///
GLuint createTexture2D(unsigned char *data, int width, int height, GLenum type);

///  create a bmp texture with imagePath
///  packaging decodeBMP() and createTexture2D()
///  we can use this more convenience to get a texture 
GLuint createTextureFromBMP(const char *imagePath);
