CC=g++
AR=ar

LIBDIR=../
LIBNAME=libmath
INCDIR=../inc

CFLAGS=-O3 -g -I$(INCDIR)

all: $(LIBDIR)/$(LIBNAME).a
$(LIBDIR)/$(LIBNAME).a: *.o
	$(AR) r $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c add.cpp sub.cpp

clean:
	rm *.o $(LIBDIR)/$(LIBNAME).a


