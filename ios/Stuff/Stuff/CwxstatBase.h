/***********************************************
   You need to import the sqlite framework first
 
 Location of code:
    http://chirico.googlecode.com/svn/trunk/Objective-C/iphone/devwork/Stuff
 Location of TODO:
    https://www.pivotaltracker.com/projects/465295/overview
 Wiki:
    http://code.google.com/p/chirico/wiki/Stuff_iPhone_Application
 
 
 http://chirico.googlecode.com/svn/trunk/Objective-C/iphone/devwork/Stuff/Stuff/CwxstatBase.h
 
 You're looking at the stuff version.
 
 //Create
 
 SqliteDoer *sD = [ [SqliteDoer alloc] init];
 [sD setPath];
 // [sD drop: 0];
 [sD create: 0];
 [sD weight: (double) 15.3 note: (NSString *) @"Teset"];
 
 
 
 
 // Drop
 SqliteDoer *sD = [ [SqliteDoer alloc] init];
 [sD setPath];
 [sD drop: 0];
 [sD create: 0];

 
 
 
 Try this instead, because what you really want to do is put this 
 all in a method
 
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

 Then you can call this as follows:
 
 
 
 [self insertWeight: (double) [text doubleValue] note: (NSString *) @"Entered from addLabel"];
 
 
 
 
 */



#import <UIKit/UIKit.h>
#import <sqlite3.h> // Import the SQLite database framework
#import <Block.h>

int myURLget(void);
int myTimeget(void);

// Used in dispatch q, must be void
void slop(void *N);

typedef int (^IntBlock)();

#pragma mark - HelloDictionary

@interface HelloDictionary : NSObject {
    NSMutableArray *keys;
    NSMutableArray *objects;
    NSMutableDictionary *dictionary;
}
-(void) key: (NSObject *) key value: (NSObject *) value;
-(void) print;
@end


#pragma mark - MyMath "Class method example"
// Cute example of class method vs instance methon

@interface MyMath: NSObject {
    int instanceCallCount; 
}
+ (int) square: (int) num;  //Class method    
    
- (void) setCount: (int) n; //Instance method
- (int) getCount;  // Instance method
    

@end



#pragma mark - SqliteDoer

@interface SqliteDoer: NSObject {
    sqlite3 *database;
    NSArray *docPaths;
    NSString *docDir;
    NSString *dbPath;
    NSFileManager *fm;
    NSString *dbPathFromApp;
    NSMutableArray *data;

    
    int numerator;
    int denominator;
}

-(int) setPath;
-(int) weight: (double) weight note: (NSString *) note;
-(int) del: (int) n;
-(int) query: (int) n;
-(int) create: (int) n;
-(int) drop: (int) n;
-(int) pr;
-(int) pr: (NSMutableArray *) n;



@end


#pragma mark - SqliteDetailed
/*
 
 Another example of sqlite database. This
 will be used for the general case.
 
 This is where all the nasty experimental stuff
 is going to go.

 */
@interface SqliteDetailed: NSObject {
    sqlite3 *database;
    NSArray *docPaths;
    NSString *docDir;
    NSString *dbPath;
    NSFileManager *fm;
    NSString *dbPathFromApp;
    NSMutableArray *data;
    NSArray *createTableStatements;
    NSArray *createTriggerStatements;

}

-(int) setPath;
-(int) note: (double) priority note: (NSString *) note;
-(int) del: (int) n;
-(int) query: (int) n;
-(int) create: (int) n;
-(int) drop: (int) n;
-(int) pr;
-(int) pr: (NSMutableArray *) n;




@end








