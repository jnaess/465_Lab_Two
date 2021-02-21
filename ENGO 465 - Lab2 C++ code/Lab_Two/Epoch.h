#pragma once

#include "Measurement.h"
#include "rinex.h"
#include "NRinexUtils.h"

using namespace std;
using namespace NGSrinex;
using namespace NRinexUtils;

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>

using namespace Eigen;

class Epoch {
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

	public:

    /*
    Definition:
        Default contructor, does nothing
    Input:

    Output:

    */
    Epoch();

    /*
    Definition:
        Sets up the Epoch/Epheremis,
    Input:
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
    Output:

    */
    Epoch(
        double Toe,
        double Sqrt_A,
        double m_0,
        double W,
        double I_0,
        double I_dot,
        double R,
        double N_delta,
        double l_0,
        double l_dot,
        double crs,
        double crc,
        double cis,
        double cic,
        double cuc,
        double cus);
};
