#pragma once

#include "rinex.h"
#include "NRinexUtils.h"
#include "Epoch.h"

using namespace std;
using namespace NGSrinex;
using namespace NRinexUtils;

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>

using namespace Eigen;

class data {

	public:

    vector<Epoch> Epochs;

    //generates a value for every 15 minutes based off of the nearest epoch value
    vector<Epoch> oneDayNearest;

    //Generates a value for every 15 minutes based off of the first epoch value
    vector<Epoch> oneDayFirst;

    double currEpoch;

    MatrixXd truepos;

    /*
    Definition:
        Default contructor, does nothing
    Input:

    Output:

    */
    data();

    /*
    Definition:
        Adds an epoch to the epoch list
    Input:

    Output:

    */
    void add_epoch(
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
        Find the nearest epoch value
    Input:
        relative time
    Output:
        reference of the nearest epoch
    */
    Epoch& nearest(double time);

    /*
    Definition:
        defines alll 96 epichs based off of the first one
    Input:
        none
    Output:
        oneDayNearest is constructed
    */
    void generateOneDayFirst();

};
