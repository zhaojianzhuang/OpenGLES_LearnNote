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



GLuint compileShader(GLenum shaderType, const char *shaderCode);


GLuint createProgram(GLuint vsShader, GLuint fsShader);
