//
//  MapViewController.m
//  Stuff
//
//  Created by Mike Chirico on 2/19/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import "MapViewController.h"
#import <MapKit/MapKit.h>  // Don't forget to add mapkit in build
#import <CoreLocation/CoreLocation.h>


@interface MapViewController(){


}

@property (weak, nonatomic) IBOutlet MKMapView *mapView;

@end


@implementation MapViewController


@synthesize mapView = _mapView;
@synthesize annotations = _annotations;
@synthesize routeLine = _routeLine;
@synthesize routeLineView = _routeLineView;





- (void) updateMapView
{
    if (self.mapView.annotations) [self.mapView removeAnnotations:self.mapView.annotations];
    if (self.annotations) [self.mapView addAnnotations:self.annotations];
   
   // self.mapView.annotations;
}


- (void) setMapView:(MKMapView *) mapView
{
    _mapView = mapView;
    [self updateMapView];
}

- (void) setAnnotations:(NSArray *) annotations
{
    _annotations = annotations;
    [self updateMapView];
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
    self.mapView.showsUserLocation = YES;
    self.mapView.mapType = MKMapTypeHybrid;
    self.mapView.delegate = self; 
}


- (void)viewDidUnload
{
    [self setMapView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return YES;
}



#pragma mark MKMapViewDelegate
- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id <MKOverlay>)overlay
{
	MKOverlayView* overlayView = nil;
	
	if(overlay == self.routeLine)
	{
		//if we have not yet created an overlay view for this overlay, create it now. 
		if(nil == self.routeLineView)
		{
			self.routeLineView = [[MKPolylineView alloc] initWithPolyline:self.routeLine];
			self.routeLineView.fillColor = [UIColor blueColor];
			self.routeLineView.strokeColor = [UIColor blueColor];
			self.routeLineView.lineWidth = 3;
		}
		
		overlayView = self.routeLineView;
		
	}
    NSLog(@"Here is where we want to be: MKMapViewDelegate");
	
	return overlayView;
	
}






- (IBAction)buttonBack:(id)sender {
    
    [[self presentingViewController] dismissModalViewControllerAnimated:YES];
 
    
}

- (IBAction)buttonTest:(id)sender {
    
    // This is only for testing. You don't want to do this.
    // Instead, put this in a delegate, in the Array above.
    
    
    MKCoordinateRegion region;
    MKCoordinateSpan span;
    span.latitudeDelta=0.012;
    span.longitudeDelta=0.012;
    CLLocationCoordinate2D userCoordinate2;
    
    CLLocation *userLoc = self.mapView.userLocation.location;
    CLLocationCoordinate2D userCoordinate = userLoc.coordinate;
    
    region.span=span;
    region.center=userCoordinate;

    self.mapView.mapType = MKMapTypeHybrid;
    
    // Works. Will give you a Pin with text.
    MKPointAnnotation *pa = [[MKPointAnnotation alloc] init];
    pa.coordinate = region.center;
    pa.title = @"Your Location";
    pa.subtitle = @"Try moving";
    [self.mapView addAnnotation:pa];
    
    
    NSLog(@"user latitude = %f",userCoordinate.latitude);
    NSLog(@"user longitude = %f",userCoordinate.longitude);
    NSLog(@" %@",[NSString stringWithFormat:@"(lat,log) = (%f,%f)",userCoordinate.latitude,userCoordinate.longitude]);
    
    
    userCoordinate2.latitude = userCoordinate.latitude + 0.003;
    userCoordinate2.longitude = userCoordinate.longitude + 0.003;
    MKPointAnnotation *pa2 = [[MKPointAnnotation alloc] init ];
    pa2.coordinate = userCoordinate2;
    pa2.title = @"Point 2";
    pa2.subtitle = @"Sub title";
    
    [self.mapView addAnnotation:pa2];
    
    [self.mapView setRegion:region animated:TRUE];
    [self.mapView regionThatFits:region];
    

  

    
    
    
    [self drawPointsFromRouteCsv];
    
    
    
    
    
    
    
    
    
}

