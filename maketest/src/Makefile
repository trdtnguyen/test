BINDIR=../bin
OBJDIR=../obj
LIBDIR=../lib
#LIBNAME: library name without prefix lib, e.g. libmath -> math
LIBNAME = math
INCDIR = ../inc
INCLIBDIR= ../lib/inc

CC = g++
CFLAGS = -I$(INCDIR) -I$(INCLIBDIR)
LFLAGS = -L$(LIBDIR) -l$(LIBNAME)

all: $(BINDIR)/test

$(BINDIR)/test: *.cpp
	        $(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)      
clean:
	        rm *.o $(BINDIR)/test

