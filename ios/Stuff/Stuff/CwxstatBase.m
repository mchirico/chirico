#import "CwxstatBase.h"


void slop(void *N) {
    char *s = (char *) N;
    NSLog(@" ->%s<-\n",s);
    
    
    
}


 int myURLget() {
    

    NSString *urlAsString = @"https://23isprime.appspot.com";
    urlAsString = [urlAsString stringByAppendingString:@"?param1=First"];
    urlAsString = [urlAsString stringByAppendingString:@"&param2=Second"];
    
    NSURL *url = [NSURL URLWithString:urlAsString];
    
    
    NSMutableURLRequest *urlRequest = [NSMutableURLRequest requestWithURL:url];
    [urlRequest setTimeoutInterval:30.0f];
    [urlRequest setHTTPMethod:@"POST"];
    
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    
    [NSURLConnection
     sendAsynchronousRequest:urlRequest
     queue:queue
     completionHandler:^(NSURLResponse *response, 
                         NSData *data, 
                         NSError *error) {
         
         if ([data length] >0  &&
             error == nil){
             NSString *html = [[NSString alloc] initWithData:data
                                                    encoding:NSUTF8StringEncoding];
             NSLog(@"HTML = %@", html);
         }
         else if ([data length] == 0 &&
                  error == nil){
             NSLog(@"Nothing was downloaded.");
         }
         else if (error != nil){
             NSLog(@"Error happened = %@", error);
         }
         
         
     }];
    
    
    return 0;
    
    
}




int myTimeget(){
    
        
    NSTimeInterval  today = [[NSDate date] timeIntervalSince1970];
    NSString *intervalString = [NSString stringWithFormat:@"%f", today];
    NSLog(@"Interval: %@",intervalString);
    
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"hh:mm:ss:A"];
    //[dateFormatter setDateStyle:NSDateFormatterMediumStyle];
    //[dateFormatter setTimeStyle:NSDateFormatterShortStyle];
    NSLog(@"%@", [dateFormatter stringFromDate:[NSDate date]]);
    
    return 0;
    
}





#pragma mark - HelloDictionary

/*
    Keep both Mutable Dictionary and Mutable array of items.
 */
@implementation HelloDictionary

-(id) init {
    self = [super init];
    dictionary = [[NSMutableDictionary alloc] init];
    keys = [[NSMutableArray alloc] initWithObjects:nil];
    objects = [[NSMutableArray alloc] initWithObjects:nil];
    return self;
}

-(void) key: (NSObject *) key value: (NSObject *) value {
    [dictionary setObject:value forKey:key];
    [keys addObject:key];
    [objects addObject:value];

}

-(void) print

{
    //keys = [NSMutableArray arrayWithObjects:@"key1", @"key2", @"key3", nil];
    
    //NSArray *keys = [NSArray arrayWithObjects:@"key1", @"key2", @"key3", nil];
    //objects = [NSMutableArray arrayWithObjects:@"How", @"are", @"you", nil];
    
    NSArray *tkeys = [dictionary allKeys];
    NSArray *stkeys = [tkeys sortedArrayUsingSelector:@selector(localizedCaseInsensitiveCompare:)];
    
	// values in foreach loop
	for (NSString *key in stkeys) {
		NSLog(@"hD[%@] = %@",key, [dictionary objectForKey:key]);
	}
    
    /*
    // Old
    dictionary = [NSDictionary dictionaryWithObjects:objects forKeys:keys];
    for (id key in dictionary) {
        NSLog(@"key: %@, value: %@", key, [dictionary objectForKey:key]);
    }
    */
}

@end

#pragma mark - MyMath
/***************************************************
 ***************************************************
         MyMath
 ***************************************************
 ***************************************************
 */


@implementation MyMath 

// Class method. Note plus sign
+(int)square:(int)num{ 
    return num * num;
}

-(void) setCount: (int) n {
    instanceCallCount=n;
}

-(int) getCount {
    return instanceCallCount;
}

-(NSString *)description {
    return @"Test Class";
}

-(void) dealloc {
    NSLog(@"Dealloc MyMath");
}

@end

