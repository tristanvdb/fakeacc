
#include <stdio.h>

void foo(int n, float ** a, float b);

int main(int argc, char ** argv) {

  const int n = 64;

  int i, j;
  float ** a = malloc(n * sizeof(float *));
  float * a_ = malloc(n * n * sizeof(float));
  for (i = 0; i < n; i++) {
    a[i] = a_ + i * n;
    for (j = 0; j < n; j++) {
      a[i][j] = i+j;
    }
  }

  foo(n, a, 3.5);

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf(" | %f", a[i][j]);
    }
    printf(" |\n");
  }

  return 0;
}

