//
//  AskerViewController.h
//  Stuff
//
//  Created by Mike Chirico on 1/28/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AskerViewController;
@protocol AskerViewControllerDelegate<NSObject>
-(void)askerViewController:(AskerViewController *)sender
              didAskQuestion:(NSString *)question
              andGotAnswer:(NSString *)answer
                andGotAns2:(NSString *) ans2;
              
@end

@interface AskerViewController : UIViewController

@property (nonatomic,copy) NSString *question;
@property (nonatomic,copy) NSString *answer;
@property (nonatomic,copy) NSString *ans2;

@property (nonatomic,weak) id <AskerViewControllerDelegate> delegate;
- (IBAction)buttonOne:(id)sender;
- (IBAction)buttonTwo:(id)sender;
- (IBAction)buttonThree:(id)sender;
@property (weak, nonatomic) IBOutlet UITextView *textMul;
@property (weak, nonatomic) IBOutlet UITextField *textWeight;

@end
