#if MOMENTUM
   #include "momentum.h"
#else
   #include "navier-stokes/centered.h"
   #if CLSVOF
      #include "two-phase-clsvof.h"
   #elif LEVELSET
      #include "two-phase-levelset.h"
   #else
      #include "two-phase.h"
   #endif
#endif

#if LEVELSET
   #include "integral.h"
#else
   #include "tension.h"
#endif

#define WIDTH 10.0
#define LEVEL 8

// Boundary conditions
// All sides use the default symmetry boundary condition, which is a slip wall.

//------------------------------------------------------------------------------
int main()
{
   rho1 = 1.0,    mu1 = 1.0/1000.0;
   rho2 = 1.0e-3, mu2 = mu1/100.0;

   #if LEVELSET
   const scalar sigma[] = 0.0;
   d.sigmaf = sigma;
   #else
   f.sigma = 0.0;
   #endif

   DT = 1.0e-2;

   origin (0.0, 0.0);
   size(WIDTH);
   init_grid(1 << LEVEL);
   run();
}

//------------------------------------------------------------------------------
// Exact distance function to the interface
//------------------------------------------------------------------------------
double distance(const double x, const double y)
{
   double a;

   if(y <= 1 && x <= WIDTH/2)
   {
      a = min(1 - y, WIDTH/2 - x);
   }
   else if(y > 1 && x <= WIDTH/2)
   {
      a = 1 - y;
   }
   else if(x > WIDTH/2 && y < 1)
   {
      a = WIDTH/2 - x;
   }
   else
   {
      a = -sqrt(sq(x - WIDTH/2) + sq(y - 1));
   }

   return a;
}

//------------------------------------------------------------------------------
event init (t = 0)
{
   mask (y >  WIDTH/4 ? top : none);

   #if LEVELSET
   foreach()
      d[] = distance(x, y);
   // Compute volume fraction since we need it to initialize velocity
   vertex scalar phi[];
   foreach_vertex()
      phi[] = distance(x, y);
   fractions (phi, f);
   output_ppm(d, file="d0.png", n=2048, box={{0,0},{10,2.5}});
   #else
   fraction (f, min(1 - y, WIDTH/2 - x));
   #endif

   output_ppm(f, file="f0.png", n=2048, box={{0,0},{10,2.5}});

   foreach()
   {
      u.x[] = f[] * 1.0e-8;
      u.y[] = 0.0;
   }

   if (is_constant(a.x))
   {
      a = new face vector;
      foreach_face()
         a.x[] = 0.0;
   }
}

//------------------------------------------------------------------------------
// Add gravity force (0,-1)
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
   output_ppm (l, min = -1,  max= 3.25, linear = true,
               n = 1024, box = {{0,-1},{10,2.5}},
               file = "dam.mp4"
               );                   
   foreach()
      l[] = level;
   boundary ({l}); 
   output_ppm (l, n = 1024,  min = 0.,   max= 12.,
               box = {{0,-1},{10,2.5}},
               file = "level.mp4")  ;         
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
