#include <bits/stdc++.h>
using namespace std;
const int BASE1 = int(1e9) + 9, BASE2 = int(1e9) + 7;

int m, n;
long long a[211][211], c[211][211];

long long power(long long x, long long y, int BASE)
{
  if (!y) return 1;
  long long res = power(x, y / 2, BASE);
  res = res * res % BASE;
  if (y % 2)
    res = res * x % BASE;
  return res;
}

int solve (long long MOD) {
    vector<int> where (m, -1);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            a[i][j] = (c[i][j] % MOD + MOD) % MOD;
        }

    int col, row;
    for (col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (a[i][col] > a[sel][col])
                sel = i;
        if (a[sel][col] == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
 
        for (int i=0; i<n; ++i)
            if (i != row) {
                long long c = a[i][col] * power(a[row][col], MOD - 2, MOD) % MOD;
                for (int j=col; j<=m; ++j)
                    a[i][j] = (a[i][j] - a[row][j] * c % MOD + MOD) % MOD;
            }
        ++row;
    }
    return row;
}

int main()
{
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> c[i][j];

  int r1 = solve(BASE1);
  int r2 = solve(BASE2);
  assert(r1 == r2);
  cout << min(r1, r2) << endl;
//  cout << min(solve(BASE1), solve(BASE2)) << endl;
}