/*
 Example usage:
 
[MyMath square:3];
MyMath *m = [[MyMath alloc] init];
m = Nil; 

 
*/





#pragma mark - SqliteDoer
@implementation SqliteDoer

-(int) setPath {
    
       
    docPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    docDir = [docPaths objectAtIndex:0];
    dbPath = [docDir stringByAppendingPathComponent:@"weight.db"] ;    
    fm = [NSFileManager defaultManager];
    BOOL success = [fm fileExistsAtPath:dbPath];
    if(success) NSLog(@"Success: %@", dbPath); 
    else {
      dbPathFromApp=[[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent :@"weight.db"];
      [fm copyItemAtPath:dbPathFromApp toPath:dbPath error:nil];
    }
    
    return 1;
    
}

//-(void) setTo: (int) n over: (int) d
-(int) weight: (double) weight note: (NSString *) note {
    
    
    // Open the database from the users filessytem
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
        
        NSString *cmp = [NSString stringWithFormat:@"insert into a (a,b) values (%lf,'%@');",
                         weight,note];
        NSLog(@" weight,note: %@",cmp);
		const char *sqlStatement = [cmp UTF8String];
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
        
	}
	sqlite3_close(database);
    NSLog(@"Path: %@",dbPath);
    return 0;
    
    
}

-(int) del: (int) n {
    
    
    // Open the database from the users filessytem
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
		const char *sqlStatement = "delete from a;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
        
	}
	sqlite3_close(database);
    NSLog(@"Path: %@",dbPath);
    return 0;
    
    
}


-(int) query: (int) n {
    

    data = [[NSMutableArray alloc]init]; 

    
    
    NSLog(@"mySQLITE");
    // Open the database from the users filessytem
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
		const char *sqlStatement = "select a,b,timeEnter from a order by timeEnter desc;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
            NSLog(@"mySQLITE: OK");
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
                
				NSString *a = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 0)];
                NSString *b = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 1)];
                NSString *timeEnter = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 2)];
                
                [data addObject:[[NSString alloc] initWithFormat:@"(%@,%@):%@",
                                   a,
                                   b,
                                   timeEnter]];



				NSLog(@"query: (%@,%@):%@",a,b,timeEnter);

                
				
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
        
	}
	sqlite3_close(database);
    return 0;
}


-(int) create: (int) n {
    
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "create table IF NOT EXISTS a (a double, b varchar(40), timeEnter Date);";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		sqlite3_finalize(compiledStatement);
    }
    if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "CREATE TRIGGER IF NOT EXISTS insert_a_timeEnter  AFTER  INSERT ON a \
        BEGIN  \
        UPDATE a SET timeEnter = DATETIME('NOW')  WHERE rowid = new.rowid; \
        END;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
        sqlite3_finalize(compiledStatement);
	}
	sqlite3_close(database);
    return 0;
}

    
    
-(int) drop: (int) n {    
    
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "drop table IF  EXISTS a;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		sqlite3_finalize(compiledStatement);
    }
    
    if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "drop TRIGGER IF EXISTS insert_a_timeEnter;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
        sqlite3_finalize(compiledStatement);
	}
	sqlite3_close(database);
    return 0;
}

-(int) pr {
    
    for (int x = 0; x < [data count]; x++) {
        NSLog(@"Row %@", [data objectAtIndex:x]);
    }
    return 0;
}

// Take a look at this... there's a problem with pass by value/ref?
-(int) pr: (NSMutableArray *) n {
    
    for (int x = 0; x < [data count]; x++) {
        NSLog(@"zRow %@", [data objectAtIndex:x]);
        
        [n addObject:[[NSString alloc] initWithFormat:@"%@",
                      [data objectAtIndex:x] ]];
        
    }
    return 0;
}

@end




#pragma mark - SqliteDetailed
/*
 
 
 SqliteDetailed *sD = [ [SqliteDetailed alloc] init];
 [sD setPath];
 // [sD drop: 0];
 [sD create: 0];
 [sD note: (double) 15.3 note: (NSString *) @"Teset"];
  sD=nil;


 
 */



