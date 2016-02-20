#include <bits/stdc++.h>
using namespace std;

unsigned long long n, f[66][66][66][2], ans, p[66];

int main()
{
  p[0] = 1;
  for (int i = 1; i < 64; i++)
    p[i] = p[i - 1] * 2;
  cin >> n;
  for (int b = 1; b <= 64; b++)
  {
    memset(f, 0, sizeof f);
    f[64][0][0][0] = 1;
    for (int i = 63; i >= 0; i--)
      for (int j = 0; j <= b; j++)
        for (int mod = 0; mod < b; mod++)
          for (int less = 0; less < 2; less++)
          {
            auto ways = f[i + 1][j][mod][less];
            if (!ways) continue;
            int x = n >> i & 1;
            for (int y = 0; y < 2; y++)
              if (less || x >= y)
                f[i][j + y][(mod + p[i] * y) % b][less | (y < x)] += ways;
          }

    ans += f[0][b][0][0] + f[0][b][0][1];
  }

  cout << ans << endl;
}