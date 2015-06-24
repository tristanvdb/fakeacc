
#include "FakeACC/defs.h"

#ifndef __FAKEACC_TILE_H__
#define __FAKEACC_TILE_H__

struct tile_desc_t {
  int idx;
  enum tile_kind_e {
    e_tile_static,
    e_tile_dynamic
  } kind;
  int param;
};

struct tile_t {
  int length;
  int stride;
//int remain;
};

#endif /* __FAKEACC_TILE_H__ */

