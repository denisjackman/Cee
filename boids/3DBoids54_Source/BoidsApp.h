/*	Filename:		BoidsApp.h
	Author:			Robert Platt
	Creation date:	15/06/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids application class.
*/


// The DirectX libraries used.
#pragma comment ( lib, "ddraw.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "d3drm.lib" )


#include "BoidsWin.h"


#ifndef BOIDS_APP_H
#define BOIDS_APP_H


class BoidsApp : public CWinApp
{
public:
	// Application start up function.
	BOOL InitInstance( );
	// Operations for when the application is idle.
	BOOL OnIdle( LONG lCount );

private:
	// Pointer to the application's main window.
	BoidsWin *mainWin;
};


#endif
