#include <bits/stdc++.h>
using namespace std;
const string C = "ACGT";
const int oo = 27081993;

int n, f[111][111][2][111], a[111];
pair <int,int> tr[111][111][2][111];
vector <int> open[4];

int dp(int i, int x1, int x2, int x3)
{
  if (x1 < 0 || x2 < 0 || x3 < 0)
    return oo;
  if ((x1 && x3) || x2 > 1)
    return oo;
  
  if (i > n)
    return x1 + x2 + x3 <= 1 ? x1 + x2 + x3 : oo;

  int &res = f[i][x1][x2][x3];
  if (res >= 0)
    return res;

  res = oo;
  for (int open = 0; open <= 3; open++)
    for (int close = 0; close <= 3; close++)
    {
      if (open && close && open == close)
        continue;

      int y1 = x1 + (open == 1) - (close == 1);
      int y2 = x2 + (open == 2) - (close == 2);
      int y3 = x3 + (open == 3) - (close == 3);

      if ((y1 + y2 * 2 + y3 * 3) % 4 == a[i])
      {
        int cur = dp(i + 1, y1, y2, y3) + (close > 0);
        if (cur < res)
        {
          res = cur;
          tr[i][x1][x2][x3] = {open, close};
        }
      }
    }

  return res;
}

void pop(int i, int x)
{
  assert(!open[x].empty());
  cout << open[x].back() << ' ' << i - 1 << ' ' << x << endl;
  open[x].pop_back();
}

void trace(int i, int x1, int x2, int x3)
{
  if (i > n) 
  {
    if (x1) pop(i, 1);
    if (x2) pop(i, 2);
    if (x3) pop(i, 3);
    return;
  }

  auto u = tr[i][x1][x2][x3];
  x1 += (u.first == 1) - (u.second == 1);
  x2 += (u.first == 2) - (u.second == 2);
  x3 += (u.first == 3) - (u.second == 3);
  if (u.first)
    open[u.first].push_back(i);
  if (u.second)
    pop(i, u.second);
  trace(i + 1, x1, x2, x3);
}

int main()
{
  freopen("transform.in", "r", stdin);
  freopen("transform.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s, t;
  cin >> s >> t;
  n = s.size();
  for (int i = 0; i < n; i++)
  {
    int x = 0, y = 0;
    while (C[x] != s[i]) x++;
    while (C[y] != t[i]) y++;
    a[i + 1] = (y + 4 - x) % 4;
  }

  memset(f, -1, sizeof f);
  cout << dp(1, 0, 0, 0) << endl;
  trace(1, 0, 0, 0);
}