#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {

}

PID::~PID() {}

void PID::Init(double Kp_in, double Ki_in, double Kd_in) {


    Kp = Kp_in;
    Kd = Kd_in;
    Ki = Ki_in;
    d_error = 0;
    i_error = 0;


}

double PID::UpdateError(double cte) {
    double correction;

    i_error += cte;

    correction = (-Kp * cte) + (-Kd * (cte - d_error)) + (-Ki * i_error);

    d_error = cte;

    cout<< "Correction " << correction << " " << d_error << " " << cte << endl;
    return correction;
}

double PID::TotalError() {
}

