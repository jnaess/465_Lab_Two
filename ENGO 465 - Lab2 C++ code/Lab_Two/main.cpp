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
#include <sstream>
#include <Eigen/Dense>

#include "rinex.h"
#include "NRinexUtils.h"
#include "Epoch.h"
#include "data.h"

using namespace std;
using namespace NGSrinex;
using namespace Eigen;


int main()
{
    /*double toe = 345600.0; //time of ephemeris
        double sqrt_A = 5153.57253456;  //square root of semi-major axis
        double M_0 = -2.12119123046; //mean anomaly at reference time
        double w = 1.1686277003; //argument of perigee
        double i_0 = 0.975712564448; //inclination angle at reference time
        double i_dot = 5.53594488004e-11; //rate of inclination angle
        double r = 0.00817955180537; //eccentricity
        double n_delta = 4.61769234542e-09; //mean motion difference from computed value
        double L_0 = -2.96572093029; //longitude of ascending node of orbit plane at weekly epoch
        double L_dot = -8.1674830656e-09; //rate of ascension
        double Crs = 35.78125; //sine harmonic correction terms of orbit radius
        double Crc = 300.09375; //cosine harmonic correction terms of orbit radius
        double Cis = 1.86264514923e-09; //sine harmonic correction terms of the angle of inclination
        double Cic = 9.685754776e-08; //cosine harmonic correction terms of the angle of inclination
        double Cuc = 1.89244747162e-06; //cosine harmonic correction terms of the argument latitude
        double Cus = 4.51505184174e-06;//sine harmonic correction terms of the argument of latitude

    cout << "Making Epoch" << endl;
    Epoch test = Epoch(toe, toe,sqrt_A,M_0,w,i_0,i_dot,r,n_delta,L_0,L_dot,Crs,Crc,Cis,Cic,Cuc,Cus);
    cout << "Printing" << endl;
    test.printValues();*/

    data Data = data();
        double toe; //time of ephemeris
        double sqrt_A;  //square root of semi-major axis
        double M_0; //mean anomaly at reference time
        double w; //argument of perigee
        double i_0; //inclination angle at reference time
        double i_dot; //rate of inclination angle
        double r; //eccentricity
        double n_delta; //mean motion difference from computed value
        double L_0; //longitude of ascending node of orbit plane at weekly epoch
        double L_dot; //rate of ascension
        double Crs; //sine harmonic correction terms of orbit radius
        double Crc; //cosine harmonic correction terms of orbit radius
        double Cis; //sine harmonic correction terms of the angle of inclination
        double Cic; //cosine harmonic correction terms of the angle of inclination
        double Cuc; //cosine harmonic correction terms of the argument latitude
        double Cus; //sine harmonic correction terms of the argument of latitude

   // input file names
   string rinexFilename = "brdc0070.21n";

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Get ephemeris data

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
   cout << "here d" << endl;
   try
   {
        cout << "Reading file" << endl;
      // for each set of ephemeris parameters in the RINEX file...
      while( rinexInput.readPRNBlock( currentRinexEph ) != 0 )
      {
         // check for unhealthy satellite
		   if( currentRinexEph.getSvHealth() != 0 )
            continue;

        if( currentRinexEph.getSatellitePRN() == 12){
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
         L_0 =        currentRinexEph.getBigOmega();      // longitude of ascending node at reference time [rad]
         L_dot =        currentRinexEph.getBigOmegaDot();   // rate of longitude of ascending node [rad/s]
         Cic =        currentRinexEph.getCic();           // harmonic correction term for inclination (1 of 2) [rad]
         Cis =        currentRinexEph.getCis();           // harmonic correction term for inclination (2 of 2) [rad]
         Crc =        currentRinexEph.getCrc();           // harmonic correction term for radius (1 of 2) [m]
         Crs =        currentRinexEph.getCrs();           // harmonic correction term for radius (2 of 2) [m]
         Cuc =        currentRinexEph.getCuc();           // harmonic correction term for argument of perigee (1 of 2) [rad]
         Cus =        currentRinexEph.getCus();           // harmonic correction term for argument of perigee (2 of 2) [rad]
         n_delta =        currentRinexEph.getDeltan();        // correction to mean motion [rad/s]
         r =        currentRinexEph.getEccen();         // eccentricity [unitless]
         i_dot =        currentRinexEph.getIdot();          // inclination rate [rad/s]
         i_0 =        currentRinexEph.getIo();            // inclincation at reference time [rad]
         w =       currentRinexEph.getLilOmega();      // argument of perigee [rad]
         M_0 =      currentRinexEph.getMo();            // mean anomaly at reference time [rad]
         sqrt_A =        currentRinexEph.getSqrtA();         // square root of semi-major axis of orbit [sqrt-m]
         toe =       currentRinexEph.getToe();           // reference time, i.e., 'time of ephemeris' [s]
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Data.add_epoch(toe, toe,sqrt_A,M_0,w,i_0,i_dot,r,n_delta,L_0,L_dot,Crs,Crc,Cis,Cic,Cuc,Cus);
        }
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

    //task 2.2
    Data.generateOneDayNearest();

    //task 2.3
    Data.generateOneDayFirst();



   // END: Read the ephemeris data
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   // end of program

   return 0;
}
