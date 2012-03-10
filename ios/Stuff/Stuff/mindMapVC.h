//
//  mindMapVC.h
//  Stuff
//
//  Created by Mike Chirico on 2/11/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "mindMapUIview.h"
@interface mindMapVC : UIViewController
- (IBAction)buttonBack:(id)sender;
- (IBAction)button0:(id)sender;
@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) IBOutlet mindMapUIview *my_mindMapUIview; // Why Strong?

- (IBAction)buttonScroll0:(id)sender;
- (IBAction)buttonScroll1:(id)sender;
@property (weak, nonatomic) IBOutlet UITextView *textS0;
@end
