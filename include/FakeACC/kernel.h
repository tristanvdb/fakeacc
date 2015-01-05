
#ifndef __KERNEL_H__
#define __KERNEL_H__

struct kernel_desc_t {
  int num_args;
  int num_loops;
  struct loop_desc_t * loop_desc;
};

struct kernel_t {
  struct kernel_desc_t * desc;
  void ** args;
  struct loop_t * loops;
};

struct kernel_t * build_kernel(
    struct kernel_desc_t * desc
);

void execute_kernel(
    struct kernel_t * kernel
);

extern struct kernel_desc_t my_kernel_desc[];

#endif /* __KERNEL_H__ */

