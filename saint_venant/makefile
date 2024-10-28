CFLAGS=-O2 -Wall
TARGETS=main

all: $(TARGETS)

main: main.c
	qcc $(CFLAGS) -o main main.c -lm

clean:
	rm -f $(TARGETS)
