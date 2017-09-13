# Makefile for Lenovo x250 BIOS EEPROM reader/writer


CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lwiringPi

_DEPS = src/ports.h src/winbond_defines.h src/winbond_functions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ports.o winbond_functions.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

x250_util: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
