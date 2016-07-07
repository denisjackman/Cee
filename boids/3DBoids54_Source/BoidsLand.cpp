/*	Filename:		BoidsLand.cpp
	Author:			Robert Platt
	Creation date:	29/08/1999
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids landscape class.
*/


#include "BoidsWin.h"


// Constructor for the landscape class.
BoidsLand::BoidsLand( )
{
	// Initialise the COM interface pointers.
	landFrame = NULL;

	solidStyle = DEFAULT_LANDSCAPE_SOLID_STYLE;
	solidColour = LSC_GREEN;


	wireframeOn = true;  // Initialize the flags.
	solidOn = false;

	exists = false;  // This will be set by the build function.

	// Call the member function to produce the landscape altitudes.
	calcHeights( );
}


// Build the full landscape using the previously set flags.
void BoidsLand::build( CFrameWnd *win, LPDIRECT3DRM d,
					  LPDIRECT3DRMFRAME s, D3DRMRENDERQUALITY solidStyle )
{
	window = win;
	d3drm = d;  // Store two pointers to the D3D interfaces inside the object.
	scene = s;  // This helps to keep future calls to the object concise.

	// Abort the build if nothing to do.
	if ( solidOn == false && wireframeOn == false )
	{
		return;
	}

	// Calculate the uniform sizes of all the landscape patches.
	xSpacing = X_LIMIT * 2 / LAND_X_SIZE;
	ySpacing = LAND_HEIGHT;
	zSpacing = Z_LIMIT * 2 / LAND_Z_SIZE;


	// Create the main landscape root frame.
	d3drm -> CreateFrame( scene, &landFrame );
	landFrame -> SetPosition( scene, D3DVALUE( 0.0 ),
										D3DVALUE( 0.0 ), D3DVALUE( 0.0 ) );

	// Create the landscape mesh.
	d3drm -> CreateMesh( &landMesh );


	// Used for producing each patch of land.
	D3DRMVERTEX patchVertices[ 6 ];
	unsigned vertOrder[] = { 0, 1, 2, 3, 4, 5 };


	// Generate the surface for the landMesh.
	for ( int row = 0; row < LAND_Z_SIZE; row++ )
	{
		for ( int col = 0; col < LAND_X_SIZE; col++ )
		{
			// Create the solid representation if required.
			if ( solidOn )
			{
				landMesh -> AddGroup( 6, 2, 3, vertOrder,
										&patchGroups[ 0 ][ row ][ col ] );
			}

			// Create the wireframe overlay if required.
			if ( wireframeOn )
			{
				landMesh -> AddGroup( 6, 2, 3, vertOrder,
										&patchGroups[ 1 ][ row ][ col ] );
			}


			// Call the auxillary function to position the land patch.
			positionPatch( patchVertices, row, col );


			// Apply flat shading to the patch of land.
			if ( solidOn )
			{
				flatShading( row, col, patchVertices );
			}


			// Complete the production of the patch of -
			// - land for solid representation.
			if ( solidOn )
			{
				landMesh -> SetVertices( patchGroups[ 0 ][ row ][ col ],
													0, 6, patchVertices );
				landMesh -> SetGroupQuality(
							patchGroups[ 0 ][ row ][ col ], solidStyle );


				// Set the landscape's colours.
				// Colour the central tower brown.
				if ( row == 4 && col == 4 )
				{
					// Brown.
					landMesh -> SetGroupColor(
								patchGroups[ 0 ][ row ][ col ], RGB_BROWN );
				}
				else  // Colour the land.
				{
					if  ( solidColour == LSC_CHECKERED )
					{
						// Colour the land checkered style.
						if ( row % 2 == 0 )
						{
							if ( col % 2 == 0 )
							{
								// Black.
								landMesh -> SetGroupColor(
									patchGroups[ 0 ][ row ][ col ], RGB_BLACK );
							}
							else
							{
								// White.
								landMesh -> SetGroupColor(
									patchGroups[ 0 ][ row ][ col ], RGB_WHITE );
							}
						}
						else
						{
							if ( col % 2 == 0 )
							{
								// White.
								landMesh -> SetGroupColor(
									patchGroups[ 0 ][ row ][ col ], RGB_WHITE );
							}
							else
							{
								// Black.
								landMesh -> SetGroupColor(
									patchGroups[ 0 ][ row ][ col ], RGB_BLACK );
							}
						}
					}

					if  ( solidColour == LSC_GREEN )
					{
						// Colour the land green.
						landMesh -> SetGroupColor(
							patchGroups[ 0 ][ row ][ col ], RGB_LAND_GREEN );
					}
				}
			}


			if ( wireframeOn )
			{
				// Complete the production of the patch of land.
				landMesh -> SetVertices( patchGroups[ 1 ][ row ][ col ],
														0, 6, patchVertices );
				landMesh -> SetGroupQuality( patchGroups[ 1 ][ row ][ col ],
													D3DRMRENDER_WIREFRAME );
				// Set the wireframe landscape colour.
				if ( solidOn )
				{
					// Black.
					landMesh -> SetGroupColor(
								patchGroups[ 1 ][ row ][ col ], RGB_BLACK );
				}
				else
				{
					// If there is no solid land, colour -
					// - the wireframe black for clarity.
					// Black.
					landMesh -> SetGroupColor(
								patchGroups[ 1 ][ row ][ col ], RGB_BLACK );
				}

			}

			// If the patch of land was a tower, add the sides of the tower.
			if ( row == 4 && col == 4 )
			{
				buildTowerSides( row, col );
			}
		}
	}


	// Add the land to the land frame.
	landFrame -> AddVisual(	landMesh );

	// Apply gouraud shading to the landscape if selected.
	if ( solidStyle == D3DRMRENDER_GOURAUD && solidOn )
	{
		gouraudShading( );
	}

	exists = true;  // Set the flag.
}


