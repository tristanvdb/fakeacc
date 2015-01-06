
#define FAKEACC_KERNEL 1

#include "FakeACC/loop.h"
#include "FakeACC/tile.h"

inline float * get_data_a(void ** data, int * param, int idx_0, int idx_1) {
  float * data_a = (float *)(data[0]);
  
  return data_a + idx_0 * param[0] + idx_1;
}

inline float get_data_b(void ** data, int * param) {
  float * data_b = (float *)(data[1]);
  
  return data_b[0];
}

void kernel_0(void ** data, int * param, struct loop_t * loops, struct tile_t * tiles) {
  int it_0_0;
  int it_0_1;
  for (it_0_0 = loops[0].lower; it_0_0 < loops[0].lower + tiles[0].length; it_0_0 += tiles[0].stride) {
    for (it_0_1 = it_0_0; it_0_1 < it_0_0 + tiles[1].length; it_0_1 += tiles[1].stride) {
      *get_data_a(data, param, it_0_1, it_0_1) += get_data_b(data, param);
    }
  }
}

