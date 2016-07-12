/*	Filename:		BoidsFlyer.cpp
	Author:			Robert Platt
	Creation date:	22/07/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids flyer class.
*/


#include "BoidsWin.h"


// Constructor for the flyer class.
BoidsFlyer::BoidsFlyer( )
{
	// Initialise the COM interface pointers.
	meshFrame = NULL;
	meshBuilder = NULL;
	leftWingFrame = NULL;
	rightWingFrame = NULL;
	builderLeftWing = NULL;
	builderRightWing = NULL;

	// Initialise the flyer's position and velocity.
	x = y = z = 0.0;
	speed = STARTING_SPEED;
	hHeading = 0.0;
	vHeading = 0.0;
	reqSpeed = STARTING_SPEED;
	reqHHeading = 0.0;
	reqVHeading = 0.0;

	startTime = clock( );  // Start the flyer's motion timer.
}


// Destructor for the flyer class.
BoidsFlyer::~BoidsFlyer( )
{
	// Release the flyers COM interfaces gracefully.
	// If the boid has wings, release them first.
	if ( leftWingFrame )
	{
		leftWingFrame -> DeleteVisual( builderLeftWing );
		rightWingFrame -> DeleteVisual( builderRightWing );
		builderLeftWing -> Release( );
		builderRightWing -> Release( );
		builderLeftWing = NULL;
		builderRightWing = NULL;
		meshFrame -> DeleteChild( leftWingFrame );
		meshFrame -> DeleteChild( rightWingFrame );
		leftWingFrame -> Release( );
		rightWingFrame -> Release( );
		leftWingFrame = NULL;
		rightWingFrame = NULL;
	}

	meshFrame -> DeleteMoveCallback( callBack, this );
	scene -> DeleteChild( meshFrame );

	if ( meshFrame )
	{
		meshFrame -> Release( );
		meshFrame = NULL;
	}

	if ( meshBuilder )
	{
		meshBuilder -> Release( );
		meshBuilder = NULL;
	}
}


void BoidsFlyer::build( CFrameWnd *win, LPDIRECT3DRM d, LPDIRECT3DRMFRAME s )
{
	window = win;
	d3drm = d;  // Store two pointers to the D3D interfaces inside the flyer.
	scene = s;  // This helps to keep future calls to the flyer concise.

	// Create the meshbuilder interface.
	d3drm -> CreateMeshBuilder( &meshBuilder );
	// Load a mesh object with the meshbuilder.
	D3DRMLOADRESOURCE resource;  // Declare a structure for the resource info.
	resource.hModule = NULL;  // Reference to module containing the resource.
	// Retrieve the shape of the flyer mesh from the main window.
	resource.lpName = MAKEINTRESOURCE( static_cast< BoidsWin * >
										( window ) -> getFlyerMesh( ) );
	resource.lpType = "MESH";  // State the type of the resource.
	// Load the mesh from the internal binary resource.
	meshBuilder -> Load( &resource, NULL,
							D3DRMLOAD_FROMRESOURCE, NULL, NULL );

	// Kept for possible future use or reference.
//	meshBuilder -> Load( OBJECT_FILENAME, NULL,
//							D3DRMLOAD_FROMFILE, NULL, NULL );

	// Set the colour of the main mesh.
	colour = static_cast< BoidsWin * >( window ) -> getFlyerColour( );
	meshBuilder -> SetColor( colour );

	// Create the mesh frame interface and add the mesh to it.
	d3drm -> CreateFrame( scene, &meshFrame );
	meshFrame -> AddVisual( meshBuilder );
	meshFrame -> AddMoveCallback( callBack, this );

	getSize( );  // Initialise the boid's size data member.

	// If the selected mesh is the animated one, add the wings to it.
	if ( static_cast< BoidsWin * >( window ) ->
									getFlyerMesh( ) == IDR_MESH_BIRDBODY )
	{
		// Add the left wing to the birds body.
		d3drm -> CreateMeshBuilder( &builderLeftWing );
		resource.lpName = MAKEINTRESOURCE( IDR_MESH_LEFTWING );
		builderLeftWing -> Load( &resource, NULL,
								D3DRMLOAD_FROMRESOURCE, NULL, NULL );
		d3drm -> CreateFrame( meshFrame, &leftWingFrame );
		leftWingFrame -> AddVisual( builderLeftWing );
		builderLeftWing -> SetColor( colour );

		// Add the right wing to the birds body.
		d3drm -> CreateMeshBuilder( &builderRightWing );
		resource.lpName = MAKEINTRESOURCE( IDR_MESH_RIGHTWING );
		builderRightWing -> Load( &resource, NULL,
								D3DRMLOAD_FROMRESOURCE, NULL, NULL );
		d3drm -> CreateFrame( meshFrame, &rightWingFrame );
		rightWingFrame -> AddVisual( builderRightWing );
		builderRightWing -> SetColor( colour );
	}
}