// Auxillary function to set the position of a patch of land.
void BoidsLand::positionPatch( D3DRMVERTEX vertices[ ], int r, int c )
{
	// Set the vertices for the patch of land.
	// First triangle.
	//////////////////////////////////
	// South west corner vertex <0>.
	//////////////////////////////////
	vertices[ 0 ].position.x = c * xSpacing - X_LIMIT;
	// If the patch of land is a tower.
	if ( r == 4 && c == 4 )
	{
		// Raise the height of the vertex to the top of the tower.
		vertices[ 0 ].position.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
	}
	else
	{
		// Just keep the normal height.
		vertices[ 0 ].position.y = landHeights[ r ][ c ]
												* ySpacing - Y_LIMIT;
	}
	vertices[ 0 ].position.z = r * zSpacing - Z_LIMIT;


	//////////////////////////////////
	// North west corner vertex <1>.
	//////////////////////////////////
	vertices[ 1 ].position.x = c * xSpacing - X_LIMIT;
	// If the patch of land is a tower.
	if ( r == 4 && c == 4 )
	{
		// Raise the height of the vertex to the top of the tower.
		vertices[ 1 ].position.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
	}
	else
	{
		// Just keep the normal height.
		vertices[ 1 ].position.y = landHeights[ r + 1 ][ c ] *
													ySpacing - Y_LIMIT;
	}
	vertices[ 1 ].position.z = ( r + 1 ) * zSpacing - Z_LIMIT;


	//////////////////////////////////
	// North east corner vertex <2>.
	//////////////////////////////////
	vertices[ 2 ].position.x = ( c + 1 ) * xSpacing - X_LIMIT;
	// If the patch of land is a tower.
	if ( r == 4 && c == 4 )
	{
		// Raise the height of the vertex to the top of the tower.
		vertices[ 2 ].position.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
	}
	else
	{
		// Just keep the normal height.
		vertices[ 2 ].position.y = landHeights[ r + 1 ][ c + 1 ] *
														ySpacing - Y_LIMIT;
	}
	vertices[ 2 ].position.z = ( r + 1 ) * zSpacing - Z_LIMIT;



	// Second triangle.
	//////////////////////////////////
	// South west corner vertex <3>.
	//////////////////////////////////
	vertices[ 3 ].position.x = c * xSpacing - X_LIMIT;
	// If the patch of land is a tower.
	if ( r == 4 && c == 4 )
	{
		// Raise the height of the vertex to the top of the tower.
		vertices[ 3 ].position.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
	}
	else
	{
		// Just keep the normal height.
		vertices[ 3 ].position.y = landHeights[ r ][ c ]
												* ySpacing - Y_LIMIT;
	}
	vertices[ 3 ].position.z = r * zSpacing - Z_LIMIT;


	//////////////////////////////////
	// North east corner vertex <4>.
	//////////////////////////////////
	vertices[ 4 ].position.x = ( c + 1 ) * xSpacing - X_LIMIT;
	// If the patch of land is a tower.
	if ( r == 4 && c == 4 )
	{
		// Raise the height of the vertex to the top of the tower.
		vertices[ 4 ].position.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
	}
	else
	{
		// Just keep the normal height.
		vertices[ 4 ].position.y = landHeights[ r + 1 ][ c + 1 ] *
														ySpacing - Y_LIMIT;
	}
	vertices[ 4 ].position.z = ( r + 1 ) * zSpacing - Z_LIMIT;


	//////////////////////////////////
	// South east corner vertex <5>.
	//////////////////////////////////
	vertices[ 5 ].position.x = ( c + 1 ) * xSpacing - X_LIMIT;
	// If the patch of land is a tower.
	if ( r == 4 && c == 4 )
	{
		// Raise the height of the vertex to the top of the tower.
		vertices[ 5 ].position.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
	}
	else
	{
		// Just keep the normal height.
		vertices[ 5 ].position.y = landHeights[ r ][ c + 1 ] *
													ySpacing - Y_LIMIT;
	}
	vertices[ 5 ].position.z = r * zSpacing - Z_LIMIT;
}


