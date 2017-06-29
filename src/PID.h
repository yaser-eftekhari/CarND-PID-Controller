#ifndef PID_H
#define PID_H

#include <uWS/uWS.h>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  const double MAX_ANGLE = 1.0;
  const double MIN_ANGLE = 0.01;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(const double Kp, const double Ki, const double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Find steering angle given cross track error.
  */
  double findSteeringAngle();

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void Restart(uWS::WebSocket<uWS::SERVER> ws);
};

#endif /* PID_H */