// Set rotation function for the flyer.
void BoidsFlyer::setRotation( D3DVALUE x, D3DVALUE y,
								D3DVALUE z, D3DVALUE magnitude )
{
	// Call the D3DRM set rotation function.
	meshFrame -> SetRotation( scene, x, y, z, magnitude );
}


// Get the position of the flyer.
void BoidsFlyer::getPosition( D3DVALUE *xPos, D3DVALUE *yPos, D3DVALUE *zPos )
{
	*xPos = x;
	*yPos = y;
	*zPos = z;
}


// Set the position of the flyer.
void BoidsFlyer::setPosition( D3DVALUE newX, D3DVALUE newY, D3DVALUE newZ )
{
	x = D3DVALUE( newX );
	y = D3DVALUE( newY );
	z = D3DVALUE( newZ );
	meshFrame -> SetPosition( scene, x, y, z );
}


// Get the velocity components of the flyer.
void BoidsFlyer::getVelocity( D3DVALUE *sp, D3DVALUE *horiz, D3DVALUE *vert )
{
	// Set the required velocity components.
	*sp = speed;
	*horiz = hHeading;
	*vert = vHeading;
}


// Set the velocity components of the flyer.
void BoidsFlyer::setVelocity( D3DVALUE sp, D3DVALUE horiz, D3DVALUE vert )
{
	// Set the required velocity components.
	speed = sp;
	hHeading = horiz;
	vHeading = vert;
}


// Get the required velocity of the flyer.
void BoidsFlyer::getReqVelocity( D3DVALUE *sp,
						D3DVALUE *horiz, D3DVALUE *vert )
{
	// Set the required velocity components.
	*sp = reqSpeed;
	*horiz = reqHHeading;
	*vert = reqVHeading;
}


// Set the required velocity of the flyer.
void BoidsFlyer::setReqVelocity( D3DVALUE sp, D3DVALUE horiz, D3DVALUE vert )
{
	// Set the required velocity components.
	reqSpeed = sp;
	reqHHeading = horiz;
	reqVHeading = vert;
}


// Set the speed of the flyer.
void BoidsFlyer::setReqSpeed( D3DVALUE sp )
{
	// Set the flyer's required speed.
	reqSpeed = sp;
}


// Retrieve the size of the boid & also update the boid's size data member.
D3DVALUE BoidsFlyer::getSize( )
{
	// First calculate the current size of the flyer.
	D3DRMBOX box;
	meshBuilder -> GetBox( &box );
	D3DVALUE sizex = box.max.x - box.min.x;
	D3DVALUE sizey = box.max.y - box.min.y;
	D3DVALUE sizez = box.max.z - box.min.z;
	// Find the average of the flyer's three dimensions.
	size = ( sizex + sizey + sizez ) / 3.0;

	return size;
}


// Scale the size of an flyer to a particular size.
void BoidsFlyer::setSize( double newSize )
{
	// Update the current size of the flyer.
	getSize( );

	// Calculate the scale factor required for the new size.
	D3DVALUE scalefactor;
	scalefactor = D3DVALUE( newSize / size );
	// Scale the flyer to the new size.
	meshBuilder -> Scale( scalefactor, scalefactor, scalefactor );

	// If the flying boid mesh is the animated one.
	if ( leftWingFrame )
	{
		// Also scale the left wing by the same amount.
		builderLeftWing -> Scale( scalefactor, scalefactor, scalefactor );

		// Also scale the right wing by the same amount.
		builderRightWing -> Scale( scalefactor, scalefactor, scalefactor );
	}

	// Update to the new size of the flyer.
	getSize( );
}


// Set the colour of the flyer.
void BoidsFlyer::setColour( D3DCOLOR col )
{
	colour = col;  // Set the data member of the boid.

	// Set the colour of the main mesh.
	meshBuilder -> SetColor( colour );

	// If the flying boid mesh is the animated one.
	if ( leftWingFrame )
	{
		// Also set the colour of the left wing.
		builderLeftWing -> SetColor( colour );

		// Also set the colour of the right wing.
		builderRightWing -> SetColor( colour );
	}
}