// Build the faces for the sides of a tower.
void BoidsLand::buildTowerSides( int row, int col )
{
	unsigned vertOrder[] = { 0, 1, 2, 3, 4, 5 };
	D3DRMVERTEX towerVertices[ 6 ];


	for ( int side = 0; side <= 3; side++ )
	{
		// Create the solid representation if required.
		if ( solidOn )
		{
			landMesh -> AddGroup( 6, 2, 3, vertOrder,
											&towerGroups[ 0 ][ side ] );
		}

		// Create the wireframe overlay if required.
		if ( wireframeOn )
		{
			landMesh -> AddGroup( 6, 2, 3, vertOrder,
											&towerGroups[ 1 ][ side ] );
		}


		// Set the vertices for the patch of land.
		D3DVECTOR	topLeftPoint,
					topRightPoint,
					bottomLeftPoint,
					bottomRightPoint;


		// These values are the same for all the sides.
		topLeftPoint.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;
		topRightPoint.y = TOWER_HEIGHT * ySpacing - Y_LIMIT;


		// The north facing side.
		if ( side == 0 )
		{
			// Define the top left point.
			topLeftPoint.x = col * xSpacing - X_LIMIT;
			topLeftPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;

			// Define the top right point.
			topRightPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			topRightPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;

			// Define the bottom left point.
			bottomLeftPoint.x = col * xSpacing - X_LIMIT;
			bottomLeftPoint.y = landHeights[ row + 1 ][ col ]
											* ySpacing - Y_LIMIT;
			bottomLeftPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;

			// Define the bottom right point.
			bottomRightPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			bottomRightPoint.y = landHeights[ row + 1 ][ col + 1 ]
											* ySpacing - Y_LIMIT;
			bottomRightPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;
		}


		// The east facing side.
		if ( side == 1 )
		{
			// Define the top left point.
			topLeftPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			topLeftPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;

			// Define the top right point.
			topRightPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			topRightPoint.z = row * zSpacing - Z_LIMIT;

			// Define the bottom left point.
			bottomLeftPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			bottomLeftPoint.y = landHeights[ row + 1 ][ col + 1 ]
											* ySpacing - Y_LIMIT;
			bottomLeftPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;

			// Define the bottom right point.
			bottomRightPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			bottomRightPoint.y = landHeights[ row ][ col + 1 ]
											* ySpacing - Y_LIMIT;
			bottomRightPoint.z = row * zSpacing - Z_LIMIT;
		}


		// The south facing side.
		if ( side == 2 )
		{
			// Define the top left point.
			topLeftPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			topLeftPoint.z = row * zSpacing - Z_LIMIT;

			// Define the top right point.
			topRightPoint.x = col * xSpacing - X_LIMIT;
			topRightPoint.z = row * zSpacing - Z_LIMIT;

			// Define the bottom left point.
			bottomLeftPoint.x = ( col + 1 ) * xSpacing - X_LIMIT;
			bottomLeftPoint.y = landHeights[ row ][ col + 1 ]
											* ySpacing - Y_LIMIT;
			bottomLeftPoint.z = row * zSpacing - Z_LIMIT;

			// Define the bottom right point.
			bottomRightPoint.x = col * xSpacing - X_LIMIT;
			bottomRightPoint.y = landHeights[ row ][ col ]
											* ySpacing - Y_LIMIT;
			bottomRightPoint.z = row * zSpacing - Z_LIMIT;
		}


		// The west facing side.
		if ( side == 3 )
		{
			// Define the top left point.
			topLeftPoint.x = col * xSpacing - X_LIMIT;
			topLeftPoint.z = row * zSpacing - Z_LIMIT;

			// Define the top right point.
			topRightPoint.x = col * xSpacing - X_LIMIT;
			topRightPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;

			// Define the bottom left point.
			bottomLeftPoint.x = col * xSpacing - X_LIMIT;
			bottomLeftPoint.y = landHeights[ row ][ col ]
											* ySpacing - Y_LIMIT;
			bottomLeftPoint.z = row * zSpacing - Z_LIMIT;

			// Define the bottom right point.
			bottomRightPoint.x = col * xSpacing - X_LIMIT;
			bottomRightPoint.y = landHeights[ row + 1 ][ col ]
											* ySpacing - Y_LIMIT;
			bottomRightPoint.z = ( row + 1 ) * zSpacing - Z_LIMIT;
		}


		// First triangle.
		// South west corner vertex <0>.
		towerVertices[ 0 ].position = topLeftPoint;

		// North west corner vertex <1>.
		towerVertices[ 1 ].position = bottomLeftPoint;

		// North east corner vertex <2>.
		towerVertices[ 2 ].position = bottomRightPoint;


		// Second triangle.
		// South west corner vertex <3>.
		towerVertices[ 3 ].position = topLeftPoint;

		// North east corner vertex <4>.
		towerVertices[ 4 ].position = bottomRightPoint;

		// South east corner vertex <5>.
		towerVertices[ 5 ].position = topRightPoint;



		// Apply flat shading to the side of the tower.
		if ( solidOn )
		{
			towerFlatShading( side, towerVertices );
		}


		// Complete the production of the patch -
		// - of land for solid representation.
		if ( solidOn )
		{
			landMesh -> SetVertices( towerGroups[ 0 ][ side ], 0, 6,
														towerVertices );
			landMesh -> SetGroupQuality( towerGroups[ 0 ][ side ],
															solidStyle );

			// Colour the tower face brown.
			landMesh -> SetGroupColor( towerGroups[ 0 ][ side ], RGB_BROWN );
		}


		if ( wireframeOn )
		{
			// Complete the production of the patch of land.
			landMesh -> SetVertices( towerGroups[ 1 ][ side ], 0, 6,
													towerVertices );
			landMesh -> SetGroupQuality( towerGroups[ 1 ][ side ],
											D3DRMRENDER_WIREFRAME );

			// Set the wireframe landscape colour.
			if ( solidOn )
			{
				// Black.
				landMesh -> SetGroupColor( towerGroups[ 1 ][ side ],
															RGB_BLACK );
			}
			else
			{
				// If there is no solid land, colour -
				// - the wireframe black for clarity.
				landMesh -> SetGroupColor( towerGroups[ 1 ][ side ],
															RGB_BLACK );
			}
		}
	}
}


