#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;

string alphabet;
int C, m, n, a[2020], b[2020], id[2020], minRow[222], minCol[222];
long long cost[222][222], f[2020][2020];
vector <int> ansA, ansB;

int read(int a[])
{
  string s;
  cin >> s;
  for (int i = 0; i < int(s.size()); i++) 
    a[i + 1] = id[s[i]];
  return s.size();
}

void preprocess()
{
  for (int i = 0; i < C; i++)
    for (int j = 0; j < C; j++)
    {
      if (cost[i][j] < cost[i][minRow[i]])
        minRow[i] = j;
      if (cost[i][j] < cost[minCol[j]][j])
        minCol[j] = i;
    }
}

void solve()
{
  f[0][0] = 0;
  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= n; j++)
    {
      if (!i && !j) continue;
      f[i][j] = oo;
      int x = a[i], y = b[j];
      if (i) f[i][j] = min(f[i][j], f[i - 1][j] + cost[x][minRow[x]]);
      if (j) f[i][j] = min(f[i][j], f[i][j - 1] + cost[minCol[y]][y]);
      if (i && j) f[i][j] = min(f[i][j], f[i - 1][j - 1] + cost[x][y]);
    }

  cout << f[m][n] << endl;
}

void trace(int m, int n)
{
  if (!m && !n) return;
  int x = a[m], y = b[n];
  if (m && f[m][n] == f[m - 1][n] + cost[x][minRow[x]])
  {
    ansA.push_back(x);
    ansB.push_back(minRow[x]);
    trace(m - 1, n);
  }
  else if (n && f[m][n] == f[m][n - 1] + cost[minCol[y]][y])
  {
    ansA.push_back(minCol[y]);
    ansB.push_back(y);
    trace(m, n - 1);
  }
  else
  {
    ansA.push_back(x);
    ansB.push_back(y);
    trace(m - 1, n - 1);
  }
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("dissim.in", "r", stdin);
  freopen("dissim.out", "w", stdout);
  cin >> alphabet;
  C = alphabet.size();
  for (int i = 0; i < C; i++) 
    id[alphabet[i]] = i;

  m = read(a);
  n = read(b);

  for (int i = 0; i < C; i++)
    for (int j = 0; j < C; j++)
      cin >> cost[i][j];

  preprocess();
  solve();
  trace(m, n);
  for (int i = int(ansA.size()) - 1; i >= 0; i--)
    cout << alphabet[ansA[i]];
  cout << endl;
  for (int i = int(ansB.size()) - 1; i >= 0; i--)
    cout << alphabet[ansB[i]];
}