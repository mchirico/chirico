//
//  mindMapUIview.h
//  Stuff
//
//  Created by Mike Chirico on 2/11/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface mindMapUIview : UIView
-(void)pinch:(UIPinchGestureRecognizer *)gesture;
@property (nonatomic) CGFloat change;
@end
