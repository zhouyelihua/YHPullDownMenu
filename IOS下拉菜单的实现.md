#IOS下拉菜单的实现
##在IOS并没有下拉菜单的实现，所以我们通过实现一个下拉菜单来实现这个功能
 代码可以在github上下载*https://github.com/zhouyelihua/YHPullDownMenu*
 把YHPullDownMenu.h和YHPullDownMenu.m文件添加到你的工程中，按照以下调用方式就可以
```objective-c
    NSArray *items = @[@"东方不败", @"步惊云", @"女娲大帝"];
    YHPullDownMenu *pd=[[YHPullDownMenu alloc]initPullDownMenuWithItems:items cellHeight:35 menuFrame:CGRectMake([UIScreen mainScreen].bounds.size.width-125-10, 136, 125, 115) clickIndexHandle:^(NSInteger index) {
        switch (index) {
            case 0://这个是选中哪一行的时候的输出，或者执行的动作，此处打印相关的信息
                NSLog(@"selected=东方不败;");
                break;
            case 1:
                
                NSLog(@"selected=步惊云;");
                break;
            case 2:
                NSLog(@"selected=女娲大帝;");
                break;
                
            default:
                break;
        }
    }];
    pd.backgroundColor=[UIColor clearColor];
    [pd show];
```
其中items是下拉菜单的中需要显示的文字内容。
显示效果：
<img src="https://bytebucket.org/zhouyelihua/markdownphoto/raw/68fb296a2ff03e85b17b797b29849ac3d5114b6d/iPhone%206s%20Plus%20-%20iPhone%206s%20Plus%20-%20iOS%209.3%20%2813E230%29%20Simulator%2C%20%E4%BB%8A%E5%A4%A9%20at%20%E4%B8%8B%E5%8D%881.12.10.png?token=688210b53fdecc97ea937ba62cb6f4fa61d44216" width="300" height="443" alt="第二次测试"/>
</div>
具体的调用函数
```objective-c
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
```
上文中的调用是设置了一个默认的图片而已
```objective-c
-(instancetype)initPullDownMenuWithItems:(NSArray*)items
                              cellHeight:(CGFloat)cellHeight
                               menuFrame:(CGRect) menuFrame
                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle{
    
    return [self initPullDownMenuWithItems:items
                                cellHeight:cellHeight
                                 menuFrame: menuFrame
                                   bgImage:[UIImage imageNamed:@"avatar"]
                          clickIndexHandle:(YHPullDownMenuClickIndexBlock)[handle copy]];
}
```
你也可以将默认的图片[UIImage imageNamed:@"avatar"]就是那个蜗牛换成你的默认背景，或者直接为空
还有注意一点就是如果你不想点击框体外时候，框框消失，你可以把以下函数删除
```objective-c
/**
 *  /
 *  /如果不想要点击外面的时候，下拉菜单也消失的话，可以去掉该函数
 */
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self dismiss];
}

```
下面是具体的代码，第一个是YHPullDownMenu.h代码
```objective-c
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

```
接着是YHPullDownMenu.m文件

