# Double shear layer

Solve vorticity-streamfunction form of 2D NS equations, see

http://basilisk.fr/src/navier-stokes/stream.h

For the test case, see 

Minion and Brown, Performance of Under-resolved Two-Dimensional Incompressible Flow Simulations, II, JCP, vol. 138, 1997.

With `rho=80` and `delta=0.05` try

```shell
./dsl 7 && open omega.mp4
./dsl 8 && open omega.mp4
./dsl 9 && open omega.mp4
```

On coarse grids, you get some extra vortices which disappear upon grid refinement.
