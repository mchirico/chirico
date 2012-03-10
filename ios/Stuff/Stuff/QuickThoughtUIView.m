//
//  QuickThoughtUIView.m
//  Stuff
//
//  Created by Mike Chirico on 2/25/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "QuickThoughtUIView.h"

@implementation QuickThoughtUIView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void) drawCircleAtPoint:(CGPoint)p withRadius:(CGFloat)radius inContext:(CGContextRef) context
{
    UIGraphicsPushContext(context);
    CGContextBeginPath(context);
    CGContextAddArc(context,p.x,p.y,radius,0,2*M_PI,YES);
    CGContextStrokePath(context);
    UIGraphicsPopContext();
}


// So this proves the graph works!
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    NSLog(@"Called drawRec");
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGPoint midPoint;
    midPoint.x = self.bounds.origin.x + self.bounds.size.width/2;
    midPoint.y = self.bounds.origin.y + self.bounds.size.height/2;
    CGContextSetLineWidth(context,5.0);
    CGFloat size = self.bounds.size.width/2;
    //size *= self.change;
    [self drawCircleAtPoint:midPoint   withRadius:size inContext:context];  
}


@end
