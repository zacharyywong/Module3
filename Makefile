CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: ltest

#list.o: list.c list.h
#	gcc $(CFLAGS) -c list.c

#ltest.o: ltest.c list.h
#	gcc $(CFLAGS) -c ltest.c

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

ltest: ltest.o list.o
	gcc $(CFLAGS) ltest.o list.o -o ${@}

clean:
	rm -f *.o ltest
