CC = gcc
CFLAGS = -Wall -g
AR = ar
ARFLAGS = rcs

all: ablib.a

ablib.a: ablib.o
	$(AR) $(ARFLAGS) $@ $^

ablib.o: ablib.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c ablib.a
	$(CC) $(CFLAGS) $< ablib.a -o $@

clean:
	rm -f *.o *.a

.PHONY: all clean
#abacus: abacus.c ablib.a
#	gcc abacus.c ablib.a -o abacus
#
#ablib.a: ablib.o
#	ar rcs ablib.a ablib.o
#
#ablib.o: ablib.c
#	gcc -c ablib.c -o ablib.o
