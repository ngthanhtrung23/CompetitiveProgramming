#include <bits/stdc++.h>
using namespace std;
const int oo = 1000111000;

pair <int,int> a[150150];
int n, k, f[150150][11];

int check(int X)
{
  for (int i = 0; i <= n; i++)
    for (int j = 1; j <= k; j++)
      f[i][j] = oo;

  for (int j = 1; j <= k; j++)
    for (int i = 1; i <= n; i++)
    {
      if (a[i].first - a[i].second >= X + f[i - 1][j - 1])
        f[i][j] = min(f[i][j], f[i - 1][j - 1] + a[i].second);
      f[i][j] = min(f[i][j], f[i - 1][j]);
    }
        
  return f[n][k] < oo;
}

int main()
{
  ios::sync_with_stdio(0);
  //freopen("k.in", "r", stdin);
  int test;
  cin >> test;
  while (test--)
  {
    cin >> n >> k;
    k++;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    
    int low = 0, high = 1 << 20, ans = 0;
    while (low <= high)
    {
      int mid = (low + high) / 2;
      if (check(mid)) ans = mid, low = mid + 1;
      else high = mid - 1;
    }
    
    cout << ans << endl;
  }
}