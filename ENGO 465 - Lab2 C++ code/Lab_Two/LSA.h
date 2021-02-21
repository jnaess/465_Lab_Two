#pragma once

#include "Measurement.h"
#include "rinex.h"
#include "NRinexUtils.h"
#include "Epoch.h"
#include "LSA.h"

using namespace std;
using namespace NGSrinex;
using namespace NRinexUtils;

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace Eigen;

class LSA {
    friend class Epoch;
    public:

    //Constructor
    LSA();

    int N_sat;          //number of satellites/number of observations
    int N_iter=0;       //number of iterations

    MatrixXd l_o;       //pseudorange observations
    MatrixXd x_o;       //initial estimate. Parameters x, y, z, t
    MatrixXd satpos;    //x y z coordinates of satellites
    MatrixXd C_l;       //variance matrix of observations
    MatrixXd P;         //weight matrix
    double apriori=1;   //apriori variance factor
    MatrixXd N;         //normal equations matrix
    MatrixXd U;         //intermediate calculation
    MatrixXd x_cap;     //corrected parameters
    MatrixXd l_cap;     //corrected observations
    MatrixXd delta;     //correction vector
    MatrixXd A;         //design matrix
    MatrixXd w;         //misclosure vector
    MatrixXd Cx;        //variance covariance of estimate
    MatrixXd v;         //residuals
    MatrixXd Qx;        //matrix for DOP = N.inverse()
    MatrixXd QL;        //Qx rotated for NEU
    double GDOP;        //geometric dilution of precision
    double PDOP;        //position DOP
    double HDOP;        //horizontal DOP
    double VDOP;        //vertical DOP
    MatrixXd R;         //Rottion matrix from xyz to neu

    /*Function: copyEpoch2LSA
    Copies observations, satellite positions, and number of satellites from epoch class
    Inputs: Epoch object for current epoch
    Outputs: None
    */
    void copyEpoch2LSA(Epoch epoch);

    /*Function: adjustment
    Runs an iterative least squares adjustment
    Inputs: None
    Outputs: None
    */
    void adjustment();

    /*Function: designA
    Populates design matrix, A
    Inputs: None
    Outputs: None
    */
    void designA();

    /*Function: misclosure
    Populates misclosure vector
    Inputs: None
    Outputs: None
    */
    void misclosure();

    /*Function: weights
    Populates variance matrix of observations and weight matrix
    Assumes uniform variances for all observations
    Inputs: None
    Outputs: None
    */
    void weights();

    /*Function: precision
    Calculates values of precision, including Cx, Qx, and DOP
    Inputs: None
    Outputs: None
    */
    void precision(MatrixXd truepos);

    /*Function: output_x
    Writes position of reciever to a text file, one line per epoch
    Inputs: name of file
    Outputs: None
    */
    void output_x(string name);

    /*Function: output_DOP
    Writes DOP values to a text file, one line per epoch
    Inputs: name of file
    Outputs: None
    */
    void output_DOP(string name);

    /*Function: output_sigma
    Writes standard deviation values to a text file, E, N, U. one line per epoch
    Inputs: name of file
    Outputs: None
    */
    void output_sigma(string name);
};
    /*Function: print_mat
    Prints matrix to console
    Inputs: MatrixXd to be printed and string for a label
    Outputs: None
    */
    void print_mat(MatrixXd mat, string name);

