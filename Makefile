
INSTALL_DIR?=/media/ssd/projects/currents/RoseACC-workspace/install_dir/

BOOST_DIR?=/media/ssd/boost/install/1_45_0

AST_TO_GRAPHVIZ_DIR?=../../ast-to-graphviz/

INCLUDES=-I$(INSTALL_DIR)/include/ -I$(INSTALL_DIR)/include/rose -I$(BOOST_DIR)/include

LIBDIRS=-L$(INSTALL_DIR)/lib -L$(BOOST_DIR)/lib

LIBS=-lMFB-sage -lrose -lboost_filesystem -lboost_system -lboost_iostreams -lboost_date_time -lboost_wave -lboost_thread -lboost_program_options -lboost_regex

all: grapher

check: check-grapher

clean:
	rm -rf grapher *.o *.dot *.png

grapher.o: grapher.cpp
	c++ $(INCLUDES) -I$(AST_TO_GRAPHVIZ_DIR)/include -c grapher.cpp -o grapher.o

grapher: grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o
	c++ $(LIBDIRS) $(LIBS) grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o -o grapher

check-grapher: grapher
	./grapher -DSKIP_ROSE_BUILTIN_DECLARATIONS -c empty.c

$(AST_TO_GRAPHVIZ_DIR)/lib/default.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib default.o

$(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib cluster.o

