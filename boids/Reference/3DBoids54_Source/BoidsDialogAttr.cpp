/*	Filename:		BoidsDialogAttr.cpp
	Author:			Robert Platt
	Creation date:	23/01/2000
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids attributes dialog class.
*/


#include "BoidsDialogAttr.h"
#include "BoidsWin.h"


// This is the new player dialog message map.
BEGIN_MESSAGE_MAP( BoidsDialogAttr, CDialog )
	ON_COMMAND( IDB_ATTR_SET, OnSet )
	ON_COMMAND( IDB_ATTR_DEFAULTS, OnDefaults )
END_MESSAGE_MAP( )


// Initialise the dialog box.
BOOL BoidsDialogAttr::OnInitDialog( )
{
	CDialog::OnInitDialog( );  // Base class initialisation.

	// Bring the new dialog to the top of the window's Z order.
	// This is needed for Windows 2000, since the dialog can
	// remain hidden behind the boids main window.
	CWnd::SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOMOVE |
										SWP_NOSIZE | SWP_SHOWWINDOW );

	outputValues( );  // Fill the edit boxes.


	return true;
}


// Place the current values into all the edit boxes.
void BoidsDialogAttr::outputValues( )
{
	BoidsWin *parent;
	parent = static_cast< BoidsWin * > ( GetParent( ) );


	// Get pointers to all the dialog's edit boxes.
	CEdit *editPtrAcc = (CEdit *) GetDlgItem( IDC_EDIT_ACC );
	CEdit *editPtrAng = (CEdit *) GetDlgItem( IDC_EDIT_ANG );
	CEdit *editPtrCol = (CEdit *) GetDlgItem( IDC_EDIT_COL );
	CEdit *editPtrFfd = (CEdit *) GetDlgItem( IDC_EDIT_FFD );
	CEdit *editPtrFra = (CEdit *) GetDlgItem( IDC_EDIT_FRA );
	CEdit *editPtrMxs = (CEdit *) GetDlgItem( IDC_EDIT_MXS );
	CEdit *editPtrMns = (CEdit *) GetDlgItem( IDC_EDIT_MNS );
	CEdit *editPtrRfh = (CEdit *) GetDlgItem( IDC_EDIT_RFH );
	CEdit *editPtrWss = (CEdit *) GetDlgItem( IDC_EDIT_WSS );

	// Place the current values into all the edit boxes.
	int  decimal, sign;
	D3DVALUE v = parent -> getAccelerationRate( );
	CString s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrAcc -> SetWindowText( s );


	v = parent -> getAngleOfVision( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrAng -> SetWindowText( s );


	v = parent -> getCollisionDistance( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrCol -> SetWindowText( s );


	v = parent -> getFlockFormingDistance( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrFfd -> SetWindowText( s );


	v = parent -> getFlockingRadius( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrFra -> SetWindowText( s );


	v = parent -> getMaximumSpeed( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrMxs -> SetWindowText( s );


	v = parent -> getMinimumSpeed( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrMns -> SetWindowText( s );


	v = parent -> getRangeOfFlockHeadings( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrRfh -> SetWindowText( s );


	v = parent -> getWingStrokesPerSecond( );
	s = _fcvt( v, 1, &decimal, &sign );
	if ( v < 1.0 )  // If the value is less than 1.0.
	{
		s.Insert( 0, '0' );  // Insert a zero.
		decimal++;
	}
	s.Insert( decimal, '.' );
	editPtrWss -> SetWindowText( s );
}


// Place the default values into all the edit boxes.
void BoidsDialogAttr::defaultValues( )
{
	BoidsWin *parent;
	parent = static_cast< BoidsWin * > ( GetParent( ) );


	// Get pointers to all the dialog's edit boxes.
	CEdit *editPtrAcc = (CEdit *) GetDlgItem( IDC_EDIT_ACC );
	CEdit *editPtrAng = (CEdit *) GetDlgItem( IDC_EDIT_ANG );
	CEdit *editPtrCol = (CEdit *) GetDlgItem( IDC_EDIT_COL );
	CEdit *editPtrFfd = (CEdit *) GetDlgItem( IDC_EDIT_FFD );
	CEdit *editPtrFra = (CEdit *) GetDlgItem( IDC_EDIT_FRA );
	CEdit *editPtrMxs = (CEdit *) GetDlgItem( IDC_EDIT_MXS );
	CEdit *editPtrMns = (CEdit *) GetDlgItem( IDC_EDIT_MNS );
	CEdit *editPtrRfh = (CEdit *) GetDlgItem( IDC_EDIT_RFH );
	CEdit *editPtrWss = (CEdit *) GetDlgItem( IDC_EDIT_WSS );

	// Place the current values into all the edit boxes.
	int  decimal, sign;
	CString s = _fcvt( ACCELERATION_RATE, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrAcc -> SetWindowText( s );

	s = _fcvt( ANGLE_OF_VISION, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrAng -> SetWindowText( s );

	s = _fcvt( COLLISION_DISTANCE, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrCol -> SetWindowText( s );

	s = _fcvt( FLOCK_FORMING_DISTANCE, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrFfd -> SetWindowText( s );

	s = _fcvt( FLOCKING_RADIUS, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrFra -> SetWindowText( s );

	s = _fcvt( MAXIMUM_SPEED, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrMxs -> SetWindowText( s );

	s = _fcvt( MINIMUM_SPEED, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrMns -> SetWindowText( s );

	s = _fcvt( RANGE_OF_FLOCK_HEADINGS, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrRfh -> SetWindowText( s );

	s = _fcvt( WING_STROKES_PER_SECOND, 1, &decimal, &sign );
	s.Insert( decimal, '.' );
	editPtrWss -> SetWindowText( s );
}


afx_msg void BoidsDialogAttr::OnSet( )
{
	BoidsWin *parent;
	parent = static_cast< BoidsWin * > ( GetParent( ) );

	// Get pointers to all the dialog's edit boxes.
	CEdit *editPtrAcc = (CEdit *) GetDlgItem( IDC_EDIT_ACC );
	CEdit *editPtrAng = (CEdit *) GetDlgItem( IDC_EDIT_ANG );
	CEdit *editPtrCol = (CEdit *) GetDlgItem( IDC_EDIT_COL );
	CEdit *editPtrFfd = (CEdit *) GetDlgItem( IDC_EDIT_FFD );
	CEdit *editPtrFra = (CEdit *) GetDlgItem( IDC_EDIT_FRA );
	CEdit *editPtrMxs = (CEdit *) GetDlgItem( IDC_EDIT_MXS );
	CEdit *editPtrMns = (CEdit *) GetDlgItem( IDC_EDIT_MNS );
	CEdit *editPtrRfh = (CEdit *) GetDlgItem( IDC_EDIT_RFH );
	CEdit *editPtrWss = (CEdit *) GetDlgItem( IDC_EDIT_WSS );

	CString s;
	float f;
	editPtrAcc -> GetWindowText( s );
	f = convert( s );
	parent -> setAccelerationRate( f );


	editPtrAng -> GetWindowText( s );
	f = convert( s );
	parent -> setAngleOfVision( f );


	editPtrCol -> GetWindowText( s );
	f = convert( s );
	parent -> setCollisionDistance( f );


	editPtrFfd -> GetWindowText( s );
	f = convert( s );
	parent -> setFlockFormingDistance( f );


	editPtrFra -> GetWindowText( s );
	f = convert( s );
	parent -> setFlockingRadius( f );


	editPtrMxs -> GetWindowText( s );
	f = convert( s );
	parent -> setMaximumSpeed( f );


	editPtrMns -> GetWindowText( s );
	f = convert( s );
	parent -> setMinimumSpeed( f );


	editPtrRfh -> GetWindowText( s );
	f = convert( s );
	parent -> setRangeOfFlockHeadings( f );


	editPtrWss -> GetWindowText( s );
	f = convert( s );
	parent -> setWingStrokesPerSecond( f );

	EndDialog( 0 );  // Close the dialog box.
}


// Small function to keep the code concise.
inline float BoidsDialogAttr::convert( CString s )
{
	// Convert the CString to a float.
	// 10 is passed as the minimum buffer size for the LPTSTR pointer.
	float f = atof( s.GetBuffer( 10 ) );

	// Keep the number positive.
	if ( f < 0.0 )
	{
		f *= -1.0;
	}

	return f;
}


afx_msg void BoidsDialogAttr::OnCancel( )
{
	EndDialog( 0 );  // Close the dialog box.
}


afx_msg void BoidsDialogAttr::OnDefaults( )
{
	defaultValues( );  // Fill the edit boxes.
}