// Generate some altitudes to shape the landscape.
void BoidsLand::calcHeights( )
{
	srand( time( 0 ) );  // Initialise random number generation.

	for ( int row = 0; row < LAND_Z_SIZE + 1; row++ )
	{
		for ( int col = 0; col < LAND_X_SIZE + 1; col++ )
		{
			landHeights[ row ][ col ] = rand( ) % LAND_Y_SIZE;
		}
	}
}


// Calculate the normals for all the face of the patches of land.
void BoidsLand::flatShading( int row, int col, D3DRMVERTEX patchVertices[ ] )
{
	// Calculate the normals for the triangular faces.
	// First make references to the values to simpify the code.
	D3DVALUE &x1 = patchVertices[ 0 ].position.x;
	D3DVALUE &x2 = patchVertices[ 1 ].position.x;
	D3DVALUE &x3 = patchVertices[ 2 ].position.x;
	D3DVALUE &y1 = patchVertices[ 0 ].position.y;
	D3DVALUE &y2 = patchVertices[ 1 ].position.y;
	D3DVALUE &y3 = patchVertices[ 2 ].position.y;
	D3DVALUE &z1 = patchVertices[ 0 ].position.z;
	D3DVALUE &z2 = patchVertices[ 1 ].position.z;
	D3DVALUE &z3 = patchVertices[ 2 ].position.z;

	D3DVALUE &x4 = patchVertices[ 3 ].position.x;
	D3DVALUE &x5 = patchVertices[ 4 ].position.x;
	D3DVALUE &x6 = patchVertices[ 5 ].position.x;
	D3DVALUE &y4 = patchVertices[ 3 ].position.y;
	D3DVALUE &y5 = patchVertices[ 4 ].position.y;
	D3DVALUE &y6 = patchVertices[ 5 ].position.y;
	D3DVALUE &z4 = patchVertices[ 3 ].position.z;
	D3DVALUE &z5 = patchVertices[ 4 ].position.z;
	D3DVALUE &z6 = patchVertices[ 5 ].position.z;

	// Produce two vectors from the first triangle.
	D3DVECTOR v1, v2, v3;
	v1.x = x3 - x2;
	v1.y = y3 - y2;
	v1.z = z3 - z2;

	v2.x = x1 - x3;
	v2.y = y1 - y3;
	v2.z = z1 - z3;

	// Find the cross product of the two vectors.
	D3DRMVectorCrossProduct( &v3, &v1, &v2 );
	// Normalise the resultant vector.
	D3DRMVectorNormalize( &v3 );

	// Set the normals of the first triangular face.
	patchFaceNormals[ row ][ col ][ 0 ] = v3;

	// Produce two vectors from the second triangle.
	v1.x = x6 - x5;
	v1.y = y6 - y5;
	v1.z = z6 - z5;

	v2.x = x4 - x6;
	v2.y = y4 - y6;
	v2.z = z4 - z6;

	// Find the cross product of the two vectors.
	D3DRMVectorCrossProduct( &v3, &v1, &v2 );
	// Normalise the resultant vector.
	D3DRMVectorNormalize( &v3 );

	// Set the normals of the second triangular face.
	patchFaceNormals[ row ][ col ][ 1 ] = v3;

	// Set the normals for the trianglar faces for flat shading.
	// First triangle.
	patchVertices[ 0 ].normal = patchFaceNormals[ row ][ col ][ 0 ];
	patchVertices[ 1 ].normal = patchFaceNormals[ row ][ col ][ 0 ];
	patchVertices[ 2 ].normal = patchFaceNormals[ row ][ col ][ 0 ];

	// Second triangle.
	patchVertices[ 3 ].normal = patchFaceNormals[ row ][ col ][ 1 ];
	patchVertices[ 4 ].normal = patchFaceNormals[ row ][ col ][ 1 ];
	patchVertices[ 5 ].normal = patchFaceNormals[ row ][ col ][ 1 ];
}


