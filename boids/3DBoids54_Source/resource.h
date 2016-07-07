/*	Filename:		resource.h
	Author:			Robert Platt
	Creation date:	15/06/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids application's resources.
*/


#ifndef RESOURCE_H
#define RESOURCE_H


// Resource mesh definitions.
#define IDR_MESH_TETRA				10010
#define IDR_MESH_BIRD				10011
#define IDR_MESH_BIRDBODY			10012
#define IDR_MESH_LEFTWING			10013
#define IDR_MESH_RIGHTWING			10014


// Menu item definitions.
// Main menu.
#define IDM_LOAD					40010
#define IDM_SAVE					40011
#define IDM_START_STOP				40012
#define IDM_EXIT					40013

// Camera view menu.
#define IDM_CAMERA_ABOVE			40020
#define IDM_CAMERA_BOID				40021
#define IDM_CAMERA_NORTH			40022
#define IDM_CAMERA_EAST				40023
#define IDM_CAMERA_SOUTH			40024
#define IDM_CAMERA_WEST				40025

#define IDM_CAMERA_UP				40026
#define IDM_CAMERA_DOWN				40027
#define IDM_CAMERA_LEFT				40028
#define IDM_CAMERA_RIGHT			40029
#define IDM_CAMERA_CENTRE			40030

// Objects menu.
#define IDM_WIREFRAME				40040
#define IDM_UNLITFLAT				40041
#define IDM_FLAT					40042
#define IDM_GOURAUD					40043

#define IDM_ADD_FLYER				40044
#define IDM_REMOVE_FLYER			40045
#define IDM_INC_FLYER_SIZE			40046
#define IDM_DEC_FLYER_SIZE			40047

#define IDM_TETRA					40048
#define IDM_SMALL_BIRD				40049
#define IDM_ANIM_BIRD				40050

#define IDM_FLYER_WHITE				40051
#define IDM_FLYER_YELLOW			40052
#define IDM_FLYER_PINK				40053

// Landscape menu.
#define IDM_LAND_NONE				40060
#define IDM_LAND_WIREFRAME			40061
#define IDM_LAND_UNLITFLAT			40062
#define IDM_LAND_FLAT				40063
#define IDM_LAND_GOURAUD			40064
#define IDM_SOLID_COLOUR_GREEN		40065
#define IDM_SOLID_COLOUR_CHECKERED	40066
#define IDM_LAND_RECALCULATE		40067

// Behaviour menu.
#define IDM_FLOCKFORMING			40070
#define IDM_VELOCITYMATCHING		40071
#define IDM_COLLISIONAVOIDANCE		40072
#define IDM_FLYER_ATTRIBUTES		40073

// Display mode menu.
#define IDM_SWITCH_FS_MODE          40080
#define IDM_SELECT_MODE				40081
#define IDM_WIN_640_480				40082
#define IDM_WIN_800_600				40083
#define IDM_WIN_1024_768			40084
#define IDM_TOGGLE_CONTROL_PANEL	40085

// Help menu.
#define IDM_ABOUT					40090

// Extra Accelerator Keys.
#define IDK_ESC_KEY					40300


// Display Mode Dialog.
#define IDB_DISPLAYMODE_ACTIVATE	1000
#define IDB_DISPLAYMODE_DEFAULT		1001
#define IDB_DISPLAYMODE_CANCEL		1002
#define IDC_MODES_COMBO				1003
#define IDS_SCREENMODE_TEXT			1004


// Icon.
#define IDI_ICON					1005


// Boid Attributes Dialog.
#define IDB_ATTR_SET				40100
#define IDB_ATTR_DEFAULTS			40101
#define IDC_EDIT_ACC				40102
#define IDC_EDIT_ANG				40103
#define IDC_EDIT_COL				40104
#define IDC_EDIT_FFD				40105
#define IDC_EDIT_FRA				40106
#define IDC_EDIT_MXS				40107
#define IDC_EDIT_MNS				40108
#define IDC_EDIT_RFH				40109
#define IDC_EDIT_WSS				40110


#endif
