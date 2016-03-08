#include <bits/stdc++.h>
using namespace std;

int n, W, f[100100][20], lg2[200200];

int getMax(int l, int r)
{
  int lg = lg2[r - l];
  return max(f[l][lg], f[r - (1 << lg)][lg]);
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> W;
  for (int i = 0; i < n; i++)
    cin >> f[i][0];

  for (int i = 0, j = 1; i <= 16; i++)
    while (j < 1 << i + 1)
      lg2[j++] = i;

  for (int j = 1; 1 << j <= n; j++)
    for (int i = 0; i + (1 << j) <= n; i++)
      f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);

  for (int line = 1; line <= n; line++)
  {
    long long sumW = -1;
    for (int i = 0; i < n; i += line)
      sumW += getMax(i, min(n, i + line)) + 1;
    if (sumW <= W)
    {
      cout << line << endl;
      return 0;
    }
  }
}