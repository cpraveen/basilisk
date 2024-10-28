all: vof levelset clsvof

vof: main.c
	qcc -g -O2 -Wall -o vof main.c -lm

levelset: main.c
	qcc -g -O2 -Wall -DLEVELSET=1 -o levelset main.c -lm

clsvof: main.c
	qcc -g -O2 -Wall -DLEVELSET=1 -DCLSVOF=1 -o clsvof main.c -lm
