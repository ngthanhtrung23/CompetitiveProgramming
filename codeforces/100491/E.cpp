#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7, K = 25, oo = 27081993;

struct Triple
{
  int i, j, s;
};

long long f[33][33][33], g[33][33][33];
vector <Triple> good;

long long calcWays(int a, int b, int c)
{
  long long res = 0;
  memset(g, 0, sizeof g);
  for (auto u : good)
    for (auto v : good)
      if (u.i + v.i < a && u.s + v.s <= c)
      {
        g[u.j][v.j][u.s + v.s] += f[u.i][u.j][u.s] * f[v.i][v.j][v.s];
        g[u.j][v.j][u.s + v.s] %= BASE;
      }

  for (int i = 0; i <= K; i++)
    for (int j = 0; j <= K; j++)
      for (int k = 0; k <= c; k++)
        for (int ii = 0; ii <= K; ii++)
          for (int jj = 0; jj <= K; jj++)
            if (i + ii < b && j + jj < b)
              res = (res + g[i][j][k] * g[ii][jj][c - k]) % BASE;

  return res;
}

int main()
{
  freopen("expedition.in", "r", stdin);
  freopen("expedition.out", "w", stdout);
  int n;
  cin >> n;

  f[0][0][0] = 1;
  good.push_back({0, 0, 0});
  for (int i = 1; i <= K; i++)
  {
    f[1][i][i] = 1;
    good.push_back({1, i, i});
  }

  for (int i = 2; i <= K; i++)
    for (int j = 1; j <= K; j++)
      for (int s = j; s <= K; s++)
      {
        for (int jj = j; jj <= K; jj++)
          f[i][j][s] = (f[i][j][s] + f[i - 1][jj][s - j]) % BASE;
        if (f[i][j][s])
          good.push_back({i, j, s});
      }

  int ans = oo;
  long long ways = 0;
  for (int i = 1; i <= K; i++)
    for (int j = i;; j++)
      if (i * j >= n)
      {
        if (i + j <= ans)
        {
          long long cur = calcWays(i, j, i * j - n) * (i == j ? 1 : 2);
          if (i + j == ans) ways += cur;
          else ways = cur;
          ans = i + j;
        }
        break;
      }

  cout << ways << endl;
}