
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

bin: grapher

check: check-grapher

clean:
	rm -rf grapher *.o *.dot *.png empty.c

########################

grapher.o: grapher.cpp
	c++ -g $(INCLUDES) -I$(AST_TO_GRAPHVIZ_DIR)/include -DFAKEACC_INC_PATH=\"$(FAKEACC_INC)/FakeACC\" -c grapher.cpp -o grapher.o

grapher: grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o
	c++ -g $(LIBDIRS) $(LIBS) grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o -o grapher

check-grapher: grapher empty.c
	./grapher -I$(FAKEACC_INC) -DSKIP_ROSE_BUILTIN_DECLARATIONS -c empty.c && ( dot -Tpng mdcg.dot -o mdcg.png || dot -Tpng model.dot -o model.png || dot -Tpng model-class.dot -o model-class.png || dot -Tpng model-function.dot -o model-function.png || dot -Tpng model-variable.dot -o model-variable.png )

empty.c:
	echo > empty.c

########################

$(AST_TO_GRAPHVIZ_DIR)/lib/default.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib default.o

$(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib cluster.o

########################

