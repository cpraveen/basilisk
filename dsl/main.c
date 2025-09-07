/**
We solve the two-dimensional incompressible Euler equations using a
vorticity--streamfunction formulation. */

#include "navier-stokes/stream.h"

const double MU = 1.0/1000.0;

double rho = 80.0;
double delta = 0.05;  
int maxlevel = 7;

int main (int argc, char * argv[])
{
  if (argc > 1)
    maxlevel = atoi(argv[1]);
  foreach_dimension()
    periodic(right);
  //mu[] = {MU,MU};
  N = 1 << maxlevel;
  run();
}

event init (i = 0)
{
  foreach ()
  {
    double u_y, v_x;
    if(y <= 0.5)
       u_y =  rho * 1.0/pow(cosh(rho*(y-0.25)),2);
    else
       u_y = -rho * 1.0/pow(cosh(rho*(0.75-y)),2);
    v_x = 2.0 * pi * delta * cos(2.0*pi*(x + 0.25));
    omega[] = v_x - u_y;
  }
}

event output (t += 0.05; t <= 1.0)
{
  //output_ppm (omega, n = 1024, min = -0.3, max = 0.3, file = "omega.mp4");
  output_ppm (omega, n = 1024, file = "omega.mp4");
}
