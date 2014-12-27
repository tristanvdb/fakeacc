
#ifndef __LOOP_H__
#define __LOOP_H__

struct tile_t {
  enum tile_kind_e {
    e_tile_kind_1,
    e_tile_kind_2,
  } kind;
  int param;
};

struct loop_desc_t {
  int num_tiles;
  struct tile_t * tiles;
};

struct loop_t {
  int lower_bound;
  int upper_bound;
  int increment;
};

#endif /* __LOOP_H__ */

