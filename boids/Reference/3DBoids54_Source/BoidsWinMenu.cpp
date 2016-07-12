/*	Filename:		BoidsWinMenu.cpp
	Author:			Robert Platt
	Creation date:	15/06/1999
	Modified:		08/02/2004
	Version:		0.54
	Description:	Implementation file for the boids main window class.
*/


#include "BoidsConfig.h"


// Message handler to load in a configuration.
afx_msg void BoidsWin::OnLoad( )
{
	// Set the multitasking flag.
	appIdle = false;

	// Restart the rendering thread if stopped.
	threadEnabled = true;

	if ( threadFinished == true )
	{
		threadFinished = false;
		ptrD3DThread = AfxBeginThread( d3dThread, this,
											THREAD_PRIORITY_NORMAL );
	}


	// Create an MFC file dialog.
	CFileDialog fileDialog( TRUE, NULL, NULL, NULL,
						"Configuration Files (*.ini)|*.ini|" );

	// Activate the dialog.
	if ( fileDialog.DoModal( ) == IDCANCEL )
	{
		return;  // Abort if cancel is pressed.
	}

	// Extract the chosen filename.
	CString fileName = fileDialog.GetFileName( );

	// Make a new configuration object.
	BoidsConfig config;

	// Load data from stored configuration file.
	config.loadConfig( fileName );

	// Adjust the number of flyers.
	int num = config.getNFlyers( );
	// If there is more in the config than active.
	if ( num > numFlyers )
	{
		// Reduce the number to be changed accordingly.
		num = numFlyers;
	}
	else
	{
		// Reduce the number of active to match the config.
		requiredFlyers = num;
	}

	// Declare a Flyer structure, to use for extraction of the data.
	Flyer flr;
	// Get a copy of the configuration object's vector.
	vector< Flyer * > fConfigs = config.getFConfigs( );
	// Iterate through all the active flyers.
	for ( int number = 0; number < num; number++ )
	{
		flr = *fConfigs[ number ];  // Get a pointer to a flyer.

		// Set the state of the relevant flyer.
		flyers[ number ] -> setPosition( flr.xPos, flr.yPos, flr.zPos );
		flyers[ number ] -> setVelocity( flr.speed,
										flr.hHeading, flr.vHeading );
		flyers[ number ] -> setReqVelocity( flr.reqSpeed,
										flr.reqHHeading, flr.reqVHeading );
	}


	// Stop the rendering thread when done.
	threadEnabled = false;


	return;
}


// Message handler to save the configuration.
afx_msg void BoidsWin::OnSave( )
{
	// Set the multitasking flag.
	appIdle = false;

	// Restart the rendering thread if stopped.
	threadEnabled = true;

	if ( threadFinished == true )
	{
		threadFinished = false;
		ptrD3DThread = AfxBeginThread( d3dThread, this,
										THREAD_PRIORITY_NORMAL );
	}


	// Make a data structure to pass to the configuration object.
	// A vector of pointers to a Flyer structure.
	vector< Flyer * > f;
	Flyer *fPtr;

	// Iterate through all the active flyers.
	for ( int number = 0; number < numFlyers; number++ )
	{
		// Make a new Flyer structure in memory;
		fPtr = new Flyer( );

		// Declare some temporary local variables.
		D3DVALUE x, y, z;
		D3DVALUE hH, vH;
		D3DVALUE reqHH, reqVH;
		D3DVALUE s, reqS;

		// Get the data from the flyer.
		flyers[ number ] -> getPosition( &x, &y, &z );
		flyers[ number ] -> getVelocity( &s, &hH, &vH );
		flyers[ number ] -> getReqVelocity( &reqS, &reqHH, &reqVH );

		// Fill the structure with the flyers data.
		fPtr -> xPos = (int)x;
		fPtr -> yPos = (int)y;
		fPtr -> zPos = (int)z;
		fPtr -> hHeading = (int)hH;
		fPtr -> vHeading = (int)vH;
		fPtr -> reqHHeading = (int)reqHH;
		fPtr -> reqVHeading = (int)reqVH;
		fPtr -> speed = (int)s;
		fPtr -> reqSpeed = (int)reqS;

		// Add a pointer to the Flyer structure to the vector.
		f.push_back( fPtr );
	}

	// Create a new config object with the data structure.
	// Pass the vector using call by reference.
	BoidsConfig config( f );

	// Create an MFC file dialog.
	CFileDialog fileDialog( FALSE, NULL, NULL, NULL,
						"Configuration Files (*.ini)|*.ini|" );

	// Activate the dialog.
	if ( fileDialog.DoModal( ) == IDCANCEL )
	{
		return;  // Abort if cancel is pressed.
	}

	// Extract the chosen filename.
	CString fileName = fileDialog.GetFileName( );

	// Append '.ini' to the end of the filename, if needed.
	if ( fileName.Right( 4 ) != ".ini" )
	{
		fileName += ".ini";
	}

	config.saveConfig( fileName );  // Save the configuration to disk.

	
	// Stop the rendering thread when done.
	threadEnabled = false;


	return;
}


