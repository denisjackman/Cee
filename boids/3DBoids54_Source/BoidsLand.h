/*	Filename:		BoidsLand.h
	Author:			Robert Platt
	Creation date:	29/08/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids landscape class.
*/


#include <d3drmwin.h>


#ifndef BOIDS_LAND_H
#define BOIDS_LAND_H


const int LAND_X_SIZE = 9;
const int LAND_Y_SIZE = 6;
const int LAND_Z_SIZE = 9;
const D3DVALUE LAND_HEIGHT = 25;
const D3DVALUE TOWER_HEIGHT = 30;
enum SolidColourEnum { LSC_GREEN, LSC_CHECKERED };


class BoidsLand
{
public:
	// Constructor for the landscape class.
	BoidsLand( );
	// Build the full landscape using the previously set flags.
	void build( CFrameWnd *win, LPDIRECT3DRM d, LPDIRECT3DRMFRAME s,
											D3DRMRENDERQUALITY newStyle );
	// Auxillary function to set the position of a patch of land.
	void positionPatch( D3DRMVERTEX vertices[ ], int r, int c );
	// Build the faces for the sides of a tower.
	void buildTowerSides( int row, int col );
	// Generate some altitudes to shape the landscape.
	void calcHeights( );
	// Calculate the normals for all the face of the patches of land.
	void flatShading( int row, int col, D3DRMVERTEX patchVertices[ ] );
	// Calculate the normals for all the face of the patches of land.
	void towerFlatShading( int side, D3DRMVERTEX towerVertices[ ] );
	// Calculate the normals for all the vertices of the patches of land.
	void gouraudShading( );


	// Deconstruct the landscape.
	void deconstruct( );
	// Remove the landscape.
	void renderNone( );
	// Functions to toggle the style of the landscape.
	void toggleWireframe( );
	void toggleUnlitFlat( );
	void toggleFlat( );
	void toggleGouraud( );
	// Set the colour of the solid landscape.
	void setSolidColour( SolidColourEnum colour );
	// Destroy, recalculate and redraw the landscape.
	void recalculate( );


	// Various get member functions.
	bool getWireframeOn( ) { return wireframeOn; };
	bool getSolidOn( ) { return solidOn; };
	SolidColourEnum getSolidColour( ) { return solidColour; };
	D3DRMRENDERQUALITY getSolidStyle( ) { return solidStyle; };
	bool getExists( ) { return exists; };
	bool getBelowSurface( D3DVALUE x, D3DVALUE y, D3DVALUE z );
	bool getBelowPlane( D3DVALUE x, D3DVALUE y, D3DVALUE z,
						D3DVALUE x1, D3DVALUE x2, D3DVALUE x3,
						D3DVALUE y1, D3DVALUE y2, D3DVALUE y3,
						D3DVALUE z1, D3DVALUE z2, D3DVALUE z3 );


private:
	CFrameWnd *window;
	LPDIRECT3DRM d3drm;
	LPDIRECT3DRMFRAME scene;


	// Data structure to hold the landscapes altitudes.
	int landHeights[ LAND_Z_SIZE + 1][ LAND_X_SIZE + 1 ];  // Rows by columns.
	// The x,y & z spacing used for positioning the patches of land.
	double xSpacing, ySpacing, zSpacing;


	// The landscape's single mesh and frame.
	LPDIRECT3DRMMESH landMesh;
	LPDIRECT3DRMFRAME landFrame;

	// Two sets of groups for the wireframe overlay and solid surface.
	D3DRMGROUPINDEX patchGroups[ 2 ][ LAND_Z_SIZE ][ LAND_X_SIZE ];
	D3DRMGROUPINDEX towerGroups[ 2 ][ 4 ];


	// Array of vectors for holding the normals for flat shading.
	// There are two triangles to each rectangle.
	D3DVECTOR patchFaceNormals[ LAND_Z_SIZE ][ LAND_X_SIZE ][ 2 ];
	D3DVECTOR towerFaceNormals[ 4 ][ 2 ];

	// Array of vectors for holding the normals for Gouraud shading.
	D3DVECTOR patchVertexNormals[ LAND_Z_SIZE + 1 ][ LAND_X_SIZE  + 1 ];


	D3DRMRENDERQUALITY solidStyle;  // The render style in use.
	SolidColourEnum solidColour;

	bool exists;  // Existance flag.

	bool wireframeOn, solidOn;  // The representation flags.
};


#endif
