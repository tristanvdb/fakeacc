
FAKEACC_INC=../include
FAKEACC_LIB=../lib/fakeacc

foo.o: rose_foo.c
	gcc -g -O0 -I$(FAKEACC_INC) -c rose_foo.c -o foo.o

foo-data.o: foo-data.c
	gcc -g -O0 -I$(FAKEACC_INC) -c foo-data.c -o foo-data.o

foo-kernel.o: foo-kernel.c
	gcc -g -O0 -I$(FAKEACC_INC) -c foo-kernel.c -o foo-kernel.o

main-foo.o: main-foo.c
	gcc -g -O0 -c main-foo.c -o main-foo.o

foo: foo.o foo-data.o foo-kernel.o $(FAKEACC_LIB)/runtime.o main-foo.o
	gcc foo.o foo-data.o foo-kernel.o $(FAKEACC_LIB)/runtime.o main-foo.o -o foo


$(FAKEACC_LIB)/runtime.o:
	make -C $(FAKEACC_LIB) runtime.o

clean:
	rm -rf foo foo.o foo-data.o foo-kernel.o main-foo.o

