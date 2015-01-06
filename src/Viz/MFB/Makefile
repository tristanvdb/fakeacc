
ROSE_DIR?=/media/ssd/projects/currents/RoseACC-workspace/install_dir/
AST_TO_GRAPHVIZ_DIR?=/media/ssd/projects/currents/ast-to-graphviz/
BOOST_DIR?=/media/ssd/boost/install/1_45_0/

FAKEACC_BASE=../../..
FAKEACC_INC=$(FAKEACC_BASE)/include
FAKEACC_LIB=$(FAKEACC_BASE)/lib/fakeacc
FAKEACC_FLAGS=
FAKEACC_EXAMPLES=$(FAKEACC_BASE)/examples

INCLUDES=-I$(ROSE_DIR)/include/ -I$(ROSE_DIR)/include/rose -I$(BOOST_DIR)/include

LIBDIRS=-L$(ROSE_DIR)/lib -L$(BOOST_DIR)/lib

LIBS=-lMFB-sage -lMDCG -lrose -lboost_filesystem -lboost_system -lboost_iostreams -lboost_date_time -lboost_wave -lboost_thread -lboost_program_options -lboost_regex

########################

bin: mfb-grapher

check: check-mfb-grapher

clean:
	rm -rf mfb-grapher *.o *.dot *.png empty.c

########################

mfb-grapher.o: mfb-grapher.cpp
	c++ -g $(INCLUDES) -I$(AST_TO_GRAPHVIZ_DIR)/include -DFAKEACC_INC_PATH=\"$(FAKEACC_INC)\" -c mfb-grapher.cpp -o mfb-grapher.o

mfb-grapher: mfb-grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o
	c++ -g $(LIBDIRS) $(LIBS) mfb-grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o -o mfb-grapher

check-mfb-grapher: mfb-grapher empty.c
	./mfb-grapher -I$(FAKEACC_INC) -DSKIP_ROSE_BUILTIN_DECLARATIONS -c empty.c
	dot -Tpng tile.h.dot -o tile.png
	dot -Tpng loop.h.dot -o loop.png
	dot -Tpng kernel.h.dot -o kernel.png

empty.c:
	echo > empty.c

########################

$(AST_TO_GRAPHVIZ_DIR)/lib/default.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib default.o

$(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib cluster.o

########################

