FakeACC
=======

FakeACC is a project to demonstrate tools concived to build RoseACC.
RoseACC is a compiler for OpenACC an extension of C/C++.
OpenACC uses directives (C preproccessor's #pragma) to provide the
compiler with information on how to parallelize.

In FakeACC region of C/C++ codes are outlined and loops can be tiled.

## Language FakeACC

A = A + bI

![equation](http://www.sciweavers.org/tex2img.php?eq=A%20%3D%20A%20%2B%20bI%0A%0AA_%7Bi%20i%7D%20%3D%20%5Csum_%7Bi%3D0%7D%5E%7Bn%7D%20A_%7Bi%20i%7D%20%2B%20b&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0())

```c++
void foo(int n, float ** a, float b) {
  for (int i = 0; i < n; i++)
    a[i][i]+=b;
}
```

## Usage 

### Building FakeACC

```sh
export PROJECT_DIR=/media/ssd/projects/currents # For my convenience, NOT used by Makefile
export ROSE_DIR=$PROJECT_DIR/RoseACC-workspace/install_dir/
export BOOST_DIR=/media/ssd/boost/install/1_45_0
export LD_LIBRARY_PATH=$BOOST_DIR/lib:$ROSE_DIR/lib:$AST_TO_GRAPHVIZ_DIR/lib:$LD_LIBRARY_PATH
make fakeacc
```

### Building Vizualizations

```sh
export AST_TO_GRAPHVIZ_DIR=$PROJECT_DIR/ast-to-graphviz/
export LD_LIBRARY_PATH=$BOOST_DIR/lib:$ROSE_DIR/lib:$AST_TO_GRAPHVIZ_DIR/lib:$LD_LIBRARY_PATH
make viz
```

### 

