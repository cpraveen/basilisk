#include "utils.h"
#include "poisson.h"

#define LEVEL  8

scalar u[], f[];

u[left]   = dirichlet(0);
u[right]  = dirichlet(0);
u[bottom] = dirichlet(0);
u[top]    = dirichlet(0);

int main()
{
   origin(0.0, 0.0);
   init_grid(1 << LEVEL);

   foreach()
   {
      f[] = -1.0;
   }

   mgstats mgu = poisson(u, f);
   output_ppm(u, file="u.png", n=1024);
}
