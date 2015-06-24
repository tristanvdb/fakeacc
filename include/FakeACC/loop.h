
#include "FakeACC/defs.h"

#ifndef __FAKEACC_LOOP_H__
#define __FAKEACC_LOOP_H__

struct loop_desc_t {
  int idx;
  int num_tiles;
  struct tile_desc_t * tile_desc;
};

struct loop_t {
  int lower;
  int upper;
  int stride;
};

#endif /* __FAKEACC_LOOP_H__ */

