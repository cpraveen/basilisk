CFLAGS=-O2 -Wall
TARGETS=poisson

all: $(TARGETS)

poisson: main.c
	qcc $(CFLAGS) -o poisson main.c -lm

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) f_*.txt *.png *.mp4
