
void foo(int n, float ** a, float b) {
  #pragma fakeacc kernel data(a[0:n][0:n], b)
  #pragma fakeacc loop tile(static, 64) tile(dynamic)
  for (int i = 0; i < n; i++)
    a[i][i]+=b;
}