// Message handler for the button that stops the simulation.
afx_msg void BoidsWin::OnStartStop( )
{
	static clock_t begin, end;

	// Toggle the start/stop button.
	if ( stopped )  // If the start button is pressed.
	{
		stopped = false;  // Unset the stopped flag.
		btnStop.SetWindowText( "Stop" );  // Toggle button text.
		end = clock( );  // End mesuring the stop time.
		stopTime += end - begin;  // Update the stop time.
	}
	else  // If the stop button is pressed.
	{
		stopped = true;  // Set the stopped flag.
		btnStop.SetWindowText( "Start" );  // Toggle button text.
		begin = clock( );  // Begin to measure the stop time.
		runTime = clock( ) - stopTime;  // Generate the time when stopped.
	}

	SetFocus( );  // Set the focus back to the main window.
}


// Menu driven command to exit the application.
afx_msg void BoidsWin::OnExit( )
{
	// Close the window and terminate the application.
	SendMessage( WM_CLOSE );
}


// Position the camera to give a birds eye view.
afx_msg void BoidsWin::OnCameraAbove( )
{
	// Remove the camera from a boid, if it is on one.
	if ( cameraOnBoid == true )
	{
		scene -> AddChild( camera );
		cameraOnBoid = false;
	}

	cameraView = CAM_ABOVE;
	positionCamera( );
}


// Attach the camera to the first boid in the vector.
afx_msg void BoidsWin::OnCameraBoid( )
{
	// First check to see that there is a boid operational.
	if ( numFlyers > 0 )
	{
		cameraView = CAM_BOID;
		positionCamera( );
	}
}


// Position the camera to face north.
afx_msg void BoidsWin::OnCameraNorth( )
{
	// Remove the camera from a boid, if it is on one.
	if ( cameraOnBoid == true )
	{
		scene -> AddChild( camera );
		cameraOnBoid = false;
	}

	cameraView = CAM_NORTH;
	positionCamera( );
}


// Position the camera to face east.
afx_msg void BoidsWin::OnCameraEast( )
{
	// Remove the camera from a boid, if it is on one.
	if ( cameraOnBoid == true )
	{
		scene -> AddChild( camera );
		cameraOnBoid = false;
	}

	cameraView = CAM_EAST;
	positionCamera( );
}


// Position the camera to face south.
afx_msg void BoidsWin::OnCameraSouth( )
{
	// Remove the camera from a boid, if it is on one.
	if ( cameraOnBoid == true )
	{
		scene -> AddChild( camera );
		cameraOnBoid = false;
	}

	cameraView = CAM_SOUTH;
	positionCamera( );
}


