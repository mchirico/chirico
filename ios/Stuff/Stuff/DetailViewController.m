//
//  DetailViewController.m
//  Stuff
//
//  Created by Mike Chirico on 2/5/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "DetailViewController.h"

@implementation DetailViewController
@synthesize navbar;
@synthesize textMul;
@synthesize textS;

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



/*******************
 Wow, if you uncomment this, it won't load correctly. Find out why.
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"Loaded Detail");
    step_count=0;
}


- (void)viewDidUnload
{
    [self setTextMul:nil];
    [self setTextS:nil];
    [self setNavbar:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)buttonBack:(id)sender {
    // This is coming in very handy
    [[self presentingViewController] dismissModalViewControllerAnimated:YES];
    
}
- (IBAction)stepper:(UIStepper *)sender {

    if ( [sender value] > 5 ) [sender setBackgroundColor:[UIColor redColor]];
    NSLog(@" Output %f step_count= %d",[sender value],step_count);
    textS.text = [NSString stringWithFormat: @"%d",(int) [sender value]];
    navbar.title = @"Stuff";
}
@end
