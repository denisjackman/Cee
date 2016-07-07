/*	Filename:		BoidsWin.cpp
	Author:			Robert Platt
	Creation date:	15/06/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids main window class.
*/


#include "BoidsWin.h"


// Windows message map.
BEGIN_MESSAGE_MAP( BoidsWin, CFrameWnd )
	ON_WM_CREATE( )
	ON_WM_PAINT( )
	ON_WM_HSCROLL( )
	ON_BN_CLICKED( 1, OnCentre )
	ON_BN_CLICKED( 2, OnStartStop )
	ON_WM_NCLBUTTONDOWN( )
	ON_WM_NCRBUTTONDOWN( )
	ON_WM_SIZE( )
	ON_WM_CLOSE( )
	ON_WM_DESTROY( )


	// Window's Menu Items.
	// Found in 'BoidsWinMenu.cpp'.
	ON_COMMAND( IDM_LOAD, OnLoad )
	ON_COMMAND( IDM_SAVE, OnSave )
	ON_COMMAND( IDM_START_STOP, OnStartStop )
	ON_COMMAND( IDM_EXIT, OnExit )

	ON_COMMAND( IDM_CAMERA_ABOVE, OnCameraAbove )
	ON_COMMAND( IDM_CAMERA_BOID, OnCameraBoid )
	ON_COMMAND( IDM_CAMERA_NORTH, OnCameraNorth )
	ON_COMMAND( IDM_CAMERA_EAST, OnCameraEast )
	ON_COMMAND( IDM_CAMERA_SOUTH, OnCameraSouth )
	ON_COMMAND( IDM_CAMERA_WEST, OnCameraWest )
	ON_UPDATE_COMMAND_UI( IDM_CAMERA_ABOVE, OnUpdateCameraAbove )
	ON_UPDATE_COMMAND_UI( IDM_CAMERA_BOID, OnUpdateCameraBoid )
	ON_UPDATE_COMMAND_UI( IDM_CAMERA_NORTH, OnUpdateCameraNorth )
	ON_UPDATE_COMMAND_UI( IDM_CAMERA_EAST, OnUpdateCameraEast )
	ON_UPDATE_COMMAND_UI( IDM_CAMERA_SOUTH, OnUpdateCameraSouth )
	ON_UPDATE_COMMAND_UI( IDM_CAMERA_WEST, OnUpdateCameraWest )

	ON_COMMAND( IDM_CAMERA_UP, OnIncCameraPos )
	ON_COMMAND( IDM_CAMERA_DOWN, OnDecCameraPos )
	ON_COMMAND( IDM_CAMERA_RIGHT, OnIncCameraRot )
	ON_COMMAND( IDM_CAMERA_LEFT, OnDecCameraRot )
	ON_COMMAND( IDM_CAMERA_CENTRE, OnCentre )

	ON_COMMAND( IDM_WIREFRAME, OnWireFrame )
	ON_COMMAND( IDM_UNLITFLAT, OnUnlitFlat )
	ON_COMMAND( IDM_FLAT, OnFlat )
	ON_COMMAND( IDM_GOURAUD, OnGouraud )
	ON_COMMAND( IDM_ADD_FLYER, OnAddFlyer )
	ON_COMMAND( IDM_REMOVE_FLYER, OnRemoveFlyer )
	ON_COMMAND( IDM_INC_FLYER_SIZE, OnIncFlyerSize )
	ON_COMMAND( IDM_DEC_FLYER_SIZE, OnDecFlyerSize )
	ON_COMMAND( IDM_TETRA, OnTetra )
	ON_COMMAND( IDM_SMALL_BIRD, OnBird )
	ON_COMMAND( IDM_ANIM_BIRD, OnAnimBird )
	ON_COMMAND( IDM_FLYER_WHITE, OnFlyerWhite )
	ON_COMMAND( IDM_FLYER_YELLOW, OnFlyerYellow )
	ON_COMMAND( IDM_FLYER_PINK, OnFlyerPink )
	ON_UPDATE_COMMAND_UI( IDM_WIREFRAME, OnUpdateWireframe )
	ON_UPDATE_COMMAND_UI( IDM_UNLITFLAT, OnUpdateUnlitFlat )
	ON_UPDATE_COMMAND_UI( IDM_FLAT, OnUpdateFlat )
	ON_UPDATE_COMMAND_UI( IDM_GOURAUD, OnUpdateGouraud )
	ON_UPDATE_COMMAND_UI( IDM_TETRA, OnUpdateTetra )
	ON_UPDATE_COMMAND_UI( IDM_SMALL_BIRD, OnUpdateBird )
	ON_UPDATE_COMMAND_UI( IDM_ANIM_BIRD, OnUpdateAnimBird )
	ON_UPDATE_COMMAND_UI( IDM_FLYER_WHITE, OnUpdateFlyerWhite )
	ON_UPDATE_COMMAND_UI( IDM_FLYER_YELLOW, OnUpdateFlyerYellow )
	ON_UPDATE_COMMAND_UI( IDM_FLYER_PINK, OnUpdateFlyerPink )

	ON_COMMAND( IDM_LAND_NONE, OnLandNone )
	ON_COMMAND( IDM_LAND_WIREFRAME, OnLandWireframe )
	ON_COMMAND( IDM_LAND_UNLITFLAT, OnLandUnlitFlat )
	ON_COMMAND( IDM_LAND_FLAT, OnLandFlat )
	ON_COMMAND( IDM_LAND_GOURAUD, OnLandGouraud )
	ON_COMMAND( IDM_SOLID_COLOUR_GREEN, OnLandSolidGreen )
	ON_COMMAND( IDM_SOLID_COLOUR_CHECKERED, OnLandSolidCheckered )
	ON_COMMAND( IDM_LAND_RECALCULATE, OnLandRecalculate )
	ON_UPDATE_COMMAND_UI( IDM_LAND_NONE, OnUpdateLandNone )
	ON_UPDATE_COMMAND_UI( IDM_LAND_WIREFRAME, OnUpdateLandWireFrame )
	ON_UPDATE_COMMAND_UI( IDM_LAND_UNLITFLAT, OnUpdateLandUnlitFlat )
	ON_UPDATE_COMMAND_UI( IDM_LAND_FLAT, OnUpdateLandFlat )
	ON_UPDATE_COMMAND_UI( IDM_LAND_GOURAUD, OnUpdateLandGouraud )
	ON_UPDATE_COMMAND_UI( IDM_SOLID_COLOUR_GREEN, OnUpdateLandSolidGreen )
	ON_UPDATE_COMMAND_UI( IDM_SOLID_COLOUR_CHECKERED,
									OnUpdateLandSolidCheckered )

	ON_COMMAND( IDM_FLOCKFORMING, OnFlockForming )
	ON_COMMAND( IDM_VELOCITYMATCHING, OnVelocityMatching )
	ON_COMMAND( IDM_COLLISIONAVOIDANCE, OnCollisionAvoidance )
	ON_COMMAND( IDM_FLYER_ATTRIBUTES, OnFlyerAttributes )
	ON_UPDATE_COMMAND_UI( IDM_FLOCKFORMING, OnUpdateFlockForming )
	ON_UPDATE_COMMAND_UI( IDM_VELOCITYMATCHING, OnUpdateVelocityMatching )
	ON_UPDATE_COMMAND_UI( IDM_COLLISIONAVOIDANCE, OnUpdateCollisionAvoidance )

	ON_COMMAND( IDM_SWITCH_FS_MODE, OnSwitchFSMode )
	ON_COMMAND( IDM_SELECT_MODE, OnSelectMode )
	ON_COMMAND( IDM_WIN_640_480, OnWin640_480 )
	ON_COMMAND( IDM_WIN_800_600, OnWin800_600 )
	ON_COMMAND( IDM_WIN_1024_768, OnWin1024_768 )
	ON_COMMAND( IDM_TOGGLE_CONTROL_PANEL, OnToggleControls )
	ON_UPDATE_COMMAND_UI( IDM_TOGGLE_CONTROL_PANEL, OnUpdateToggleControls )

	ON_COMMAND( IDM_ABOUT, OnAbout )

	ON_COMMAND( IDK_ESC_KEY, OnEscKey )
