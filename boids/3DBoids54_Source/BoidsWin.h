/*	Filename:		BoidsWin.h
	Author:			Robert Platt
	Creation date:	15/06/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids main window class.
*/


#include <afxcmn.h>
#include <vector>  // Also set the namespace for the vector.
#include "BoidsFlyer.h"
#include "BoidsDialogAttr.h"
#include "BoidsDialogDisp.h"


#ifndef BOIDS_WIN_H
#define BOIDS_WIN_H


using namespace std;  // Used for the STL Vector.


const char VERSION[] = "0.54";  // The version number.
const char RELEASE_DATE[] = "18th April 2000";


// The size of the simulation area is specified here.
const D3DVALUE X_LIMIT = 1200.0;
const D3DVALUE Y_LIMIT = 300.0;
const D3DVALUE Z_LIMIT = 1200.0;

const D3DRMRENDERQUALITY DEFAULT_RENDER_STYLE = D3DRMRENDER_WIREFRAME;
const D3DRMRENDERQUALITY DEFAULT_LANDSCAPE_SOLID_STYLE = D3DRMRENDER_FLAT;
const ULONG DEFAULT_FLYER_MESH = IDR_MESH_BIRD;

const int CONTROL_PANEL_SIZE = 200;
const int VIEWPORT_BACK_DISTANCE = 7000;
const int MAXIMUM_NUM_FLYERS = 100;
const int INITIAL_NUM_FLYERS = 10;
const int INITIAL_SIZE_SLIDER_POSITION = 24;
const int CAMERA_HEIGHT = 200;

const int FULLSCREEN_WIDTH = 640;  // Measured in pixels.
const int FULLSCREEN_HEIGHT = 480;
const int FULLSCREEN_COLOUR_DEPTH = 16;  // Measured in bits.
const int FULLSCREEN_ZBUFFER_DEPTH = 16;
const bool FULLSCREEN_STARTUP = false;
const bool CONTROL_PANEL_ON_STARTUP = true;

const int WINDOW_LEFT_POSITION = 120;  // Default window size & position.
const int WINDOW_TOP_POSITION = 120;   // Size is 640 x 480.
const int WINDOW_RIGHT_POSITION = 760;
const int WINDOW_BOTTOM_POSITION = 600;

const int FLYER_SIZE_SLIDER_SPEED = 5;
const int POSITION_SLIDER_SPEED = 25;
const int ROTATION_SLIDER_SPEED = 4;
const D3DVALUE SIZE_SCALE_FACTOR = 1.0;
const int BOID_VIEW_CAMERA_DISTANCE_FACTOR = 2;

const int MINIMUM_FRAME_RATE = 7;
const D3DVALUE MAXIMUM_TIMESPAN = D3DVALUE( 0.3 );
//const D3DVALUE MAXIMUM_TIMESPAN = D3DVALUE( 1.0 / MINIMUM_FRAME_RATE );
const int ADD_BOID_FRAME_DELAY = 1;  // Only add a new boid every X frames.


// Define some RGB colour constants.
const D3DCOLOR RGB_WHITE =      D3DRGB( 1.0,  1.0,  1.0 );   // White.
const D3DCOLOR RGB_YELLOW =     D3DRGB( 1.0,  1.0,  0.0 );   // Yellow.
const D3DCOLOR RGB_PINK =       D3DRGB( 1.0,  0.6,  1.0 );   // Pink.
const D3DCOLOR RGB_BACKGROUND = D3DRGB( 0.1,  0.5,  1.0 );   // Light Blue.
const D3DCOLOR RGB_BROWN =      D3DRGB( 0.65, 0.4,  0.2 );   // Brown.
const D3DCOLOR RGB_BLACK =      D3DRGB( 0.2,  0.2,  0.2 );   // Black.
const D3DCOLOR RGB_LAND_GREEN = D3DRGB( 0.0,  0.6,  0.0 );   // Land Green.




// Class BoidsWin is an extension of the MFC CFrameWnd class.
class BoidsWin : public CFrameWnd
{

public:

	///////////////////////////////////////////////////////////////////////////
	// Direct3D Window utility functions.
	///////////////////////////////////////////////////////////////////////////

