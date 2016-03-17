#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;

int n, m, ans[33], at[33];
pair <int,int> tr[33][1111];
pair <long long,int> a[33];
long long f[33][1111];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("cookies.in", "r", stdin);
  freopen("cookies.out", "w", stdout);
  cin >> n >> m;

  if (m % n == 0)
  {
    cout << 0 << endl;
    for (int i = 1; i <= n; i++)
      cout << m / n << ' ';
    return 0;
  }

  for (int i = 1; i <= n; i++)
  {
    cin >> a[i].first;
    a[i].second = i;
  }

  sort(a + 1, a + n + 1);
  if (m > n * (n + 1))
  {
    cout << a[1].first * (n - 1LL) << endl;
    m -= n;
    ans[a[1].second] = m % (n - 1) + 1;
    for (int i = 2; i <= n; i++)
      ans[a[i].second] = m / (n - 1) + 1;
    for (int i = 1; i <= n; i++)
      cout << ans[i] << ' ';
    return 0;
  }

  for (int i = 2; i <= n; i++)
    a[i].first += a[i - 1].first;

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      f[i][j] = oo;
  f[0][m] = 0;

  for (int i = 0; i < n; i++)
    for (int j = 0; j <= m; j++)
    {
      if (f[i][j] == oo) 
        continue;
      for (int ii = i + 1; ii <= n; ii++)
        for (int k = 1; k * (n - i) <= j; k++)
        {
          int jj = j - k * (n - i);
          long long newF = f[i][j] + (a[ii].first - a[i].first) * (n - ii);
          if (newF < f[ii][jj])
          {
            f[ii][jj] = newF;
            tr[ii][jj] = {i, j};
          }
        }
    }

  cout << f[n][0] << endl;
  for (int i = n, j = 0; i;)
  {
    int ii = tr[i][j].first, jj = tr[i][j].second;
    for (int k = ii + 1; k <= n; k++)
      at[k] += (jj - j) / (n - ii);
    i = ii;
    j = jj;
  }
  for (int i = 1; i <= n; i++)
    ans[a[i].second] = at[i];
  for (int i = 1; i <= n; i++)
    cout << ans[i] << ' ';
}