// Calculate the normals for all the face of the patches of land.
void BoidsLand::towerFlatShading( int side, D3DRMVERTEX towerVertices[ ] )
{
	// Calculate the normals for the triangular faces.
	// First make references to the values to simpify the code.
	D3DVALUE &x1 = towerVertices[ 0 ].position.x;
	D3DVALUE &x2 = towerVertices[ 1 ].position.x;
	D3DVALUE &x3 = towerVertices[ 2 ].position.x;
	D3DVALUE &y1 = towerVertices[ 0 ].position.y;
	D3DVALUE &y2 = towerVertices[ 1 ].position.y;
	D3DVALUE &y3 = towerVertices[ 2 ].position.y;
	D3DVALUE &z1 = towerVertices[ 0 ].position.z;
	D3DVALUE &z2 = towerVertices[ 1 ].position.z;
	D3DVALUE &z3 = towerVertices[ 2 ].position.z;

	D3DVALUE &x4 = towerVertices[ 3 ].position.x;
	D3DVALUE &x5 = towerVertices[ 4 ].position.x;
	D3DVALUE &x6 = towerVertices[ 5 ].position.x;
	D3DVALUE &y4 = towerVertices[ 3 ].position.y;
	D3DVALUE &y5 = towerVertices[ 4 ].position.y;
	D3DVALUE &y6 = towerVertices[ 5 ].position.y;
	D3DVALUE &z4 = towerVertices[ 3 ].position.z;
	D3DVALUE &z5 = towerVertices[ 4 ].position.z;
	D3DVALUE &z6 = towerVertices[ 5 ].position.z;

	// Produce two vectors from the first triangle.
	D3DVECTOR v1, v2, v3;
	v1.x = x3 - x2;
	v1.y = y3 - y2;
	v1.z = z3 - z2;

	v2.x = x1 - x3;
	v2.y = y1 - y3;
	v2.z = z1 - z3;

	// Find the cross product of the two vectors.
	D3DRMVectorCrossProduct( &v3, &v1, &v2 );
	// Normalise the resultant vector.
	D3DRMVectorNormalize( &v3 );

	// Set the normals of the first triangular face.
	towerFaceNormals[ side ][ 0 ] = v3;

	// Produce two vectors from the second triangle.
	v1.x = x6 - x5;
	v1.y = y6 - y5;
	v1.z = z6 - z5;

	v2.x = x4 - x6;
	v2.y = y4 - y6;
	v2.z = z4 - z6;

	// Find the cross product of the two vectors.
	D3DRMVectorCrossProduct( &v3, &v1, &v2 );
	// Normalise the resultant vector.
	D3DRMVectorNormalize( &v3 );

	// Set the normals of the second triangular face.
	towerFaceNormals[ side ][ 1 ] = v3;

	// Set the normals for the trianglar faces for flat shading.
	// First triangle.
	towerVertices[ 0 ].normal = towerFaceNormals[ side ][ 0 ];
	towerVertices[ 1 ].normal = towerFaceNormals[ side ][ 0 ];
	towerVertices[ 2 ].normal = towerFaceNormals[ side ][ 0 ];

	// Second triangle.
	towerVertices[ 3 ].normal = towerFaceNormals[ side ][ 1 ];
	towerVertices[ 4 ].normal = towerFaceNormals[ side ][ 1 ];
	towerVertices[ 5 ].normal = towerFaceNormals[ side ][ 1 ];
}


