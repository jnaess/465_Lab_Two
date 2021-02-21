#pragma once

#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Eigen;
using namespace std;

class Measurement {
	public:

    double epoch;
    int SatNum;
    double X, Y, Z;
    double correction;

    double obs;

    /*
    Definition:
        Default contructor, does nothing
    Input:

    Output:

    */
    Measurement();

    /*
    Definition:
        Assigns the mesurements via
        a string line that is processed
    Input:
        string line: the file line
        double Epoch: the epoch for the line given
    Output:

    */
    Measurement(string line, double Epoch);


    /*
    Definition:
        Reads in the file line to initialize several class variables
    Input:

    Output:

    */
    void readLine(string line);

    /*
    Definition:
        does nothing
    Input:

    Output:

    */
    void Output();

    /*
    Definition:
        sets the observation via a psuerdorange and correction
    Input:

    Output:

    */
    void setObs(double pseudorange);








};