END_MESSAGE_MAP( )


// Constructor for Window class.
BoidsWin::BoidsWin( )
{
	// Create the D3DRM interface.
	Direct3DRMCreate( &d3drm );

	// Initialise the D3D interface pointers as being initially unused.
	device = NULL;  
	scene = NULL;
	clipper = NULL;
	frontSurface = NULL;  // Used for full screen mode.
	zBuffer = NULL;
	directDraw = NULL;

	numFlyers = INITIAL_NUM_FLYERS;  // Various initialisations.
	requiredFlyers = numFlyers;
	renderStyle = DEFAULT_RENDER_STYLE;
	flyerMesh = DEFAULT_FLYER_MESH;
	flyerColour = RGB_WHITE;

	frameCount = 0;  // Reset the frame counter to start at zero.
	overloaded = false;  // The simulation is not overloaded to start with.

	flockFormingActive = true;  // Activate the behaviour flags.
	velocityMatchingActive = true;
	collisionAvoidanceActive = true;

	cameraView = CAM_ABOVE;  // Initialise the camera view.
	cameraOnBoid = false;


	threadEnabled = false;  // Initialise the multitasking flags.
	threadFinished = true;
	appIdle = false;
	needShutdown = false;
	needToggleControls = false;
	needFullScreen = false;


	fullScreenMode = FULLSCREEN_STARTUP;  // Windowed & Full Screen modes.
	showControlPanel = CONTROL_PANEL_ON_STARTUP;
	windowedModePos.length = 0;  // Used to indicate as being uninitialised.
	resolutionFS.widthPixels = FULLSCREEN_WIDTH;  // Set default FS mode.
	resolutionFS.heightPixels = FULLSCREEN_HEIGHT;
	resolutionFS.colourDepthBits = FULLSCREEN_COLOUR_DEPTH;

	stopped = false;
	runTime = 0;
	stopTime = 0;
	frameStartTime = clock( );


	// Flyer attributes dialog settings.
	accelerationRate = ACCELERATION_RATE;
	angleOfVision = ANGLE_OF_VISION;
	collisionDistance = COLLISION_DISTANCE;
	flockFormingDistance = FLOCK_FORMING_DISTANCE;
	flockingRadius = FLOCKING_RADIUS;
	maximumSpeed = MAXIMUM_SPEED;
	minimumSpeed = MINIMUM_SPEED;
	rangeOfFlockHeadings = RANGE_OF_FLOCK_HEADINGS;
	wingStrokesPerSecond = WING_STROKES_PER_SECOND;
}


