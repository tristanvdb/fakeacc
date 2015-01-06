
#include "FakeACC/defs.h"

#ifndef __FAKEACC_LOOP_H__
#define __FAKEACC_LOOP_H__

#if FAKEACC_SPACE(__FAKEACC_STATIC__)
struct loop_desc_t {
  int idx;
  int num_tiles;
  struct tile_desc_t * tile_desc;
};
#endif /* FAKEACC_SPACE */

#if FAKEACC_SPACE_(__FAKEACC_USER__, __FAKEACC_KERNEL__)
struct loop_t {
  int lower;
  int upper;
  int stride;
};
#endif /* FAKEACC_SPACE */

#endif /* __FAKEACC_LOOP_H__ */