// Private
@interface SqliteDetailed()
-(void) initStatement;  // Want this private  
@end

@implementation SqliteDetailed


-(int) setPath {
    [self initStatement];  // Private
    
    docPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    docDir = [docPaths objectAtIndex:0];
    dbPath = [docDir stringByAppendingPathComponent:@"detailed.db"] ;    
    fm = [NSFileManager defaultManager];
    BOOL success = [fm fileExistsAtPath:dbPath];
    if(success) NSLog(@"Success: %@", dbPath); 
    else {
        dbPathFromApp=[[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent :@"detailed.db"];
        [fm copyItemAtPath:dbPathFromApp toPath:dbPath error:nil];
    }
    return 1;
}


//-(void) setTo: (int) n over: (int) d
-(int) note: (double) priority note: (NSString *) note {
    
    
    // Open the database from the users filessytem
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
        
        NSString *cmp = [NSString stringWithFormat:@"insert into note (a,b) values (%lf,'%@');",
                         priority,note];
        NSLog(@" weight,note: %@",cmp);
		const char *sqlStatement = [cmp UTF8String];
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
        
	}
	sqlite3_close(database);
    NSLog(@"Path: %@",dbPath);
    return 0;
    
    
}


-(int) del: (int) n {
    
    
    // Open the database from the users filessytem
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
		const char *sqlStatement = "delete from note;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
        
	}
	sqlite3_close(database);
    NSLog(@"Path: %@",dbPath);
    return 0;
    
    
}


-(int) query: (int) n {
    
    
    data = [[NSMutableArray alloc]init]; 
    
    
    
    NSLog(@"mySQLITE");
    // Open the database from the users filessytem
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
		const char *sqlStatement = "select a,b,timeEnter from note order by timeEnter desc;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
            NSLog(@"mySQLITE: OK");
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
                
				NSString *a = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 0)];
                NSString *b = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 1)];
                NSString *timeEnter = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 2)];
                
                [data addObject:[[NSString alloc] initWithFormat:@"(%@,%@):%@",
                                 a,
                                 b,
                                 timeEnter]];
                
                
                
				NSLog(@"query: (%@,%@):%@",a,b,timeEnter);
                
                
				
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
        
	}
	sqlite3_close(database);
    return 0;
}

-(int) create: (int) n {
    
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "create table IF NOT EXISTS note (a double, b varchar(40), timeEnter Date);";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		sqlite3_finalize(compiledStatement);
    }
    if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "CREATE TRIGGER IF NOT EXISTS insert_note_timeEnter  AFTER  INSERT ON note \
        BEGIN  \
        UPDATE note SET timeEnter = DATETIME('NOW')  WHERE rowid = new.rowid; \
        END;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
        sqlite3_finalize(compiledStatement);
	}
	sqlite3_close(database);
    return 0;
}


-(int) drop: (int) n {    
    
	if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "drop table IF  EXISTS note;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
		sqlite3_finalize(compiledStatement);
    }
    
    if(sqlite3_open([dbPath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "drop TRIGGER IF EXISTS insert_note_timeEnter;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
			}
		}
        sqlite3_finalize(compiledStatement);
	}
	sqlite3_close(database);
    return 0;
}


-(int) pr {
    
    for (int x = 0; x < [data count]; x++) {
        NSLog(@"Row %@", [data objectAtIndex:x]);
    }
    return 0;
}

// Take a look at this... there's a problem with pass by value/ref?
-(int) pr: (NSMutableArray *) n {
    
    for (int x = 0; x < [data count]; x++) {
        NSLog(@"zRow %@", [data objectAtIndex:x]);
        
        [n addObject:[[NSString alloc] initWithFormat:@"%@",
                      [data objectAtIndex:x] ]];
        
    }
    return 0;
}

-(void) initStatement {
    createTableStatements = [NSArray arrayWithObjects:
                             @"Cat", 
                             @"Dog", @"Fish", @"Squirrel", @"Bear", @"Turtle", nil];
    for( int x = 0; x < [createTableStatements count]; x++) {
        NSLog(@" %@",[createTableStatements objectAtIndex:x]);
    }
}

@end

