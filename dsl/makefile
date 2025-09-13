#CC=/opt/homebrew/opt/llvm/bin/clang
CFLAGS=-Xclang -fopenmp -O2 -Wall -disable-dimensions -I/opt/homebrew/include
LDFLAGS=-L/opt/homebrew/lib -lomp
TARGETS=dsl

all: $(TARGETS)

dsl: main.c
	qcc $(CFLAGS) -o $@ $< -lm $(LDFLAGS)

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) f_*.txt *.png *.mp4
