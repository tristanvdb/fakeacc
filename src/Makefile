
TILEK_DIR?=..
TILEK_FLAGS?=
TILEK_CONFIG?=

include $(TILEK_DIR)/config.mk

########################

all: compiler

check: check-foo check-bar check-test_1

clean:
	rm -f rose_*.c *-kernel.c *.o compiler

########################

compiler.o: compiler.cpp $(TILEK_INC)/DLX/TileK/language.hpp $(TILEK_INC)/KLT/TileK/tilek.hpp 
	c++ -g $(INCLUDES) -DTILEK_INC_PATH=\"$(TILEK_INC)\" -c compiler.cpp -o compiler.o

compiler: compiler.o $(TILEK_LIB)/dlx/tilek/language.o \
                     $(TILEK_LIB)/dlx/tilek/frontend.o \
                     $(TILEK_LIB)/dlx/tilek/clauses.o \
                     $(TILEK_LIB)/dlx/tilek/constructs.o \
                     $(TILEK_LIB)/klt/tilek/tilek.o
	c++ -g $(LIBDIRS) $(LIBS) \
                                  $(TILEK_LIB)/dlx/tilek/language.o \
                                  $(TILEK_LIB)/dlx/tilek/frontend.o \
                                  $(TILEK_LIB)/dlx/tilek/clauses.o \
                                  $(TILEK_LIB)/dlx/tilek/constructs.o \
                                  $(TILEK_LIB)/klt/tilek/tilek.o \
                                  compiler.o \
                               -o compiler

########################

check-foo: rose_foo.c

check-bar: rose_bar.c

check-test_1: rose_test_1.c

rose_%.c: $(TILEK_EXAMPLES)/%.c  compiler
	./compiler -DSKIP_ROSE_BUILTIN_DECLARATIONS -I$(TILEK_INC) -c $<

########################

$(TILEK_LIB)/dlx/tilek/language.o:
	make -C $(TILEK_LIB)/dlx/tilek language.o

$(TILEK_LIB)/dlx/tilek/frontend.o:
	make -C $(TILEK_LIB)/dlx/tilek frontend.o

$(TILEK_LIB)/dlx/tilek/clauses.o:
	make -C $(TILEK_LIB)/dlx/tilek clauses.o

$(TILEK_LIB)/dlx/tilek/constructs.o:
	make -C $(TILEK_LIB)/dlx/tilek constructs.o

########################

$(TILEK_LIB)/klt/tilek/tilek.o:
	make -C $(TILEK_LIB)/klt/tilek tilek.o

########################