// Reload the flyer's mesh.
void BoidsFlyer::updateMesh( )
{
	// If the boid has wings, release them first.
	if ( leftWingFrame )
	{
		leftWingFrame -> DeleteVisual( builderLeftWing );
		rightWingFrame -> DeleteVisual( builderRightWing );
		builderLeftWing -> Release( );
		builderRightWing -> Release( );
		builderLeftWing = NULL;
		builderRightWing = NULL;
		meshFrame -> DeleteChild( leftWingFrame );
		meshFrame -> DeleteChild( rightWingFrame );
		leftWingFrame -> Release( );
		rightWingFrame -> Release( );
		leftWingFrame = NULL;
		rightWingFrame = NULL;
	}

	// First remove the previous meshbuilder from the boid's frame.
	meshFrame -> DeleteVisual( meshBuilder );
	meshBuilder -> Release( );  // Release the meshbuilder.
	meshBuilder = NULL;  // Release the meshbuilder.

	// Create a new meshbuilder.
	d3drm -> CreateMeshBuilder( &meshBuilder );

	// Load a new mesh from a resource with the new meshbuilder.
	D3DRMLOADRESOURCE resource;  // Declare a structure for the resource info.
	resource.hModule = NULL;  // Reference to module containing the resource.
	resource.lpName = MAKEINTRESOURCE( static_cast< BoidsWin * >
											( window ) -> getFlyerMesh( ) );
	resource.lpType = "MESH";
	meshBuilder -> Load( &resource, NULL,
					D3DRMLOAD_FROMRESOURCE, NULL, NULL );

	// Set the colour of the mesh to pure white.
	meshBuilder -> SetColor( colour );

	// Add the new meshbuilder to the boid's frame.
	meshFrame -> AddVisual( meshBuilder );

	// If the selected mesh is the animated one.
	if ( static_cast< BoidsWin * >( window ) -> getFlyerMesh( )
												== IDR_MESH_BIRDBODY )
	{
		// Add the left wing to the birds body.
		d3drm -> CreateMeshBuilder( &builderLeftWing );
		resource.lpName = MAKEINTRESOURCE( IDR_MESH_LEFTWING );
		builderLeftWing -> Load( &resource, NULL,
									D3DRMLOAD_FROMRESOURCE, NULL, NULL );
		d3drm -> CreateFrame( meshFrame, &leftWingFrame );
		leftWingFrame -> AddVisual( builderLeftWing );
		builderLeftWing -> SetColor( colour );

		// Add the right wing to the birds body.
		d3drm -> CreateMeshBuilder( &builderRightWing );
		resource.lpName = MAKEINTRESOURCE( IDR_MESH_RIGHTWING );
		builderRightWing -> Load( &resource, NULL,
									D3DRMLOAD_FROMRESOURCE, NULL, NULL );
		d3drm -> CreateFrame( meshFrame, &rightWingFrame );
		rightWingFrame -> AddVisual( builderRightWing );
		builderRightWing -> SetColor( colour );
	}
}


// Static callback function to move the flyer.
void BoidsFlyer::callBack( LPDIRECT3DRMFRAME meshframe,
										void *arg, D3DVALUE delta )
{
	// Use the provided pointer argument to -
	// - call a specific flyer's member functions.
	BoidsFlyer *boidsFlyer = static_cast< BoidsFlyer * >( arg );

	boidsFlyer -> directToBoid( );
	boidsFlyer -> velocityMatching( );
	boidsFlyer -> collisionAvoidance( );
	boidsFlyer -> landscapeAvoidance( );
	boidsFlyer -> moveObject( );
}


