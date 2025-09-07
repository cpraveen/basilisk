#include "utils.h"
#include "poisson.h"
#include "vtk.h"

#define LEVEL  8

scalar u[], f[];

u[left]   = dirichlet(0);
u[right]  = dirichlet(0);
u[bottom] = dirichlet(0);
u[top]    = dirichlet(0);

void mg_print (mgstats mg)
{
   if (mg.i > 0 && mg.resa > 0.)
      printf ("Iter=%d, ||f||=%g, ||u||=%g, %g, nrelax=%d\n", 
              mg.i, mg.resb, mg.resa,
              mg.resb > 0 ? exp (log (mg.resb/mg.resa)/mg.i) : 0.0,
              mg.nrelax);
}

int main()
{
   origin(0.0, 0.0);
   init_grid(1 << LEVEL);

   foreach()
   {
      f[] = -1.0;
   }

   mgstats mgu = poisson(u, f, tolerance=1e-6);
   mg_print(mgu);
   output_ppm(u, file="u.png", n=1024);
   FILE* fp = fopen("u.vtk", "w");
   output_vtk({u}, 1<<LEVEL, fp, true);
   fclose(fp);
}

