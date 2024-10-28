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

If you want to use `view.h`, install opengl; on mac with homebrew, do 

```shell
brew install mesa-glu
cd $BASILISK/gl
CFLAGS=-I/opt/homebrew/include make libglutils.a libfb_osmesa.a
```

You will also need other softwares like

* Gnuplot: for plotting
* Imagemagick: to convert ppm to gif, mp4, etc.

## Two-phase methods

VOF:
http://basilisk.fr/src/two-phase.h

Levelset:
http://basilisk.fr/src/two-phase-levelset.h

VOF + levelset:
http://basilisk.fr/src/two-phase-clsvof.h
