# Makefile for Lenovo x250 BIOS EEPROM reader/writer

CC=gcc
CFLAGS=-I src
DEPS = winbond_defines.h winbond_functions.h ports.h

x250_util: 


# Include directory
IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =lib

LIBS=-lwiringPi

_DEPS = src/ports.h src/winbond_defines.h src/winbond_functions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ports.o winbond_functions.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 