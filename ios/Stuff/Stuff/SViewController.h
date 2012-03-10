//
//  SViewController.h
//  Stuff
//
//  Created by Mike Chirico on 1/28/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SViewController : UIViewController
@property (weak, nonatomic) IBOutlet UITextView *textViewS;
@property (strong, nonatomic) IBOutlet UIButton *button0;
@property (weak, nonatomic) IBOutlet UITextView *textMul0;

- (IBAction)buttonData:(id)sender;
@property (weak, nonatomic) IBOutlet UITextView *textMulData;

@end
