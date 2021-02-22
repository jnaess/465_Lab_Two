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
