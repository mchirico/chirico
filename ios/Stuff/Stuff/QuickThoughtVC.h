//
//  QuickThoughtVC.h
//  Stuff
//
//  Created by Mike Chirico on 2/25/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface QuickThoughtVC : UIViewController
- (IBAction)buttonBack:(id)sender;

@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;

@property (weak, nonatomic) IBOutlet UITextView *textMul;
@end
