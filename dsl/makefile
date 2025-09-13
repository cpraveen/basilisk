CFLAGS=-O2 -Wall -disable-dimensions
LDFLAGS=-lm
TARGETS=dsl

all: $(TARGETS)

dsl: main.c
	qcc $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) omega.mp4
