#include <bits/stdc++.h>
using namespace std;
const long long MAX = (long long)1e18;

long long f[20];
unordered_set <long long> s;

void go(int i, long long x)
{
  if (i > 19) return;
  if (!s.count(x))
    s.insert(x);
  if (MAX / x >= f[i])
    go(i, x * f[i]);
  go(i + 1, x);
}

int main()
{
  ios::sync_with_stdio(0);
  f[1] = 1;
  for (int i = 2; i < 20; i++)
    f[i] = f[i - 1] * i;

  go(2, 1);

  int test;
  cin >> test;
  long long n;
  while (test--)
  {
    cin >> n;
    cout << (s.count(n) ? "YES" : "NO") << '\n';
  }
}