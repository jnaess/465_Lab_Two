#include "Epoch.h"

Epoch::Epoch(){
}

Epoch::Epoch(double Toe,
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
        double cus){
    double toe = Toe;
    double sqrt_A = Sqrt_A;
    double M_0 = m_0;
    double w = W;
    double i_0 = I_0;
    double i_dot = I_dot;
    double r = R;
    double n_delta = N_delta;
    double L_0 = l_0;
    double L_dot = l_dot;
    double Crs = crs;
    double Crc = crc;
    double Cis = cis;
    double Cic = cic;
    double Cuc = cuc;
    double Cus = cus;
}

void Epoch::computePosition(){
    // relative time
    //[incomplete]
    computeTime();


    A = sqrt_A^2; //Semi-major axis
    n_0 = sqrt(u/(A^3)); // computed mean motion
    n = n_0 + n_delta; //corrected mean motion
    Mk = correctRange(M_0 + n*tk); //Mean anomaly [0,2PI]
    Ek; //kepler's equation for eccentric anomaly
}

void Epoch::computeTime(){
    tk = t - toe;
}

double Epoch::correctRange(double x){
    while (x >= 2.0*PI || x < 0.0){
        if (x >= 2.0*PI)
            x -= 2.0*PI;
        if (x < 0.0)
            x += 2.0*PI;
    }
    return x;
}
