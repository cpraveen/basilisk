# Short examples

Use the makefile to compile executables.

```shell
make
```

## Heat equation in 2d

* heat2da.c: solve 2d heat equation with explicit scheme
* heat2db.c: solve 2d heat equation with diffusion.h which uses implicit scheme

```shell
heat2da > a.txt
heat2db > b.txt
```

In gnuplot

```gnuplot
gnuplot> p 'a.txt' w lp,'b.txt' w lp
```
