CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: ltest qtest htest

#list.o: list.c list.h
#	gcc $(CFLAGS) -c list.c

#ltest.o: ltest.c list.h
#	gcc $(CFLAGS) -c ltest.c
#test

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

#queue.o: queue.c queue.h
#	gcc $(CFLAGS) -c queue.c

hash.o: hash.c hash.h
	gcc $(CFLAGS) -c hash.c

ltest: ltest.o list.o
	gcc $(CFLAGS) ltest.o list.o -o ${@}

qtest: qtest.o queue.o
	gcc $(CFLAGS) qtest.o queue.o -o ${@}

htest: htest.o hash.o
	gcc $(CFLAGS) htest.o hash.o -o ${@}

clean:
	rm -f *.o ltest qtest htest
