
ROSE_DIR?=/media/ssd/projects/currents/RoseACC-workspace/install_dir/
AST_TO_GRAPHVIZ_DIR?=/media/ssd/projects/current/ast-to-graphviz/
BOOST_DIR?=/media/ssd/boost/install/1_45_0/

INCLUDES=-I$(ROSE_DIR)/include/ -I$(ROSE_DIR)/include/rose -I$(BOOST_DIR)/include

LIBDIRS=-L$(ROSE_DIR)/lib -L$(BOOST_DIR)/lib

LIBS=-lMFB-sage -lMDCG -lrose -lboost_filesystem -lboost_system -lboost_iostreams -lboost_date_time -lboost_wave -lboost_thread -lboost_program_options -lboost_regex

########################

all: mfb-grapher mdcg-grapher

check: check-mfb-grapher check-mdcg-grapher

clean:
	rm -rf mfb-grapher *.o *.dot *.png

########################

mfb-grapher.o: mfb-grapher.cpp
	c++ -g $(INCLUDES) -I$(AST_TO_GRAPHVIZ_DIR)/include -c mfb-grapher.cpp -o mfb-grapher.o

mfb-grapher: mfb-grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o
	c++ -g $(LIBDIRS) $(LIBS) mfb-grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o -o mfb-grapher

check-mfb-grapher: mfb-grapher
	./mfb-grapher -DSKIP_ROSE_BUILTIN_DECLARATIONS -c empty.c

########################

mdcg-grapher.o: mdcg-grapher.cpp
	c++ -g $(INCLUDES) -I$(AST_TO_GRAPHVIZ_DIR)/include -c mdcg-grapher.cpp -o mdcg-grapher.o

mdcg-grapher: mdcg-grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o
	c++ -g $(LIBDIRS) $(LIBS) mdcg-grapher.o $(AST_TO_GRAPHVIZ_DIR)/lib/default.o $(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o -o mdcg-grapher

check-mdcg-grapher: mdcg-grapher
	./mdcg-grapher -DSKIP_ROSE_BUILTIN_DECLARATIONS -c empty.c

########################

$(AST_TO_GRAPHVIZ_DIR)/lib/default.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib default.o

$(AST_TO_GRAPHVIZ_DIR)/lib/cluster.o:
	make -C $(AST_TO_GRAPHVIZ_DIR)/lib cluster.o

########################

