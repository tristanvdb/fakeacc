
TILEK_DIR?=../../..
TILEK_FLAGS?=
TILEK_CONFIG?=

include $(TILEK_DIR)/config.mk

all: tilek.o

tilek.o: tilek.cpp
	g++ -g -O0 $(INCLUDES) -I$(TILEK_INC) -c tilek.cpp -o tilek.o

clean:
	rm -f tilek.o