// Function that directs a boid to another boid in it's field of vision.
void BoidsFlyer::directToBoid( )
{
	BoidsWin *win = static_cast< BoidsWin * >( window );

	// Only perform direct to boid if the flag is set.
	if ( win -> getFlockFormingActive( ) == false )
	{
		return;
	}

	D3DVALUE tempX, tempY, tempZ;
	bool newVelocity = false;
	D3DVALUE distance;
	D3DVALUE shortestDistance = win -> getFlockFormingDistance( );
	D3DVALUE hHeadingTo, vHeadingTo;
	D3DVALUE newSpeed, newHHeading, newVHeading;

	// Find out the number of Boids present by calling the parent window.
	int &numFlyers = win -> getNumObjects( );

	// Get a reference to the window's vector of boids.
	vector< BoidsFlyer * > &objects = win -> getFlyersRef( );

	// Iterate through all the boids ignoring the current one.
	for ( int index = 0; index < numFlyers; index++ )
	{
		// Skip the current boid.
		if ( objects[ index ] != this )
		{
			// Shift the other boid so that the current boid is on the origin.
			// This prevents the screen wrap around interfering.
			tempX = objects[ index ] -> x - x;
			tempY = objects[ index ] -> y - y;
			tempZ = objects[ index ] -> z - z;
			wrapAround( &tempX, &tempY, &tempZ );

			// Do a distance check on the boids.
			distance = sqrt( pow( tempX, 2 ) + pow( tempY, 2 )
													+ pow( tempZ, 2 ) );

			if ( distance <= win -> getFlockFormingDistance( ) )
			{
				// Check if the boid is in the angle of vision.
				// Find the headings to the other boid.
				// First find the vertical heading.
				if ( distance < 0.5 )  // Prevent division by zero.
				{
					distance = D3DVALUE( 0.5 );
				}

				vHeadingTo = asin( tempY / distance ) * 180.0 / PI;


				// Then find the horizontal heading.
				// Prevent division by zero.
				if ( ( tempZ > -0.5 ) && ( tempZ < 0.5 ) )
				{
					tempZ = D3DVALUE( 0.5 );
				}

				hHeadingTo = atan( tempX / tempZ ) * 180.0 / PI;


				// Correct the headings if z is less than zero.
				if ( ( tempX > 0.0 ) && ( tempZ < 0.0 ) )
				{
					hHeadingTo += 180.0;
				}

				if ( ( tempX < 0.0 ) && ( tempZ < 0.0 ) )
				{
					hHeadingTo -= 180.0;
				}


				// Normalize the headings, so that -
				// - they can be properly compared.
				hHeadingTo -= hHeading;
				vHeadingTo -= vHeading;
				maintainHeadings( &hHeadingTo, &vHeadingTo );

				if ( ( hHeadingTo <= win -> getAngleOfVision( ) )
					&& ( hHeadingTo >= -( win -> getAngleOfVision( ) ) )
					&& ( vHeadingTo <= win -> getAngleOfVision( ) )
					&& ( vHeadingTo >= -( win -> getAngleOfVision( ) ) ) )
				{
					if ( distance < shortestDistance )
					{
						// Restore the headings so that -
						// - they can be used properly.
						hHeadingTo += hHeading;
						vHeadingTo += vHeading;
						maintainHeadings( &hHeadingTo, &vHeadingTo );

						// Set the new required velocity.
						newVelocity = true;
						shortestDistance = distance;
						newHHeading = hHeadingTo;
						newVHeading = vHeadingTo;
						newSpeed = objects[ index ] ->
										speed + CATCH_UP_INCREASE;

						// Limit the speed.
						if ( newSpeed > win -> getMaximumSpeed( ) )
						{
							newSpeed = win -> getMaximumSpeed( );
						}
					}
				}
			}
		}
	}

	if ( newVelocity )
	{
		setReqVelocity( newSpeed, newHHeading, newVHeading );
	}
}


// Function to enable a boid to match it's flockmates velocites.
void BoidsFlyer::velocityMatching( )
{
	BoidsWin *win = static_cast< BoidsWin * >( window );

	// Only perform velocity matching if the flag is set.
	if ( win -> getVelocityMatchingActive( ) == false )
	{
		return;
	}

	D3DVALUE tempX, tempY, tempZ;
	bool newVelocity = false;
	D3DVALUE distance;
	D3DVALUE hHeadingOf, vHeadingOf;
	D3DVALUE totalSpeed = 0, totalHHeading = 0, totalVHeading = 0;
	int flockmates = 0;
	D3DVALUE newSpeed, newHHeading, newVHeading;

	// Find out the number of Boids present by calling the parent window.
	int &numFlyers = win -> getNumObjects( );

	// Get a reference to the window's vector of boids.
	vector< BoidsFlyer * > &objects = win -> getFlyersRef( );

	// Iterate through all the boids ignoring the current one.
	for ( int index = 0; index < numFlyers; index++ )
	{
		// Skip the current boid.
		if ( objects[ index ] != this )
		{
			// Shift the other boid so that the current boid is on the origin.
			// This prevents the screen wrap around from interfering.
			tempX = objects[ index ] -> x - x;
			tempY = objects[ index ] -> y - y;
			tempZ = objects[ index ] -> z - z;
			wrapAround( &tempX, &tempY, &tempZ );

			// Do a distance check on the boids.
			distance = sqrt( pow( tempX, 2 ) +
							pow( tempY, 2 ) + pow( tempZ, 2 ) );

			// If the distance is in the flocking radius.
			if ( distance <= win -> getFlockingRadius( ) )
			{
				// Check that the headings are similar.
				// Get the headings of the other boid.
				hHeadingOf = objects[ index ] -> hHeading;
				vHeadingOf = objects[ index ] -> vHeading;

				// Normalise the headings, so that -
				// - they can be properly compared.
				hHeadingOf -= hHeading;
				vHeadingOf -= vHeading;
				maintainHeadings( &hHeadingOf, &vHeadingOf );

				if ( ( hHeadingOf <= +( win ->
									getRangeOfFlockHeadings( ) ) )
					&& ( hHeadingOf >= -( win ->
									getRangeOfFlockHeadings( ) ) )
					&& ( vHeadingOf <= +( win ->
									getRangeOfFlockHeadings( ) ) )
					&& ( vHeadingOf >= -( win ->
									getRangeOfFlockHeadings( ) ) ) )
				{
					// Restore the headings so that they can be used properly.
					hHeadingOf += hHeading;
					vHeadingOf += vHeading;
					maintainHeadings( &hHeadingOf, &vHeadingOf );

					// Take the boids velocity into account ( in the flock ).
					// Add the components to the totals -
					// - to find an average later on.
					totalSpeed += objects[ index ] -> speed;
					totalHHeading += hHeadingOf;
					totalVHeading += vHeadingOf;
					flockmates++;
					newVelocity = true;
				}
			}
		}
	}

	if ( newVelocity )
	{
		newSpeed = totalSpeed / flockmates;
		newHHeading = totalHHeading / flockmates;
		newVHeading = totalVHeading / flockmates;
		setReqVelocity( newSpeed, newHHeading, newVHeading );
	}
}


