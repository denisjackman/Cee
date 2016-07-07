/*	Filename:		BoidsConfig.h
	Author:			Robert Platt
	Creation date:	23/01/2000
	Modified:		13/05/2000
	Version:		0.54
	Description:	Header file for the boids configuration class.
*/


#include <vector>  // Also set the namespace for the vector.
#include <fstream>
#include <afxwin.h>
#include <afxdlgs.h>


#include "BoidsWin.h"


#ifndef BOIDS_CONFIG_H
#define BOIDS_CONFIG_H


using namespace std;  // Used for the STL Vector.


const int TEXT_BUFFER_SIZE = 256;
const int CONFIG_FIELD_SIZE = 4;


// Record to store all the boid's details.
struct Flyer
{
	int xPos, yPos, zPos;
	int hHeading, vHeading;
	int reqHHeading, reqVHeading;
	int speed, reqSpeed;
};


// Configuration Class for the Boids Simulation.
class BoidsConfig
{
public:
	BoidsConfig( );
	BoidsConfig( vector< Flyer * > &f );  // Constructor.
	void loadConfig( CString f );  // Load in a configuration.
	void scanToNext( ifstream &file );
	int readNextInt( ifstream &file );
	void saveConfig( CString f );  // Save a configuration.
	CString convertInt( int i, bool sign, bool braces );
	int getNFlyers( ) { return nFlyers; };
	vector< Flyer * > getFConfigs( ) { return fConfigs; };

private:
	int nFlyers;
	// An STL vector for the flyers.
	vector< Flyer * > fConfigs;
};


#endif
