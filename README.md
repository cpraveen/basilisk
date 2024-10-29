# Codes written in Basilisk

## Installation

Get code with darcs

```shell
darcs clone http://basilisk.fr/basilisk
```

or download tarball

```shell
wget http://basilisk.fr/basilisk/basilisk.tar.gz
tar zxvf basilisk.tar.gz
```

To compile on mac

```shell
cd basilisk/src
ln -s config.osx config
make
```

Add to PATH

```shell

export BASILISK=/path/to/basilisk/src
export PATH=$PATH:$BASILISK
```

You will also need other softwares like

* Gnuplot: for plotting
* Imagemagick: to convert ppm to gif, mp4, etc.

## Documentation

* NS centered solver
  * http://basilisk.fr/src/navier-stokes/centered.h
  * http://basilisk.fr/sandbox/ecipriano/doc/centered
* Two-phase flow methods
  * VOF: http://basilisk.fr/src/two-phase.h
  * Levelset: http://basilisk.fr/src/two-phase-levelset.h
  * VOF + levelset: http://basilisk.fr/src/two-phase-clsvof.h
* Surface tension
  * http://basilisk.fr/src/tension.h
  * Integral formulation: http://basilisk.fr/src/integral.h