// Function to detect and prevent any boid collisions.
void BoidsFlyer::collisionAvoidance( )
{
	BoidsWin *win = static_cast< BoidsWin * >( window );

	// Only perform collision avoidance if the flag is set.
	if ( win -> getCollisionAvoidanceActive( ) == false )
	{
		return;
	}

	D3DVALUE tempX, tempY, tempZ;
	bool newVelocity = false;
	D3DVALUE distance;
	D3DVALUE shortestDistance = win -> getCollisionDistance( );
	D3DVALUE hHeadingTo, vHeadingTo;
	D3DVALUE newSpeed, newHHeading, newVHeading;

	// Find out the number of Boids present by calling the parent window.
	int &numFlyers = win -> getNumObjects( );

	// Get a reference to the window's vector of boids.
	vector< BoidsFlyer * > &objects = win -> getFlyersRef( );

	// Iterate through all the boids ignoring the current one.
	for ( int index = 0; index < numFlyers; index++ )
	{
		// Skip the current boid.
		if ( objects[ index ] != this )
		{
			// Shift the other boid so that the current boid is on the origin.
			// This prevents the screen wrap around interfering.
			tempX = objects[ index ] -> x - x;
			tempY = objects[ index ] -> y - y;
			tempZ = objects[ index ] -> z - z;
			wrapAround( &tempX, &tempY, &tempZ );

			// Do a distance check on the boids.
			distance = sqrt( pow( tempX, 2 ) +
							pow( tempY, 2 ) + pow( tempZ, 2 ) );

			if ( distance <= win -> getCollisionDistance( ) )
			{
				// Find the headings to the other boid.
				// First find the vertical heading.
				if ( distance < 0.5 )  // Prevent division by zero.
				{
					distance = D3DVALUE( 0.5 );
				}

				vHeadingTo = asin( tempY / distance ) * 180.0 / PI;


				// Then find the horizontal heading.
				// Prevent division by zero.
				if ( ( tempZ > -0.5 ) && ( tempZ < 0.5 ) )
				{
					tempZ = D3DVALUE( 0.5 );
				}

				hHeadingTo = atan( tempX / tempZ ) * 180.0 / PI;


				// Correct the headings if z is less than zero.
				if ( ( tempX > 0.0 ) && ( tempZ < 0.0 ) )
				{
					hHeadingTo += 180.0;
				}

				if ( ( tempX < 0.0 ) && ( tempZ < 0.0 ) )
				{
					hHeadingTo -= 180.0;
				}

				if ( distance < shortestDistance )
				{
					newVelocity = true;
					shortestDistance = distance;
					// Set the new headings.
					// Normalise the headings, so that -
					// - they can be properly calculated.
					hHeadingTo -= hHeading;
					vHeadingTo -= vHeading;
					maintainHeadings( &hHeadingTo, &vHeadingTo );
					if ( hHeadingTo >= 0.0 )  // Turn left.
					{
						newHHeading = hHeading + ( hHeadingTo - 90 )
							* ( distance / win -> getCollisionDistance( ) );
					}
					if ( hHeadingTo < 0.0 )  // Turn right.
					{
						newHHeading = hHeading + ( hHeadingTo + 90 )
							* ( distance / win -> getCollisionDistance( ) );
					}
					if ( vHeadingTo >= 0.0 )  // Turn down.
					{
						newVHeading = vHeading + ( vHeadingTo - 90 )
							* ( distance / win -> getCollisionDistance( ) );
					}
					if ( vHeadingTo < 0.0 )  // Turn up.
					{
						newVHeading = vHeading + ( vHeadingTo + 90 )
							* ( distance / win -> getCollisionDistance( ) );
					}

					// Set the new speed.
					newSpeed = objects[ index ] -> speed - (
						SLOW_DOWN_DECREASE * ( distance / win ->
											getCollisionDistance( ) ) );

					// Limit the speed.
					if ( newSpeed < win -> getMinimumSpeed( ) )
					{
						newSpeed = win -> getMinimumSpeed( );
					}
				}
			}
		}
	}

	if ( newVelocity )
	{
		setReqVelocity( newSpeed, newHHeading, newVHeading );
	}
}


