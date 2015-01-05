
#include "loop.h"
#include "kernel.h"

void foo(int n, float ** a) {
  struct kernel_t * kernel = build_kernel(&(my_kernel_desc[0]));

  kernel->args[0] = &(a[0][0]);

  kernel->loops[0].lower_bound = 0;
  kernel->loops[0].upper_bound = n;
  kernel->loops[0].increment = 1;

  execute_kernel(kernel);
}

