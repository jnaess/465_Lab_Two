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
    public:

    double PI = 3.1415926535898;
    double t; //raltive time
    double u = 3.986005E14; //WGS 84 value of the earth's gravitational constant for GPS user
    double Le = 7.2921151467E-5; //WGS 84 value of earth's rotation rate
    double A; //semi-major axis
    double n_0; // computed mean motion
    double tk; //time from ephemeris epoch
    double n; //corrected mean motion
    double Mk; //Mean anomaly [0,2PI]
    double Ek; //kepler's equation for eccentric anomaly
    double vk; //true anomaly [atan2] [0,2pi]
    double Dk; //argument of latitude
    MatrixXd SHP = MatrixXd(3,1); //second harmonic pertubations [uk, rk, ik]^T
    double uk; //corrected argument of latitude
    double rk; //corrected radius
    double ik; // positions in orbital plane
    MatrixXd POP = MatrixXd(2,1); //Positions in orbital plane [xk', yk']^T
    double Lk; //Corrected longitude of ascending node
    MatrixXd EFC = MatrixXd(3,1); //earth fixed coordinates [xk, yk, zk]^T

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
        double T; //time of transmission
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
        double T,
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

    /*
    Definition:
        Computes all neccesary values in order to find the satelites position
    Input:

    Output:

    */
    void computePosition();

    /*
    Definition:
        Compute the relative time using the time correction
    Input:

    Output:

    */
    void computeTime();

    /*
    Definition:
        Makes sure that the range of the value is [0,2PI]
    Input:
        Double
    Output:
        Double within [0,2PI]
    */
    double correctRange(double x);

    /*
    Definition:
        Initialized eccentric anomaly Ek
    Input:
        uses Mk
    Output:
        none
    */
    void eccentricAnomaly();

    /*
    Definition:
        Computes corrections to Keplerian orbit
        Initializes SHP (Second Harmonis Pertubations)
    Input:
        Mk
    Output:
        none
    */
    void secondHarmonicPertubations();

    /*
    Definition:
        Prints the computes and input values
    Input:
        none
    Output:
        none
    */
    void printValues();


};
