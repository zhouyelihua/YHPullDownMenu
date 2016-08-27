//
//  YHPullDownMenu.h
//  GrabOnePackage
//
//  Created by maoer on 16/8/26.
//  Copyright © 2016年  All rights reserved.
//


#import <UIKit/UIKit.h>
typedef void(^YHPullDownMenuClickIndexBlock)(NSInteger index);
@interface YHPullDownMenu : UIView
@property(nonatomic,strong)UIView*pdContentView;
+ (instancetype)dropdownMenuWithItems:(NSArray*)items;
-(instancetype)initPullDownMenuWithItems:(NSArray*)items
                              cellHeight:(CGFloat)cellHeight
                               menuFrame:(CGRect) menuFrame
                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle;
/**
 *  IOS下拉菜单初始化函数
 *
 *  @param items      此处传入的是一个nsarray主要是listview的显示内容
 *  @param cellHeight 这个是每个cell的高度
 *  @param menuFrame  这个是listview的frame信息
 *  @param bgImage    这个是背景图案
 *  @param handle     这个是传回来的参数
 *
 *  @return instancetype
 */
-(instancetype)initPullDownMenuWithItems:(NSArray*)items
                              cellHeight:(CGFloat)cellHeight
                               menuFrame:(CGRect) menuFrame
                                  bgImge:(UIImage*)bgImage
                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle;
-(void)show;
@end
