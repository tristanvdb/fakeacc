
#define FAKEACC_STATIC 1

#include "FakeACC/loop.h"
#include "FakeACC/kernel.h"
#include "FakeACC/tile.h"

extern kernel_func_ptr kernel_0;

struct tile_desc_t tiles_loop_1[2] = {
  { 0, e_tile_num_it,  4 },
  { 1, e_tile_dynamic, 0 }
};

struct loop_desc_t loop_desc[1] = {
  { 0, 2, tiles_loop_1 }
};

struct kernel_desc_t kernel_desc[1] = {
  { 2, 1, 1, 2, loop_desc, &kernel_0 }
};