// Calculate the normals for all the vertices of the patches of land.
void BoidsLand::gouraudShading( )
{
	// Local buffer for storing the current patches details.
	D3DRMVERTEX patchVertices[ 6 ];
	D3DVECTOR averageNormal;
	int faces;

	// Iterate through the patches of land on the landscape.
	for ( int row = 0; row < LAND_Z_SIZE; row++ )
	{
		for ( int col = 0; col < LAND_X_SIZE; col++ )
		{
			// Get the current state of the current vertex.
			landMesh -> GetVertices( patchGroups[ 0 ][ row ][ col ],
													0, 6, patchVertices );

			// Recalculate the normals from vertices 0 & 3.
			// Find the average of the face normals surrounding the vertex.
			averageNormal.x = 0;
			averageNormal.y = 0;
			averageNormal.z = 0;
			faces = 0;

			// Working round in a clockwise direction -
			// - starting from the current face.
			D3DRMVectorAdd( &averageNormal, &averageNormal,
									&patchFaceNormals[ row ][ col ][ 1 ] );
			D3DRMVectorAdd( &averageNormal, &averageNormal,
									&patchFaceNormals[ row ][ col ][ 0 ] );
			faces += 2;
			if ( row > 0 )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row - 1 ][ col ][ 0 ] );
				faces++;
			}
			if ( row > 0 && col > 0 )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row - 1 ][ col - 1 ][ 1 ] );
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row - 1 ][ col - 1 ][ 0 ] );
				faces += 2;
			}
			if ( col > 0 )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row ][ col - 1 ][ 1 ] );
				faces++;
			}

			averageNormal.x /= faces;
			averageNormal.y /= faces;
			averageNormal.z /= faces;
			// Normalise the resultant vector.
			D3DRMVectorNormalize( &averageNormal );
			// Update the normal of vertex 0.
			patchVertices[ 0 ].normal = averageNormal;
			// Update the normal of vertex 3.
			patchVertices[ 3 ].normal = averageNormal;


			// Recalculate the normal from vertex 1.
			// Find the average of the face normals surrounding the vertex.
			averageNormal.x = 0;
			averageNormal.y = 0;
			averageNormal.z = 0;
			faces = 0;


			// Working round in a clockwise direction -
			// - starting from the current face.
			D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row ][ col ][ 0 ] );
			faces++;
			if ( col > 0 )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row ][ col - 1 ][ 1 ] );
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row ][ col - 1 ][ 0 ] );
				faces += 2;
			}
			if ( col > 0 && ( ( row + 1 ) < LAND_Z_SIZE ) )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row + 1 ][ col - 1 ][ 1 ] );
				faces++;
			}
			if ( ( row + 1 ) < LAND_Z_SIZE )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row + 1 ][ col ][ 0 ] );
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row + 1 ][ col ][ 1 ] );
				faces += 2;
			}

			averageNormal.x /= faces;
			averageNormal.y /= faces;
			averageNormal.z /= faces;
			// Normalise the resultant vector.
			D3DRMVectorNormalize( &averageNormal );
			// Update the normal of vertex 1.
			patchVertices[ 1 ].normal = averageNormal;


			// Recalculate the normals from vertices 2 & 4.
			// Find the average of the face normals surrounding the vertex.
			averageNormal.x = 0;
			averageNormal.y = 0;
			averageNormal.z = 0;
			faces = 0;


			// Working round in a clockwise direction -
			// - starting from the current face.
			D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row ][ col ][ 1 ] );
			D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row ][ col ][ 0 ] );
			faces += 2;
			if ( ( row + 1 ) < LAND_Z_SIZE )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row + 1 ][ col ][ 1 ] );
				faces++;
			}
			if ( ( row + 1 ) < LAND_Z_SIZE && ( col + 1 ) < LAND_X_SIZE )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row + 1 ][ col + 1 ][ 0 ] );
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row + 1 ][ col + 1 ][ 1 ] );
				faces += 2;
			}
			if ( ( col + 1 ) < LAND_X_SIZE )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row ][ col + 1 ][ 0 ] );
				faces++;
			}

			averageNormal.x /= faces;
			averageNormal.y /= faces;
			averageNormal.z /= faces;
			// Normalise the resultant vector.
			D3DRMVectorNormalize( &averageNormal );
			// Update the normal of vertex 2.
			patchVertices[ 2 ].normal = averageNormal;
			// Update the normal of vertex 4.
			patchVertices[ 4 ].normal = averageNormal;


			// Recalculate the normal from vertex 5.
			// Find the average of the face normals surrounding the vertex.
			averageNormal.x = 0;
			averageNormal.y = 0;
			averageNormal.z = 0;
			faces = 0;


			// Working round in a clockwise direction -
			//- starting from the current face.
			D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row ][ col ][ 1 ] );
			faces++;
			if ( ( col + 1 ) < LAND_X_SIZE )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row ][ col + 1 ][ 0 ] );
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row ][ col + 1 ][ 1 ] );
				faces += 2;
			}
			if ( row > 0 && ( ( col + 1 ) < LAND_X_SIZE ) )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
							&patchFaceNormals[ row - 1 ][ col + 1 ][ 0 ] );
				faces++;
			}
			if ( row > 0 )
			{
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row - 1 ][ col ][ 1 ] );
				D3DRMVectorAdd( &averageNormal, &averageNormal,
								&patchFaceNormals[ row - 1 ][ col ][ 0 ] );
				faces += 2;
			}

			averageNormal.x /= faces;
			averageNormal.y /= faces;
			averageNormal.z /= faces;
			// Normalise the resultant vector.
			D3DRMVectorNormalize( &averageNormal );
			// Update the normal of vertex 5.
			patchVertices[ 5 ].normal = averageNormal;

			// Store the state of the current vertex.
			landMesh -> SetVertices( patchGroups[ 0 ][ row ][ col ],
													0, 6, patchVertices );
		}
	}
}


