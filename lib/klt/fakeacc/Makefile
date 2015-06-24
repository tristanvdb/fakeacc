
FAKEACC_DIR?=../../..
FAKEACC_FLAGS?=
FAKEACC_CONFIG?=

include $(FAKEACC_DIR)/config.mk

lib: fakeacc.o

fakeacc.o: fakeacc.cpp
	g++ -g -O0 $(INCLUDES) -I$(FAKEACC_INC) -c fakeacc.cpp -o fakeacc.o

clean:
	rm -f fakeacc.o

