#include "diffusion.h"
#include "run.h"

scalar A[];

// boundary conditions
A[left]   = 0.0;
A[top]    = 0.0;
A[right]  = 0.0;
A[bottom] = 0.0;

// initial conditions
event init (t = 0) 
{
  foreach()
    A[] =  1.0/0.1*(fabs(x*x+y*y)<0.05);
  boundary ({A});
}

// integration
event integration (i++)
{
  double dt = DT;
  dt = dtnext(dt);
  diffusion(A, dt);
  boundary ({A});
}

// print
event print (i=10)
{
  for (double y = -L0/2; y <= L0/2; y += 0.01)
  {
    printf("%g %g \n", y, interpolate (A, 0, y));
  }
}

int main()
{
  origin(-0.5,-0.5);
  L0 = 1.0;
  N = 256;
  
  // stability criteria
  DT = 0.25*(L0/N)*(L0/N);

  run();
}

