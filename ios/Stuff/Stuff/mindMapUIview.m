//
//  mindMapUIview.m
//  Stuff
//
//  Created by Mike Chirico on 2/11/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "mindMapUIview.h"

@implementation mindMapUIview
@synthesize change = _change;

#define DEFAULT_CHANGE 0.90

- (id)initWithFrame:(CGRect)frame
{
    NSLog(@"initWithFrame");
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

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    NSLog(@"Called drawRec");
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGPoint midPoint;
    midPoint.x = self.bounds.origin.x + self.bounds.size.width/2;
    midPoint.y = self.bounds.origin.y + self.bounds.size.height/2;
    CGContextSetLineWidth(context,5.0);
    CGFloat size = self.bounds.size.width/2;
    size *= self.change;
    [self drawCircleAtPoint:midPoint   withRadius:size inContext:context];  
}

-(void)pinch:(UIPinchGestureRecognizer *)gesture
{
    NSLog(@"Gesture here");
    if ((gesture.state == UIGestureRecognizerStateChanged) ||
        (gesture.state == UIGestureRecognizerStateEnded)) {
        self.change *= gesture.scale; // adjust our scale
        gesture.scale = 1;           // reset gestures scale to 1 (so future changes are incremental, not cumulative)
    }

}


- (CGFloat)change
{
    if (!_change) {
        return DEFAULT_CHANGE; // don't allow zero scale
    } else {
        return _change;
    }
}

- (void)setChange:(CGFloat)change
{
    if (change != _change) {
        _change = change;
        [self setNeedsDisplay]; // any time our change changes, call for redraw
    }
}

@end
