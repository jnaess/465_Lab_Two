#include "data.h"

#include <sstream>

//Test comment here
data::data(){

}

void data::add_epoch(
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
                    double cus){
    Epochs.emplace_back(
         T,
         Toe,
         Sqrt_A,
         m_0,
         W,
         I_0,
         I_dot,
         R,
         N_delta,
         l_0,
         l_dot,
         crs,
         crc,
         cis,
         cic,
         cuc,
         cus);
}

Epoch& data::nearest(double time){
    for(int i=1; i<Epochs.size(); i++){
        if(Epochs[i].toe > time){
            //first time that is larger than desired time
            //therefore this is the first large
            //find if large or small is more relavent
            double large = pow((Epochs[i].toe - time),2);
            double small = pow((Epochs[i-1].toe - time),2);

            cout << "Choosing for time: " << time << endl;
            cout << "Epochs[i].toe - time has a toe of: " << Epochs[i].toe << " and a delta^2 of: " << large << endl;
            cout << "Epochs[i-1].toe - time has a toe of: " << Epochs[i-1].toe << " and a delta^2 of: " << small << endl;

            if(small < large){
                cout << "Chose: " << small << endl << endl;
                //small delta is smaller and therefore closer to desired time
                return Epochs[i-1];
            }
            else{
                cout << "Chose: " << large << endl << endl;
                return Epochs[i];
            }
        }
    }
    //only one epoch in the vector and therefore automatically the closest
    return Epochs[Epochs.size()-1];
}

void data::generateOneDayFirst(){
    double timeOfTransmission = 345600;
    double maxTime = timeOfTransmission + 3600*24;
    double interval = 900;
    int c = 1;

    while(timeOfTransmission < maxTime){
        cout << "Generating Epoch number " << c << " t: " << timeOfTransmission << endl;
        cout << "With toe: " << Epochs[0].toe << endl << endl;

        oneDayFirst.emplace_back(
                                 timeOfTransmission,
                                 Epochs[0].toe,
                                 Epochs[0].sqrt_A,
                                 Epochs[0].M_0,
                                 Epochs[0].w,
                                 Epochs[0].i_0,
                                 Epochs[0].i_dot,
                                 Epochs[0].r,
                                 Epochs[0].n_delta,
                                 Epochs[0].L_0,
                                 Epochs[0].L_dot,
                                 Epochs[0].Crs,
                                 Epochs[0].Crc,
                                 Epochs[0].Cis,
                                 Epochs[0].Cic,
                                 Epochs[0].Cuc,
                                 Epochs[0].Cus);
        timeOfTransmission += interval;

        c++;
    }

    outputEpochVector("brdc24hr.xyz", oneDayFirst);
}

void data::generateOneDayNearest(){
    double timeOfTransmission = 345600;
    double maxTime = timeOfTransmission + 3600*24;
    double interval = 900;
    int c = 1;

    while(timeOfTransmission < maxTime){

        Epoch& e = nearest(timeOfTransmission);

        cout << "Generating Epoch number " << c << " t: " << timeOfTransmission << endl;
        cout << "With toe: " << e.toe << endl << endl;

        oneDayFirst.emplace_back(
                                 timeOfTransmission,
                                 e.toe,
                                 e.sqrt_A,
                                 e.M_0,
                                 e.w,
                                 e.i_0,
                                 e.i_dot,
                                 e.r,
                                 e.n_delta,
                                 e.L_0,
                                 e.L_dot,
                                 e.Crs,
                                 e.Crc,
                                 e.Cis,
                                 e.Cic,
                                 e.Cuc,
                                 e.Cus);
        timeOfTransmission += interval;

        c++;
    }

    outputEpochVector("brdcbest.xyz", oneDayNearest);
}

void data::outputEpochVector(string filename, vector<Epoch>& eps){
    ofstream file;
    file.open(filename);

    for(int i = 0; i<eps.size(); i++){
        file << eps[i].t << "/t" << eps[i].EFC(0,0) << "/t" << eps[i].EFC(1,0) << "/t" << eps[i].EFC(2,0) << endl;
    }

    file.close();
}
