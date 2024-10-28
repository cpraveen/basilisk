CFLAGS=-O2 -Wall
TARGETS=vof levelset clsvof

all: $(TARGETS)

vof: main.c
	qcc $(CFLAGS) -o vof main.c -lm

levelset: main.c
	qcc $(CFLAGS) -DLEVELSET=1 -o levelset main.c -lm

clsvof: main.c
	qcc $(CFLAGS) -DLEVELSET=1 -DCLSVOF=1 -o clsvof main.c -lm

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) f_*.txt *.png *.mp4
