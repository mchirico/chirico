//
//  MapViewController.h
//  Stuff
//
//  Created by Mike Chirico on 2/19/12.
//  Copyright (c) 2012 CWXSTAT INC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>  // Don't forget to add mapkit in build
#import <CoreLocation/CoreLocation.h>







@interface MapViewController : UIViewController <MKMapViewDelegate> {
    // the data representing the route points. 
	MKPolyline* _routeLine;
	
    
	// the view we create for the line on the map
	MKPolylineView* _routeLineView;
	
	// the rect that bounds the loaded points
	MKMapRect _routeRect;
    
    
}


@property (nonatomic, retain) MKPolyline* routeLine;
@property (nonatomic, retain) MKPolylineView* routeLineView;


- (IBAction)buttonBack:(id)sender;
- (IBAction)buttonTest:(id)sender;
@property (nonatomic, strong) NSArray *annotations; // Hmm got it from CS193p


// My Special functions, which I may get rid of later

- (void) drawPointsFromRouteCsv;
@end
