//
//  ViewController.m
//  MediaFrameworkTest
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "ViewController.h"
#import <FFMpegDemuxer/FFMpegDemuxer.h>

@interface ViewController ()

@property (strong, nonatomic) FFMpegDemuxer     *ffmpegDemuxer;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)testButtonClick:(UIButton *)sender {
//    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"demo" ofType:@"mp4"];
    NSString *filePath = @"rtsp://192.168.42.1/live";
    [self.ffmpegDemuxer openFileByPath:filePath];
}

#pragma mark - get & set
- (FFMpegDemuxer *)ffmpegDemuxer {
    if (_ffmpegDemuxer == nil) {
        _ffmpegDemuxer = createFFMpegDemuxer();
    }
    return _ffmpegDemuxer;
}
@end
