//
//  OffTableViewCTL0.m
//  Stuff
//
//  Created by Mike Chirico on 2/4/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "OffTableViewCTL0.h"

@implementation OffTableViewCTL0
@synthesize s=_s;
@synthesize textMul = _textMul;


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
    self.textMul.text = self.s;
}


- (void)viewDidUnload
{
    NSLog(@"Going to unload OffTableCTL0");
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