// Deconstruct the landscape.
void BoidsLand::deconstruct( )
{
	// Abort the function if no landscape exists.
    if ( exists == false )
	{
		return;
	}

	// First turn off the landscape existance flag.
	// This is important because the boids will reference it.
	exists = false;


	// Release the land patch COM interface gracefully.
	landFrame -> DeleteVisual( landMesh );
	landMesh -> Release( );
	landMesh = NULL;


	if ( landFrame )
	{
		landFrame -> Release( );
		landFrame = NULL;
	}
}


// Remove the landscape.
void BoidsLand::renderNone( )
{
	// Deconstruct the landscape.
	deconstruct( );

	solidOn = false;  // Update the flags.
	wireframeOn = false;
}


// Toggle the style of the landscape.
void BoidsLand::toggleWireframe( )
{
	// Deconstruct the landscape.
	if ( landFrame )
	{
		deconstruct( );
	}

	// Perform the toggle.
	if ( wireframeOn )
	{
		wireframeOn = false;  // Update the flag.
	}
	else
	{
		wireframeOn = true;  // Update the flag.
	}

	// Re-build the landscape if required.
	if ( solidOn || wireframeOn )
	{
		build( window, d3drm, scene, solidStyle );
	}
}


// Toggle the style of the landscape.
void BoidsLand::toggleUnlitFlat( )
{
	// Deconstruct the landscape.
	if ( landFrame )
	{
		deconstruct( );
	}

	// Perform the toggle.
	if ( solidStyle == D3DRMRENDER_UNLITFLAT && solidOn == true )
	{
		solidOn = false;  // Update the flag.
	}
	else
	{
		solidStyle = D3DRMRENDER_UNLITFLAT;  // Update the style.
		solidOn = true;  // Update the flag.
	}

	// Re-build the landscape if required.
	if ( solidOn || wireframeOn )
	{
		build( window, d3drm, scene, solidStyle );
	}
}


// Toggle the style of the landscape.
void BoidsLand::toggleFlat( )
{
	// Deconstruct the landscape.
	if ( landFrame )
	{
		deconstruct( );
	}

	// Perform the toggle.
	if ( solidStyle == D3DRMRENDER_FLAT && solidOn == true )
	{
		solidOn = false;  // Update the flag.
	}
	else
	{
		solidStyle = D3DRMRENDER_FLAT;  // Update the style.
		solidOn = true;  // Update the flag.
	}

	// Re-build the landscape if required.
	if ( solidOn || wireframeOn )
	{
		build( window, d3drm, scene, solidStyle );
	}
}


// Toggle the style of the landscape.
void BoidsLand::toggleGouraud( )
{
	// Deconstruct the landscape.
	if ( landFrame )
	{
		deconstruct( );
	}

	// Perform the toggle.
	if ( solidStyle == D3DRMRENDER_GOURAUD && solidOn == true )
	{
		solidOn = false;  // Update the flag.
	}
	else
	{
		solidStyle = D3DRMRENDER_GOURAUD;  // Update the style.
		solidOn = true;  // Update the flag.
	}

	// Re-build the landscape if required.
	if ( solidOn || wireframeOn )
	{
		build( window, d3drm, scene, solidStyle );
	}
}


// Set the colour of the solid landscape.
void BoidsLand::setSolidColour( SolidColourEnum colour )
{
	// Re-build the landscape if required.
	if ( !solidOn || solidColour != colour )
	{
		// Deconstruct the landscape.
		deconstruct( );

		solidOn = true;  // Update the flag.
		solidColour = colour;  // Set the colour.

		build( window, d3drm, scene, solidStyle );
	}
}


// Destroy, recalculate and redraw the landscape.
void BoidsLand::recalculate( )
{
	// Deconstruct the landscape.
	if ( landFrame )
	{
		deconstruct( );
	}

	// Call the member function to produce the landscape altitudes.
	calcHeights( );

	// If the lanscape is not present, bring it back as a wireframe -
	// - to show the recalculation.
	if ( solidOn == false && wireframeOn == false )
	{
		wireframeOn = true;
	}

	// Re-build the landscape.
	build( window, d3drm, scene, solidStyle );
}


