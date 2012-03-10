//
//  mindMapVC.m
//  Stuff
//
//  Created by Mike Chirico on 2/11/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "mindMapVC.h"
#import "mindMapUIview.h"


@interface mindMapVC(){
    UITextField *textField;
}
      // You should have done caps here.
@property (nonatomic, weak) IBOutlet mindMapUIview *mmU;
@end



@implementation mindMapVC
@synthesize textS0 = _textS0;
@synthesize scrollView = _scrollView;
@synthesize my_mindMapUIview = _my_mindMapUIview;

@synthesize mmU = _mmU;


-(void) setMmU:(mindMapUIview *)mmU
{
    NSLog(@"setMmU !!!!! ");
     _mmU = mmU; // If you don't do this, it won't work!
    [self.mmU addGestureRecognizer:[[UIPinchGestureRecognizer alloc] initWithTarget:self.mmU action:@selector(pinch:)]];
     
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



#pragma mark - My Own Functions

-(void)buttonPressed0 {
    NSLog(@"Button Pressed!");
    textField.text = @"Button Pressed";
 
}

/*

 I think this is very cool stuff - creating buttons and text fields
 programatically in the scroll view.
 
*/
- (void)createOurButton
{
    // Create our own button?
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];

                      
    //set the position of the button
    button.frame = CGRectMake(750, 170, 100, 30);
    
    //set the button's title
    [button setTitle:@"Click Me!" forState:UIControlStateNormal];
    
    
    
    //listen for clicks
    [button addTarget:self action:@selector(buttonPressed0) 
     forControlEvents:UIControlEventTouchUpInside];
    
    
    //add the button to the view
    //[self.view addSubview:button];
    // Or add to scrollView
    [self.scrollView addSubview:button];
    
    
    
    textField = [[UITextField alloc] initWithFrame:CGRectMake(750, 200, 300, 40)];
    textField.borderStyle = UITextBorderStyleRoundedRect;
    textField.font = [UIFont systemFontOfSize:15];
    textField.placeholder = @"enter text";
    textField.autocorrectionType = UITextAutocorrectionTypeNo;
    textField.keyboardType = UIKeyboardTypeDefault;
    textField.returnKeyType = UIReturnKeyDone;
    textField.clearButtonMode = UITextFieldViewModeWhileEditing;
    textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;


   // This is for the current view 
   // [self.view addSubview:textField];

   // This is for the scrollView 
    [self.scrollView addSubview:textField];
    
    
    
    
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
    
    // But want this in scroll view too
    [self createOurButton];

    
    


}





- (void)viewDidUnload
{
    [self setScrollView:nil];
    [self setMy_mindMapUIview:nil];
    [self setTextS0:nil];
    [super viewDidUnload];
    
    textField=nil;
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

- (IBAction)button0:(id)sender {
    NSLog(@"self.mmu");
    [self.mmU setNeedsDisplay];
}




- (IBAction)buttonScroll0:(id)sender {
}

- (IBAction)buttonScroll1:(id)sender {
}
@end
