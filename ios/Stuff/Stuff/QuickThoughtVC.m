//
//  QuickThoughtVC.m
//  Stuff
//
//  Created by Mike Chirico on 2/25/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "QuickThoughtVC.h"

@implementation QuickThoughtVC
@synthesize scrollView = _scrollView;
@synthesize textMul = _textMul;



- (IBAction)button0:(id)sender {
    NSLog(@"button 0");
    
    if (self.textMul.editable == NO ) {
        self.textMul.editable= YES;
    }else
    {
      self.textMul.editable = NO;
    }
}


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


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    // Now we're getting somewhere                                              
    self.scrollView.contentSize = CGSizeMake(4280, 4960);
}


- (void)viewDidUnload
{

    [self setScrollView:nil];
    [self setTextMul:nil];
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
   [[self presentingViewController] dismissModalViewControllerAnimated:YES];  
    
}
@end
