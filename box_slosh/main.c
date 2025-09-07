#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"

#define LEVEL 8

// Boundary conditions
// All sides use the default symmetry boundary condition, which is a slip wall.

//------------------------------------------------------------------------------
int main()
{
   rho1 = 1.0,    mu1 = 1.0/1000.0;
   rho2 = 1.0e-3, mu2 = mu1/100.0;
   f.sigma = 0.0;
   DT = 1.0e-2;

   init_grid(1 << LEVEL);
   run();
}

//------------------------------------------------------------------------------
event init (t = 0)
{
   const double y0 = 0.5, amp = 0.1, beta = 50.0, x0 = 0.5;

   vertex scalar phi[];
   foreach_vertex()
      phi[] = y0 + amp*exp(-beta*(x-x0)*(x-x0)) - y;
   fractions (phi, f);

   output_ppm(f, file="f0.png", n=2048, box={{0,0},{1,1}});

   if (is_constant(a.x))
   {
      a = new face vector;
      foreach_face()
         a.x[] = 0.0;
   }
}

//------------------------------------------------------------------------------
// Add gravity force  in -y direction
//------------------------------------------------------------------------------
event acceleration (i++)
{
   face vector av = a;
   foreach_face(y)
      av.y[] -= 1.0;
}

//------------------------------------------------------------------------------
event interface (t += 1.0; t <= 3.0)
{
   char name[80];
   sprintf (name, "f_%g.txt", t);
   FILE * fp = fopen (name, "w");
   output_facets (f, fp);
}

//------------------------------------------------------------------------------
void mg_print (mgstats mg)
{
   if (mg.i > 0 && mg.resa > 0.)
      printf ("%d %g %g %g %d ", mg.i, mg.resb, mg.resa,
	           mg.resb > 0 ? exp (log (mg.resb/mg.resa)/mg.i) : 0.0,
	           mg.nrelax);
}

//------------------------------------------------------------------------------
event logfile (i++) 
{
   #if !MOMENTUM
   mg_print (mgp);
   mg_print (mgpf);
   mg_print (mgu);
   #endif

   putchar ('\n');
   fflush (stdout);
}

//------------------------------------------------------------------------------
event movie (t += 0.05)
{
   scalar l[];
   foreach()
      l[] = -1 + f[] * (0.25 + sqrt(sq(u.x[]) + sq(u.y[])));
   boundary ({l}); 
   output_ppm (l, min=-1, max=3.25, linear=true, n=1024, box={{0,0},{1,1}},
               file="slosh.mp4");                   
   foreach()
      l[] = level;
   boundary ({l}); 
   output_ppm (l, n=1024, min=0.0, max=12.0, box = {{0,0},{1,1}},
               file="level.mp4");         
}

//------------------------------------------------------------------------------
event adapt(i++)
{
   scalar g[];
   foreach()
      g[]=f[]*(1+noise())/2;
   boundary({g});
   adapt_wavelet({g,f}, (double[]){0.001,0.01}, minlevel=5, maxlevel=LEVEL);
} 

//------------------------------------------------------------------------------
event end (t = 3)
{
   printf ("i = %d t = %g\n", i, t);
}
