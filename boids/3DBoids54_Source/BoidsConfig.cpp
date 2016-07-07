/*	Filename:		BoidsConfig.cpp
	Author:			Robert Platt
	Creation date:	23/01/2000
	Modified:		13/05/2000
	Version:		0.54
	Description:	Implementation file for the boids configuration class.
*/


#include "BoidsConfig.h"


// Constructor.
BoidsConfig::BoidsConfig( )
{
	// Create an empty configuration file.
	nFlyers = 0;
}


// Overloaded Constructor.
BoidsConfig::BoidsConfig( vector< Flyer * > &f )
{
	fConfigs = f;
	nFlyers = fConfigs.size( );
}


// Load in a configuration.
void BoidsConfig::loadConfig( CString f )
{
	char text[ TEXT_BUFFER_SIZE ];

	// Clear the vector.
	fConfigs.clear( );

	// Open the file in read only mode.
	ifstream dataFile( f, ios::in );

	// Read the file up to the first number.
	scanToNext( dataFile );

	// Read in the number of flyers.
	dataFile.read( reinterpret_cast<char *>( text ), CONFIG_FIELD_SIZE );
	// Convert the string to an integer and store in the class.
	nFlyers = atoi( text );


	// Read in all the data about the individual flyers.
	// The order is specified by the format of the config file.
	Flyer *fPtr;
	for ( int number = 0; number < nFlyers; number++ )
	{
		// Make a new Flyer structure in memory;
		fPtr = new Flyer( );

		// Read in the X pos.
		fPtr -> xPos = readNextInt( dataFile );

		// Read in the horizontal heading.
		fPtr -> hHeading = readNextInt( dataFile );

		// Read in the required horizontal heading.
		fPtr -> reqHHeading = readNextInt( dataFile );

		// Read in the Y pos.
		fPtr -> yPos = readNextInt( dataFile );

		// Read in the vertical heading.
		fPtr -> vHeading = readNextInt( dataFile );

		// Read in the required vertical heading.
		fPtr -> reqVHeading = readNextInt( dataFile );

		// Read in the Z pos.
		fPtr -> zPos = readNextInt( dataFile );

		// Read in the speed.
		fPtr -> speed = readNextInt( dataFile );

		// Read in the required speed.
		fPtr -> reqSpeed = readNextInt( dataFile );


		// Add a pointer to the Flyer structure to the vector.
		fConfigs.push_back( fPtr );
	}


	return;
}


// Scan to the next number, by finding the '>' character.
void BoidsConfig::scanToNext( ifstream &file )
{
	char c[ 1 ];

	// Read the file up to the first number.
	do
	{
		file.read( reinterpret_cast<char *>( c ), 1 );
	}
	while( c[ 0 ] != '>' );
}


// read the next int.
int BoidsConfig::readNextInt( ifstream &file )
{
	int number;
	int polarity;
	char text[ CONFIG_FIELD_SIZE ];

	// Scan to the next number.
	scanToNext( file );
	// Read the polarity of the number.
	file.read( reinterpret_cast<char *>( text ), 1 );

	// Interpret the polarity.
	if ( text[ 0 ] == '+' )
	{
		polarity = +1;
	}
	else
	{
		polarity = -1;
	}

	// Read the four numeric digits.
	file.read( reinterpret_cast<char *>( text ), CONFIG_FIELD_SIZE );
	// Convert the text to an integer.
	number = atoi( text );
	// Apply the polarity to the integer.
	number *= polarity;

	return number;
}


// Save a configuration.
void BoidsConfig::saveConfig( CString f )
{
	// Open the config file for output, overwriting any previous data.
	ofstream dataFile( f, ios::out );


	// Write the header for the config file.
	CString text = "3D Boids V";
	text += VERSION;
	text += " Configuration File\n\n";

	// Write the number of flyers.
	// First write the data label.
	text += "Number of Flyers ";
	// Next write the number in character format.
	text += convertInt( nFlyers, false, true );

	// Write a couple of blank lines.
	text += "\n\n";
	dataFile.write( reinterpret_cast<const char *>
				( text.GetBuffer( TEXT_BUFFER_SIZE ) ), text.GetLength( ) );


	// Write out all the flyers data.
	Flyer flr;
	for ( int number = 0; number < nFlyers; number++ )
	{
		flr = *fConfigs[ number ];  // Get a pointer to a flyer.

		// First write out the number of the flyer.
		text = "Flyer ";
		text += convertInt( number + 1, false, false );
		text += "\n";

		// Then the flyer's details.
		text += "    X pos ";
		text += convertInt( flr.xPos, true, true );
		text += "    H Heading ";
		text += convertInt( flr.hHeading, true, true );
		text += "    req H Heading ";
		text += convertInt( flr.reqHHeading, true, true );
		text += "\n";


		text += "    Y pos ";
		text += convertInt( flr.yPos, true, true );
		text += "    V Heading ";
		text += convertInt( flr.vHeading, true, true );
		text += "    req V Heading ";
		text += convertInt( flr.reqVHeading, true, true );
		text += "\n";


		text += "    Z pos ";
		text += convertInt( flr.zPos, true, true );
		text += "    Speed     ";
		text += convertInt( flr.speed, true, true );
		text += "    req Speed     ";
		text += convertInt( flr.reqSpeed, true, true );
		text += "\n";

		// Write a couple of blank lines.
		text += "\n\n";
		dataFile.write( reinterpret_cast<const char *>
				( text.GetBuffer( TEXT_BUFFER_SIZE ) ), text.GetLength( ) );
	}

	return;
}


// Function to convert an interger to a CString.
// The extras flag adds braces and a sign to the number.
CString BoidsConfig::convertInt( int i, bool sign, bool braces )
{
	CString letters;
	char buffer[ TEXT_BUFFER_SIZE ];

	_itoa( i, buffer, 10 );
	letters = buffer;

	// Insert zeros if needed.
	if ( i >= 0 )
	{
		// If the number is less than 1000 insert a '0'.
		if ( i < 1000 )
		{
			letters.Insert( 0, '0' );
		}
		// If the number is less than 100 insert a '0'.
		if ( i < 100 )
		{
			letters.Insert( 0, '0' );
		}
		// If the number is less than 10 insert a '0'.
		if ( i < 10 )
		{
			letters.Insert( 0, '0' );
		}

		if ( sign )
		{
			// Plus sign.
			letters.Insert( 0, '+' );
		}
	}
	else
	{
		// If the number is less than 1000 insert a '0'.
		if ( i > -1000 )
		{
			letters.Insert( 1, '0' );
		}
		// If the number is less than 100 insert a '0'.
		if ( i > -100 )
		{
			letters.Insert( 1, '0' );
		}
		// If the number is less than 10 insert a '0'.
		if ( i > -10 )
		{
			letters.Insert( 1, '0' );
		}
	}


	if ( braces )
	{
		// Place the number in >< braces.
		letters.Insert( 0, '>' );
		letters += '<';
	}


	return letters;
}
