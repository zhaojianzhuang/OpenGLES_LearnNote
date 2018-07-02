//
//  ViewController.m
//  ES
//
//  Created by jianzhuangzhao on 2018/5/26.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#import "ViewController.h"
#include "scene.h"

//加载文件
unsigned char *loadFileContent(const char *path, int &fileSize)
{
    unsigned char *fileContent = nullptr;
    fileSize = 0;
    NSString *nsPath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:path] ofType:nil];
    NSData *data = [NSData dataWithContentsOfFile:nsPath];
    if (data.length > 0)
    {
        fileSize = (int )data.length;
        fileContent = new unsigned char[fileSize + 1];
        memcpy(fileContent, data.bytes, fileSize);
        fileContent[fileSize] = '\0';
    }
    return fileContent;
}




@interface ViewController ()

/**~上下文~**/
@property (nonatomic, strong) EAGLContext *context;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    [self p_InitConfig];
}
#pragma mark - private
//初始化设置
- (void)p_InitConfig
{
//    初始化上下文, 如果es3不成功设置成es2 再不成, 失败返回
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!self.context) self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!self.context)  NSLog(@"失败");
    if (!self.context)  return;
    
//    设置view
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:self.context];
    init();
    CGRect rect = [UIScreen mainScreen].bounds;
    setViewPortSize(rect.size.width, rect.size.height);
}
#pragma mark - draw
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    draw();
}

@end
