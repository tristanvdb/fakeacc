
ROSE_DIR?=/media/ssd/projects/currents/RoseACC-workspace-release/install_dir/
AST_TO_GRAPHVIZ_DIR?=/media/ssd/projects/currents/ast-to-graphviz/
BOOST_DIR?=/media/ssd/boost/install/1_45_0/

FAKEACC_INC=$(FAKEACC_DIR)/include
FAKEACC_LIB=$(FAKEACC_DIR)/lib
FAKEACC_EXAMPLES=$(FAKEACC_DIR)/examples

BOOST_LIBS=-lboost_filesystem -lboost_system -lboost_iostreams -lboost_date_time -lboost_wave -lboost_thread -lboost_program_options -lboost_regex

ROSE_LIBS=-lrose
DLX_LIBS=-lDLX-core
MFB_LIBS=-lMFB-sage
MDCG_LIBS=-lMDCG
KLT_LIBS=-lKLT -lKLT-core

INCLUDES=-I$(FAKEACC_INC) -I$(ROSE_DIR)/include/ -I$(ROSE_DIR)/include/rose -I$(BOOST_DIR)/include

LIBDIRS=-L$(ROSE_DIR)/lib -L$(BOOST_DIR)/lib

LIBS=$(BOOST_LIBS) $(ROSE_LIBS) $(DLX_LIBS) $(MFB_LIBS) $(MDCG_LIBS) $(KLT_LIBS)

