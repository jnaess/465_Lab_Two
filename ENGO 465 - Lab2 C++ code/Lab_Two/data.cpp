#include "data.h"

#include <sstream>

//Test comment here
data::data(){

}

void data::add_epoch(
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