// OnCreate is called after the window is created but before it is visible.
afx_msg void BoidsWin::OnCreate( )
{
	// Record the initial window size.
	GetClientRect( &prevWindowSize );

	DWORD visible = NULL;  // Flag for making the components visible.

	if ( showControlPanel )
	{
		visible = WS_VISIBLE;  // Set the flag to show the components.
	}

	// Set up the controls for the window.
	CRect position;
	GetClientRect( &position );
	position.left = position.right - CONTROL_PANEL_SIZE;

	// Create and draw the contols from the bottom up.
	// border5 to place some spacing in the controls.
	position.top = 400;
	border5.Create( "", WS_CHILD | visible | SS_CENTER, position, this, 12 );

	// btnStop CButton control as a push button to stop the simulation.
	position.top = 370;
	position.bottom = 400;
	btnStop.Create( "Stop", WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON |
												visible, position, this, 2 );

	// staticTime for the simulation time.
	position.top = 350;
	position.bottom = 370;
	staticTime.Create( "Time: ", WS_CHILD | visible | SS_CENTER,
													position, this, 11 );

	// staticFrames for the frames per second.
	position.top = 330;
	position.bottom = 350;
	staticFrames.Create( "Frames per Second: ", WS_CHILD | visible |
											SS_CENTER, position, this, 10 );

	// border4 to place some spacing in the controls.
	position.top = 310;
	position.bottom = 330;
	border4.Create( "", WS_CHILD | visible | SS_CENTER, position, this, 9 );

	// btnCentre CButton control as a push button to reset the camera angle.
	position.top = 280;
	position.bottom = 310;
	btnCentre.Create( "Centre Angle", WS_TABSTOP | WS_CHILD |
							BS_DEFPUSHBUTTON | visible, position, this, 1 );

	// sliderCam2 for the camera position.
	position.top = 250;
	position.bottom = 280;
	sliderCam2.Create( visible | TBS_ENABLESELRANGE, position, this, 4 );
	sliderCam2.SetRange( 0, 359 );
	sliderCam2.SetPos( 180 );

	// staticCam2 for the camera position.
	position.top = 230;
	position.bottom = 250;
	staticCam2.Create( "Camera Rotation", WS_CHILD | visible |
											SS_CENTER, position, this, 8 );

	// border3 to place some spacing in the controls.
	position.top = 210;
	position.bottom = 230;
	border3.Create( "", WS_CHILD | visible | SS_CENTER, position, this, 7 );

	// sliderCam for the camera position.
	position.top = 180;
	position.bottom = 210;
	sliderCam.Create( visible | TBS_ENABLESELRANGE, position, this, 3 );
	sliderCam.SetRange( 0, 1000 );
	sliderCam.SetPos( 0 );

	// staticCam for the camera position.
	position.top = 160;
	position.bottom = 180;
	staticCam.Create( "Camera Position", WS_CHILD | visible |
											SS_CENTER, position, this, 6 );

	// border2 to place some spacing in the controls.
	position.top = 140;
	position.bottom = 160;
	border2.Create( "", WS_CHILD | visible | SS_CENTER, position, this, 5 );

	// sliderSize for the size of the flyers.
	position.top = 110;
	position.bottom = 140;
	sliderSize.Create( visible | TBS_ENABLESELRANGE, position, this, 2 );
	/* NOTE: The size of the boid is calculated by dividing the slider position
	   by the scale factor.  Therefore to prevent the size from becoming zero
	   the minimum value of the range should be the scale factor.  Then the
	   size of the boid will always be >= 1. */
	sliderSize.SetRange( SIZE_SCALE_FACTOR, 200 );
	sliderSize.SetPos( INITIAL_SIZE_SLIDER_POSITION );

	// staticSize for the size of the flyers.
	position.top = 90;
	position.bottom = 110;
	staticSize.Create( "Flyer Size", WS_CHILD | visible |
											SS_CENTER, position, this, 4 );

	// border1 to place some spacing in the controls.
	position.top = 70;
	position.bottom = 90;
	border1.Create( "", WS_CHILD | visible | SS_CENTER, position, this, 3 );

	// sliderNum for the number of flyers.
	position.top = 40;
	position.bottom = 70;
	sliderNum.Create( visible | TBS_ENABLESELRANGE, position, this, 1 );
	sliderNum.SetRange( 0, MAXIMUM_NUM_FLYERS );
	sliderNum.SetPos( numFlyers );

	// staticNum for the number of Flyers.
	position.top = 20;
	position.bottom = 40;
	// Set the text of the static control to show the starting number.
	CString numberObjText( "Number of Flyers: " );
	char buffer[ 50 ]; // Temporary buffer for string conversion.
	numberObjText += _itoa( numFlyers, buffer, 10 );
	staticNum.Create( numberObjText, WS_CHILD | visible |
											SS_CENTER, position, this, 2 );

	// topBorder static control.
	position.top = 0;
	position.bottom = 20;
	topBorder.Create( "", WS_CHILD | visible | SS_CENTER, position, this, 1 );


	// Used for starting up the application in full screen mode.
	// To do this, just set the flag contants.
	if ( fullScreenMode == true )
	{
		// Disable the menu and the window's normal features.
		CMenu *mnu;
		mnu = GetMenu( );
		mnu -> DestroyMenu( );
		SetMenu( mnu );
		mnu -> Detach( );
		ModifyStyle( WS_OVERLAPPEDWINDOW, WS_POPUP, 0 );


		ShowCursor( false );  // Hide the mouse pointer.


		// Create the direct draw interface.
		DirectDrawCreate( 0, &directDraw, 0 );
		directDraw -> SetCooperativeLevel( GetSafeHwnd( ),
				DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
		directDraw -> SetDisplayMode( resolutionFS.widthPixels,
				resolutionFS.heightPixels, resolutionFS.colourDepthBits );

		createFSDevice( );
	}

	// NOTE: The windowed mode device is automatically called -
	// - by the window by virtue of the MFC 'OnPaint' function.
}


// Create the full screen direct draw device for Direct3D to display with.
void BoidsWin::createFSDevice( )
{
	// Hide the control panel if it is showing.
	if ( showControlPanel == true )
	{
		showControls( false );
	}


	// Release the previous surfaces if any.
	// The back buffer is attached to the front buffer here.
	if ( frontSurface )
	{
		frontSurface -> Release( );
		frontSurface = NULL;
	}

	if ( zBuffer )
	{
		zBuffer -> Release( );
		zBuffer = NULL;
	}


	// Create a front surface with a single back buffer.
	DDSURFACEDESC surfaceDesc;
	memset( &surfaceDesc, 0, sizeof( surfaceDesc ) );
	surfaceDesc.dwSize = sizeof( surfaceDesc );
	surfaceDesc.dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_CAPS;
	surfaceDesc.dwBackBufferCount = 1;
	surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
						DDSCAPS_3DDEVICE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	directDraw -> CreateSurface( &surfaceDesc, &frontSurface, 0 );


	// Get an interface to the back buffer surface.
	DDSCAPS capabilities;
	capabilities.dwCaps = DDSCAPS_BACKBUFFER;
	frontSurface -> GetAttachedSurface( &capabilities , &backSurface );


	// Create a Z buffer surface and attach it to the back surface.
	memset( &surfaceDesc, 0, sizeof( surfaceDesc ) );
	surfaceDesc.dwSize = sizeof( DDSURFACEDESC );
	surfaceDesc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT |
								DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;
	surfaceDesc.dwWidth = resolutionFS.widthPixels;
	surfaceDesc.dwHeight = resolutionFS.heightPixels;
	surfaceDesc.dwZBufferBitDepth = FULLSCREEN_ZBUFFER_DEPTH;
	surfaceDesc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;
	directDraw -> CreateSurface( &surfaceDesc, &zBuffer, 0 );
	backSurface -> AddAttachedSurface( zBuffer );


	// Create a D3DRM device and attach it to the back surface.
	d3drm -> CreateDeviceFromSurface( 0, directDraw, backSurface, &device );


	// If the scene is not constructed, set the device to -
	// - default render quality and create the scene.
	if ( !scene )
	{
		// Initial render style.
		device -> SetQuality( DEFAULT_RENDER_STYLE );
		createScene( );  // Set up all the simulation's graphics.
	}
	else
	{
		// The scene has already been created, -
		// - just reconfigure the device and viewport.
		device -> SetQuality( renderStyle );  // Restore the render style.

		// Create the viewport.
		d3drm -> CreateViewport( device, camera, 0, 0,
				device -> GetWidth( ), device -> GetHeight( ), &viewPort );

		// Set the range of vision, default is 100.
		viewPort -> SetBack( D3DVALUE( VIEWPORT_BACK_DISTANCE ) );
	}
}


// Render the next frame and perform a page flip when in full screen mode.
void BoidsWin::renderFullScreen( )
{
	// Restore the front surface if it has been lost.
	if ( frontSurface -> IsLost( ) == DDERR_SURFACELOST )
	{
		frontSurface -> Restore( );
	}

	// Paint the next frame onto to back buffer with the D3DRM device.
	scene -> Move( D3DVALUE( 1.0 ) );
	viewPort -> Clear( );
	viewPort -> Render( scene );
	viewPort -> ForceUpdate( 0, 0, resolutionFS.widthPixels - 1,
											resolutionFS.heightPixels - 1 );
	device -> Update( );

	// Perform a page flip.
	frontSurface -> Flip( 0, DDFLIP_WAIT );
}


// Create the windowed direct draw device for Direct3D to display with.
void BoidsWin::createWinDevice( )
{
	// Create the Direct Draw clipper
	DirectDrawCreateClipper( 0, &clipper, NULL );
	clipper -> SetHWnd( 0, m_hWnd );


	// Create the D3DRM drawing device.
	CRect size;
	GetClientRect( &size );

	if ( showControlPanel )  // Make space for the control panel.
	{
		size.right -= CONTROL_PANEL_SIZE;
	}

	d3drm -> CreateDeviceFromClipper( clipper, NULL,
							size.right, size.bottom, &device );


	// If the scene is not constructed, set the device to -
	// - the default render style and then create the scene.
	if ( scene == NULL )
	{
		// Set the initial render style.
		device -> SetQuality( DEFAULT_RENDER_STYLE );

		// IMPORTANT STEP: Set up all the simulation's graphics.
		createScene( );
	}
	else
	{
		// The scene has already been created, -
		// - just reconfigure the device and viewport.
		device -> SetQuality( renderStyle );  // Restore the render style.
		// Create the viewport.
		d3drm -> CreateViewport( device, camera, 0, 0,
				device -> GetWidth( ), device -> GetHeight( ), &viewPort );
		// Set the range of vision, default is 100.
		viewPort -> SetBack( D3DVALUE( VIEWPORT_BACK_DISTANCE ) );
	}
}


// Maintain the scene before rendering the next frame.
void BoidsWin::maintainScene( )
{
	// Abort if the rendering thread is still active.
	if ( threadFinished == false )
	{
		return;
	}


	// Gradually change the meshes over frame by frame.
	// This prevents the system from being locked up.
	if ( flyerMeshesChanged < numFlyers )
	{
		// Set the mesh.
		flyers[ flyerMeshesChanged ] -> updateMesh( );
		// Size the mesh according to the size slider.
		double posSize = ( sliderSize.GetPos() * SIZE_SCALE_FACTOR );
		flyers[ flyerMeshesChanged++ ] -> setSize( posSize );
	}


	// If any extra flyers are required add one to the scene.
	if ( numFlyers < requiredFlyers && !overloaded )
	{
		// Wait for the correct frame delay before adding.
		if ( frameCount % ADD_BOID_FRAME_DELAY == 0 )
		{
			createFlyers( 1 );  // Add a flyer.
			updateAddFlyers( );
		}
	}


	// If the application is overloaded, remove some flyers.
	if ( overloaded && numFlyers > 1 )
	{
		requiredFlyers = numFlyers * 0.75;
		overloaded = false;
		updateRemoveFlyers( );
	}


	// If less flyers are required remove the right amount.
	if ( numFlyers > requiredFlyers )
	{
		int amount = numFlyers - requiredFlyers;
		removeFlyers( amount );  // Remove the surplus amount.
		updateRemoveFlyers( );
	}
}


// Set up the necessary requirements to start the simulation.
void BoidsWin::createScene( )
{
	// Create the root frame for the scene.
	d3drm -> CreateFrame( NULL, &scene );


	srand( time( 0 ) );  // Initialise random number generation.
	int randomX, randomY, randomZ;
	int speed, hHeading, vHeading;


	// Create the flyers at random positions and velocities.
	BoidsFlyer *newObjPtr;
	for ( int number = 0; number < numFlyers; number++ )
	{
		newObjPtr = new BoidsFlyer( );
		flyers.push_back( newObjPtr );
		flyers[ number ] -> build( this, d3drm, scene );
		randomX = ( ( 1 + rand( ) % (int)( X_LIMIT * 2 ) ) - X_LIMIT );
		randomY = ( ( 1 + rand( ) %	10 ) - 5 );
		randomZ = ( ( 1 + rand( ) % (int)( Z_LIMIT * 2 ) ) - Z_LIMIT );
		speed = ( ( 1 + rand( ) % (int)( maximumSpeed -
										minimumSpeed ) ) + minimumSpeed );
		hHeading = ( ( 1 + rand( ) % 360 ) - 180 );
		vHeading = ( ( 1 + rand( ) % 10 ) - 5 );
		flyers[ number ] -> setPosition( randomX, randomY, randomZ );
		flyers[ number ] -> setReqVelocity( speed, hHeading, vHeading );
	}


	// All the flyers meshes are set to the right type to start with.
	flyerMeshesChanged = numFlyers;


	// Set all the object's sizes to the position of the size slider.
	for ( int index = 0; index < numFlyers; index++ )
	{
		double posSize = ( sliderSize.GetPos() * SIZE_SCALE_FACTOR );
		flyers[ index ] ->	setSize( posSize );
	}


	// Create the directional lighting.
	LPDIRECT3DRMLIGHT light;
	d3drm -> CreateLightRGB( D3DRMLIGHT_DIRECTIONAL,
			D3DVALUE( 1.0 ), D3DVALUE( 1.0 ), D3DVALUE( 1.0 ), &light );

	// Create a frame for the lighting.
	LPDIRECT3DRMFRAME lightFrame;
	d3drm -> CreateFrame( scene, &lightFrame );
	lightFrame -> AddLight( light );
	lightFrame -> SetOrientation( scene, 
			D3DVALUE( 0 ), D3DVALUE( -1 ), D3DVALUE( 1 ),
			D3DVALUE( 0 ), D3DVALUE( 1 ), D3DVALUE( 1 ) );
	light -> Release( );
	light = NULL;
	lightFrame -> Release( );
	lightFrame = NULL;

	// Create some white ambient lighting and add it to the scene.
	d3drm -> CreateLightRGB( D3DRMLIGHT_AMBIENT,
			D3DVALUE( 0.4 ), D3DVALUE( 0.4 ), D3DVALUE( 0.4 ), &light );
	scene -> AddLight( light );
	light -> Release( );
	light = NULL;


	// Create a viewport frame for the viewport called camera.
	d3drm -> CreateFrame( scene, &camera );
	// Set the camera's position with reference to the sliderCam control.
	cameraPosition = sliderCam.GetPos();
	cameraPosition2 = sliderCam2.GetPos();
	positionCamera( );


	// Create the viewport and attach it to the frame called camera.
	d3drm -> CreateViewport( device, camera, 0, 0, device -> GetWidth( ),
										device -> GetHeight( ), &viewPort );
	// Set the range of vision, default is 100.
	viewPort -> SetBack( D3DVALUE( VIEWPORT_BACK_DISTANCE ) );


	// Set the background colour to a light blue (sky colour).
	scene -> SetSceneBackground( RGB_BACKGROUND );

	// Create the landscape.
	landscape.build( this, d3drm, scene, DEFAULT_LANDSCAPE_SOLID_STYLE );
}


// Window's event hander to repaint the window.
afx_msg void BoidsWin::OnPaint( )
{
	// Create the device if not yet present.
	if ( device == NULL )
	{
		createWinDevice( );
	}


	// Use the D3DRMWinDevice interface to repaint the window.
	LPDIRECT3DRMWINDEVICE windev;
	PAINTSTRUCT ps;
	BeginPaint( &ps );
		device -> QueryInterface( IID_IDirect3DRMWinDevice, (void**)&windev );
		windev -> HandlePaint( ps.hdc );
		windev -> Release( );
	EndPaint( &ps );
}


// Resize the main application's window.
void BoidsWin::reSizeD3D( )
{
	// Abort if the rendering thread is still active.
	if ( threadFinished == false )
	{
		return;
	}


	// Reposition the window's controls.
	// Work from the bottom of the window upwards.
	CRect position;
	GetClientRect( &position );
	position.left = position.right - CONTROL_PANEL_SIZE;

	// border5 to place some spacing in the controls.
	position.top = 400;
	border5.MoveWindow( position );

	// btnStop CButton control as a push button to stop the simulation.
	position.top = 370;
	position.bottom = 400;
	btnStop.MoveWindow( position );

	// staticTime for the simulation time.
	position.top = 350;
	position.bottom = 370;
	staticTime.MoveWindow( position );

	// staticFrames for the frames per second.
	position.top = 330;
	position.bottom = 350;
	staticFrames.MoveWindow( position );

	// border4 to place some spacing in the controls.
	position.top = 310;
	position.bottom = 330;
	border4.MoveWindow( position );

	// btnCentre CButton control as a push button to reset the camera angle.
	position.top = 280;
	position.bottom = 310;
	btnCentre.MoveWindow( position );

	// sliderCam2 for the camera position.
	position.top = 250;
	position.bottom = 280;
	sliderCam2.MoveWindow( position );

	// staticCam2 for the camera position.
	position.top = 230;
	position.bottom = 250;
	staticCam2.MoveWindow( position );

	// border3 to place some spacing in the controls.
	position.top = 210;
	position.bottom = 230;
	border3.MoveWindow( position );

	// sliderCam for the camera position.
	position.top = 180;
	position.bottom = 210;
	sliderCam.MoveWindow( position );

	// staticCam for the camera position.
	position.top = 160;
	position.bottom = 180;
	staticCam.MoveWindow( position );

	// border2 to place some spacing in the controls.
	position.top = 140;
	position.bottom = 160;
	border2.MoveWindow( position );

	// sliderSize for the size of the flyers.
	position.top = 110;
	position.bottom = 140;
	sliderSize.MoveWindow( position );

	// staticSize for the size of the flyers.
	position.top = 90;
	position.bottom = 110;
	staticSize.MoveWindow( position );

	// border1 to place some spacing in the controls.
	position.top = 70;
	position.bottom = 90;
	border1.MoveWindow( position );

	// sliderNum for the number of flyers.
	position.top = 40;
	position.bottom = 70;
	sliderNum.MoveWindow( position );

	// staticNum for the number of flyers.
	position.top = 20;
	position.bottom = 40;
	staticNum.MoveWindow( position );

	// topBorder static control.
	position.top = 0;
	position.bottom = 20;
	topBorder.MoveWindow( position );


	// Abort if no device present.
	if ( !device )
	{
		return;
	}


	// Get new the dimensions of the window.
	CRect size;
	GetClientRect( &size );
	int width = size.right;
	if ( showControlPanel )
	{
		width -= CONTROL_PANEL_SIZE;
	}
	int height = size.bottom;


	// Destroy and recreate a new device if -
	// - provided with any client window area.
	if ( ( width > 0 ) && height )
	{
		// Retrieve the device characteristics before destroying it.
		D3DRMRENDERQUALITY old_quality = device -> GetQuality();
		viewPort -> Release( );  // Destroy the previous viewport.
		viewPort = NULL;
		device -> Release( );  // Destroy the previous device.
		device = NULL;

		// Recreate a new device & viewPort for the new window size.
		d3drm -> CreateDeviceFromClipper( clipper,
								NULL, width, height, &device );
		device -> SetQuality( old_quality );
		width = device -> GetWidth( );
		height = device -> GetHeight( );
		d3drm -> CreateViewport( device, camera, 0, 0,
										width, height, &viewPort );
		// Set the range of vision, default is 100.
		viewPort ->SetBack( D3DVALUE( VIEWPORT_BACK_DISTANCE ) );
	}

	// Update the window's data member when -
	// - the resize operation has completed.
	prevWindowSize = newWindowSize;
}


// Function to increase the number of boids active.
void BoidsWin::createFlyers( int amount )
{
	// Create all the new flyers.
	BoidsFlyer *newObjPtr;
	int randomX, randomY, randomZ;
	int speed, hHeading, vHeading;

	for ( int index = 0; index < amount; index++ )
	{
		newObjPtr = new BoidsFlyer( );  // Create a new flyer.
		flyers.push_back( newObjPtr );
		flyers[ numFlyers ] -> build( this, d3drm, scene );
		randomX = ( ( 1 + rand( ) % 900 ) - 450 );
		randomY = ( ( 1 + rand( ) % 100 ) - 50 );
		randomZ = ( ( 1 + rand( ) % 900 ) - 450 );
		speed = ( ( 1 + rand( ) % (int)( maximumSpeed - minimumSpeed ) )
															+ minimumSpeed );
		hHeading = ( ( 1 + rand( ) % 360 ) - 180 );
		vHeading = ( ( 1 + rand( ) % 10 ) - 5 );
		flyers[ numFlyers ] -> setPosition( randomX, randomY, randomZ );
		flyers[ numFlyers ] -> setReqVelocity( speed, hHeading, vHeading );
		numFlyers++;
	}
}


// Function to reduce the number of active flyers.
void BoidsWin::removeFlyers( int amount )
{
	// Remove the correct number of flyers.
	BoidsFlyer *oldObjPtr;

	for ( int index = 0; index < amount; index++ )
	{
		oldObjPtr = flyers[ numFlyers - 1 ];
		flyers.pop_back( );
		delete oldObjPtr;
		numFlyers--;
	}
}


// Set the appropriate position and orientation for the camera.
void BoidsWin::positionCamera( )
{
	if ( cameraView == CAM_ABOVE )
	{
		camera -> SetPosition( scene, D3DVALUE( 0 ),
				D3DVALUE( ( 2.3 * X_LIMIT ) - ( cameraPosition
							* X_LIMIT / 450.0 ) ), D3DVALUE( 0 ) );

		// Convert the angle of the camera rotation to a suitable vector.
		D3DVALUE xVector = D3DVALUE( sin( ( 180 -
								cameraPosition2 ) / 180.0 * PI ) );
		D3DVALUE zVector = D3DVALUE( cos( ( 180 -
								cameraPosition2 ) / 180.0 * PI ) );

		camera -> SetOrientation( scene, D3DVALUE( 0 ), D3DVALUE( -1 ),
									D3DVALUE( 0 ), D3DVALUE( -xVector ),
									D3DVALUE( 0 ), D3DVALUE( zVector ) );
	}

	if ( cameraView == CAM_BOID )
	{
		// Convert the angle of the camera rotation to a suitable position.
		// Subtract scale to reverse the scale.
		int positioning = 1001 - cameraPosition;
		// Add the size of the boid to the camera -
		// - distance, to prevent an internal view.
		D3DVALUE sizeSetting = ( sliderSize.GetPos() * SIZE_SCALE_FACTOR );
		positioning += sizeSetting * BOID_VIEW_CAMERA_DISTANCE_FACTOR;

		D3DVALUE xPos = positioning * D3DVALUE( sin( (
							cameraPosition2 - 180 ) / 180.0 * PI ) );
		D3DVALUE zPos = positioning * D3DVALUE( cos( (
							cameraPosition2 - 180 ) / 180.0 * PI ) );

		// Add the viewport to a boid.
		// This code is activated when the camera first moves to the boid.
		if ( cameraOnBoid == false )
		{
			camera -> SetPosition( scene, 0, 0, 0 );
			flyers[ 0 ] -> getFramePtr( ) -> AddChild( camera );
			cameraOnBoid = true;
		}
		camera -> SetPosition( flyers[ 0 ] ->
							getFramePtr( ), -xPos, 0, -zPos );
		camera -> SetOrientation( flyers[ 0 ] ->
							getFramePtr( ), xPos, 0, zPos, 0, 1, 0 );
	}

	// Process the north camera view.
	if ( cameraView == CAM_NORTH )
	{
		// Convert the angle of the camera rotation to a suitable position.
		D3DVALUE xPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( sin( ( cameraPosition2 - 180 ) / 180.0 * PI ) );
		D3DVALUE zPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( cos( ( cameraPosition2 - 180 ) / 180.0 * PI ) );

		// Set the camera position and orientation.
		camera -> SetPosition( scene, -xPos, CAMERA_HEIGHT, -zPos );
		camera -> SetOrientation( scene, xPos, 0, zPos, 0, 1, 0 );
	}

	// Process the east camera view.
	if ( cameraView == CAM_EAST )
	{
		// Convert the angle of the camera rotation to a suitable position.
		D3DVALUE xPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( cos( ( cameraPosition2 - 180 ) / 180.0 * PI ) );
		D3DVALUE zPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( sin( ( cameraPosition2 - 180 ) / 180.0 * PI ) );

		// Set the camera position and orientation.
		camera -> SetPosition( scene, -xPos, CAMERA_HEIGHT,	zPos );
		camera -> SetOrientation( scene, xPos, 0, -zPos, 0, 1, 0 );
	}

	// Process the south camera view.
	if ( cameraView == CAM_SOUTH )
	{
		// Convert the angle of the camera rotation to a suitable position.
		D3DVALUE xPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( sin( ( cameraPosition2 - 180 ) / 180.0 * PI ) );
		D3DVALUE zPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( cos( ( cameraPosition2 - 180 ) / 180.0 * PI ) );

		// Set the camera position and orientation.
		camera -> SetPosition( scene, xPos, CAMERA_HEIGHT, zPos );
		camera -> SetOrientation( scene, -xPos, 0, -zPos, 0, 1, 0 );
	}

	// Process the west camera view.
	if ( cameraView == CAM_WEST )
	{
		// Convert the angle of the camera rotation to a suitable position.
		D3DVALUE xPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( cos( ( cameraPosition2 - 180 ) / 180.0 * PI ) );
		D3DVALUE zPos = X_LIMIT * 4 / 1000 * ( 1001 - cameraPosition ) *
			D3DVALUE( sin( ( cameraPosition2 - 180 ) / 180.0 * PI ) );

		// Set the camera position and orientation.
		camera -> SetPosition( scene, xPos, CAMERA_HEIGHT, -zPos );
		camera -> SetOrientation( scene, -xPos, 0, zPos, 0, 1, 0 );
	}
}


// Member function to update the rest of the simulation, -
// - after adding a quantity of new flyers.
void BoidsWin::updateAddFlyers( )
{
	// Set the text of the static control to show the current number.
	CString numberObjText( "Number of Flyers: " );
	char buffer[ 50 ]; // Temporary buffer for string conversion.
	numberObjText += _itoa( numFlyers, buffer, 10 );
	staticNum.SetWindowText( numberObjText );

	// Set all the object's sizes to the position of the size slider.
	for ( int index = 0; index < numFlyers; index++ )
	{
		double posSize = ( sliderSize.GetPos() * SIZE_SCALE_FACTOR );
		flyers[ index ] ->	setSize( posSize );
	}
}


// Member function to update the rest of the simulation, -
// - after removing a quantity of flyers.
void BoidsWin::updateRemoveFlyers( )
{
	// Set the text of the static control to show the current number.
	CString numberObjText( "Number of Flyers: " );
	char buffer[ 50 ]; // Temporary buffer for string conversion.
	numberObjText += _itoa( numFlyers, buffer, 10 );
	staticNum.SetWindowText( numberObjText );

	// Check if the view from a boid has been invalidated.
	if ( numFlyers == 0 && cameraView == CAM_BOID )
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

	// Move the slider to the correct position.
	sliderNum.SetPos( numFlyers );
}


// Window's event handler to process the control panel's sliders.
afx_msg void BoidsWin::OnHScroll( UINT SBCode, UINT Pos, CScrollBar *SB )
{
	// Only update the correct slider.
	// Cast the pointer to the scroll bar -
	// - to a pointer to a void for the comparison.
	if ( static_cast< void * >( SB ) == &sliderNum )
	{
		// Process the slider for the number of flyers.
		// Adjust the number of flyers.
		requiredFlyers = sliderNum.GetPos();
	}

	// Process the slider for the object's size.
	if ( static_cast< void * >( SB ) == &sliderSize )
	{
		for ( int index = 0; index < numFlyers; index++ )
		{
			D3DVALUE posSize = ( sliderSize.GetPos() * SIZE_SCALE_FACTOR );
			flyers[ index ] ->	setSize( posSize );
		}

		// If the camera is pointing to the boid, update it's position.
		// This is to prevent an internal view of the boid.
		if ( cameraView == CAM_BOID )
		{
			positionCamera( );
		}
	}

	// Process the first slider for the position of the camera.
	if ( static_cast< void * >( SB ) == &sliderCam )
	{
		cameraPosition = sliderCam.GetPos( );
		positionCamera( );
	}

	// Process the second slider for the position of the camera.
	if ( static_cast< void * >( SB ) == &sliderCam2 )
	{
		cameraPosition2 = sliderCam2.GetPos( );
		positionCamera( );
	}

	SetFocus( );  // Set the focus back to the main window.
}


// Member function to start the simulation.
void BoidsWin::start( )
{
	if ( stopped )
	{
		OnStartStop( );  // Call the toggle function to start.
	}
}


// Member function to temporarily stop the simulation.
void BoidsWin::stop( )
{
	if ( !stopped )
	{
		OnStartStop( );  // Call the toggle function to stop.
	}
}


// Perform some maintenance tasks every second.
void BoidsWin::performEverySecond( )
{
	if ( fullScreenMode == false )
	{
		// Update the frame rate display every second.
		// Set the text of the static control to show the current frame rate.
		CString framesText( "Frames per Second: " );
		char buffer[ 50 ]; // Temporary buffer for string conversion.
		framesText += _itoa( frameCount, buffer, 10 );
		staticFrames.SetWindowText( framesText );

		// Force the refresh of the whole viewport,
		// to erase any unwanted junk.
		viewPort -> ForceUpdate( 0, 0, device -> GetWidth( ) - 1,
										  device -> GetHeight( ) - 1 );

		// Force the update the control panel's controls.
		sliderNum.Invalidate( true );
		sliderSize.Invalidate( true );
		sliderCam.Invalidate( true );
		sliderCam2.Invalidate( true );
		topBorder.Invalidate( true );
		border1.Invalidate( true );
		border2.Invalidate( true );
		border3.Invalidate( true );
		border4.Invalidate( true );
		border5.Invalidate( true );
		staticNum.Invalidate( true );
		staticSize.Invalidate( true );
		staticCam.Invalidate( true );
		staticCam2.Invalidate( true );
		staticFrames.Invalidate( true );
		staticTime.Invalidate( true );
		btnCentre.Invalidate( true );
		btnStop.Invalidate( true );
	}


	// Determine if the simulation is overloaded.
	if ( frameCount < MINIMUM_FRAME_RATE )
	{
		overloaded = true;  // Set the flag if true.
	}
	else
	{
		overloaded = false;  // Unset the flag if false.
	}


	// Reset the counter for the next second.
	frameCount = 0;  
	// Reset the start time for the next second period.
	frameStartTime = clock( );
}


// Start/continue the shutdown of the simulation.
afx_msg void BoidsWin::OnClose( )
{
	threadEnabled = false;  // Unset the flag, to stop the thread rendering.
	needShutdown = true;  // Set the flag to shutdown the application.

	// If the rendering thread has not finished then prospone the shutdown.
	if ( threadFinished == false )
	{
		return;
	}

	// Shutdown the application by calling the standard window's function.
	CFrameWnd::OnClose( );
}


// Shutdown the application gracefully.
afx_msg void BoidsWin::OnDestroy( )
{
	// Release all of the window's COM interfaces.
	// The order of the release of the interfaces is important.
	if ( scene )
	{
		scene -> Release( );
		scene = NULL;
	}

	if ( viewPort )
	{
		viewPort -> Release( );
		viewPort = NULL;
	}

	if ( device )
	{
		device -> Release( );
		device = NULL;
	}

	if ( directDraw )
	{
		directDraw -> FlipToGDISurface( );
		directDraw -> RestoreDisplayMode( );
		directDraw -> Release( );
		directDraw = NULL;
		frontSurface = NULL;
		backSurface = NULL;
		zBuffer = NULL;
	}

	if ( d3drm )
	{
		d3drm -> Release( );
		d3drm = NULL;
	}

	if ( clipper )
	{
		clipper -> Release( );
		clipper = NULL;
	}

	if ( camera )
	{
		camera -> Release( );
		camera = NULL;
	}
}


// Change the display mode to full screen FROM windowed mode.
afx_msg void BoidsWin::OnFullScreen( )
{
	// Abort if the rendering thread is still active.
	if ( threadFinished == false )
	{
		// Set the flag to retry the operation.
		needFullScreen = true;

		return;
	}


	// First stop the simulation.
	bool alreadyStopped = stopped;  // Make note of the start/stop state.
	stop( );

	// Make a record of the size and position of the window.
	GetWindowPlacement( &windowedModePos );


	// Release the relevant COM interfaces.
	if ( viewPort )
	{
		viewPort -> Release( );
		viewPort = NULL;
	}

	if ( device )
	{
		device -> Release( );
		device = NULL;
	}

	if ( clipper )
	{
		clipper -> Release( );
		clipper = NULL;
	}

	// Switch to FS mode.
	// Disable the menu and the window's normal features.
	CMenu *mnu;
	mnu = GetMenu( );
	mnu -> DestroyMenu( );
	SetMenu( mnu );
	mnu -> Detach( );
	ModifyStyle( WS_OVERLAPPEDWINDOW, WS_POPUP, 0 );

	ShowCursor( false );  // Hide the mouse pointer.

	// Create the direct draw interface.
	DirectDrawCreate( 0, &directDraw, 0 );

	directDraw -> SetCooperativeLevel( GetSafeHwnd( ),
				DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
	directDraw -> SetDisplayMode( resolutionFS.widthPixels,
					resolutionFS.heightPixels, resolutionFS.colourDepthBits );

	fullScreenMode = true;
	createFSDevice( );

	// Restore the start/stop state of the simulation.
	if ( !alreadyStopped )
	{
		start( );
	}


	// Set the flag to state that the operation has completed.
	needFullScreen = false;
}


// Change the display mode back to windowed mode from full screen mode.
void BoidsWin::windowedMode( )
{
	// Stop the simulation.
	bool alreadyStopped = stopped;  // Make note of the start/stop state.
	stop( );

	// Release the relevant COM interfaces.
	if ( directDraw )
	{
		directDraw -> SetCooperativeLevel( GetSafeHwnd( ), DDSCL_NORMAL );
		directDraw -> RestoreDisplayMode( );
		directDraw -> Release( );
		directDraw = NULL;
		frontSurface = NULL;
		backSurface = NULL;
		zBuffer = NULL;
	}

	if ( viewPort )
	{
		viewPort -> Release( );
		viewPort = NULL;
	}

	if ( device )
	{
		device -> Release( );
		device = NULL;
	}

	if ( clipper )
	{
		clipper -> Release( );
		clipper = NULL;
	}


	// Reposition the window.
	// Check if the structure has been properly filled.
	if ( windowedModePos.length != 0 )
	{
		// If valid use the structure.
		SetWindowPlacement( &windowedModePos );
	}
	// If not a valid structure, reposition the window using default values.
	else
	{
		MoveWindow( CRect( WINDOW_LEFT_POSITION, WINDOW_TOP_POSITION,
					WINDOW_RIGHT_POSITION, WINDOW_BOTTOM_POSITION ), true );
	}


	// Switch to windowed mode.
	// Enable the menu and the window's normal features.
	CMenu mnu;
	(&mnu) -> LoadMenu( "MFCMENU" );
	SetMenu( &mnu );
	mnu . Detach( );
	ModifyStyle( WS_POPUP, WS_OVERLAPPEDWINDOW, SWP_FRAMECHANGED );

	ShowCursor( true );  // Show the mouse pointer.

	createWinDevice( );
	fullScreenMode = false;

	// Show the control panel if it should be showing.
	if ( showControlPanel )
	{
		showControls( true );
	}

	// Repaint the sliders after Direct Draw FS by just giving them the focus.
	// This is so because a repaint just won't do the update sufficientley.
	sliderNum.SetFocus( );
	sliderSize.SetFocus( );
	sliderCam.SetFocus( );
	sliderCam2.SetFocus( );


	// Restore the start/stop state of the simulation.
	if ( !alreadyStopped )
	{
		start( );
	}
}


// Show or hide the control panel.
void BoidsWin::showControls( bool show )
{
	int nCmdShow;  // Used to hold the Window's command flags.

	if ( show )
	{
		// Show the control panel.
		nCmdShow = SW_SHOW;  // Command to show the component.
		reSizeD3D( );  // Resize D3D *BEFORE* drawing the controls.
	}
	else
	{
		// Hide the control panel.
		nCmdShow = SW_HIDE;  // Command to hide the component.
	}

	// Update the control panel's controls.
	sliderNum.ShowWindow( nCmdShow );
	sliderSize.ShowWindow( nCmdShow );
	sliderCam.ShowWindow( nCmdShow );
	sliderCam2.ShowWindow( nCmdShow );
	topBorder.ShowWindow( nCmdShow );
	border1.ShowWindow( nCmdShow );
	border2.ShowWindow( nCmdShow );
	border3.ShowWindow( nCmdShow );
	border4.ShowWindow( nCmdShow );
	border5.ShowWindow( nCmdShow );
	staticNum.ShowWindow( nCmdShow );
	staticSize.ShowWindow( nCmdShow );
	staticCam.ShowWindow( nCmdShow );
	staticCam2.ShowWindow( nCmdShow );
	staticFrames.ShowWindow( nCmdShow );
	staticTime.ShowWindow( nCmdShow );
	btnCentre.ShowWindow( nCmdShow );
	btnStop.ShowWindow( nCmdShow );

	if ( !show )
	{
		reSizeD3D( );  // Resize D3D *AFTER* hiding the controls.
	}
}


// Restore the window if maximised.
void BoidsWin::restore( )
{
	if ( IsZoomed( ) )
	{
		WINDOWPLACEMENT placement;
		GetWindowPlacement( &placement );
		placement.showCmd = SW_RESTORE;
		SetWindowPlacement( &placement );
	}
}


// Message handler to respond to the user pressing the <ESC> key.
afx_msg void BoidsWin::OnEscKey( )
{
	// If in full screen mode, return to windowed mode.
	if ( fullScreenMode )
	{
		windowedMode( );
	}
	else  // If in windowed mode, shutdown the application.
	{
		PostMessage( WM_CLOSE );
	}
}


// Member function to update the static timer comtrol.
void BoidsWin::updateTimer( )
{
	// Set the text of the static control to show the current time.
	// Update the runTime.
	clock_t time;  // Local variable used to hold the time.

	if ( stopped == false )
	{
		time = clock( ) - stopTime;
		runTime = time;
	}
	else  // The simulation is stopped so just display the current run time.
	{
		time = runTime;
	}

	CString timeText( "Time: " );
	char buffer[ 50 ];  // Temporary buffer for string conversion.
	long minutes = ( time / CLOCKS_PER_SEC ) / 60;
	long seconds = ( time / CLOCKS_PER_SEC ) % 60;
	long hundreds = ( time / ( CLOCKS_PER_SEC / 100 ) ) % 100;
	timeText += _ltoa( minutes, buffer, 10 );

	if ( seconds < 10 )
	{
		timeText += ".0";
	}
	else
	{
		timeText += ".";
	}
	timeText += _ltoa( seconds, buffer, 10 );

	if ( hundreds < 10 )
	{
		timeText += ".0";
	}
	else
	{
		timeText += ".";
	}

	timeText += _ltoa( hundreds, buffer, 10 );
	staticTime.SetWindowText( timeText );
}


// Overided windows function to execute when the left mouse -
// - button is pressed in the non client area.
afx_msg void BoidsWin::OnNcLButtonDown( UINT nHitTest, CPoint point )
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

	// Call the default windows function.
	CWnd::OnLButtonDown( nHitTest, point );
}


// Overided windows function to execute when the right mouse -
// - button is pressed in the non client area.
afx_msg void BoidsWin::OnNcRButtonDown( UINT nHitTest, CPoint point )
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

	// Call the default windows function.
	CWnd::OnRButtonDown( nHitTest, point );
}


// Function to stop the rendering thread if the window has been maximized.
afx_msg void BoidsWin::OnSize( UINT nType, int cx, int cy )
{
	// Stop the rendering thread if the window has been maximized.
	// This is needed to fix Window2000's high thread priorities.
	if ( nType == SIZE_MAXIMIZED )
	{
		threadEnabled = false;
	}
}
