#include "saint-venant.h"

#define LEVEL 8

event init (t = 0)
{
  double a = 1.0, b = 200.0;
  foreach()
    h[] = 0.1 + a*exp(-b*(x*x + y*y));
}

event graphs (i++)
{
  stats s = statsf (h);
  fprintf (stderr, "%g %g %g\n", t, s.min, s.max);
}

event images (t += 4.0/300.0)
{
  output_ppm (h, linear = true);

  scalar l[];
  foreach()
    l[] = level;
  static FILE * fp = fopen ("grid.ppm", "w");
  output_ppm (l, fp, min=0, max=LEVEL);
}

event end (t = 4)
{
  printf ("i = %d t = %g\n", i, t);
}

event adapt (i++)
{
  adapt_wavelet ({h}, (double []){4e-3}, maxlevel=LEVEL);
}

int main()
{
  origin (-0.5, -0.5);
  init_grid (1 << LEVEL);
  run();
}
