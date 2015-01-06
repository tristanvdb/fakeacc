
INC_DIR=../../include

lib: runtime.o

runtime.o: runtime.c $(INC_DIR)/FakeACC/kernel.h $(INC_DIR)/FakeACC/loop.h $(INC_DIR)/FakeACC/tile.h
	gcc -g -O0 -I$(INC_DIR) -c runtime.c -o runtime.o

clean:
	rm -rf runtime.o