	// The Constructor for the boids window class.
	BoidsWin( );
	// OnCreate is called after the window is created but before it is visible.
	afx_msg void OnCreate( );
	// Window's event hander to repaint the window.
	afx_msg void OnPaint( );
	// Window's event handler to process the control panel's sliders.
	afx_msg void OnHScroll( UINT SBCode, UINT Pos, CScrollBar *SB );
	// Perform some maintenance tasks every second.
	void performEverySecond( );
	// Start/continue the shutdown of the simulation.
	afx_msg void OnClose( );
	// Shutdown the application gracefully.
	afx_msg void OnDestroy( );
	// Message handler to respond to the user pressing the <ESC> key.
	afx_msg void OnEscKey( );
	// Create the windowed direct draw device for Direct3D to display with.
	void createWinDevice( );
	// Create the full screen direct draw device for Direct3D to display with.
	void createFSDevice( );
	// Render the next frame and perform a page flip when in full screen mode.
	void renderFullScreen( );
	// Resize the main application's window.
	void reSizeD3D( );
	// Change the display mode back to windowed mode from full screen mode.
	void windowedMode( );
	// Bring up the dialog box for selecting the full screen mode resolution.
	void OnSelectMode( );
	// Switch between FS mode and Windowed mode.
	void OnSwitchFSMode( );
	// Restore the window if maximised.
	void restore( );
	// Set the windowed mode screen size to 640 x 480.
	void OnWin640_480( );
	// Set the windowed mode screen size to 800 x 600.
	void OnWin800_600( );
	// Set the windowed mode screen size to 1024 x 768.
	void OnWin1024_768( );
	// Show or hide the control panel.
	void showControls( bool show );
	// Member function to update the static timer comtrol.
	void updateTimer( );
	// Overided windows function to execute when the left mouse -
	// - button is pressed in the non client area.
	afx_msg void OnNcLButtonDown( UINT nHitTest, CPoint point );
	// Overided windows function to execute when the right mouse -
	// - button is pressed in the non client area.
	afx_msg void OnNcRButtonDown( UINT nHitTest, CPoint point );
	// Function to stop the rendering thread if the window has been maximized.
	afx_msg void BoidsWin::OnSize( UINT nType, int cx, int cy );





	///////////////////////////////////////////////////////////////////////////
	// Simulation & Visualization utility functions.
	///////////////////////////////////////////////////////////////////////////

	void start( );  // Used with the OnStartStop menu method -
	void stop( );   // - to temporarily start or stop the simulation.

	// Set up the necessary requirements to start the simulation.
	void createScene( );
	// Function to increase the number of boids active.
	void createFlyers( int amount );
	// Function to reduce the number of active flyers.
	void removeFlyers( int amount );
	// Member function to update the rest of the simulation, -
	// - after adding a quantity of new flyers.
	void updateAddFlyers( );
	// Member function to update the rest of the simulation, -
	// - after removing a quantity of flyers.
	void updateRemoveFlyers( );
	// Maintain the scene before rendering the next frame.
	void maintainScene( );
	// Set the appropriate position and orientation for the camera.
	void positionCamera( );
	// Message handler for the button that centres the camera.
	afx_msg void OnCentre( );





	///////////////////////////////////////////////////////////////////////////
	// Get & Set member functions.
	///////////////////////////////////////////////////////////////////////////

	// Return the number of flyers currently active.
	int &getNumObjects( ) { return numFlyers; };
	// Return the state of the stopped flag.
	bool getStopped( ) { return stopped; };
	// Return whether the landscape is present or not.
	bool getLandExists( ) { return landscape.getExists( ); };
	// Return the shape of the flyer mesh.
	ULONG getFlyerMesh( ) { return flyerMesh; };
	// Return the colour of the flyers.
	D3DCOLOR getFlyerColour( ) { return flyerColour; };
	// Return whether the flock forming AI is activated or not.
	bool getFlockFormingActive( ) { return flockFormingActive; }
	// Return whether the velocity matching AI is activated or not.
	bool getVelocityMatchingActive( ) { return velocityMatchingActive; }
	// Return whether the collision avoidance AI is activated or not.
	bool getCollisionAvoidanceActive( ) { return collisionAvoidanceActive; }
	// Return a reference to the vector containing the pointers to the flyers.
	vector< BoidsFlyer * > &getFlyersRef( ) { return flyers; };
	// Returns whether a certain point in the scene lies below the landscape.
	bool getBelowLandscapeSurface( D3DVALUE x, D3DVALUE y, D3DVALUE z )
							{ return landscape.getBelowSurface( x, y, z ); };
	// Return the current full screen display mode selection.
	DisplayMode getFSResolution( ) { return resolutionFS; };
	// Set the required full screen display mode selection.
	void setFSResolution( DisplayMode res ) { resolutionFS = res; };


