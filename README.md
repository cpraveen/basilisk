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

## Two-phase methods

VOF:
http://basilisk.fr/src/two-phase.h

Levelset:
http://basilisk.fr/src/two-phase-levelset.h

VOF + levelset:
http://basilisk.fr/src/two-phase-clsvof.h
