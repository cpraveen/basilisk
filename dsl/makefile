CFLAGS=-O2 -Wall -disable-dimensions
TARGETS=dsl

all: $(TARGETS)

dsl: main.c
	qcc $(CFLAGS) -o $@ $< -lm

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) f_*.txt *.png *.mp4
