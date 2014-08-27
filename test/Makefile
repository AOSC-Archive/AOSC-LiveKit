CC		= 	gcc
CFLAGS	= 	-g -O2 -Wall -fPIC
CPPPATH	=
LIBPATH	=
LIBS	= 	$(shell pkg-config --libs libparted)
LIBS	+= 	-lblkid

all: test_libparted test_libblkid

test_libparted:
	$(CC) -o test_libparted.o -c $(CFLAGS) $(CPPPATH) test_libparted.c
	$(CC) -o test_libparted test_libparted.o $(LIBPATH) $(LIBS)

test_libblkid:
	$(CC) -o test_libblkid.o -c $(CFLAGS) $(CPPPATH) test_libblkid.c
	$(CC) -o test_libblkid test_libblkid.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test_libparted test_libblkid
