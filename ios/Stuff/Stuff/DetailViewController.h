//
//  DetailViewController.h
//  Stuff
//
//  Created by Mike Chirico on 2/5/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DetailViewController : UIViewController {
    int step_count;
}
- (IBAction)buttonBack:(id)sender;
@property (weak, nonatomic) IBOutlet UITextView *textMul;
@property (weak, nonatomic) IBOutlet UITextField *textS;
- (IBAction)stepper:(id)sender;
@property (weak, nonatomic) IBOutlet UINavigationItem *navbar;

@end
