
FAKEACC_INC=../include
FAKEACC_LIB=../lib/fakeacc

all: foo foo-fakeacc

check: check-foo check-foo-fakeacc

clean:
	rm -rf foo foo-fakeacc *.o

# Main

main-foo.o: main-foo.c
	gcc -g -O0 -c main-foo.c -o main-foo.o

# Original

foo.o: foo.c
	gcc -g -O0 -I$(FAKEACC_INC) -c foo.c -o foo.o

foo: foo.o main-foo.o
	gcc foo.o main-foo.o -o foo

check-foo: foo
	./foo

# FakeACC

foo-fakeacc.o: rose_foo.c
	gcc -g -O0 -I$(FAKEACC_INC) -c rose_foo.c -o foo-fakeacc.o

foo-data.o: foo-data.c
	gcc -g -O0 -I$(FAKEACC_INC) -c foo-data.c -o foo-data.o

foo-kernel.o: foo-kernel.c
	gcc -g -O0 -I$(FAKEACC_INC) -c foo-kernel.c -o foo-kernel.o

foo-fakeacc: foo-fakeacc.o foo-data.o foo-kernel.o $(FAKEACC_LIB)/runtime.o main-foo.o
	gcc foo-fakeacc.o foo-data.o foo-kernel.o $(FAKEACC_LIB)/runtime.o main-foo.o -o foo-fakeacc

check-foo-fakeacc: foo-fakeacc
	./foo-fakeacc

# Libraries

$(FAKEACC_LIB)/runtime.o:
	make -C $(FAKEACC_LIB) runtime.o