// Calculate a position relative to a boid & the -
// - scene, given the distance and direction.
D3DVECTOR BoidsFlyer::calculateOffset( D3DVALUE distance,
									D3DVALUE hAngle, D3DVALUE vAngle )
{
	D3DVECTOR position;

	// 1. Find the Y component of the points position.
	position.y = distance * D3DVALUE( sin( vAngle / 180.0 * PI ) );
	position.y += y;  // Make relative to the boid's position.

	// 2. Find the horizontal distance to points position
	//     ( intermediate calculation ).
	D3DVALUE horizontalDistance = distance * D3DVALUE(
									cos( vAngle / 180.0 * PI ) );

	// 3. Find the X component of the points position.
	position.x = horizontalDistance * D3DVALUE(
									sin( hAngle / 180.0 * PI ) );
	position.x += x;  // Make relative to the boid's position.

	// 4. Find the Z component of the points position.
	position.z = horizontalDistance * D3DVALUE(
									cos( hAngle / 180.0 * PI ) );
	position.z += z;  // Make relative to the boid's position.
	
	// 5. Perform a wrap around on the position to ensure it is within range.
	wrapAround( &position.x, &position.y, &position.z );

	return position;
}


// Function to prevent any boid collisions with the landscape.
void BoidsFlyer::landscapeAvoidance( )
{
	BoidsWin *win = static_cast< BoidsWin * >( window );

	// Abort the function if the landscape is not present.
	if ( win -> getLandExists( ) == false )
	{
		return;
	}

	// Continue with the function if the lanscape is present.
	// If the position of the boid is over the height limit.
	if ( y > Y_LIMIT )
	{
		// Turn the boid downwards to keep in it's correct area.
		reqVHeading = DOWNWARD_ANGLE_FROM_CEILING;
	}

	// Make the boid avoid any collision with the landscape.
	// Find the distance to the nearest collision in the path of the boid.
	D3DVECTOR offset;
	bool collisionDetected = false;
	D3DVALUE collisionDistance = 0;

	// Scan ahead of the boid using fine -
	// - increments to catch the jagged landscape.
	for ( collisionDistance; ( ( !collisionDetected ) && 
		( collisionDistance <= LAND_COLLISION_DISTANCE ) ); /* see below */ )
	{
		// 1. Find the position of the point, in the current direction
		//    of the current boid and also at the given collision
		//    distance away from it.
		offset = calculateOffset( collisionDistance, hHeading, vHeading );

		// 2. Check if the position of the point is below the landscape.
		collisionDetected = win -> getBelowLandscapeSurface(
										offset.x, offset.y, offset.z );

		// 3. Increment the collision distance proportional -
		// - to the distance from the boid.
		if ( collisionDistance < FINE_SCAN_LIMIT )
		{
			// Fine scan for short range.
			collisionDistance += D3DVALUE( FINE_SCAN_RATE );
		}
		else if ( collisionDistance < MEDIUM_SCAN_LIMIT )
		{
			// Medium scan for medium range.
			collisionDistance += D3DVALUE( MEDIUM_SCAN_RATE );
		}
		else
		{
			// Fast scan for long range.
			collisionDistance += D3DVALUE( FAST_SCAN_RATE );
		}
	}

	// 4.  Manouver the boid so that it avoids -
	//     - collision with the landscape if necessary.
	if ( collisionDetected )
	{
		landCollisionAvoidance( collisionDistance );
	}
}


// Calculate the X Z distance from a boid, given the distance and direction.
D3DVECTOR BoidsFlyer::calculateClearance( D3DVALUE length, D3DVALUE hAngle )
{
	D3DVECTOR distance;

	// Find the X component of the points distance.
	distance.x = length * D3DVALUE( sin( hAngle / 180.0 * PI ) );

	distance.y = 0;  // Not used in the X Z plane.

	// Find the Z component of the points distance.
	distance.z = length * D3DVALUE( cos( hAngle / 180.0 * PI ) );

	return distance;
}


