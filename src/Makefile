
FAKEACC_DIR?=..
FAKEACC_FLAGS?=
FAKEACC_CONFIG?=

include $(FAKEACC_DIR)/config.mk

########################

all: compiler

check: check-foo check-bar check-test_1

clean:
	rm -f compiler.o compiler

########################

compiler.o: compiler.cpp $(FAKEACC_INC)/DLX/FakeACC/language.hpp $(FAKEACC_INC)/KLT/FakeACC/fakeacc.hpp 
	c++ -g $(INCLUDES) -DFAKEACC_INC_PATH=\"$(FAKEACC_INC)\" -c compiler.cpp -o compiler.o

compiler: compiler.o $(FAKEACC_LIB)/dlx/fakeacc/language.o \
                     $(FAKEACC_LIB)/dlx/fakeacc/frontend.o \
                     $(FAKEACC_LIB)/dlx/fakeacc/clauses.o \
                     $(FAKEACC_LIB)/dlx/fakeacc/constructs.o \
                     $(FAKEACC_LIB)/klt/fakeacc/fakeacc.o
	c++ -g $(LIBDIRS) $(LIBS) \
                                  $(FAKEACC_LIB)/dlx/fakeacc/language.o \
                                  $(FAKEACC_LIB)/dlx/fakeacc/frontend.o \
                                  $(FAKEACC_LIB)/dlx/fakeacc/clauses.o \
                                  $(FAKEACC_LIB)/dlx/fakeacc/constructs.o \
                                  $(FAKEACC_LIB)/klt/fakeacc/fakeacc.o \
                                  compiler.o \
                               -o compiler

########################

check-foo: rose_foo.c

check-bar: rose_bar.c

check-test_1: rose_test_1.c

rose_%.c: $(FAKEACC_EXAMPLES)/%.c  compiler
	./compiler -DSKIP_ROSE_BUILTIN_DECLARATIONS -I$(FAKEACC_INC) -c $<

########################

$(FAKEACC_LIB)/dlx/fakeacc/language.o:
	make -C $(FAKEACC_LIB)/dlx/fakeacc language.o

$(FAKEACC_LIB)/dlx/fakeacc/frontend.o:
	make -C $(FAKEACC_LIB)/dlx/fakeacc frontend.o

$(FAKEACC_LIB)/dlx/fakeacc/clauses.o:
	make -C $(FAKEACC_LIB)/dlx/fakeacc clauses.o

$(FAKEACC_LIB)/dlx/fakeacc/constructs.o:
	make -C $(FAKEACC_LIB)/dlx/fakeacc constructs.o

########################

$(FAKEACC_LIB)/klt/fakeacc/fakeacc.o:
	make -C $(FAKEACC_LIB)/klt/fakeacc fakeacc.o

########################

