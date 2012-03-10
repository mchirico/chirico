//
//  OffTableViewCTL0.h
//  Stuff
//
//  Created by Mike Chirico on 2/4/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface OffTableViewCTL0 : UIViewController
@property (nonatomic,strong) NSString *s;
@property (weak, nonatomic) IBOutlet UITextView *textMul;
- (IBAction)buttonBack:(id)sender;
@end
