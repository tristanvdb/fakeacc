
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "FakeACC/kernel.h"
#include "FakeACC/loop.h"
#include "FakeACC/tile.h"

struct kernel_t * build_kernel(int idx) {
  struct kernel_desc_t * desc = &(kernel_desc[idx]);

  int size = sizeof(struct kernel_t)
           + desc->num_data  * sizeof(void *)
           + desc->num_param * sizeof(int)
           + desc->num_loops * sizeof(struct loop_t)
           + desc->num_tiles * sizeof(struct tile_t);

  void * alloc = malloc(size);

  memset(alloc, 0, size);

  struct kernel_t * res = (struct kernel_t *)alloc;
      res->desc  = desc;
      res->data  =         (void **)(alloc += sizeof(struct kernel_t));
      res->param =           (int *)(alloc += desc->num_data  * sizeof(void *));
      res->loops = (struct loop_t *)(alloc += desc->num_param * sizeof(int));
      res->tiles = (struct tile_t *)(alloc += desc->num_loops * sizeof(struct loop_t));

  return res;
}

void execute_kernel(struct kernel_t * kernel) {
  const struct kernel_desc_t * desc = kernel->desc;

  int loop_it, tile_it;

  for (loop_it = 0; loop_it < desc->num_loops; loop_it++) {
    const int loop_idx = desc->loop_desc[loop_it].idx;
    
    int length = kernel->loops[loop_idx].upper - kernel->loops[loop_idx].lower;
    kernel->tiles[desc->loop_desc[loop_it].num_tiles-1].stride = kernel->loops[loop_idx].stride;

    for (tile_it = 0; tile_it < desc->loop_desc[loop_it].num_tiles; tile_it++) {
      const int tile_idx = desc->loop_desc[loop_it].tile_desc[tile_it].idx;
      const int param = desc->loop_desc[loop_it].tile_desc[tile_it].param;

      kernel->tiles[tile_idx].length = length;

      if (desc->loop_desc[loop_it].tile_desc[tile_it].kind == e_tile_stride) {
        if (kernel->tiles[tile_idx].stride == 0)
          kernel->tiles[tile_idx].stride = param;
        else
          assert(kernel->tiles[tile_idx].stride == param);
      }
      else if (desc->loop_desc[loop_it].tile_desc[tile_it].kind == e_tile_num_it) {
        if (kernel->tiles[tile_idx].stride == 0)
          kernel->tiles[tile_idx].stride = length / param;
        else
          assert(kernel->tiles[tile_idx].stride == length / param);
      }
      else break;

      assert(kernel->tiles[tile_idx].stride > 0);

//    kernel->tiles[tile_idx].remain = length % kernel->tiles[tile_idx].stride;

      length = kernel->tiles[tile_idx].stride;
    }

    int stride = kernel->loops[loop_idx].stride;
    for (tile_it = desc->loop_desc[loop_it].num_tiles - 1; tile_it >= 1; tile_it--) {
      const int tile_idx = desc->loop_desc[loop_it].tile_desc[tile_it].idx;
      const int param = desc->loop_desc[loop_it].tile_desc[tile_it].param;

      if (kernel->tiles[tile_idx].stride == 0)
        kernel->tiles[tile_idx].stride = stride;
      else
        assert(kernel->tiles[tile_idx].stride == stride);

      if (kernel->tiles[tile_idx].length == 0) {
        assert(desc->loop_desc[loop_it].tile_desc[tile_it].kind == e_tile_num_it);
        kernel->tiles[tile_idx].length = stride * param;
//      kernel->tiles[tile_idx].remain = 0;
      }
      else if (desc->loop_desc[loop_it].tile_desc[tile_it].kind == e_tile_dynamic) {
//      kernel->tiles[tile_idx].remain = kernel->tiles[tile_idx].length % kernel->tiles[tile_idx].stride;
        break;
      }
      else break;

      stride = kernel->tiles[tile_idx].length;
    }
  }

  (*desc->kernel_ptr)(kernel->data, kernel->param, kernel->loops, kernel->tiles);
}

