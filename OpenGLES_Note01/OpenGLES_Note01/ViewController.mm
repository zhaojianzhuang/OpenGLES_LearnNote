//
//  ViewController.m
//  OpenGLES_Note01
//
//  Created by jianzhuangzhao on 2018/6/19.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#import "ViewController.h"
#import "scene.h"
@interface ViewController ()
@property (nonatomic, strong) EAGLContext *mContext;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self p_InitConfig];
    init();
    CGRect rect = self.view.bounds;
    setViewPortSize(rect.size.width, rect.size.height);
}


#pragma mark - private
/// init config
- (void)p_InitConfig
{
    self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!self.mContext)
    {
        self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    }
    if (!self.mContext)
    {
        self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    }
    NSAssert(self.mContext, @"mContext 初始化失败");
    
    GLKView *glkView = (GLKView *)self.view;
    glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    glkView.context = self.mContext;
    [EAGLContext setCurrentContext:self.mContext]; 
}


- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    draw();
}


@end
