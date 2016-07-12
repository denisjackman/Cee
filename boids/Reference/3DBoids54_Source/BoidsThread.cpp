/*	Filename:		BoidsThread.cpp
	Author:			Robert Platt
	Creation date:	14/09/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Global function to perform the concurrency support.
*/


#include "BoidsWin.h"


// The display thread's main function.
UINT d3dThread( LPVOID pParam )
{
	// Create a pointer to the main window.
	BoidsWin *mainWin = static_cast< BoidsWin * >( pParam );

	// The thread's main rendering loop.
	// This while loop is only active while -
	// - the simulation running flag is set.
	while( mainWin -> threadEnabled )
	{
		// Continue the D3DRM rendering.
		mainWin -> d3drm -> Tick( D3DVALUE( 1.0 ) );
		mainWin -> frameCount++;  // Increment the frame count.


		// Update the static timer control.
		mainWin -> updateTimer( );


		// Call the function to maintain and update the main window.
		if ( mainWin -> appIdle == false )
		{
			// Perform some maintenance tasks every second.
			if ( (double)( clock( ) - mainWin -> frameStartTime ) / 
										(double)CLOCKS_PER_SEC >= 1.0 )
			{
				mainWin -> performEverySecond( );
			}
		}
	}


	// Set the flag to state that the thread has finished.
	mainWin -> threadFinished = true;


	return 0;  // End the thread's execution.
}
