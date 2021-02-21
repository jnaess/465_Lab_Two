#include "LSA.h"

//LSA::LSA(){}

LSA::LSA()
{

}

void LSA::copyEpoch2LSA(Epoch epoch)
{

    N_sat = epoch.Satelites;

    l_o.resize(epoch.meas.size(), 1);
    //cout << "\n observation vector \n";
    for(int i = 0; i<l_o.rows(); ++i)
    {
        l_o(i,0) = epoch.meas[i].obs;
        //cout<<l_o(i,0)<<"\n";
    }

    x_o.resize(4,1);
    x_o(0,0) = -1641890.0812;
    x_o(1,0) = -3664879.3462;
    x_o(2,0) = 4939969.4303;
    x_o(3,0) = 0;
//    for(int i = 0; i<x_o.rows(); ++i)
//    {
//        x_o(i,0) = 0;
//    }

    satpos.resize(epoch.Satelites, 3);
    for(int i = 0; i<satpos.rows(); ++i)
    {
        satpos(i,0) = epoch.meas[i].X;
        satpos(i,1) = epoch.meas[i].Y;
        satpos(i,2) = epoch.meas[i].Z;
    }
    //print_mat(satpos, "satpos");
}


void LSA::adjustment()
{
    N_iter++;
	cout << "~~~~~~~~ ITERATION #" << N_iter << " ~~~~~~~~~~\n";

	this->designA();
	this->misclosure();
	this->weights();

	N = A.transpose() * P * A;
	U = A.transpose() * P * w;
	delta = -N.inverse() * U;
	v = A * delta + w;

	x_cap = x_o + delta;
	l_cap = l_o + v;

//    print_mat(satpos, "satpos");
//    print_mat(A, "A");
//    print_mat(w, "w");
//    print_mat(P, "P");
//	print_mat(delta, "delta");
//	print_mat(x_cap, "x_cap");
//	print_mat(l_cap, "l_cap");
//	print_mat(v, "v");

    for (int i = 0; i < delta.rows(); ++i)
    {
        if (this->delta(i, 0) > 0.00001 || this->delta(i, 0) < -0.00001)
        {
            l_o = l_cap;
            x_o = x_cap;
            adjustment();
        }
    }
}

void LSA::designA()
{
    A.resize(N_sat, 4);
    for(int i = 0; i<A.rows(); ++i)
    {
        double p_o = sqrt(pow(satpos(i,0)-x_o(0,0),2) + pow(satpos(i,1)-x_o(1,0),2) + pow(satpos(i,2)-x_o(2,0),2));
        for(int j=0; j<A.cols()-1; ++j)
        {
            A(i,j) = (x_o(j,0)-satpos(i,j))/p_o;
        }
        A(i,A.cols()-1) = -1;
    }
}

void LSA::misclosure()
{
    w.resize(N_sat, 1);
    for(int i = 0; i<w.rows(); ++i)
    {
        double p_o = sqrt(pow(satpos(i,0)-x_o(0,0),2) + pow(satpos(i,1)-x_o(1,0),2) + pow(satpos(i,2)-x_o(2,0),2));
        w(i,0) = p_o - l_o(i,0) - x_o(3,0);
    }
}

void LSA::weights()
{
    C_l.resize(N_sat, N_sat);
    C_l.setIdentity();

    P = apriori*C_l.inverse();
}

void LSA::precision(MatrixXd truepos)
{
    Qx = (A.transpose()*P*A).inverse();
    Cx = apriori*Qx;
    GDOP = sqrt(Qx(0,0)+Qx(1,1)+Qx(2,2)+Qx(3,3));   //x y z cdt
    PDOP = sqrt(Qx(0,0)+Qx(1,1)+Qx(2,2));           //x y z

    //assume sphere, all in radians
    double lat = asin(truepos(2,0)/sqrt(pow(truepos(0,0),2)+pow(truepos(1,0),2)+pow(truepos(2,0),2)));
    double lon = asin(truepos(1,0)/sqrt(pow(truepos(0,0),2)+pow(truepos(1,0),2)+pow(truepos(2,0),2)))/cos(lat);
    //cout << "lat " << lat << " lon " << lon << "\n";
    R.resize(4,4);
    R << -sin(lat)*cos(lon), -sin(lat)*cos(lon), cos(lat), 0, -sin(lon), cos(lon), 0, 0, cos(lat)*cos(lon), cos(lat)*sin(lon), sin(lat), 0, 0, 0, 0, 1;
    //print_mat(R, "R");

    QL = R*Qx*R.transpose();
    HDOP = sqrt(QL(0,0)+QL(1,1));   //North and east
    VDOP = sqrt(QL(2,2));           //up
}

void LSA::output_x(string name)
{
    ofstream outfile;
    outfile.open(name, ios::app);   //will continue to append each time you run. Clear file or create new
    if (outfile.fail())
    {
        cout << "could not open output file";
    }
    outfile << fixed << setprecision(3) << x_cap(0,0) << " " << x_cap(1,0) << " " << x_cap(2,0) << " \n";
}

void LSA::output_DOP(string name)
{
    ofstream outfile;
    outfile.open(name, ios::app);   //will continue to append each time you run. Clear file or create new
    if (outfile.fail())
    {
        cout << "could not open output file";
    }
    outfile << fixed << setprecision(3) << N_sat << " " << GDOP << " " << PDOP << " " << HDOP << " " << VDOP << " \n";
}

void LSA::output_sigma(string name)
{
    ofstream outfile;
    outfile.open(name, ios::app);   //will continue to append each time you run. Clear file or create new
    if (outfile.fail())
    {
        cout << "could not open output file";
    }
    outfile << fixed << setprecision(3) << sqrt(QL(0,0)) << " " << sqrt(QL(1,1)) << " " << sqrt(QL(2,2)) << " \n";
}

void print_mat(MatrixXd mat, string name)
{
    cout << "\n" << name << "\n";
    for(int i = 0; i<mat.rows(); ++i)
    {
        for(int j = 0; j<mat.cols(); ++j)
        {
            cout << mat(i,j) << "  ";
        }
        cout << "\n";
    }
}

