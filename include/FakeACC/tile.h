
#include "FakeACC/defs.h"

#ifndef __FAKEACC_TILE_H__
#define __FAKEACC_TILE_H__

#if FAKEACC_SPACE(__FAKEACC_STATIC__)
struct tile_desc_t {
  int idx;
  enum tile_kind_e {
    e_tile_stride,
    e_tile_num_it,
    e_tile_dynamic
  } kind;
  int param;
};
#endif /* FAKEACC_SPACE */

#if FAKEACC_SPACE_(__FAKEACC_STATIC__, __FAKEACC_KERNEL__)
struct tile_t {
  int length;
  int stride;
//int remain;
};
#endif /* FAKEACC_SPACE */

#endif /* __FAKEACC_TILE_H__ */