/**********************************************************************************
 **********************************************************************************
 *
 *        Test Functions, which I may get rid of later.
 *
 *
 *
 *
 *
 */


- (void) drawPointsFromRouteCsv {
    
    MKCoordinateRegion region;
    MKCoordinateSpan span;
    span.latitudeDelta=0.012;
    span.longitudeDelta=0.012;
    //CLLocationCoordinate2D userCoordinate2;
    
    CLLocation *userLoc = self.mapView.userLocation.location;
    CLLocationCoordinate2D userCoordinate = userLoc.coordinate;
    
    region.span=span;
    region.center=userCoordinate;
    
    self.mapView.mapType = MKMapTypeHybrid;

    
    NSString* filePath = [[NSBundle mainBundle] pathForResource:@"route" ofType:@"csv"];
	NSString* fileContents = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:nil];
	NSArray* pointStrings = [fileContents componentsSeparatedByCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	
	
	// while we create the route points, we will also be calculating the bounding box of our route
	// so we can easily zoom in on it. 
	MKMapPoint northEastPoint; 
	MKMapPoint southWestPoint; 
    
    MKMapPoint* pointArr = malloc(sizeof(CLLocationCoordinate2D) * pointStrings.count);
	
    
    
    // This is way too slow. You can't use this.
    // Makes the case that you need to clean everything.
    /* 
    NSRegularExpression *regex = [NSRegularExpression 
                                      regularExpressionWithPattern:@"([-]+[0-9]*.[0-9]*,[-]+[0-9]*.[0-9]*)" 
                                      options:0 error:NULL];
    for (int i = 0; i < pointStrings.count; i++)
    {
        NSLog (@"Element %i = %@", i, [pointStrings objectAtIndex: i]);
        
        NSTextCheckingResult *match = [regex firstMatchInString:[pointStrings objectAtIndex: i] options:0 range:NSMakeRange(0, [[pointStrings objectAtIndex: i] length])];
        [match rangeAtIndex:1]; 
    
    }
    */
    
	for(int idx = 0; idx < pointStrings.count; idx++)
	{
		// break the string down even further to latitude and longitude fields. 
		NSString* currentPointString = [pointStrings objectAtIndex:idx];
		NSArray* latLonArr = [currentPointString componentsSeparatedByCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@","]];
        
		CLLocationDegrees latitude  = [[latLonArr objectAtIndex:0] doubleValue];
		CLLocationDegrees longitude = [[latLonArr objectAtIndex:1] doubleValue];
        
        
        
        
        
      
        
        
        
        
		// create our coordinate and add it to the correct spot in the array 
		CLLocationCoordinate2D coordinate = CLLocationCoordinate2DMake(latitude, longitude);
		MKMapPoint point = MKMapPointForCoordinate(coordinate);
		//
		// adjust the bounding box
		//
		
		// if it is the first point, just use them, since we have nothing to compare to yet. 
		if (idx == 0) {
			northEastPoint = point;
			southWestPoint = point;
		}
		else 
		{
			if (point.x > northEastPoint.x) 
				northEastPoint.x = point.x;
			if(point.y > northEastPoint.y)
				northEastPoint.y = point.y;
			if (point.x < southWestPoint.x) 
				southWestPoint.x = point.x;
			if (point.y < southWestPoint.y) 
				southWestPoint.y = point.y;
		}
		pointArr[idx] = point;
	}
	
	// create the polyline based on the array of points. 
	self.routeLine = [MKPolyline polylineWithPoints:pointArr count:pointStrings.count];
    
	_routeRect = MKMapRectMake(southWestPoint.x, southWestPoint.y, (northEastPoint.x - southWestPoint.x), northEastPoint.y - southWestPoint.y);
    
	// clear the memory allocated earlier for the points
	free(pointArr);
    // You cannot have a return on the last line. You'll need
    // to check for this.
    // This actually draws the points.
    if (nil != self.routeLine) {
		[self.mapView addOverlay:self.routeLine];
	}
    
}



@end
