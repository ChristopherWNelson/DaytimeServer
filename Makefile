COPTS = gcc -std=c99 -pedantic -Wall
ALL = dayserve  daytime

all: $(ALL)

clean:
	-rm -rf *.o *~ *.dSYM *dayserve *daytime

dayserve: dayserve.c
	${COPTS} dayserve.c -o dayserve -lm

daytime: daytime.c
	${COPTS} daytime.c -o daytime -lm