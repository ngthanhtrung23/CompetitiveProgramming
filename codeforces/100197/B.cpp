#include <bits/stdc++.h>
using namespace std;
const unsigned long long oo = 18446744073709551615LL;

vector <int> a[100];
vector <string> ans;
int M, tr[100][100], blocked[100];
unsigned long long f[100][100];

string toStr(int x)
{
  string res = "";
  while (x)
  {
    res += char(x % 10 + '0');
    x /= 10;
  }
  reverse(res.begin(), res.end());
  return res;
}

string move(int from, int to)
{
  assert(!a[from].empty());
  int x = a[from].back();
  a[from].pop_back();
  string res = "move "; 
  res += toStr(x);
  res += " from ";
  res += toStr(from);
  res += " to ";
  res += toStr(to);
  if (!a[to].empty())
  {
    res += " atop ";
    res += toStr(a[to].back());
  }
  a[to].push_back(x);
  return res;
}

void solve(int n, int m, int from, int to)
{
  // Case 1
  if (n == 1)
  {
    ans.push_back(move(from, to));
    return;
  }

  // Case 2
  if (n < m)
  {
    vector <int> usedPegs;
    int cnt = 0;
    for (int i = 1; i <= M; i++)
      if (i != to && i != from && !blocked[i] && cnt < n - 1)
      {
        ans.push_back(move(from, i));
        usedPegs.push_back(i);
        cnt++;
      }

    ans.push_back(move(from, to));

    reverse(usedPegs.begin(), usedPegs.end());
    for (auto peg : usedPegs)
      ans.push_back(move(peg, to));

    return;
  }

  // Case 3
  int target = 0;
  for (int i = 1; i <= M; i++)
    if (i != to && i != from && !blocked[i])
    {
      target = i;
      break;
    }

  if (m == 3)
  {
    solve(n - 1, m, from, target);
    ans.push_back(move(from, to));
    solve(n - 1, m, target, to);
  }
  else 
  {
    solve(tr[n][m], m, from, target); 
    blocked[target] = 1;
    solve(n - tr[n][m], m - 1, from, to);
    blocked[target] = 0;
    solve(tr[n][m], m, target, to);   
  }
}

void init()
{
  for (int j = 3; j <= 65; j++)
    f[1][j] = 1;
  for (int i = 2; i <= 64; i++)
  {
    f[i][3] = f[i - 1][3] * 2 + 1;
    for (int j = 4; j <= 65; j++)
    {
      f[i][j] = oo;
      for (int k = 1; k < i; k++)
        if (f[i][j] > f[k][j] * 2 + f[i - k][j - 1])
        {
          f[i][j] = f[k][j] * 2 + f[i - k][j - 1];
          tr[i][j] = k;
        }
    }
  }
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("hanoi.in", "r", stdin);
  freopen("hanoi.out", "w", stdout);

  init();

  int n, m;
  cin >> n >> m;
  M = m;
  for (int i = n; i >= 1; i--) 
    a[1].push_back(i);
  solve(n, m, 1, m);
  cout << ans.size() << '\n';
  for (auto s : ans)
    cout << s << '\n';
}