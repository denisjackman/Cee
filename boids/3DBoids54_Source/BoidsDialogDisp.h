/*	Filename:		BoidsDialogDisp.h
	Author:			Robert Platt
	Creation date:	23/10/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids display dialog class.
*/


#include <afxwin.h>
#include <d3drmwin.h>
#include "resource.h"


#ifndef BOIDS_DIALOG_DISP_H
#define BOIDS_DIALOG_DISP_H


// The maximum number of display modes to emunerate.
const int MODES_LIMIT = 100;
const int TEMP_BUFFER_SIZE = 256;


// Stucture to hold the details of a display mode.
struct DisplayMode
{
	DWORD widthPixels;
	DWORD heightPixels;
	DWORD colourDepthBits;
};


// Dialog box for selecting the full screen display mode.
class BoidsDialogDisp : public CDialog
{
public:
	BoidsDialogDisp( char * DialogName, CWnd *Owner ) :
		CDialog( DialogName, Owner ) { }

	BOOL OnInitDialog();
	afx_msg void OnActivate( );
	afx_msg void OnDefault( );
	afx_msg void OnCancel( );

	static HRESULT WINAPI storeMode( LPDDSURFACEDESC surface, LPVOID ptr );
	static int compareModes( const void *arg1, const void *arg2 );

	DECLARE_MESSAGE_MAP( )

private:
	LPDIRECTDRAW directDraw;  // Direct Draw Interface.
	static DisplayMode modesArray[ MODES_LIMIT ];
	static int numModes;
};


#endif