// Finds the safe route to take to avoid collision with the landscape.
void BoidsFlyer::landCollisionAvoidance( D3DVALUE distance )
{
	BoidsWin *win = static_cast< BoidsWin * >( window );

	D3DVECTOR offset;
	bool safePath = false;
	// Number of scan increments.
	D3DVALUE accuracy = LAND_COLLISION_AVOIDANCE_ACCURACY;


	// Scan arround the collsion point to find a safe path.
	for ( int factor = 1; factor <= (int)accuracy; factor++ )
	{
		// Turn the boid left.
		offset = calculateOffset( distance, hHeading - 60.0 /
										accuracy * factor, vHeading );
		safePath = !( win -> getBelowLandscapeSurface( offset.x,
							offset.y - LANDSCAPE_CLEARANCE, offset.z ) );
		if ( safePath )
		{
			reqHHeading = hHeading - 60.0 / accuracy *
									factor - SIDE_CLEARANCE_ANGLE;
			return;
		}

		// Turn the boid right.
		offset = calculateOffset( distance, hHeading + 60.0 /
										accuracy * factor, vHeading );
		safePath = !( win -> getBelowLandscapeSurface( offset.x,
							offset.y - LANDSCAPE_CLEARANCE, offset.z ) );
		if ( safePath )
		{
			reqHHeading = hHeading + 60.0 / accuracy *
									factor + SIDE_CLEARANCE_ANGLE;
			return;
		}

		// Turn the boid up and left.
		offset = calculateOffset( distance, hHeading - 45.0 / accuracy *
								factor, vHeading + 45.0 / accuracy * factor );
		safePath = !( win -> getBelowLandscapeSurface( offset.x,
							offset.y - LANDSCAPE_CLEARANCE, offset.z ) );
		if ( safePath )
		{
			reqHHeading = hHeading - 45.0 / accuracy *
										factor - SIDE_CLEARANCE_ANGLE;
			reqVHeading = vHeading + 45.0 / accuracy * factor;
			return;
		}

		// Turn the boid up and right.
		offset = calculateOffset( distance, hHeading + 45.0 / accuracy *
								factor, vHeading + 45.0 / accuracy * factor );
		safePath = !( win -> getBelowLandscapeSurface( offset.x,
							offset.y - LANDSCAPE_CLEARANCE, offset.z ) );
		if ( safePath )
		{
			reqHHeading = hHeading + 45.0 / accuracy *
										factor + SIDE_CLEARANCE_ANGLE;
			reqVHeading = vHeading + 45.0 / accuracy * factor;
			return;
		}

		// Turn the boid upwards.
		offset = calculateOffset( distance, hHeading,
									vHeading + 60.0 / accuracy * factor );
		safePath = !( win -> getBelowLandscapeSurface( offset.x,
								offset.y - LANDSCAPE_CLEARANCE, offset.z ) );
		if ( safePath )
		{
			reqVHeading = vHeading + 60.0 / accuracy * factor;
			return;
		}
	}

	// If no safe route was found, just turn the boid upwards.
	reqVHeading = UPWARD_ANGLE_FROM_COLLISION;
}


// This function converts a speed & heading vector to an x, y, z vector.
void BoidsFlyer::convertVector( D3DVALUE *xi, D3DVALUE *yi, D3DVALUE *zi )
{
	// 1. Calculate the Y velocity component.
	*yi = speed * D3DVALUE( sin( vHeading / 180.0 * PI ) );

	// 2. Calculate the horizontal speed ( intermediate calcuation ).
	D3DVALUE horizontalSpeed = D3DVALUE( sqrt( pow( speed, 2 )
													- pow( *yi, 2 ) ) );

	// 3. Calculate the Z velocity component.
	*zi = horizontalSpeed * D3DVALUE( cos( hHeading / 180.0 * PI ) );

	// 4. Calculate the X velocity component.
	*xi = horizontalSpeed * D3DVALUE( sin( hHeading / 180.0 * PI ) );
}


// Make sure that the headings are in the correct ranges.
void BoidsFlyer::maintainHeadings( D3DVALUE *horiz, D3DVALUE *vert )
{
	while( *horiz > 180.0 )
	{
		*horiz -= 360.0;
	}
	while( *horiz < -180.0 )
	{
		*horiz += 360.0;
	}
	while( *vert > 90.0 )
	{
		*vert -= 90.0;
	}
	while( *vert < -90.0 )
	{
		*vert += 90.0;
	}
}


