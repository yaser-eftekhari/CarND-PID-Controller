#include "PID.h"
#include <uWS/uWS.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(const double Kp_, const double Ki_, const double Kd_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  p_error = 0;
  i_error = 0;
  d_error = 0;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
}

double PID::findSteeringAngle() {
  double angle = -Kp*p_error -Kd*d_error -Ki*i_error;
  if(angle > 0) {
    if(angle > MAX_ANGLE)
      angle = MAX_ANGLE;
    else if(angle < MIN_ANGLE)
      angle = 0;
  } else {
    if (angle < -MAX_ANGLE)
      angle = -MAX_ANGLE;
    else if(angle > -MIN_ANGLE)
      angle = 0;
  }

  return angle;
}

double PID::TotalError() {
  return i_error;
}

// abs(cte) > 2.2 means off track
void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}
