/*
 Solves
     Laplace(u) = f with u=0 on boundary
 */
#include "utils.h"
#include "poisson.h"
#include "vtk.h"

// Grid will be 2^L x 2^L where L=LEVEL
#define LEVEL  8

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
   origin(0.0, 0.0); // [0,1]x[0,1]
   init_grid(1 << LEVEL);

   scalar u[], f[];

   // Boundary conditions
   u[left]   = dirichlet(0);
   u[right]  = dirichlet(0);
   u[bottom] = dirichlet(0);
   u[top]    = dirichlet(0);

   // Set rhs function
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
