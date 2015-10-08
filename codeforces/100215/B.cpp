#include <bits/stdc++.h>
using namespace std;

long long solve(int m, int n)
{
  int f[50] = {1, 2, 3}, k = 1;
  if (n % 2 == 0) k = 2;
  if (n % 3 == 0) k = 3;
  for (int i = 3; i < 50 && f[i - 1] <= n; i++)
  {
    f[i] = f[i - 1] + f[i - 2];
    if (n % f[i] == 0) k = f[i];
  }
  return n / k * (k - 1LL) * m;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("choco.in", "r", stdin);
  freopen("choco.out", "w", stdout);
  int m, n;
  cin >> m >> n;
  cout << max(solve(m, n), solve(n, m)) << endl;
}