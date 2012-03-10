//
//  MailComposeViewController.h
//  Stuff
//
//  Created by Mike Chirico on 2/20/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>
#import <MessageUI/MFMailComposeViewController.h>

@interface MailComposeViewController : UIViewController 
<MFMailComposeViewControllerDelegate,UINavigationControllerDelegate> {
    
}
- (IBAction)sendButton:(id)sender;
- (IBAction)buttonBack:(id)sender;

@end