	// Get member functions for the flyer attributes variables.
	D3DVALUE getAccelerationRate( ){ return accelerationRate; };
	D3DVALUE getAngleOfVision( ){ return angleOfVision; };
	D3DVALUE getCollisionDistance( ){ return collisionDistance; };
	D3DVALUE getFlockFormingDistance( ){ return flockFormingDistance; };
	D3DVALUE getFlockingRadius( ){ return flockingRadius; };
	D3DVALUE getMaximumSpeed( ){ return maximumSpeed; };
	D3DVALUE getMinimumSpeed( ){ return minimumSpeed; };
	D3DVALUE getRangeOfFlockHeadings( ){ return rangeOfFlockHeadings; };
	D3DVALUE getWingStrokesPerSecond( ){ return wingStrokesPerSecond; };

	// Set member functions for the flyer attributes variables.
	void setAccelerationRate( D3DVALUE x ){ accelerationRate = x; };
	void setAngleOfVision( D3DVALUE x ){ angleOfVision = x; };
	void setCollisionDistance( D3DVALUE x ){ collisionDistance = x; };
	void setFlockFormingDistance( D3DVALUE x ){ flockFormingDistance = x; };
	void setFlockingRadius( D3DVALUE x ){ flockingRadius = x; };
	void setMaximumSpeed( D3DVALUE x ){ maximumSpeed = x; };
	void setMinimumSpeed( D3DVALUE x ){ minimumSpeed = x; };
	void setRangeOfFlockHeadings( D3DVALUE x ){ rangeOfFlockHeadings = x; };
	void setWingStrokesPerSecond( D3DVALUE x ){ wingStrokesPerSecond = x; };





	///////////////////////////////////////////////////////////////////////////
	// Menu item message handlers.
	///////////////////////////////////////////////////////////////////////////

	afx_msg void OnLoad( );
	afx_msg void OnSave( );
	afx_msg void OnStartStop( );
	afx_msg void OnExit( );

