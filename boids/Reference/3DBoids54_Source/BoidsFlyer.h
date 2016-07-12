/*	Filename:		BoidsFlyer.h
	Author:			Robert Platt
	Creation date:	22/07/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids flyer class.
*/


#include <math.h>
#include "resource.h"
#include "BoidsLand.h"


// Retained for possible future use.
//#define OBJECT_FILENAME "stealth.x"
//#define OBJECT_FILENAME "bird.x"
//#define OBJECT_FILENAME "fullbird.x"
//#define OBJECT_FILENAME "viper.x"
//#define OBJECT_FILENAME "tetra.x"


#ifndef BOIDS_FLYER_H
#define BOIDS_FLYER_H


const double PI = 3.14159;  // Maths PI constant.


// Constants for the flyers.
const D3DVALUE STARTING_SPEED = 200.0;
const D3DVALUE MINIMUM_SPEED = 150.0;
const D3DVALUE MAXIMUM_SPEED = 350.0;
const D3DVALUE FLOCK_FORMING_DISTANCE = 500.0;
const D3DVALUE ANGLE_OF_VISION = 90.0;
const D3DVALUE CATCH_UP_INCREASE = 50.0;
const D3DVALUE COLLISION_DISTANCE = 50.0;
const D3DVALUE SLOW_DOWN_DECREASE = 50.0;
const D3DVALUE FLOCKING_RADIUS = 150.0;
const D3DVALUE RANGE_OF_FLOCK_HEADINGS = 60.0;
const D3DVALUE DOWNWARD_ANGLE_FROM_CEILING = -22.5;
const D3DVALUE UPWARD_ANGLE_FROM_COLLISION = 60.0;
const D3DVALUE LAND_COLLISION_DISTANCE = 500.0;
const D3DVALUE LAND_COLLISION_AVOIDANCE_ACCURACY = 20.0;
const D3DVALUE LANDSCAPE_CLEARANCE = 150.0;
const D3DVALUE SIDE_CLEARANCE_ANGLE = 20.0;
const D3DVALUE WING_STROKES_PER_SECOND = 1.5;
const D3DVALUE ACCELERATION_RATE = 2.0;
const D3DVALUE FINE_SCAN_RATE = 5.0;
const D3DVALUE MEDIUM_SCAN_RATE = 25.0;
const D3DVALUE FAST_SCAN_RATE = 50.0;
const int FINE_SCAN_LIMIT = 150;
const int MEDIUM_SCAN_LIMIT = 250;


class BoidsFlyer
{
public:
	BoidsFlyer( );  // Flyer constructor.
	~BoidsFlyer( ); // Flyer destructor.

	// Some flyer get/set member functions.
	void build( CFrameWnd *win, LPDIRECT3DRM d, LPDIRECT3DRMFRAME s );
	void setRotation( D3DVALUE x, D3DVALUE y,
							D3DVALUE z, D3DVALUE magintude );
	void getPosition( D3DVALUE *xPos, D3DVALUE *yPos, D3DVALUE *zPos );
	void setPosition( D3DVALUE newX, D3DVALUE newY, D3DVALUE newZ );
	void getVelocity( D3DVALUE *sp, D3DVALUE *horiz, D3DVALUE *vert );
	void setVelocity( D3DVALUE sp, D3DVALUE horiz, D3DVALUE vert );
	void getReqVelocity( D3DVALUE *sp, D3DVALUE *horiz, D3DVALUE *vert );
	void setReqVelocity( D3DVALUE speed, D3DVALUE horizontal,
												D3DVALUE vertical );
	void setReqSpeed( D3DVALUE speed );
	D3DVALUE getSize( );
	void setSize( double s );
	void setColour( D3DCOLOR col );
	LPDIRECT3DRMFRAME getFramePtr( ) { return meshFrame; }
	void updateMesh( );  // Reload the flyer's mesh.


	// Callback function used to call behaviour functions.
	static void callBack( LPDIRECT3DRMFRAME frame,
									void *arg, D3DVALUE delta );

	// The main boid behaviour functions.
	void directToBoid( );
	void velocityMatching( );
	void collisionAvoidance( );
	void landscapeAvoidance( );
	void landCollisionAvoidance( D3DVALUE distance );

	// Auxillary functions for the callbacks.
	void wrapAround( D3DVALUE *x, D3DVALUE *y, D3DVALUE *z );
	void moveObject( );
	void convertVector( D3DVALUE *xi, D3DVALUE *yi, D3DVALUE *zi );
	void maintainHeadings( D3DVALUE *horiz, D3DVALUE *vert );
	void updateVelocity( double timeSpan );
	D3DVECTOR calculateOffset( D3DVALUE distance,
							D3DVALUE hAngle, D3DVALUE vAngle );
	D3DVECTOR calculateClearance( D3DVALUE distance, D3DVALUE hAngle );

private:
	// The flyer's data members.
	CFrameWnd *window;
	LPDIRECT3DRM d3drm;
	LPDIRECT3DRMFRAME scene;
	LPDIRECT3DRMMESHBUILDER meshBuilder;
	LPDIRECT3DRMMESHBUILDER builderLeftWing;
	LPDIRECT3DRMMESHBUILDER builderRightWing;
	LPDIRECT3DRMFRAME meshFrame;
	LPDIRECT3DRMFRAME leftWingFrame;
	LPDIRECT3DRMFRAME rightWingFrame;
	D3DCOLOR colour;
	D3DVALUE size;

	// Position and velocity vectors.
	D3DVALUE x, y, z;
	D3DVALUE speed, hHeading, vHeading;
	D3DVALUE reqSpeed, reqHHeading, reqVHeading;

	// Used to time the motion of the object.
	clock_t startTime, finishTime;
};


#endif
