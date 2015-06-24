
FAKEACC_DIR?=../../..
FAKEACC_FLAGS?=
FAKEACC_CONFIG?=

include $(FAKEACC_DIR)/config.mk

all: clauses.o constructs.o language.o frontend.o

clauses.o: clauses.cpp
	g++ -g -O0 $(INCLUDES) -I$(FAKEACC_INC) -c clauses.cpp -o clauses.o

constructs.o: constructs.cpp
	g++ -g -O0 $(INCLUDES) -I$(FAKEACC_INC) -c constructs.cpp -o constructs.o

frontend.o: frontend.cpp
	g++ -g -O0 $(INCLUDES) -I$(FAKEACC_INC) -c frontend.cpp -o frontend.o

language.o: language.cpp
	g++ -g -O0 $(INCLUDES) -I$(FAKEACC_INC) -c language.cpp -o language.o

clean:
	rm -f clauses.o constructs.o language.o frontend.o

