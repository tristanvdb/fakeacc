
#include "FakeACC/defs.h"

#ifndef __FAKEACC_KERNEL_H__
#define __FAKEACC_KERNEL_H__

struct loop_t;
struct tile_t;

#if FAKEACC_SPACE(__FAKEACC_STATIC__)
typedef void (*kernel_func_ptr)(void **, int *, struct loop_t *, struct tile_t *);

struct kernel_desc_t {
  int num_data;
  int num_param;
  int num_loops;
  int num_tiles;
  struct loop_desc_t * loop_desc;
  kernel_func_ptr kernel_ptr;
};

extern struct kernel_desc_t kernel_desc[];
#endif /* FAKEACC_SPACE */

#if FAKEACC_SPACE(__FAKEACC_USER__)
struct kernel_t {
  struct kernel_desc_t * desc;
  void ** data;
  int   * param;
  struct loop_t * loops;
  struct tile_t * tiles; // filled by runtime
};

struct kernel_t * build_kernel(int idx);

void execute_kernel(struct kernel_t * kernel);
#endif /* FAKEACC_SPACE */

#endif /* __KERNEL_H__ */

