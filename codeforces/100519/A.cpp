#include <bits/stdc++.h>
using namespace std;
const string DIRECTIONS = "URDL";

int n, a[111][111];

int move(int z)
{
  int res = 0;
  
  if (!z)
  {
    for (int j = 1; j <= n; j++)
      for (int i = 1, cur = 1, merged = 0; i <= n; i++)
        if (a[i][j])
        {
          int x = a[i][j];
          a[i][j] = 0;
          if (merged != x)
          {
            merged = x;
            a[cur++][j] = x;
          }
          else 
          {
            res += x * 2;
            a[cur - 1][j] *= 2;
            merged = 0;
          }
        }
  }
  else if (z == 2)
  {
    for (int j = 1; j <= n; j++)
      for (int i = n, cur = n, merged = 0; i; i--)
        if (a[i][j])
        {
          int x = a[i][j];
          a[i][j] = 0;
          if (merged != x)
          {
            merged = x;
            a[cur--][j] = x;
          }
          else 
          {
            res += x * 2;
            a[cur + 1][j] *= 2;
            merged = 0;
          }
        }
  }
  else if (z == 3)
  {
    for (int i = 1; i <= n; i++)
      for (int j = 1, cur = 1, merged = 0; j <= n; j++)
        if (a[i][j])
        {
          int x = a[i][j];
          a[i][j] = 0;
          if (merged != x) 
          {
            merged = x;
            a[i][cur++] = x;
          }
          else 
          {
            res += x * 2;
            a[i][cur - 1] *= 2;
            merged = 0;
          }
        }
  }
  else
  {
    for (int i = 1; i <= n; i++)
      for (int j = n, cur = n, merged = 0; j; j--)
        if (a[i][j])
        {
          int x = a[i][j];
          a[i][j] = 0;
          if (merged != x) 
          {
            merged = x;
            a[i][cur--] = x;
          }
          else 
          {
            res += x * 2;
            a[i][cur + 1] *= 2;
            merged = 0;
          }
        }
  }
  
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  int k, v, x, y;
  char z;
  
  cin >> n >> k;
  while (k--)
  {
    cin >> v >> x >> y;
    a[x][y] = v;
  }
  
  long long ans = 0;
  cin >> k;
  while (k--)
  {
    cin >> z >> v >> x >> y;
    for (int i = 0; i < 4; i++)
      if (DIRECTIONS[i] == z)
        ans += move(i);
    a[x][y] = v;
  }
  
  cout << ans << endl;
}
