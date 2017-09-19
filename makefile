# Makefile for Lenovo x250 BIOS EEPROM reader/writer


CC=gcc
#CFLAGS=-I$(IDIR)
CFLAGS=-g
LIBS=-lwiringPi
#LIBS=

OBJDIR=obj
EXEDIR=bin
SRCDIR=src

HFILES := $(wildcard $(SRCDIR)/*.h)
CFILES := $(wildcard $(SRCDIR)/*.c)

OBJFILES := $(notdir $(CFILES))
OBJFILES := $(basename $(OBJFILES))
OBJFILES := $(addsuffix .o, $(OBJFILES))
OBJFILES := $(addprefix $(OBJDIR)/, $(OBJFILES))

$(EXEDIR)/x250_util: $(OBJFILES) | $(OBJDIR) $(EXEDIR)
	$(CC) -o $@ $(OBJFILES) $(CFLAGS) $(LIBS)

# '|' means prerequisite must exist, not be older
$(OBJFILES) : $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HFILES) | $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

$(EXEDIR):
	mkdir $(EXEDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXEDIR)/*
