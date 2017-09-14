# Makefile for Lenovo x250 BIOS EEPROM reader/writer


CC=gcc
#CFLAGS=-I$(IDIR)
CFLAGS=-g
LIBS=-lwiringPi

OBJDIR=obj
EXEDIR=bin
SRCDIR=src

HFILES := $(wildcard $(SRCDIR)/*.h)
CFILES := $(wildcard $(SRCDIR)/*.c)

OBJFILES := $(notdir $(CFILES))
OBJFILES := $(basename $(OBJFILES))
OBJFILES := $(addsuffix .o, $(OBJFILES))
OBJFILES := $(addprefix $(OBJDIR)/, $(OBJFILES))

x250_util: $(OBJFILES) $(OBJDIR) $(EXEDIR)
	$(CC) -o $(EXEDIR)/$@ $(OBJFILES) $(CFLAGS) $(LIBS)


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HFILES) $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEDIR):
	mkdir $(EXEDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXEDIR)/*
