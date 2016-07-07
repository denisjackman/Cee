/*	Filename:		BoidsApp.cpp
	Author:			Robert Platt
	Creation date:	15/06/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids application class.
*/


#include "BoidsApp.h"


// Function called when the application is first instantiated.
BOOL BoidsApp::InitInstance()
{
	// Create the main window.
	mainWin = new BoidsWin;

	// Set the positioning of the window.
	CRect windowSize( WINDOW_LEFT_POSITION, WINDOW_TOP_POSITION,
						WINDOW_RIGHT_POSITION, WINDOW_BOTTOM_POSITION );

	// Code that is needed for setting the icon and mouse pointer.
	// Brush used for painting the background of the window's client area.
	CBrush bkbrush;
	bkbrush.CreateStockObject( HOLLOW_BRUSH );
	LPCSTR cname = AfxRegisterWndClass( 0,
						LoadStandardCursor( IDC_ARROW ),
						bkbrush,
						LoadIcon( IDI_ICON ) );

	mainWin -> Create( cname, "3D Boids", WS_OVERLAPPEDWINDOW,
										windowSize, NULL, "MFCMENU" );


	// Load in the Accelerator Table.
	mainWin -> LoadAccelTable( "ACCELKEYS" );
	mainWin -> ShowWindow( m_nCmdShow );


	// Register mainWin as the main window for the application.
	m_pMainWnd = mainWin;


	return TRUE;
}


// Function called when the application's main thread becomes idle.
BOOL BoidsApp::OnIdle( LONG count )
{
	// Set the multitasking flag to show that the OnIdle thread is working.
	mainWin -> appIdle = true;


	// Stop the rendering thread.
	mainWin -> threadEnabled = false;


	// Check if the D3D device needs resizing, -
	// - but don't if in full screen mode.
	mainWin -> GetClientRect( &( mainWin -> newWindowSize ) );
	if ( ( mainWin -> newWindowSize.right !=
				mainWin -> prevWindowSize.right
				||	mainWin -> newWindowSize.bottom !=
						mainWin -> prevWindowSize.bottom )
				&& ( mainWin -> fullScreenMode == false ) )
	{
		mainWin -> reSizeD3D( );
	}


	// Toggle the control panel if needed.
	if ( mainWin -> needToggleControls == true )
	{
		mainWin -> OnToggleControls( );
	}


	// Switch to full screen mode if needed.
	if ( mainWin -> needFullScreen == true )
	{
		mainWin -> OnFullScreen( );
	}


	// Maintain the scene before rendering the next frame.
	mainWin -> maintainScene( );


	if ( mainWin -> fullScreenMode == false )
	{
		// Continue the D3DRM rendering.
		mainWin -> d3drm -> Tick( D3DVALUE( 1.0 ) );
		mainWin -> frameCount++;  // Increment the frame count.


		// Update the static timer control.
		mainWin -> updateTimer( );

		
		// Perform some maintenance tasks every second.
		if ( (double)( clock( ) - mainWin -> frameStartTime ) / 
								(double)CLOCKS_PER_SEC >= 1.0 )
		{
			mainWin -> performEverySecond( );
		}
	}


	// If in full screen mode and the thread has finished, do the rendering.
	if ( mainWin -> fullScreenMode && mainWin -> threadFinished )
	{
		// Maintain the scene before rendering the next frame.
		mainWin -> maintainScene( );


		// Render the next frame in full screen mode.
		mainWin -> renderFullScreen( );
		mainWin -> frameCount++;  // Increment the frame count.


		// Update the static timer control.
		mainWin -> updateTimer( );


		// Perform some maintenance tasks every second.
		if ( (double)( clock( ) - mainWin -> frameStartTime ) /
										(double)CLOCKS_PER_SEC >= 1.0 )
		{
			mainWin -> performEverySecond( );
		}
	}


	// When then shutdown flag has been set, try to close the window.
	if ( mainWin -> needShutdown )
	{
		mainWin -> SendMessage( WM_CLOSE );
	}


	return TRUE;
}


BoidsApp boidsApp;
