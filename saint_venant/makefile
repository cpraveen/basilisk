CFLAGS=-O2 -Wall
TARGETS=bump

all: $(TARGETS)

bump: bump.c
	qcc $(CFLAGS) -o bump bump.c -lm

run: bump
	./bump > out.ppm 2> log.txt
	magick out.ppm out.gif
	magick grid.ppm grid.gif

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) *.ppm *.gif
