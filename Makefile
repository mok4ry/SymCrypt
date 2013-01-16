# Makefile for Mersenne Twister

OBJS= mtwist.o symcrypt.o

compile: $(OBJS)
	gcc -o symcrypt main.c $(OBJS)

symcrypt.o:
	gcc -c symcrypt.c

mtwist.o:
	gcc -c mtwist.c

clean:
	rm symcrypt *.o
