#include "Measurement.h"

//Test comment here
Measurement::Measurement(){
    return;
}

Measurement::Measurement(string line, double Epoch){
    epoch = Epoch;
    readLine(line);
}

void Measurement::readLine(string line){
    string arr[5];
    int i = 0;

    //splits the line from spaces into an array of three
    stringstream ssin(line);
    while (ssin.good() && i < 5){
        ssin >> arr[i];
        ++i;
    }
  //Initiate all values

    SatNum = stoi(arr[0]);

    //assign coordinate values
    //convert string to a long double
    X = stold(arr[1]);
    Y = stold(arr[2]);
    Z = stold(arr[3]);

    //assign correction value
    correction = stold(arr[4]);
}

void Measurement::Output(){
    cout << "epoch: " << epoch << endl;
    cout << "SatNum: " << SatNum << endl;
    cout << "X: " << X << " Y: " << Y << " Z: " << Z << endl;
}

void Measurement::setObs(double pseudorange){
    obs = pseudorange - correction;
}
