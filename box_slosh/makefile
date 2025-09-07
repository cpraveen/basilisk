CFLAGS=-O2 -Wall
TARGETS=vof

all: $(TARGETS)

vof: main.c
	qcc $(CFLAGS) -o vof main.c -lm

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) f_*.txt *.png *.mp4
