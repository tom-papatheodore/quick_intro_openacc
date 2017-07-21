CCOMP=pgcc
CFLAGS= -acc -ta=tesla:cc60 -Minfo=accel -fast

LD=$(CCOMP)
LFLAGS=$(CFLAGS)

.PHONY: clean

run:  main.o
	$(LD) main.o -o run $(LFLAGS)

main.o: main.c
	$(CCOMP) $(CFLAGS) -c main.c

clean:
	rm -f *.o run