```objective-c
//
//  YHPullDownMenu.m
//  GrabOnePackage
//
//  Created by maoer on 16/8/26.
//  Copyright © 2016年 . All rights reserved.
//

#import "YHPullDownMenu.h"

@interface YHPullDownMenu()<UITableViewDelegate,UITableViewDataSource>
@property(nonatomic, strong)NSArray<NSString*> *items;
@property(nonatomic,strong)YHPullDownMenuClickIndexBlock block;
@property(nonatomic,strong)UITableView*tableView;
@property(nonatomic,strong)UIWindow*pdContainerwindow;
@property(nonatomic,strong)UIImageView*bgImageView;
@property(nonatomic,assign)NSInteger  cellHeight;
@property(nonatomic,strong)UIImage*bgImage;
@end

@implementation YHPullDownMenu

-(instancetype)initPullDownMenuWithItems:(NSArray*)items
                              cellHeight:(CGFloat)cellHeight
                               menuFrame:(CGRect) menuFrame
                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle{
    
    return [self initPullDownMenuWithItems:items
                                cellHeight:cellHeight
                                 menuFrame: menuFrame
                                   bgImage:[UIImage imageNamed:@"avatar"]
                          clickIndexHandle:(YHPullDownMenuClickIndexBlock)[handle copy]];
}

-(instancetype)initPullDownMenuWithItems:(NSArray*)items
                              cellHeight:(CGFloat)cellHeight
                               menuFrame:(CGRect) menuFrame
                                 bgImage:(UIImage*)bgImage
                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle{
    self=[super init];
    if(self){
        self.items=items;
        self.frame=[UIScreen mainScreen].bounds;
        self.backgroundColor=[UIColor yellowColor];
        self.block=[handle copy];
        self.bgImage=bgImage;
        [self setupPullDownMenuWithcellHeight:cellHeight
                                    menuFrame: menuFrame];
    }
    return self;
}
-(void)setupPullDownMenuWithcellHeight:(CGFloat)cellHeight
                             menuFrame:(CGRect) menuFrame{
    _pdContentView=[[UIView alloc]initWithFrame:menuFrame];
    _pdContentView.backgroundColor=[UIColor  clearColor];//设置背景颜色
    [self addSubview: self.pdContentView];
    _pdContentView.layer.borderWidth=0.5;//设置边框颜色
    _pdContentView.layer.borderColor=[UIColor grayColor].CGColor;//设置边框颜色
    self.bgImageView=[[UIImageView alloc]initWithImage:self.bgImage];
    [self.pdContentView addSubview:self.bgImageView];
    self.bgImageView.translatesAutoresizingMaskIntoConstraints=NO;
    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.bgImageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:menuFrame.size.width]];
    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.bgImageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:menuFrame.size.height]];
    
    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.bgImageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self.pdContentView attribute:NSLayoutAttributeCenterX multiplier:1.0f constant:0.0f]];
    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.bgImageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self.pdContentView attribute:NSLayoutAttributeCenterY multiplier:1.0f constant:0.0f]];
 
    self.cellHeight=cellHeight;
    _tableView=[[UITableView alloc]initWithFrame:menuFrame style:UITableViewStylePlain];
    _tableView.delegate=self;
    _tableView.dataSource=self;
    _tableView.backgroundColor=[UIColor clearColor];//设置表格背景颜色
    [self addSubview:_tableView];
//    self.tableView.translatesAutoresizingMaskIntoConstraints=NO;
//    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.tableView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:menuFrame.size.width]];
//    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.tableView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:menuFrame.size.height]];
//    
//    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.tableView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self.pdContentView attribute:NSLayoutAttributeCenterX multiplier:1.0f constant:0.0f]];
//    [self.pdContentView addConstraint:[NSLayoutConstraint constraintWithItem:self.tableView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self.pdContentView attribute:NSLayoutAttributeCenterY multiplier:1.0f constant:0.0f]];
    NSLog(@"");

}

/**
 *  /
 *  /如果不想要点击外面的时候，下拉菜单也消失的话，可以去掉该函数
 */
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self dismiss];
}


- (void)show{
    
    _pdContainerwindow=[[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    _pdContainerwindow.windowLevel=UIWindowLevelAlert;
    [_pdContainerwindow becomeKeyWindow];
    [_pdContainerwindow makeKeyAndVisible];
    [_pdContainerwindow addSubview:self];
    
    //  [self setShowAnimation];
    
}

-(void)dismiss{
    _items=nil;
    _tableView=nil;
    _pdContentView = nil;
    [self removeFromSuperview];
}
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.items count];
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:NSStringFromClass([self class])];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:NSStringFromClass([self class])];
        cell.textLabel.font = [UIFont fontWithName:@"Marion" size:14];
        cell.textLabel.textColor = [UIColor colorWithRed:255/255 green:66.0/255 blue:66.0/255 alpha:1.0];
        cell.backgroundColor = [UIColor clearColor];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    cell.textLabel.textAlignment=NSTextAlignmentCenter;
    cell.textLabel.text = self.items[indexPath.row];
    return cell;
}
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return  self.cellHeight;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    if (self.block) {
        self.block([indexPath row]);
        self.block = nil;
    }
    [self dismiss];
}-(void)setShowAnimation{
    
    CAKeyframeAnimation* animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
    animation.duration = 0.3;
    NSMutableArray *values = [NSMutableArray array];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(0.1, 0.1, 1.0)]];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.2, 1.2, 1.0)]];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(0.9, 0.9, 1.0)]];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.0, 1.0, 1.0)]];
    animation.values = values;
    
    [_pdContentView.layer addAnimation:animation forKey:nil];
}
- (CGSize)labelAutoCalculateRectWith:(NSString *)text Font:(UIFont *)font MaxSize:(CGSize)maxSize
{
    NSMutableParagraphStyle * paragraphStyle = [[NSMutableParagraphStyle alloc]init];
    paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
    NSDictionary * attributes = @{NSFontAttributeName:font, NSParagraphStyleAttributeName:paragraphStyle.copy};
    
    CGSize labelSize = [text boundingRectWithSize:maxSize options:NSStringDrawingUsesLineFragmentOrigin |NSStringDrawingUsesFontLeading |NSStringDrawingTruncatesLastVisibleLine attributes:attributes context:nil].size;
    labelSize.height = ceil(labelSize.height);
    labelSize.width = ceil(labelSize.width);
    return labelSize;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath{
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsMake(0, 10, 0, 10)];
    }
    
    // Prevent the cell from inheriting the Table View's margin settings
    if ([cell respondsToSelector:@selector(setPreservesSuperviewLayoutMargins:)]) {
        [cell setPreservesSuperviewLayoutMargins:NO];
    }
    
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
    
    ;
}

@end





///Masonry实现版本
////
////  YHPullDownMenu.m
////  GrabOnePackage
////
////  Created by maoer on 16/8/26.
////  Copyright © 2016年 All rights reserved.
////
//
//#import "YHPullDownMenu.h"
//#import "Masonry.h"
//
//@interface YHPullDownMenu()<UITableViewDelegate,UITableViewDataSource>
//@property(nonatomic, strong)NSArray<NSString*> *items;
//@property(nonatomic,strong)YHPullDownMenuClickIndexBlock block;
//@property(nonatomic,strong)UITableView*tableView;
//@property(nonatomic,strong)UIWindow*pdContainerwindow;
//@property(nonatomic,strong)UIImageView*bgImageView;
//@property(nonatomic,assign)NSInteger  cellHeight;
//@property(nonatomic,strong)UIImage*bgimage;
//@end
//
//@implementation YHPullDownMenu
//
//
//-(instancetype)initPullDownMenuWithItems:(NSArray*)items
//                              cellHeight:(CGFloat)cellHeight
//                               menuFrame:(CGRect) menuFrame
//                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle{
//    return [self initPullDownMenuWithItems:items
//                                cellHeight:cellHeight
//                                 menuFrame: menuFrame
//                                   bgImage:[UIImage imageNamed:@"avatar"]
//                          clickIndexHandle:[handle copy]];
//}
//-(instancetype)initPullDownMenuWithItems:(NSArray*)items
//                              cellHeight:(CGFloat)cellHeight
//                               menuFrame:(CGRect) menuFrame
//                                 bgImage:(UIImage*)bgImage
//                        clickIndexHandle:(YHPullDownMenuClickIndexBlock)handle{
//    self=[super init];
//    if(self){
//        self.items=items;
//        self.frame=[UIScreen mainScreen].bounds;
//        self.backgroundColor=[UIColor clearColor];
//        self.block=[handle copy];
//        self.bgimage=bgImage;
//        [self setupPullDownMenuWithcellHeight:cellHeight
//                                    menuFrame: menuFrame];
//    }
//    return self;
//    
//}
//-(void)setupPullDownMenuWithcellHeight:(CGFloat)cellHeight
//                             menuFrame:(CGRect) menuFrame{
//    _pdContentView=[[UIView alloc]initWithFrame:menuFrame];
//    _pdContentView.backgroundColor=[UIColor  clearColor];
//    [self addSubview: self.pdContentView];
//    self.bgImageView=[[UIImageView alloc]initWithImage:self.bgimage];
//    [self addSubview:self.bgImageView];
//    @weakify(self)
//    [self.bgImageView mas_makeConstraints:^(MASConstraintMaker *make) {
//        @strongify(self)
//        make.width.mas_equalTo(self.pdContentView.mas_width);
//        make.height.mas_equalTo(self.pdContentView.mas_height);
//        make.center.mas_equalTo(self.pdContentView);
//    }];
//    self.cellHeight=cellHeight;
//    _tableView=[[UITableView alloc]init];
//    _tableView.delegate=self;
//    _tableView.dataSource=self;
//    _tableView.backgroundColor=[UIColor clearColor];
//    [self addSubview:_tableView];
//    [self.tableView mas_makeConstraints:^(MASConstraintMaker *make) {
//        @strongify(self)
//        make.width.mas_equalTo(self.pdContentView.mas_width);
//        make.height.mas_equalTo((cellHeight)*([self.items count]));//需要自己设置
//        make.bottom.mas_equalTo(self.pdContentView.mas_bottom);
//        make.left.and.right.mas_equalTo(self.pdContentView);
//        ;
//    }];
//}
//-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
//    [self dismiss];
//}
//
//
//- (void)show{
//    
//    _pdContainerwindow=[[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
//    _pdContainerwindow.windowLevel=UIWindowLevelAlert;
//    [_pdContainerwindow becomeKeyWindow];
//    [_pdContainerwindow makeKeyAndVisible];
//    [_pdContainerwindow addSubview:self];
//    
//    //  [self setShowAnimation];
//    
//}
//
//-(void)dismiss{
//    _items=nil;
//    _tableView=nil;
//    _pdContentView = nil;
//    [self removeFromSuperview];
//}
//-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
//{
//    return 1;
//}
//-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
//{
//    return [self.items count];
//}
//-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
//{
//    
//    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:NSStringFromClass([self class])];
//    if (cell == nil) {
//        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:NSStringFromClass([self class])];
//        cell.textLabel.font = [STStyle fontRegularOfSize:14];
//        cell.textLabel.textColor = [UIColor colorWithRGB:0x666666];
//        cell.backgroundColor = [UIColor clearColor];
//        cell.selectionStyle = UITableViewCellSelectionStyleNone;
//    }
//    [cell.textLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
//        make.centerX.and.centerY.equalTo(cell.contentView);
//    }];
//    cell.textLabel.text = self.items[indexPath.row];
//    return cell;
//}
//-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
//{
//    return  self.cellHeight;
//}
//-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
//{
//    
//    if (self.block) {
//        self.block([indexPath row]);
//        self.block = nil;
//    }
//    [self dismiss];
//}-(void)setShowAnimation{
//    
//    CAKeyframeAnimation* animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
//    animation.duration = 0.3;
//    NSMutableArray *values = [NSMutableArray array];
//    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(0.1, 0.1, 1.0)]];
//    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.2, 1.2, 1.0)]];
//    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(0.9, 0.9, 1.0)]];
//    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.0, 1.0, 1.0)]];
//    animation.values = values;
//    
//    [_pdContentView.layer addAnimation:animation forKey:nil];
//}
//- (CGSize)labelAutoCalculateRectWith:(NSString *)text Font:(UIFont *)font MaxSize:(CGSize)maxSize
//{
//    NSMutableParagraphStyle * paragraphStyle = [[NSMutableParagraphStyle alloc]init];
//    paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
//    NSDictionary * attributes = @{NSFontAttributeName:font, NSParagraphStyleAttributeName:paragraphStyle.copy};
//    
//    CGSize labelSize = [text boundingRectWithSize:maxSize options:NSStringDrawingUsesLineFragmentOrigin |NSStringDrawingUsesFontLeading |NSStringDrawingTruncatesLastVisibleLine attributes:attributes context:nil].size;
//    labelSize.height = ceil(labelSize.height);
//    labelSize.width = ceil(labelSize.width);
//    return labelSize;
//}
//
//- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath{
//    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
//        [cell setSeparatorInset:UIEdgeInsetsMake(0, 10, 0, 10)];
//    }
//    
//    // Prevent the cell from inheriting the Table View's margin settings
//    if ([cell respondsToSelector:@selector(setPreservesSuperviewLayoutMargins:)]) {
//        [cell setPreservesSuperviewLayoutMargins:NO];
//    }
//    
//    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
//        [cell setLayoutMargins:UIEdgeInsetsZero];
//    }
//}
//
//@end

```
















