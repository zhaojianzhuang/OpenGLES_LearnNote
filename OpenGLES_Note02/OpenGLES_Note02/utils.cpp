//
//  utils.cpp
//  OpenGLES_Note02
//
//  Created by jianzhuangzhao on 2018/6/19.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "utils.h"

GLuint compileShader(GLenum shaderType, const char *shaderCode)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE)
    {
        char szLog[1024] = {0};
        GLsizei loglen = 0;
        glGetShaderInfoLog(shader, 1024, &loglen, szLog);
        printf("compile shader failed error log\n: %s shaderCode:\n%s", szLog, shaderCode);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint createProgram(GLuint vsShader, GLuint fsShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vsShader);
    glAttachShader(program, fsShader);
    glLinkProgram(program);
    glDetachShader(program, vsShader);
    glDetachShader(program, fsShader);
    GLint nResult;
    glGetProgramiv(program, GL_LINK_STATUS, &nResult);
    if (nResult==GL_FALSE)
    {
        char log[1024]={0};
        GLsizei writed = 0;
        glGetProgramInfoLog(program, 1024, &writed, log);
        printf("create gpu program failed link error: \n %s \n", log);
        glDeleteProgram(program);
        program = 0;
        
    }
    return program;
}

unsigned char *decodeBMP(unsigned char *bmpFileData, int &width, int &height)
{
    if (0x4D42 == *((unsigned short*)bmpFileData))
    {
        int pixelDataOffset = *((int*)(bmpFileData + 10));
        width = *((int*)(bmpFileData + 18));
        height = *((int*)(bmpFileData + 22));
        unsigned char*pixelData = bmpFileData + pixelDataOffset;
        for (int i = 0; i < width*height * 3; i += 3)
        {
            unsigned char temp = pixelData[i];
            pixelData[i] = pixelData[i + 2];
            pixelData[i + 2] = temp;
        }
        return pixelData;
    }
    return nullptr;
}

GLuint createTexture2D(unsigned char *data, int width, int height, GLenum type)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

GLuint createTextureFromBMP(const char *imagePath)
{
    int fileSize = 0;
    unsigned char *bmpContent = loadFileContent(imagePath, fileSize);
    if (bmpContent == nullptr) return 0;
    
    int width = 0, height = 0 ;
    unsigned char *dataContent = decodeBMP(bmpContent, width, height);
    if (width == 0) return 0;
    GLuint texture = createTexture2D(dataContent, width, height, GL_RGB);
    
    delete bmpContent;
    return texture;
}




















