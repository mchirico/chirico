//
//  MailComposeViewController.m
//  Stuff
//
//  Created by Mike Chirico on 2/20/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "MailComposeViewController.h"

@implementation MailComposeViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
}
*/

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)sendButton:(id)sender {
    
    MFMailComposeViewController *mail = [[MFMailComposeViewController alloc] init];
    mail.mailComposeDelegate = self;
    if ([MFMailComposeViewController canSendMail]) {
        //Setting up the Subject, recipients, and message body.
        [mail setToRecipients:[NSArray arrayWithObjects:@"chirico@openadsi.com",nil]];
        [mail setSubject:@"Subject of Email"];
        [mail setMessageBody:@"Message of email" isHTML:NO];
        [self presentModalViewController:mail animated:YES];
    }
    
    
    
}

- (IBAction)buttonBack:(id)sender {
    
     [[self presentingViewController] dismissModalViewControllerAnimated:YES];
}



// Dismisses the Mail composer when the user taps Cancel or Send.
- (void)mailComposeController:(MFMailComposeViewController*)controller
          didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    NSString *resultTitle = nil;
    NSString *resultMsg = nil;
    
    switch (result)
    {
        case MFMailComposeResultCancelled:
            resultTitle = @"Email Cancelled";
            resultMsg = @"You elected to cancel the email";
            break;
        case MFMailComposeResultSaved:
            resultTitle = @"Email Saved";
            resultMsg = @"You saved the email as a draft";
            break;
        case MFMailComposeResultSent:
            resultTitle = @"Email Sent";
            resultMsg = @"Your email was sent";
            break;
        case MFMailComposeResultFailed:
            resultTitle = @"Email Failed";
            resultMsg = @"Sorry, the Mail Composer failed. Please try again.";
            break;
        default:
            resultTitle = @"Email Not Sent";
            resultMsg = @"Sorry, an error occurred. Your email could not be sent.";
            break;
    }
    
    // Notifies user of any Mail Composer errors received with an Alert View dialog.
    UIAlertView *mailAlertView = [[UIAlertView alloc] initWithTitle:resultTitle
                                                            message:resultMsg delegate:self cancelButtonTitle:@"Okay" otherButtonTitles:nil];
    [mailAlertView show];
 
    [self dismissModalViewControllerAnimated:YES];
}


@end
