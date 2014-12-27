FAKE-ACC: An example for MFB and MDCG
=====================================

```sh
export INSTALL_DIR=/media/ssd/projects/currents/RoseACC-workspace/install_dir/
export BOOST_DIR=/media/ssd/boost/install/1_45_0
export LD_LIBRARY_PATH=$BOOST_DIR/lib:$INSTALL_DIR/lib:$LD_LIBRARY_PATH

export AST_TO_GRAPHVIZ_DIR=../../ast-to-graphviz/

make -C $AST_TO_GRAPHVIZ_DIR clean
make clean
make -C $AST_TO_GRAPHVIZ_DIR -j2
make
make check
for i in kernel.h loop.h data.c foo.c
do
  dot -Tpng $i.dot -o $i.png
done
eog loop.h.png
```
