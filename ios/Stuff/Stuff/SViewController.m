//
//  SViewController.m
//  Stuff
//
//  Created by Mike Chirico on 1/28/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "SViewController.h"
#import "AskerViewController.h"
#import "CwxstatBase.h"
#import "TableController.h"

@interface SViewController()<AskerViewControllerDelegate>
@property (weak, nonatomic) IBOutlet UIView *connectView;

@end



@implementation SViewController
@synthesize textMulData = _textMulData;
@synthesize textViewS = _textViewS;
@synthesize button0 = _button0;
@synthesize textMul0 = _textMul0;
@synthesize connectView = _connectView;


-(void) insertWeight: (double) weight note: (NSString *) note
{   
    SqliteDoer *sD = [ [SqliteDoer alloc] init];
    [sD setPath];
    // [sD drop: 0];
    [sD create: 0];
    [sD weight: (double) weight note: (NSString *) note];
   // [sD pr];
    [sD query: 0];
    sD=nil; // Is this correct?
    
   
}


- (void)setRandomLocationForView:(UIView *)view
{
    [view sizeToFit];
    CGRect cBounds = CGRectInset(self.connectView.bounds,view.frame.size.width/2,view.frame.size.height/2);
    CGFloat x = arc4random() % (int) cBounds.size.width + view.frame.size.width/2;
    CGFloat y = arc4random() % (int) cBounds.size.height + view.frame.size.height/2;
    view.center = CGPointMake(x,y);
  //  view.center = CGPointMake(20,20);
  //  view.backgroundColor = [UIColor whiteColor];
}

- (void)addLabel:(NSString *)text
{
    UILabel *label = [[UILabel alloc] init];
    label.text = text;
    label.font = [UIFont systemFontOfSize:30.0];
    label.textColor = [UIColor blueColor];
    label.backgroundColor = [UIColor clearColor];
    [self setRandomLocationForView:label];
    [self.connectView addSubview:label];
    

 
    
}


- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier hasPrefix:@"Create Label"]) {
        AskerViewController *asker = (AskerViewController *)segue.destinationViewController;
        asker.question = @"What";
        asker.delegate = self;

    }
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
        
        [segue.destinationViewController setDataArray:n];
        
        
 /*       //Here's a basic example
        
        NSMutableArray *dataArray;
        dataArray = [[NSMutableArray alloc] init ];
        [dataArray addObject:@"brown"];
        [dataArray addObject:@"red"];
        [dataArray addObject:@"green"];
        [dataArray addObject:@"yellow"];
        [segue.destinationViewController setDataArray:dataArray];
*/
        
    }

    
}




-(void)askerViewController:(AskerViewController *)sender didAskQuestion:(NSString *)question andGotAnswer:(NSString *)answer andGotAns2:(NSString *)ans2
{
    NSLog(@"** answer %@, ans2 %@",answer,ans2);
    [self addLabel:answer];
    [self dismissModalViewControllerAnimated:YES];
    self.textViewS.text = answer;
    [self insertWeight: (double) [answer doubleValue] note: (NSString *) ans2];    
    
}



- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (void)viewDidUnload {
    [self setTextViewS:nil];
    [self setButton0:nil];
    [self setTextMul0:nil];
    [self setTextMulData:nil];
    [super viewDidUnload];
}
- (IBAction)buttonData:(id)sender {
    
    SqliteDoer *sD = [ [SqliteDoer alloc] init];
    [sD setPath];
    //[sD drop: 0];
    [sD create: 0];
    [sD query: 0];
    [sD pr];
    NSMutableArray * n = [[NSMutableArray alloc] initWithObjects:nil];
    [sD pr: n];
    NSString * result = @"";
    for (int x = 0; x < [n count]; x++) {
        result = [result stringByAppendingFormat:@"%@\n",[n objectAtIndex:x]];
    }
    self.textMulData.text=result;
   
       

    
}

@end
