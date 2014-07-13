CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=$(shell pkg-config --libs libparted)

all: hello

hello:
	$(CC) -o hello.o -c $(CFLAGS) $(CPPPATH) helloparted.c
	#$(CC) -o strlist.o -c $(CFLAGS) $(CPPPATH) strlist.c
	#$(CC) -o table.o -c $(CFLAGS) $(CPPPATH) table.c
	#$(CC) -o hello hello.o table.o strlist.o $(LIBPATH) $(LIBS)
	$(CC) -o hello hello.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o hello
