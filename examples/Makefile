
TILEK_INC=../include
TILEK_LIB=../lib/tilek

all: foo foo-tilek

check: check-foo check-foo-tilek

clean:
	rm -rf foo foo-tilek *.o

# Main

main-foo.o: main-foo.c
	gcc -g -O0 -c main-foo.c -o main-foo.o

# Original

foo.o: foo.c
	gcc -g -O0 -I$(TILEK_INC) -c foo.c -o foo.o

foo: foo.o main-foo.o
	gcc foo.o main-foo.o -o foo

check-foo: foo
	./foo

# TileK

foo-tilek.o: rose_foo.c
	gcc -g -O0 -I$(TILEK_INC) -c rose_foo.c -o foo-tilek.o

foo-data.o: foo-data.c
	gcc -g -O0 -I$(TILEK_INC) -c foo-data.c -o foo-data.o

foo-kernel.o: foo-kernel.c
	gcc -g -O0 -I$(TILEK_INC) -c foo-kernel.c -o foo-kernel.o

foo-tilek: foo-tilek.o foo-data.o foo-kernel.o $(TILEK_LIB)/runtime.o main-foo.o
	gcc foo-tilek.o foo-data.o foo-kernel.o $(TILEK_LIB)/runtime.o main-foo.o -o foo-tilek

check-foo-tilek: foo-tilek
	./foo-tilek

# Libraries

$(TILEK_LIB)/runtime.o:
	make -C $(TILEK_LIB) runtime.o

