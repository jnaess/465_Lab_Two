// Summary:
//    Skeleton program to open and read a RINEX ephemeris (navigation) file.  Students in 
//    ENGO 465 will use this to develop code to compute satellite positions at specified times.
//
// History:
//    Feb 04/13 - Created by Mark Petovello
//
// Copyright:
//    Position, Location And Navigation (PLAN) Group
//    Department of Geomatics Engineering
//    Schulich School of Engineering
//    University of Calgary
//
// Disclaimer:
//    This source code is not freeware nor shareware and is only provided under 
//    an agreement between authorized users/licensees and the University of 
//    Calgary (Position, Location And Navigation (PLAN) Group, Geomatics 
//    Engineering, Schulich School of Engineering) and may only be used under 
//    the terms and conditions set forth therein.

#include <iostream>
#include <fstream>

#include "rinex.h"
#include "NRinexUtils.h"

using namespace std;
using namespace NGSrinex;


int main( int argc, char* argv[] )
{
   // input file names
   string rinexFilename;

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Get ephemeris data


   // prompt for RINEX file name
   cout << "Please enter the name of the RINEX ephemeris (navigation) file: ";
   getline( cin, rinexFilename );


   // open the input RINEX file
   RinexNavFile rinexInput;
   if( !NRinexUtils::OpenRinexNavigationFileForInput( rinexInput, rinexFilename ) )
   {
      cout << "NRinexUtils::OpenRinexNavigationFileForInput() - Could not open RINEX file." << endl;
      return 0;
   }


   // END: Get ephemeris data
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Read the ephemeris data

   // current GPS ephemeris data from RINEX file
   NGSrinex::PRNBlock  currentRinexEph;
        

   // read the ephemeris
   try
   {
      // for each set of ephemeris parameters in the RINEX file...
      while( rinexInput.readPRNBlock( currentRinexEph ) != 0 )
      {
         // check for unhealthy satellite
		   if( currentRinexEph.getSvHealth() != 0 )
            continue;


         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         // NOTE: This while loop reads ONE set of the ephemeris parameters for ONE satellite and
         //       stores it in the variable named 'currentRinexEph'.  In other words, this loop 
         //       will have to be executed several times in order to read all sets of ephemeris 
         //       parameters in the file.  It is your decision as to how you handle these 
         //       (e.g., store them all, only store specific ones, do all computations for the 
         //       current parameters and then discard them, etc.), but ultimately, you will need
         //       the parameters to compute the satellite's position.
         //
         //
         //       When you are ready to compute the satellite positions (either in this loop, or
         //       elsewhere in your code), you can access the specific ephemeris parameters using 
         //       the following member functions:
         //
         //       currentRinexEph.getBigOmega();      // longitude of ascending node at reference time [rad]
         //       currentRinexEph.getBigOmegaDot();   // rate of longitude of ascending node [rad/s]
         //       currentRinexEph.getCic();           // harmonic correction term for inclination (1 of 2) [rad]
         //       currentRinexEph.getCis();           // harmonic correction term for inclination (2 of 2) [rad]
         //       currentRinexEph.getCrc();           // harmonic correction term for radius (1 of 2) [m]
         //       currentRinexEph.getCrs();           // harmonic correction term for radius (2 of 2) [m]
         //       currentRinexEph.getCuc();           // harmonic correction term for argument of perigee (1 of 2) [rad]
         //       currentRinexEph.getCus();           // harmonic correction term for argument of perigee (2 of 2) [rad]
         //       currentRinexEph.getDeltan();        // correction to mean motion [rad/s]
         //       currentRinexEph.getEccen();         // eccentricity [unitless]
         //       currentRinexEph.getIdot();          // inclination rate [rad/s]
         //       currentRinexEph.getIo();            // inclincation at reference time [rad]
         //       currentRinexEph.getLilOmega();      // argument of perigee [rad]
         //       currentRinexEph.getMo();            // mean anomaly at reference time [rad]
         //       currentRinexEph.getSqrtA();         // square root of semi-major axis of orbit [sqrt-m]
         //       currentRinexEph.getToe();           // reference time, i.e., 'time of ephemeris' [s]
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   

         // TO BE COMPLETED (here or elsewhere in the code):
         //  - With reference to the lab handout, compute satellite coordinates using the appropriate
         //    ephemeris record at the appropriate times
         //  - Output the computed coordinates to file

      }//for each set of ephemeris parameters in the RINEX file...

   }
   catch( RinexReadingException &readingExcep )
   {
      cout << " RinexReadingException is: " << endl << readingExcep.getMessage() << endl;
   }
   

   // END: Read the ephemeris data
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   // end of program
   return 0;
}
