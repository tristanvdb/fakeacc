
#define FAKEACC_USER 1

#include "FakeACC/loop.h"
#include "FakeACC/kernel.h"

void foo(int n, float ** a, float b) {
  struct kernel_t * kernel = build_kernel(0);

  kernel->data[0] = &(a[0][0]);
  kernel->data[1] = &(b);

  kernel->param[0] = n;

  kernel->loops[0].lower = 0;
  kernel->loops[0].upper = n;
  kernel->loops[0].stride = 1;

  execute_kernel(kernel);
}

