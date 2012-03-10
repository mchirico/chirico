//
//  AskerViewController.m
//  Stuff
//
//  Created by Mike Chirico on 1/28/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "AskerViewController.h"


@interface AskerViewController() <UITextFieldDelegate>
@property (weak, nonatomic) IBOutlet UILabel *questionLabel;
@property (weak, nonatomic) IBOutlet UITextField *answerTextField;
@property (weak, nonatomic) IBOutlet UISlider *slider;

@end

@implementation AskerViewController
@synthesize textMul = _textMul;
@synthesize textWeight = _textWeight;
@synthesize questionLabel = _questionLabel;
@synthesize answerTextField = _answerTextField;
@synthesize slider = _slider;


@synthesize question = _question;
@synthesize answer = _answer;
@synthesize ans2 = _ans2;
@synthesize delegate = _delegate;


- (void)setQuestion:(NSString *)question
{
    NSLog(@"setQuestion, question = %@\n",question);
    _question= question;
    self.questionLabel.text = question;  // See below, viewDidLoad

}

- (void) setAns2:(NSString *)ans2
{
    _ans2=ans2;
}

- (void) setTextMul:(UITextView *)textMul
{
    _textMul=textMul;
}

- (void) setTextWeight:(UITextField *)textWeight    
{
    _textWeight = textWeight;
}


- (void) setSlider:(UISlider *)slider
{
    NSLog(@"Here %f %f",_slider.value,slider.value);
    _slider = slider;
}

- (void) setAnswerTextField:(UITextField *)answerTextField
{
    NSLog(@"setAnswerTextField");
    _answerTextField = answerTextField; 
}



// Important for delegation
- (void)viewDidLoad
{
    NSLog(@"viewDidLoad");
    [super viewDidLoad];
    self.questionLabel.text = self.question;  //Need this. setQuestion won't do it alone.
    self.answerTextField.delegate = self;
}

- (void)myUpdateValuesStuff
{
    // Confusing this textMul vs _textMul stuff
    NSLog(@"textField=%@,_textMul %@",self.textWeight.text,self.textMul.text);
    self.answer = self.textWeight.text;
    //self.ans2 = @"This is where textMul should go";
    self.ans2 = self.textMul.text;    
}

// This will add the caret to answerTextField
- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.answerTextField becomeFirstResponder];
}

- (void) textFieldDidEndEditing:(UITextField *)textField
{  

    
    // HERE's how Hagerty did it...... HHHHHHHHHHHHHHHHHHHHhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
        // Confusing this textMul vs _textMul stuff
    NSLog(@"textField=%@,_textMul %@",textField.text,self.textMul.text);
    self.answer = textField.text;
    //self.ans2 = @"This is where textMul should go";
    self.ans2 = self.textMul.text;    
    // HERE's how Hagerty did it. (above)HHHHHHHHHHHHHHHHHHHHhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
    
    
    // I'm redoing it here.
    // Could have called the following?
    [self myUpdateValuesStuff];
    
    
    
    //*******************
    return;
    //******* SKIPPING EVERYTHING BELOW. Using Exit button ****
    //                                   To return the value 
    
    if(![textField.text length]) {
        // This is if we want to return after 
        // Text was entered. But will do this on button 3
       // [[self presentingViewController] dismissModalViewControllerAnimated:YES];
         } else {
             // need to communicate
             [self.delegate askerViewController:self didAskQuestion:self.question andGotAnswer:self.answer andGotAns2:self.ans2];
         }
    
    
}




- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if ([textField.text length]) {
        [textField resignFirstResponder];
         return YES;
        
    } else {
        return NO;
    }
}



/* Change from id to UISlider * that way
   we can get sender values.
*/
- (IBAction)sliderA:(UISlider *)sender {
    
 //   NSLog(@"Slider %f",_slider.value);
    NSLog(@"Slider %f",self.slider.value);
    NSLog(@"Slider [sender value] is equl to %f",   [sender value]);
   // self.answerTextField.text = [NSString stringWithFormat:@"%.1f", self.slider.value];
    // or can say
    self.answerTextField.text = [NSString stringWithFormat:@"%.1f", [sender value]];

   
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}

- (void)viewDidUnload {
    [self setQuestionLabel:nil];
    [self setAnswerTextField:nil];
    [self setSlider:nil];
    [self setTextMul:nil];
    [self setTextWeight:nil];
    [super viewDidUnload];
}
- (IBAction)buttonOne:(id)sender {
    self.questionLabel.text = @"Button One";
}

- (IBAction)buttonTwo:(id)sender {
    
    self.textMul.text = @"Button Two";
}

- (IBAction)buttonThree:(id)sender {
    [self myUpdateValuesStuff];
    
                 [self.delegate askerViewController:self didAskQuestion:self.question andGotAnswer:self.answer andGotAns2:self.ans2];
    
    // Do we need this?
    [[self presentingViewController] dismissModalViewControllerAnimated:YES];

    
}
@end
