/*	Filename:		BoidsDialogAttr.h
	Author:			Robert Platt
	Creation date:	23/01/2000
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids attributes dialog class.
*/


#include <afxwin.h>
#include <d3drmwin.h>
#include "resource.h"


#ifndef BOIDS_DIALOG_ATTR_H
#define BOIDS_DIALOG_ATTR_H


// Dialog box for selecting the full screen display mode.
class BoidsDialogAttr : public CDialog
{
public:
	BoidsDialogAttr( char * DialogName, CWnd *Owner ) :
		CDialog( DialogName, Owner ) { }

	BOOL OnInitDialog();
	afx_msg void OnSet( );  // Respective button handlers.
	afx_msg void OnCancel( );
	afx_msg void OnDefaults( );

	void outputValues( );  // Display the current values.
	void defaultValues( );  // Display the default values.
	inline float convert( CString s );  // Auxillary function.

	DECLARE_MESSAGE_MAP( )

private:

};


#endif
