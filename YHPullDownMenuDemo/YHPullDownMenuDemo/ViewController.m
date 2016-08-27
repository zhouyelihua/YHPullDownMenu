//
//  ViewController.m
//  YHPullDownMenuDemo
//
//  Created by maoer on 16/8/27.
//  Copyright © 2016年 snail run. All rights reserved.
//

#import "ViewController.h"
#import "YHPullDownMenu.h"

@interface ViewController ()
- (IBAction)btn:(id)sender;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)btn:(id)sender {
    
    NSArray *items = @[@"东方不败", @"步惊云", @"女娲大帝"];
    YHPullDownMenu *pd=[[YHPullDownMenu alloc]initPullDownMenuWithItems:items cellHeight:35 menuFrame:CGRectMake([UIScreen mainScreen].bounds.size.width-125-10, 136, 125, 115) clickIndexHandle:^(NSInteger index) {
        switch (index) {
            case 0:
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
    
}
@end
