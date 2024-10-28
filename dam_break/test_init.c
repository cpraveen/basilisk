#include "grid/cartesian.h"
#include "fractions.h"
#include "utils.h"

#define LEVEL 8

int main()
{
   L0 = 10.0;
   origin (0.0, 0.0);
   size(L0);
   init_grid(1 << LEVEL);

   // (1) exact volume fractions
   {
      scalar f[];
      foreach()
         f[] = (y < 1 && x < L0/2) ? 1.0 : 0.0;
      FILE* fp = fopen("f1.txt", "w");
      output_facets(f, fp);
      output_ppm(f, file="f1.png", n=1024, box={{0,0},{10,2.5}});
   }

   // (2) levelset to volume fraction
   {
      vertex scalar phi[];
      foreach_vertex()
         phi[] = min(1-y, L0/2-x);
      scalar f[];
      fractions(phi, f);
      FILE* fp = fopen("f2.txt", "w");
      output_facets(f, fp);
      output_ppm(f, file="f2.png", n=1024, box={{0,0},{10,2.5}});
   }

   // (3) levelset to volume fraction
   {
      scalar f[];
      fraction(f, min(1-y, L0/2-x));
      FILE* fp = fopen("f3.txt", "w");
      output_facets(f, fp);
      output_ppm(f, file="f3.png", n=1024, box={{0,0},{10,2.5}});
   }
}
