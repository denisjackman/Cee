/*	Filename:		BoidsDialogDisp.cpp
	Author:			Robert Platt
	Creation date:	23/10/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids display dialog class.
*/


#include "BoidsDialogDisp.h"
#include "BoidsWin.h"


DisplayMode BoidsDialogDisp::modesArray[ MODES_LIMIT ];
int BoidsDialogDisp::numModes;


// This is the new player dialog message map.
BEGIN_MESSAGE_MAP( BoidsDialogDisp, CDialog )
	ON_COMMAND( IDB_DISPLAYMODE_ACTIVATE, OnActivate )
	ON_COMMAND( IDB_DISPLAYMODE_DEFAULT, OnDefault )
	ON_COMMAND( IDB_DISPLAYMODE_CANCEL, OnCancel )
END_MESSAGE_MAP( )


// Initialise the dialog box.
BOOL BoidsDialogDisp::OnInitDialog( )
{
	CDialog::OnInitDialog( );  // Base class initialisation.

	// Bring the new dialog to the top of the window's Z order.
	// This is needed for Windows 2000, since the dialog can
	// remain hidden behind the boids main window.
	CWnd::SetWindowPos( &wndTop, 0, 0, 0, 0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );


	// Create the direct draw interface.
	DirectDrawCreate( 0, &directDraw, 0 );
	numModes = 0;

	// Enumerate the available display modes.
	directDraw -> EnumDisplayModes( 0, 0, 0, storeMode );

	// Sort the display modes.
	qsort( modesArray, numModes, sizeof( DisplayMode ), compareModes );

	// Place the available modes in the combo box.
	CComboBox *comboPtr = (CComboBox *) GetDlgItem( IDC_MODES_COMBO );

	char buffer[ TEMP_BUFFER_SIZE ];  // Used for integer conversion.
	CString modeText;  // Combo box display text.

	// Fill the combo box with the display modes.
	for ( int i = 0; i < numModes; i++ )
	{
		// Write the display mode into the combo box.
		_itoa( modesArray[ i ].widthPixels, buffer, 10 );
		modeText = buffer;
		modeText += " x ";
		_itoa( modesArray[ i ].heightPixels, buffer, 10 );
		modeText += buffer;
		modeText += " x ";
		_itoa( modesArray[ i ].colourDepthBits, buffer, 10 );
		modeText += buffer;

		comboPtr -> AddString( modeText );
	}

	// .
	// Get the data member in the main window.
	DisplayMode curent = static_cast<BoidsWin *>( GetOwner( ) ) ->
														getFSResolution( );

	// Find the position of the curent mode in the mode array.
	int position = -1;

	for ( int j = 0; j < numModes; j++ )
	{
		if ( modesArray[ j ].widthPixels == curent.widthPixels &&
			modesArray[ j ].heightPixels == curent.heightPixels &&
			modesArray[ j ].colourDepthBits == curent.colourDepthBits )
		{
			position = j;
		}
	}

	// If found set the combo box value to the current mode,
	// for user reference.
	if ( position > -1 )
	{
		// Set the combo box selection to the curent mode.
		comboPtr -> SetCurSel( position );
	}
	else
	{
		// Set the combo box selection to the begining of the list.
		comboPtr -> SetCurSel( 0 );
	}

	comboPtr -> SetFocus( );  // Set the focus as the combo box.

	directDraw -> Release( );  // Release the Direct Draw Interface.

	// Return false because I manually set the combo box as the focus.
	return false;
}


// Process the IDB_DISPLAYMODE_DEFAULT message.
afx_msg void BoidsDialogDisp::OnDefault( )
{
	// Get a pointer to the combo box.
	CComboBox *comboPtr = (CComboBox *) GetDlgItem( IDC_MODES_COMBO );
	// Get the combo box's current selection.
	int modeIndex = comboPtr -> GetCurSel( );

	// Set the data member in the main window.
	static_cast<BoidsWin *>( GetOwner( ) ) ->
								setFSResolution( modesArray[ modeIndex ] );

	EndDialog( 0 );  // Close the dialog box.
}


// Process the IDB_DISPLAYMODE_ACTIVATE message.
afx_msg void BoidsDialogDisp::OnActivate( )
{
	// Get a pointer to the combo box.
	CComboBox *comboPtr = (CComboBox *) GetDlgItem( IDC_MODES_COMBO );
	// Get the combo box's current selection.
	int modeIndex = comboPtr -> GetCurSel( );

	// Set the data member in the main window.
	static_cast<BoidsWin *>( GetOwner( ) ) ->
								setFSResolution( modesArray[ modeIndex ] );

	EndDialog( 0 );  // Close the dialog box.

	// Activate the full screen mode.
	static_cast<BoidsWin *>( GetOwner( ) ) -> OnFullScreen( );
}


// Process the IDB_DISPLAYMODE_CANCEL message.
afx_msg void BoidsDialogDisp::OnCancel( )
{
	EndDialog( 0 );  // Close the dialog box.
}


// Standard callback function for storing the available display modes.
HRESULT WINAPI BoidsDialogDisp::storeMode(
						LPDDSURFACEDESC surface, LPVOID ptr )
{
	if ( numModes == MODES_LIMIT )
	{
		return DDENUMRET_CANCEL;  // Abort if at end of modes array.
	}

	// Store the surface details in the array of display modes.
	modesArray[ numModes ].widthPixels = surface -> dwWidth;
	modesArray[ numModes ].heightPixels = surface -> dwHeight;
	modesArray[ numModes ].colourDepthBits = surface ->
										ddpfPixelFormat.dwRGBBitCount;

	// Skip all the modes with 8 bit colour depth.
	if ( surface -> ddpfPixelFormat.dwRGBBitCount != 8 )
	{
		numModes++;  // Move to the next array element & increment the count.
	}

	return DDENUMRET_OK;
}


// Utility function to assist the sorting of the display modes.
int BoidsDialogDisp::compareModes( const void *arg1, const void *arg2 )
{
	DisplayMode *mode1 = (DisplayMode *)arg1;
	DisplayMode *mode2 = (DisplayMode *)arg2;

	DWORD volume1 = mode1 -> widthPixels * mode1 -> heightPixels;
	DWORD volume2 = mode2 -> widthPixels * mode2 -> heightPixels;

	if ( volume1 < volume2 )
	{
		return -1;
	}
	else if ( volume1 > volume2 )
	{
		return 1;
	}

	if ( mode1 -> colourDepthBits < mode2 -> colourDepthBits )
	{
		return -1;
	}
	else if ( mode1 -> colourDepthBits > mode2 -> colourDepthBits )
	{
		return 1;
	}
	
	return 0;
}
