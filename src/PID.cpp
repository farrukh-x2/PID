#include "PID.h"
#include <iostream>
#include <uWS/uWS.h>

using namespace std;

PID::PID() {

}

PID::~PID() {}

void PID::Init(double Kp_in, double Ki_in, double Kd_in) {

    cout<<"Intialized!!"<<endl;
    p[0] = Kp_in;
    p[1] = Ki_in;
    p[2] = Kd_in;

    d_error = 0;
    i_error = 0;

    //paramets for twiddle use
    counter_iterations = 0;

    best_err = 0;
    total_error = 0;

    // values to start 'twiddling' with
    dp[0] = 0.025; // p
    dp[1] = 0.0005; // i
    dp[2] = 0.25; // d

    flag_1 = 0;
    p_i_d = 0;

}


double PID::UpdateError(double cte, uWS::WebSocket<uWS::SERVER> ws) {

    double correction;

    i_error += cte;

    correction = (-p[0] * cte) + (-p[1] * i_error) + (-p[2] * (cte - d_error));

    d_error = cte;


// uncomment if Twiddle is used
/*
    if (counter_iterations > 250){
        TotalError(cte);
    }

    counter_iterations += 1;


    if (counter_iterations == 950)
    {

        twiddle();
        cout<< "Total Error " << total_error<<endl;
        total_error =0;
        counter_iterations = 0;

        Restart(ws);

    }
*/
    return correction;
}


void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}


void PID::TotalError(double cte) {

    total_error += (cte * cte);

}


double PID::twiddle() {

    d_error = 0;
    i_error = 0;

    //this if condition is only run once in the beginning
    if (flag_1 == 0)
    {
        flag_1 = 1;
        best_err = total_error;

        cout<< "flag 1 = 0, total_error " << total_error<<  " PID " << p_i_d
        <<" Best Error "<< best_err<<" Ks "<< p[0]<<" "<<p[1] <<" "<<p[2] << " dp[] " << dp[p_i_d] <<endl;

        p[p_i_d] += dp[p_i_d];
        return 0;
    }

    if (flag_1 == 1)
    {


        if (total_error < best_err ){

            cout<< "flag 1 = 1.1, total_error " << total_error << " PID " << p_i_d <<" Best Error "<< best_err<<" Ks "<< p[0]<<" "<<p[1] <<" "<<p[2] << " dp[] " << dp[p_i_d] <<endl;

            best_err = total_error;
            dp[p_i_d] *= 1.5;

            // move on to next parameter in PID
            p_i_d += 1;
            if (p_i_d == 3) p_i_d = 0;

            p[p_i_d] += dp[p_i_d];
               //flag_ind += 1;
        }

        else{
            cout<< "flag 1 = 1.2, total_error " << total_error << " PID " << p_i_d <<" Best Error "<< best_err<<" Ks "<< p[0]<<" "<<p[1] <<" "<<p[2] << " dp[] " << dp[p_i_d] <<endl;
            p[p_i_d] -= 2*dp[p_i_d];

            flag_1 = 2;

            return 0;
        }
     }

    if (flag_1 == 2)
    {
        if (total_error < best_err ){
            best_err = total_error;

            cout<< "flag 1 = 2.1, total_error " << total_error << " PID " << p_i_d <<" Best Error "<< best_err<<" Ks "<< p[0]<<" "<<p[1] <<" "<<p[2] << " dp[] " << dp[p_i_d] <<endl;
            dp[p_i_d] *= 1.5;

            // move on to next parameter in PID
            p_i_d += 1;
            if (p_i_d == 3) p_i_d = 0;

            p[p_i_d] += dp[p_i_d];
            flag_1 = 1;
                    }
        else{
            cout<< "flag 1 = 2.2, total_error " << total_error << " PID " << p_i_d <<" Best Error "<< best_err<<" Ks "<< p[0]<<" "<<p[1] <<" "<<p[2] << " dp[] " << dp[p_i_d] <<endl;
            p[p_i_d] += dp[p_i_d];
            dp[p_i_d] *= 0.5;

            // move on to next parameter in PID
            p_i_d += 1;
            if (p_i_d == 3) p_i_d = 0;

            p[p_i_d] += dp[p_i_d];
            flag_1 = 1 ;
                    }

    }

}