// Position the camera to face west.
afx_msg void BoidsWin::OnCameraWest( )
{
	// Remove the camera from a boid, if it is on one.
	if ( cameraOnBoid == true )
	{
		scene -> AddChild( camera );
		cameraOnBoid = false;
	}

	cameraView = CAM_WEST;
	positionCamera( );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCameraAbove( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( cameraView == CAM_ABOVE );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCameraBoid( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( cameraView == CAM_BOID );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCameraNorth( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( cameraView == CAM_NORTH );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCameraEast( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( cameraView == CAM_EAST );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCameraSouth( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( cameraView == CAM_SOUTH );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCameraWest( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( cameraView == CAM_WEST );
}


// Increase the position of the camera.
afx_msg void BoidsWin::OnIncCameraPos( )
{
	// Increase the position of the slider.
	int num = sliderCam.GetPos( );
	sliderCam.SetPos( num += POSITION_SLIDER_SPEED );

	// Call the Horizontal Scroll Bar update handler.
	OnHScroll( 3, num, (CScrollBar *)&sliderCam );
}


// Decrease the position of the camera.
afx_msg void BoidsWin::OnDecCameraPos( )
{
	// Decrease the position of the slider.
	int num = sliderCam.GetPos( );
	sliderCam.SetPos( num -= POSITION_SLIDER_SPEED );

	// Call the Horizontal Scroll Bar update handler.
	OnHScroll( 3, num, (CScrollBar *)&sliderCam );
}


// Increase the rotation of the camera.
afx_msg void BoidsWin::OnIncCameraRot( )
{
	// Increase the position of the slider by one unit.
	int num = sliderCam2.GetPos( );

	num += ROTATION_SLIDER_SPEED;

	// Make the slider smoothly wrap around.
	if ( num > sliderCam2.GetRangeMax( ) )
	{
		int overlap = num - sliderCam2.GetRangeMax( );
		num = sliderCam2.GetRangeMin( ) + overlap;
	}

	sliderCam2.SetPos( num );

	// Call the Horizontal Scroll Bar update handler.
	OnHScroll( 4, num, (CScrollBar *)&sliderCam2 );
}


// Decrease the rotation of the camera.
afx_msg void BoidsWin::OnDecCameraRot( )
{
	// Decrease the position of the slider by one unit.
	int num = sliderCam2.GetPos( );

	num -= ROTATION_SLIDER_SPEED;

	// Make the slider smoothly wrap around.
	if ( num < sliderCam2.GetRangeMin( ) )
	{
		int overlap = sliderCam2.GetRangeMin( ) - num;
		num = sliderCam2.GetRangeMax( ) - overlap;
	}

	sliderCam2.SetPos( num );

	// Call the Horizontal Scroll Bar update handler.
	OnHScroll( 4, num, (CScrollBar *)&sliderCam2 );
}


// Message handler for the button that centres the camera.
afx_msg void BoidsWin::OnCentre( )
{
	// Centre the camera angle slider.
	sliderCam2.SetPos( 180 );
	// Update the window's data member.
	cameraPosition2 = sliderCam2.GetPos( );
	// Update the camera.
	positionCamera( );

	SetFocus( );  // Set the focus back to the main window.
}


// Menu driven command to set the rendering style to wireframe.
afx_msg void BoidsWin::OnWireFrame( )
{
	renderStyle = D3DRMRENDER_WIREFRAME;
	device -> SetQuality( renderStyle );
}


// Menu driven command to set the rendering style to unlit flat.
afx_msg void BoidsWin::OnUnlitFlat( )
{
	renderStyle = D3DRMRENDER_UNLITFLAT;
	device -> SetQuality( renderStyle );
}


// Menu driven command to set the rendering style to flat shaded.
afx_msg void BoidsWin::OnFlat( )
{
	renderStyle = D3DRMRENDER_FLAT;
	device -> SetQuality( renderStyle );
}


// Menu driven command to set the rendering style to Gouraud.
afx_msg void BoidsWin::OnGouraud( )
{
	renderStyle = D3DRMRENDER_GOURAUD;
	device -> SetQuality( renderStyle );
}


// Add a flyer to the scene by interacting with the slider control.
afx_msg void BoidsWin::OnAddFlyer( )
{
	// Also move the slider to the correct position.
	requiredFlyers++;

	if ( requiredFlyers > MAXIMUM_NUM_FLYERS )
	{
		requiredFlyers = MAXIMUM_NUM_FLYERS;
	}

	sliderNum.SetPos( requiredFlyers );
}


// Remove a flyer from the scene by interacting with the slider control.
afx_msg void BoidsWin::OnRemoveFlyer( )
{
	if ( requiredFlyers > 0 )
	{
		requiredFlyers--;
	}
}


// Increase the size of the flyers.
afx_msg void BoidsWin::OnIncFlyerSize( )
{
	// Increase the position of the slider.
	int num = sliderSize.GetPos( );
	sliderSize.SetPos( num += FLYER_SIZE_SLIDER_SPEED );

	// Call the Horizontal Scroll Bar update handler.
	OnHScroll( 2, num, (CScrollBar *)&sliderSize );
}


// Decrease the size of the flyers.
afx_msg void BoidsWin::OnDecFlyerSize( )
{
	// Decrease the position of the slider.
	int num = sliderSize.GetPos( );
	sliderSize.SetPos( num -= FLYER_SIZE_SLIDER_SPEED );

	// Call the Horizontal Scroll Bar update handler.
	OnHScroll( 2, num, (CScrollBar *)&sliderSize );
}


// Menu driven command to change boids to tetrahedrons.
afx_msg void BoidsWin::OnTetra( )
{
	// Abort change if mesh is already in use.
	if ( flyerMesh == IDR_MESH_TETRA )
	{
		return;
	}


	// Set the window's data member.
	flyerMesh = IDR_MESH_TETRA;

	// Set the mesh counter back to zero.
	flyerMeshesChanged = 0;
}


// Menu driven command to change boids to small birds.
afx_msg void BoidsWin::OnBird( )
{
	// Abort change if mesh is already in use.
	if ( flyerMesh == IDR_MESH_BIRD )
	{
		return;
	}


	// Set the window's data member.
	flyerMesh = IDR_MESH_BIRD;

	// Set the mesh counter back to zero.
	flyerMeshesChanged = 0;
}


// Menu driven command to change boids to animated birds.
afx_msg void BoidsWin::OnAnimBird( )
{
	// Abort change if mesh is already in use.
	if ( flyerMesh == IDR_MESH_BIRDBODY )
	{
		return;
	}


	// Set the window's data member.
	flyerMesh = IDR_MESH_BIRDBODY;

	// Set the mesh counter back to zero.
	flyerMeshesChanged = 0;
}


// Menu driven command to change the colour of the flyers.
afx_msg void BoidsWin::OnFlyerWhite( )
{
	flyerColour = RGB_WHITE;  // Set the main window's data member.

	for ( int index = 0; index < numFlyers; index++ )
	{
		flyers[ index ] -> setColour( flyerColour );
	}
}


// Menu driven command to change the colour of the flyers.
afx_msg void BoidsWin::OnFlyerYellow( )
{
	flyerColour = RGB_YELLOW;  // Set the main window's data member.

	for ( int index = 0; index < numFlyers; index++ )
	{
		flyers[ index ] -> setColour( flyerColour );
	}
}


// Menu driven command to change the colour of the flyers.
afx_msg void BoidsWin::OnFlyerPink( )
{
	flyerColour = RGB_PINK;  // Set the main window's data member.

	for ( int index = 0; index < numFlyers; index++ )
	{
		flyers[ index ] -> setColour( flyerColour );
	}
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateWireframe( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( renderStyle == D3DRMRENDER_WIREFRAME );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateUnlitFlat( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( renderStyle == D3DRMRENDER_UNLITFLAT );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateFlat( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( renderStyle == D3DRMRENDER_FLAT );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateGouraud( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( renderStyle == D3DRMRENDER_GOURAUD );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateTetra( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flyerMesh == IDR_MESH_TETRA );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateBird( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flyerMesh == IDR_MESH_BIRD );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateAnimBird( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flyerMesh == IDR_MESH_BIRDBODY );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateFlyerWhite( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flyerColour == RGB_WHITE );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateFlyerYellow( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flyerColour == RGB_YELLOW );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateFlyerPink( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flyerColour == RGB_PINK );
}


// Menu driven command to deactivate the landscape.
afx_msg void BoidsWin::OnLandNone( )
{
	landscape.renderNone( );
}


// Menu driven command to render the landscape in a wireframe style.
afx_msg void BoidsWin::OnLandWireframe( )
{
	landscape.toggleWireframe( );
}


// Menu driven command to render the landscape in a flat unlit style.
afx_msg void BoidsWin::OnLandUnlitFlat( )
{
	landscape.toggleUnlitFlat( );
}


// Menu driven command to render the landscape in a flat shaded style.
afx_msg void BoidsWin::OnLandFlat( )
{
	landscape.toggleFlat( );
}


// Menu driven command to render the landscape in a Gouraud style.
afx_msg void BoidsWin::OnLandGouraud( )
{
	landscape.toggleGouraud( );
}


// Menu driven command to set the solid fill colour of the land to green.
afx_msg void BoidsWin::OnLandSolidGreen( )
{
	landscape.setSolidColour( LSC_GREEN );
}


// Menu driven command to set the solid fill colour of the land to checkered.
afx_msg void BoidsWin::OnLandSolidCheckered( )
{
	landscape.setSolidColour( LSC_CHECKERED );
}


// Menu driven command to recalculate the altitudes of the landscape's matrix.
afx_msg void BoidsWin::OnLandRecalculate( )
{
	landscape.recalculate( );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandNone( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getExists( ) == false );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandWireFrame( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getWireframeOn( ) );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandUnlitFlat( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getSolidStyle( ) ==
					D3DRMRENDER_UNLITFLAT && landscape.getSolidOn( ) );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandFlat( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getSolidStyle( ) ==
						D3DRMRENDER_FLAT && landscape.getSolidOn( ) );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandGouraud( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getSolidStyle( ) ==
					D3DRMRENDER_GOURAUD && landscape.getSolidOn( ) );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandSolidGreen( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getSolidColour( ) ==
							LSC_GREEN && landscape.getSolidOn( ) );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateLandSolidCheckered( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( landscape.getSolidColour( ) ==
							LSC_CHECKERED && landscape.getSolidOn( ) );
}


// Toggle the menu driven flock forming behaviour flag.
afx_msg void BoidsWin::OnFlockForming( )
{
	if ( flockFormingActive == false )
	{
		flockFormingActive = true;
	}
	else
	{
		flockFormingActive = false;
	}
}


// Toggle the menu driven velocity matching behaviour flag.
afx_msg void BoidsWin::OnVelocityMatching( )
{
	if ( velocityMatchingActive == false )
	{
		velocityMatchingActive = true;
	}
	else
	{
		velocityMatchingActive = false;
	}
}


// Toggle the menu driven collision avoidance behaviour flag.
afx_msg void BoidsWin::OnCollisionAvoidance( )
{
	if ( collisionAvoidanceActive == false )
	{
		collisionAvoidanceActive = true;
	}
	else
	{
		collisionAvoidanceActive = false;
	}
}


// Bring up the Flyer Attributes dialog.
afx_msg void BoidsWin::OnFlyerAttributes( )
{
	// Abort the command if currently in full screen mode.
	if ( fullScreenMode )
	{
		return;
	}


	// Set the multitasking flag.
	appIdle = false;

	// Restart the rendering thread if stopped.
	threadEnabled = true;

	if ( threadFinished == true )
	{
		threadFinished = false;
		ptrD3DThread = AfxBeginThread( d3dThread, this,
											THREAD_PRIORITY_NORMAL );
	}


	// Create the dialog box.
	BoidsDialogAttr dialogBox( "IDD_ATTRIBUTES_DIALOG", this );

	dialogBox.DoModal( );  // Make the dialog box appear.


	// Stop the rendering thread when done.
	threadEnabled = false;
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateFlockForming( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( flockFormingActive );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateVelocityMatching( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( velocityMatchingActive );
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateCollisionAvoidance( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( collisionAvoidanceActive );
}


// Switch between FS mode and Windowed mode.
void BoidsWin::OnSwitchFSMode( )
{
	// If in full screen mode, return to windowed mode.
	if ( fullScreenMode )
	{
		windowedMode( );
	}
	else  // If in windowed mode, switch to full screen mode.
	{
		OnFullScreen( );
	}
}


// Bring up the dialog box for selecting the full screen mode resolution.
afx_msg void BoidsWin::OnSelectMode( )
{
	// Abort the command if currently in full screen mode.
	if ( fullScreenMode )
	{
		return;
	}


	// Set the multitasking flag.
	appIdle = false;

	// Restart the rendering thread if stopped.
	threadEnabled = true;

	if ( threadFinished == true )
	{
		threadFinished = false;
		ptrD3DThread = AfxBeginThread( d3dThread, this,
										THREAD_PRIORITY_NORMAL );
	}


	// Create the dialog box.
	BoidsDialogDisp dialogBox( "IDD_DISPLAYMODE_DIALOG", this );

	dialogBox.DoModal( );  // Make the dialog box appear.


	// Stop the rendering thread when done.
	threadEnabled = false;
}


// Set the windowed mode screen size to 640 x 480.
afx_msg void BoidsWin::OnWin640_480( )
{
	// Abort the command if currently in full screen mode.
	if ( fullScreenMode )
	{
		return;
	}

	restore( );  // Restore the window if maximised.

	// Create the size.
	CRect windowSize( WINDOW_LEFT_POSITION, WINDOW_TOP_POSITION,
					WINDOW_LEFT_POSITION + 640, WINDOW_TOP_POSITION + 480 );

	// Move the window to the new size.
	MoveWindow( &windowSize, true );
}


// Set the windowed mode screen size to 800 x 600.
afx_msg void BoidsWin::OnWin800_600( )
{
	// Abort the command if currently in full screen mode.
	if ( fullScreenMode )
	{
		return;
	}

	restore( );  // Restore the window if maximised.

	// Create the size.
	CRect windowSize( WINDOW_LEFT_POSITION, WINDOW_TOP_POSITION,
					WINDOW_LEFT_POSITION + 800, WINDOW_TOP_POSITION + 600 );

	// Move the window to the new size.
	MoveWindow( &windowSize, true );
}


// Set the windowed mode screen size to 1024 x 768.
afx_msg void BoidsWin::OnWin1024_768( )
{
	// Abort the command if currently in full screen mode.
	if ( fullScreenMode )
	{
		return;
	}

	restore( );  // Restore the window if maximised.

	// Create the size.
	CRect windowSize( WINDOW_LEFT_POSITION, WINDOW_TOP_POSITION,
					WINDOW_LEFT_POSITION + 1024, WINDOW_TOP_POSITION + 768 );

	// Move the window to the new size.
	MoveWindow( &windowSize, true );
}


// Toggle the control panel to show or hide itself.
afx_msg void BoidsWin::OnToggleControls( )
{
	// Only perform the change if in windowed mode.
	if ( fullScreenMode )
	{
		return;  // Abort the function.
	}


	// Abort if the rendering thread is still active.
	if ( threadFinished == false )
	{
		// Set the multitasking flags.
		threadEnabled = false;
		needToggleControls = true;

		return;
	}


	// Toggle the flags.
	if ( showControlPanel )
	{
		// Hide the control panel.
		showControlPanel = false;
	}
	else
	{
		// Show the control panel.
		showControlPanel = true;
	}

	// Call the worker function.
	showControls( showControlPanel );


	// Clear the flag when the operation has completed.
	needToggleControls = false;
}


// Update the checkmark on the window's menu item.
afx_msg void BoidsWin::OnUpdateToggleControls( CCmdUI *ptrCmdUI )
{
	ptrCmdUI -> SetCheck( showControlPanel );
}


// Display an about box for the window's help menu.
afx_msg void BoidsWin::OnAbout( )
{
	// Abort the command if currently in full screen mode.
	if ( fullScreenMode )
	{
		return;
	}


	// Set the multitasking flag.
	appIdle = false;

	// Restart the rendering thread if stopped.
	threadEnabled = true;

	if ( threadFinished == true )
	{
		threadFinished = false;
		ptrD3DThread = AfxBeginThread( d3dThread, this,
									THREAD_PRIORITY_NORMAL );
	}


	// Message box giving details about the application.
	// Generate the text string.
	CString text = "3D Boids v";
	text += VERSION;
	text += "\n";
	text += RELEASE_DATE;
	text += "\n\nBy Robert Platt\n";
	text += "http://www.navgen.com/\n\n";
	text += "BSc(Hons) Software Engineering Project\n";
	text += "University of Westminster, London, England";

	// Display the message box.
	MessageBox( text, "3D Boids", MB_OK );


	// Stop the rendering thread when done.
	threadEnabled = false;
}
