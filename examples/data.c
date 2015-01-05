
#include "loop.h"
#include "kernel.h"

struct tile_t tiles_loop_1[2] = {
  {e_tile_kind_2, 64},
  {e_tile_kind_1, 0}
};

struct loop_desc_t loop_desc[1] = {
  {2, tiles_loop_1}
};

struct kernel_desc_t my_kernel_desc[1] = {{
  1, 1, loop_desc
}};