	afx_msg void OnCameraAbove( );
	afx_msg void OnCameraBoid( );
	afx_msg void OnCameraNorth( );
	afx_msg void OnCameraEast( );
	afx_msg void OnCameraSouth( );
	afx_msg void OnCameraWest( );
	afx_msg void OnUpdateCameraAbove( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateCameraBoid( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateCameraNorth( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateCameraEast( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateCameraSouth( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateCameraWest( CCmdUI *ptrCmdUI );

	afx_msg void OnIncCameraPos( );
	afx_msg void OnDecCameraPos( );
	afx_msg void OnIncCameraRot( );
	afx_msg void OnDecCameraRot( );

	afx_msg void OnWireFrame( );
	afx_msg void OnUnlitFlat( );
	afx_msg void OnFlat( );
	afx_msg void OnGouraud( );
	afx_msg void OnAddFlyer( );
	afx_msg void OnRemoveFlyer( );
	afx_msg void OnIncFlyerSize( );
	afx_msg void OnDecFlyerSize( );
	afx_msg void OnTetra( );
	afx_msg void OnBird( );
	afx_msg void OnAnimBird( );
	afx_msg void OnFlyerWhite( );
	afx_msg void OnFlyerYellow( );
	afx_msg void OnFlyerPink( );
	afx_msg void OnUpdateWireframe( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateUnlitFlat( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateFlat( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateGouraud( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateTetra( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateBird( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateAnimBird( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateFlyerWhite( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateFlyerYellow( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateFlyerPink( CCmdUI *ptrCmdUI );

	afx_msg void OnLandNone( );
	afx_msg void OnLandWireframe( );
	afx_msg void OnLandUnlitFlat( );
	afx_msg void OnLandFlat( );
	afx_msg void OnLandGouraud( );
	afx_msg void OnLandSolidGreen( );
	afx_msg void OnLandSolidCheckered( );
	afx_msg void OnLandRecalculate( );
	afx_msg void OnUpdateLandNone( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateLandWireFrame( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateLandUnlitFlat( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateLandFlat( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateLandGouraud( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateLandSolidGreen( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateLandSolidCheckered( CCmdUI *ptrCmdUI );

	afx_msg void OnFlockForming( );
	afx_msg void OnVelocityMatching( );
	afx_msg void OnCollisionAvoidance( );
	afx_msg void OnFlyerAttributes( );
	afx_msg void OnUpdateFlockForming( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateVelocityMatching( CCmdUI *ptrCmdUI );
	afx_msg void OnUpdateCollisionAvoidance( CCmdUI *ptrCmdUI );

	afx_msg void OnFullScreen( );
	afx_msg void OnToggleControls( );
	afx_msg void OnUpdateToggleControls( CCmdUI *ptrCmdUI );

	afx_msg void OnAbout( );

	DECLARE_MESSAGE_MAP( )



private:

	friend class BoidsApp;
	friend UINT d3dThread( LPVOID pParam );

	CRect prevWindowSize, newWindowSize;  // The size of the main window.


	// Pointers to the D3D COM interfaces.
	LPDIRECT3DRM d3drm;
	LPDIRECTDRAWCLIPPER clipper;
	LPDIRECT3DRMDEVICE device;
	LPDIRECT3DRMFRAME scene;
	LPDIRECT3DRMFRAME camera;
	LPDIRECT3DRMVIEWPORT viewPort;
	LPDIRECTDRAW directDraw;  // Added for full screen mode.



	// The window's controls.
	CStatic staticNum, staticSize, staticCam,
			staticCam2, staticFrames, staticTime;
	// The following CStatics are used for spacing the controls.
	CStatic topBorder, border1, border2, border3, border4, border5;
	CSliderCtrl sliderNum, sliderSize, sliderCam, sliderCam2;
	CButton btnCentre, btnStop;  // Control panel push buttons.

	// An STL vector for the Windows's flyers.
	vector< BoidsFlyer * > flyers;
	int numFlyers;  // Number of flyers in the vector.
	int requiredFlyers;  // Number of required flyers for the vector.
	ULONG flyerMesh;  // Holds the number of the flyers' mesh shape.
	int flyerMeshesChanged;  // Keeps track of changing the boid meshes.
	D3DCOLOR flyerColour;  // The colour of the flyers.

	volatile int frameCount;  // Number of rendered frames counted per second.
	bool overloaded;  // Flag to state that the application is overloaded.

	D3DRMRENDERQUALITY renderStyle;

	bool flockFormingActive;  // A.I. activation flags.
	bool velocityMatchingActive;
	bool collisionAvoidanceActive;

	BoidsLand landscape;  // The landscape for the simulation.

	enum ViewType { CAM_ABOVE, CAM_BOID, CAM_NORTH,
					CAM_EAST, CAM_SOUTH, CAM_WEST };
	ViewType cameraView;
	double cameraPosition, cameraPosition2;
	bool cameraOnBoid;

	CWinThread* ptrD3DThread;  // Pointer to the rendering thread.


	volatile bool threadEnabled;  // Flags used for multitasking.
	volatile bool threadFinished;
	volatile bool appIdle;
	volatile bool needShutdown;
	volatile bool needToggleControls;
	volatile bool needFullScreen;


	volatile bool stopped;  // Flag to start/stop the simulation.

	volatile clock_t runTime,  // Used to hold the simulation time.
			stopTime,  // Used to hold the simulation time in stopped mode.
			frameStartTime;  // Used to measure the frame rate per second.

	// Display mode data members.
	LPDIRECTDRAWSURFACE frontSurface, backSurface, zBuffer;
	DisplayMode resolutionFS;
	WINDOWPLACEMENT windowedModePos;
	volatile bool fullScreenMode;
	volatile bool showControlPanel;


	// Flyer attributes variables.
	D3DVALUE accelerationRate;
	D3DVALUE angleOfVision;
	D3DVALUE collisionDistance;
	D3DVALUE flockFormingDistance;
	D3DVALUE flockingRadius;
	D3DVALUE maximumSpeed;
	D3DVALUE minimumSpeed;
	D3DVALUE rangeOfFlockHeadings;
	D3DVALUE wingStrokesPerSecond;
};


#endif