// Perform a calculation to determine if a given point is below the surface.
bool BoidsLand::getBelowSurface( D3DVALUE x, D3DVALUE y, D3DVALUE z )
{
	// 1. Find the correct patch of land on the landscape.
	// Find the column number of the landscape patch.
	int col =  (double)( x + X_LIMIT ) / (double)xSpacing;
	// Find the row number of the landscape patch.
	int row = (double)( z + Z_LIMIT ) / (double)zSpacing;

	if ( col < 0 )
	{
		col++;  // Adjust for lost precision purposes.
	}
	if ( col == LAND_X_SIZE )
	{
		col--;  // Adjust for lost precision purposes.
	}
	if ( row < 0 )
	{
		row++;  // Adjust for lost precision purposes.
	}
	if ( row == LAND_Z_SIZE )
	{
		row--;  // Adjust for lost precision purposes.
	}


	// Local buffer for storing the current patches vertex zero.
	D3DRMVERTEX patchVertices[ 6 ];
	// Make sure that the correct patch of land is being used.
	do
	{
		// Find the position of point 0 of the landscape patch.
		if ( solidOn )
		{
			// Get the solid patch.
			landMesh -> GetVertices( patchGroups[ 0 ][ row ][ col ],
													0, 6, patchVertices );
		}
		else
		{
			// Get the wireframe patch.
			landMesh -> GetVertices( patchGroups[ 1 ][ row ][ col ],
													0, 6, patchVertices );
		}


		if ( x < patchVertices[ 0 ].position.x )
		{
			col--;
		}
		if ( x > patchVertices[ 2 ].position.x )
		{
			col++;
		}
		if ( z < patchVertices[ 0 ].position.z )
		{
			row--;
		}
		if ( z > patchVertices[ 2 ].position.z )
		{
			row++;
		}
	}
	while( !( x >= patchVertices[ 0 ].position.x &&
			  x <= patchVertices[ 2 ].position.x &&
			  z >= patchVertices[ 0 ].position.z &&
			  z <= patchVertices[ 2 ].position.z ) );


	// 2. Find the correct triangle within that patch of land.
	// 2.1 Calculate the z/x gradient of the division between the triangles.
	D3DVALUE gradient = (double)zSpacing / (double)xSpacing;
	// 2.2 Subtract the X & Z position of vertex 0 from the points position.
	D3DVALUE tempX = x - patchVertices[ 0 ].position.x;
	D3DVALUE tempZ = z - patchVertices[ 0 ].position.z;
	// 2.3 Multiply the X position by the gradient -
	// - to find the dividing lines Z position.
	D3DVALUE zBorder = (double)tempX * (double)gradient;
	// 2.4 Compare the positions to see which triangle the point lies in.
	bool upperTriangle = false;
	if ( tempZ >= zBorder )
	{
		upperTriangle = true;
	}


	// 3. Determine wether the point lies -
	// - below the triangle's surface plane.
	// 3.1 Get the heights of the appropiate triangle.
	D3DVALUE x1, x2, x3, y1, y2, y3, z1, z2, z3;

	if ( upperTriangle )
	{
		x1 = patchVertices[ 0 ].position.x;
		x2 = patchVertices[ 1 ].position.x;
		x3 = patchVertices[ 2 ].position.x;
		y1 = patchVertices[ 0 ].position.y;
		y2 = patchVertices[ 1 ].position.y;
		y3 = patchVertices[ 2 ].position.y;
		z1 = patchVertices[ 0 ].position.z;
		z2 = patchVertices[ 1 ].position.z;
		z3 = patchVertices[ 2 ].position.z;
	}
	else
	{
		x1 = patchVertices[ 3 ].position.x;
		x2 = patchVertices[ 4 ].position.x;
		x3 = patchVertices[ 5 ].position.x;
		y1 = patchVertices[ 3 ].position.y;
		y2 = patchVertices[ 4 ].position.y;
		y3 = patchVertices[ 5 ].position.y;
		z1 = patchVertices[ 3 ].position.z;
		z2 = patchVertices[ 4 ].position.z;
		z3 = patchVertices[ 5 ].position.z;
	}

	return getBelowPlane( x, y, z, x1, x2, x3, y1, y2, y3, z1, z2, z3 );
}


// Mathematical function to determine if a 3D point lies below a plane
// that is represented by three vertices.
bool BoidsLand::getBelowPlane( D3DVALUE x, D3DVALUE y, D3DVALUE z,
							D3DVALUE x1, D3DVALUE x2, D3DVALUE x3,
							D3DVALUE y1, D3DVALUE y2, D3DVALUE y3,
							D3DVALUE z1, D3DVALUE z2, D3DVALUE z3 )
{
	// Calculate the plane's coefficients.
	D3DVALUE a, b, c, d;

	a = y1 * ( z2 - z3 ) + y2 * ( z3 - z1 ) + y3 * ( z1 - z2 );
	b = z1 * ( x2 - x3 ) + z2 * ( x3 - x1 ) + z3 * ( x1 - x2 );
	c = x1 * ( y2 - y3 ) + x2 * ( y3 - y1 ) + x3 * ( y1 - y2 );
	d = -x1 * ( y2 * z3 - y3 * z2 ) + -x2 * ( y3 * z1 - y1 * z3 )
										+ -x3 * ( y1 * z2 - y2 * z1 );

	// Using the plane equation:  a * x + b * y + c * z + d = 0.
	D3DVALUE surfaceYValue = ( ( -a * x ) - ( c * z ) - d ) / b;

	// Return the correct answer.
	if ( y < surfaceYValue )
	{
		return true;
	}
	else
	{
		return false;
	}
}