// Function to make the object tend towards it's required velocity.
void BoidsFlyer::updateVelocity( double time )
{
	maintainHeadings( &reqHHeading, &reqVHeading );

	// Calculate the differences in the velocity values.
	D3DVALUE difSpeed = reqSpeed - speed;
	D3DVALUE difHHeading = reqHHeading - hHeading;
	D3DVALUE difVHeading = reqVHeading - vHeading;

	// If the horizontal turn is greater than 180 degrees, turn the other way.
	if ( difHHeading < -180.0 )
	{
		difHHeading = ( reqHHeading + 360.0 ) - hHeading;
	}

	BoidsWin *win = static_cast< BoidsWin * >( window );

	// Update the boid.
	if ( time <= MAXIMUM_TIMESPAN )  // This prevents any jumping.
	{
		// Update the flyer's speed.
		speed += D3DVALUE( difSpeed * win -> getAccelerationRate( ) * time );

		// Apply some rotation to the flyer's orientation.
		hHeading += D3DVALUE( difHHeading * win ->
								getAccelerationRate( ) * time );
		vHeading += D3DVALUE( difVHeading * win ->
								getAccelerationRate( ) * time );
	}


	// Update the flyer's visual orientation.
	D3DVALUE xi, yi, zi;
	convertVector( &xi, &yi, &zi );
	meshFrame -> SetOrientation( scene, xi, yi, zi, 0, 1, 0 );
}


// Make the flyer re-appear on the other side of it's space.
void BoidsFlyer::wrapAround( D3DVALUE *xPtr, D3DVALUE *yPtr, D3DVALUE *zPtr )
{
	// Loop around the six sides of the cubed area.
	if ( *xPtr > X_LIMIT )
	{
		*xPtr = -X_LIMIT;
	}

	if ( *xPtr < -X_LIMIT )
	{
		*xPtr = X_LIMIT;
	}

	// If the position of the boid is over the height limit.
	if ( *yPtr > Y_LIMIT )
	{
		// If the landscape is not present.
		if ( static_cast< BoidsWin * >( window ) ->
										getLandExists( ) == false )
		{
			// Perform wrap around on the boid.
			*yPtr = -Y_LIMIT;
		}
	}

	// If the position of the boid is under the height limit.
	if ( *yPtr < -Y_LIMIT )
	{
		// If the landscape is not present.
		if ( static_cast< BoidsWin * >( window ) ->
										getLandExists( ) == false )
		{
			// Perform wrap around on the boid.
			*yPtr = Y_LIMIT;
		}
	}

	if ( *zPtr > Z_LIMIT )
	{
		*zPtr = -Z_LIMIT;
	}

	if ( *zPtr < -Z_LIMIT )
	{
		*zPtr = Z_LIMIT;
	}
}


// Move the flyer while the application is running.
void BoidsFlyer::moveObject( )
{
	BoidsWin *win = static_cast< BoidsWin * >( window );

	// Read the end time for the flyers motion.
	finishTime = clock( );

	// Calculate the time in seconds since the last update.
	double timeSpan = (double)( finishTime - startTime ) /
											(double)CLOCKS_PER_SEC;
	// Stop the boid's motion if the stopped flag is set.
	bool stopped = win -> getStopped( );
	if ( stopped )
	{
		timeSpan = 0;  // Update time interval equal to zero.
	}

	// Update the flyer's velocity to it's required velocity.
	updateVelocity( timeSpan );

	// Convert the flyer's vector before applying it.
	D3DVALUE xi, yi, zi;
	convertVector( &xi, &yi, &zi );


	// Increment the new position of the boid.
	// This prevents the boid from jumping.
	if ( timeSpan <= MAXIMUM_TIMESPAN )
	{
		x += xi * D3DVALUE( timeSpan );
		y += yi * D3DVALUE( timeSpan );
		z += zi * D3DVALUE( timeSpan );
	}

	// Reset the start time for the flyers motion.
	startTime = clock( );

	wrapAround( &x, &y, &z );  // Make the screen loop around.

	// Set the new position of the flyer.
	meshFrame -> SetPosition( scene, x, y, z );

	// Animate the boids wings if any.
	// Only if the selected mesh is the animated -
	// - one and the simulation is running.
	if ( leftWingFrame && !stopped && ( timeSpan <= MAXIMUM_TIMESPAN ) )
	{
		// Get the system time in milliseconds.
		ULONG milliTime = clock( ) * 1000 / CLOCKS_PER_SEC *
									win -> getWingStrokesPerSecond( );
		// Remove the seconds, just keeping the milliseconds.
		milliTime %= 1000;
		// Convert the milliseconds into radians.
		D3DVALUE radians = milliTime / 159.1549431;
		// Calculate the X vector component.
		D3DVALUE xVector = D3DVALUE( sin( radians ) );

		// Set the new orientation of the wings.
		leftWingFrame -> SetOrientation( meshFrame, 0, 0, 1,
													xVector, 2, 0 );
		rightWingFrame -> SetOrientation( meshFrame, 0, 0, 1,
													-xVector, 2, 0 );
	}
}
