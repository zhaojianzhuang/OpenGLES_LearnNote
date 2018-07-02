//
//  until.cpp
//  ES
//
//  Created by jianzhuangzhao on 2018/5/26.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "until.h"
#include <sys/time.h>

GLuint complileShader(GLenum shaderType, const char *shaderCode)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE)
    {
        char szLog[1024] = { 0 };
        GLsizei logLen = 0;
        glGetShaderInfoLog(shader, 1024, &logLen, szLog);
        printf("Compile Shader fail error log : %s \nshader code :\n%s\n", szLog, shaderCode);
        glDeleteShader(shader);
        shader = 0;
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
    if (nResult == GL_FALSE)
    {
        char log[1024] = { 0 };
        GLsizei writed = 0;
        glGetProgramInfoLog(program, 1024, &writed, log);
        printf("create gpu program fail,link error : %s\n", log);
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}

float getFrameTime()
{
    static unsigned long long lastTime = 0 , currentTime = 0;
    timeval current;
    gettimeofday(&current, nullptr);
//    tv_sec 秒 tv_usec 微妙 1000000
    currentTime = current.tv_sec * 1000 + current.tv_usec / 1000;
    unsigned long long frameTime = lastTime == 0 ? 0 : currentTime - lastTime;
    lastTime = currentTime;
    return float(frameTime) / 1000.0f;
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
    unsigned char *dataContent =  decodeBMP(bmpContent, width, height);
    if (width == 0) return 0;
    GLuint texture = createTexture2D(dataContent, width, height, GL_RGB);
    
    delete bmpContent;
    return texture;
}



GLuint createBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data /* == nullptr */)
{
    GLuint object;
    glGenBuffers(1, &object);
    glBindBuffer(bufferType, object);
    glBufferData(bufferType, size, data, usage);
    glBindBuffer(bufferType, 0);
    return  object;
}

GLuint createProduceTexture(int size)
{
    unsigned char *imageData = new unsigned char[size * size * 4];
    float halfSize = (float)size / 2.0f;
    float maxDistance = sqrt(halfSize * halfSize + halfSize * halfSize);
    float centerX = halfSize;
    float centerY = halfSize;
    for (int y = 0 ; y < size; y++) {
        for (int x = 0;  x < size; x++ ) {
            int currentPixedOffset= (x + y * size) * 4;
            imageData[currentPixedOffset] = 255;
            imageData[currentPixedOffset + 1] = 255;
            imageData[currentPixedOffset + 2] = 255;
            float deltaX = (float)x - centerX;
            float deltaY = (float)y - centerY;
            float distancce = sqrt(deltaX * deltaX + deltaY * deltaY);
            float alpha = powf(1.0f- (distancce / maxDistance), 8.0f);
            alpha = alpha > 1.0f ? 1.0f : alpha;
            imageData[currentPixedOffset + 3] = (unsigned char)(alpha * 255.0f);
        }
    }
    GLuint texture = createTexture2D(imageData, size, size, GL_RGBA);
    delete imageData;
    return texture;
}



















