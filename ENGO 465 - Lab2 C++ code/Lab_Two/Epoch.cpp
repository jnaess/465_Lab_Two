#include "Epoch.h"

Epoch::Epoch(){
}

Epoch::Epoch(double T,
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
        double cus){
    t = T;
     toe = Toe;
     sqrt_A = Sqrt_A;
     M_0 = m_0;
     w = W;
     i_0 = I_0;
     i_dot = I_dot;
     r = R;
     n_delta = N_delta;
     L_0 = l_0;
     L_dot = l_dot;
     Crs = crs;
     Crc = crc;
     Cis = cis;
     Cic = cic;
     Cuc = cuc;
     Cus = cus;

    computePosition();
}

void Epoch::computePosition(){
    computeTime(); // relative time


    A = pow(sqrt_A,2); //Semi-major axis
    n_0 = sqrt(u/(pow(A,3))); // computed mean motion
    n = n_0 + n_delta; //corrected mean motion
    Mk = correctRange(M_0 + n*tk); //Mean anomaly [0,2PI]
    eccentricAnomaly(); //kepler's equation for eccentric anomaly
    vk = correctRange(atan2(sqrt(1.0-pow(r,2))*sin(Ek),(cos(Ek)-r)));
    Dk = w + vk; //argument of latitude
    secondHarmonicPertubations(); //second harmonic pertubations
    uk = Dk + SHP(0,0); //corrected argument of latitude
    rk = A*(1.0-r*cos(Ek))+ SHP(1,0); //corrected radius
    ik = i_0 + i_dot*tk + SHP(2,0); // positions in orbital plane

    Lk = (L_0-Le*toe) + (L_dot-Le)*tk; //Corrected longitude of ascending node
    Lk = fmod(Lk,2.0*PI);

    POP(0,0) = rk*cos(uk); //Positions in orbital plane [xk', yk']^T
    POP(1,0) = rk*sin(uk);

    EFC(0,0) = POP(0,0)*cos(Lk) - POP(1,0)*sin(Lk)*cos(ik); //earth fixed coordinates [xk, yk, zk]^T
    EFC(1,0) = POP(0,0)*sin(Lk) + POP(1,0)*cos(Lk)*cos(ik);
    EFC(2,0) = POP(1,0)*sin(ik);
}

void Epoch::computeTime(){
    tk = t - toe;
}

double Epoch::correctRange(double x){
    while (x >= 2.0*PI || x < 0.0){
        if (x >= 2.0*PI){
            x -= 2.0*PI;
        }
        if (x < 0.0){
            x += 2.0*PI;
        }
    }
    return x;
}

void Epoch::eccentricAnomaly(){
    Ek = Mk;
    for(int i=0; i<6; i++){
        Ek = Mk + r*sin(Ek);
    }
}

void Epoch::secondHarmonicPertubations(){
    SHP(0,0) = Cuc*cos(2.0*Dk)+Cus*sin(2.0*Dk);
    SHP(1,0) = Crc*cos(2.0*Dk)+Crs*sin(2.0*Dk);
    SHP(2,0) = Cic*cos(2.0*Dk)+Cis*sin(2.0*Dk);
}

void Epoch::printValues(){
    cout << "____________Input Values____________" << setprecision(15) << endl;
    cout << "toe: " <<  toe << endl;
    cout << "sqrt_A: " <<  sqrt_A << endl;
    cout << "M_0: " << M_0  << endl;
    cout << "w: " << w  << endl;
    cout << "i_0: " << i_0 << endl;
    cout << "i_dot: " << i_dot << endl;
    cout << "r: " <<  r << endl;
    cout << "n_delta: " <<  n_delta << endl;
    cout << "L_0: " << L_0  << endl;
    cout << "L_dot: " <<  L_dot << endl;
    cout << "Crs: " << Crs  << endl;
    cout << "Crc: " << Crc  << endl;
    cout << "Cis: " <<  Cis << endl;
    cout << "Cic: " << Cic  << endl;
    cout << "Cuc: " <<  Cuc << endl;
    cout << "Cus: " <<  Cus << endl;


    cout << "____________Calculated Values____________" << endl;
    cout << "A: " <<  A << endl;
    cout << "n_0: " <<  n_0 << endl;
    cout << "tk: " << tk  << endl;
    cout << "n: " << n  << endl;
    cout << "Mk: " << Mk  << endl;
    cout << "Ek: " <<  Ek << endl;
    cout << "vk: " << vk  << endl;
    cout << "Dk: " <<  Dk << endl;
    cout << "SHP: " << endl; cout << SHP;
    cout << "uk: " <<  uk << endl;
    cout << "rk: " << rk  << endl;
    cout << "ik: " << ik  << endl;
    cout << "POP: " << endl; cout << POP;
    cout << "Lk: " <<  Lk << endl;
    cout << "EFC: " << endl; cout << EFC;
}
