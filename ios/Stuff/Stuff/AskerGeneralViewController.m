//
//  AskerGeneralViewController.m
//  Stuff
//
//  Created by Mike Chirico on 2/5/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "AskerGeneralViewController.h"
#import "CwxstatBase.h"

@implementation AskerGeneralViewController

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
    NSLog(@"Yes we did load");
}


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


- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier hasPrefix:@"Sleep"]) {
        NSLog(@"Sleep");
        /*
        AskerViewController *asker = (AskerViewController *)segue.destinationViewController;
        asker.question = @"What";
        asker.delegate = self;
         
         
         
         // This is really cool.
         if ([segue.identifier hasPrefix:@"Segue Table0"]) {
         NSLog(@"Going to table");
         
         
         
         SqliteDoer *sD = [ [SqliteDoer alloc] init];
         [sD setPath];
         //[sD drop: 0];
         [sD create: 0];
         [sD query: 0];
         [sD pr];
         NSMutableArray * n = [[NSMutableArray alloc] initWithObjects:nil];
         [sD pr: n];
         
         // [segue.destinationViewController setDataArray:n];
         
         
         
         }
 
         
        */
    }
    
    
}

// Most excellent way to do the back button
- (IBAction)buttonBack:(id)sender {
     [[self presentingViewController] dismissModalViewControllerAnimated:YES];
}

/**************************************************
 
 I love this! Change id to UIButton *, then, you can
 see what methods are available. Note, that two
 buttons "Test" and "Test II" reach this function.
 
 
*/
- (IBAction)button:(UIButton *)sender {
    NSLog(@"Clicked button %@", [sender currentTitle]);
    
    if ([ [sender currentTitle] isEqualToString: @"Test"]) {
         NSLog(@" output: %d",[MyMath square:3]);
         MyMath *m = [[MyMath alloc] init];
         [m setCount: 4];
         NSLog(@"Output getCount:%d",m.getCount);
         NSLog(@"Description: %@",m.description);
    //m = Nil;
    }
    
 
    
    
    SqliteDetailed *sD = [ [SqliteDetailed alloc] init];
    [sD setPath];
    // [sD drop: 0];
    [sD create: 0];
    [sD note: (double) 15.3 note: (NSString *) @"Test in Button."];
    sD=nil;


    

    
}








@end
