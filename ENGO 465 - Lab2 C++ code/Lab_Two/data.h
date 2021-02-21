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
};
