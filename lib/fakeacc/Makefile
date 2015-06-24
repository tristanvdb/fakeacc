
INC_DIR=../../include

all: runtime.o

runtime.o: runtime.c $(INC_DIR)/TileK/kernel.h $(INC_DIR)/TileK/loop.h $(INC_DIR)/TileK/tile.h
	gcc -g -O0 -I$(INC_DIR) -c runtime.c -o runtime.o

clean:
	rm -rf runtime.o

