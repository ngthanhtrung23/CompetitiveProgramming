#include <bits/stdc++.h>
using namespace std;

int n, d[111], isGood[111], visited[111], to[111];
vector <int> path;

int get(int x)
{
  return x == d[x] ? x : d[x] = get(d[x]);
}

void visit(int x)
{
  visited[x] = 1;
  path.push_back(x);
  if (!visited[to[x]]) visit(to[x]);
  else if (visited[to[x]] == 1)
    for (int i = int(path.size()) - 1; i >= 0; i--)
    {
      int y = path[i];
      isGood[y]++;
      if (y == to[x])
      {
        d[get(y)] = get(x);
        break;
      }
      d[get(y)] = get(path[i - 1]);
    }
  path.pop_back();
  visited[x] = 2;
}

void init()
{
  int deg, a[111];

  cin >> deg;
  for (int i = deg; i >= 0; i--)
    cin >> a[i];

  for (int i = 0; i < n; i++)
  {
    int p = 1, v = 0;
    for (int j = 0; j <= deg; j++)
    {
      v = (v + a[j] * p) % n;
      p = p * i % n;
    }
    to[i] = v;
  }

  memset(visited, 0, sizeof visited);
  path.clear();
  for (int i = 0; i < n; i++)
    if (!visited[i])
      visit(i);
}

int len(long long x)
{
  return x < 10 ? 1 : len(x / 10) + 1;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("stable.in", "r", stdin);  
  freopen("stable.out", "w", stdout); 

  cin >> n;
  for (int i = 0; i < n; i++)
    d[i] = i;
  init();
  init();

  int cnt = 0;
  for (int i = 0; i < n; i++)
    if (isGood[i] == 2 && d[i] == i)
    {
      int ok = 1;
      for (int j = 0; j < n; j++)
        if (d[j] == i)
          ok &= isGood[j] == 2;
      cnt += ok;
    }

  long long base = (long long)1e16, ans1 = 1, ans2 = 0;
  while (cnt--)
  {
    ans1 *= 2;
    ans2 *= 2;
    ans2 += ans1 / base;
    ans1 %= base;
  }
  if (ans2)
  {
    cout << ans2;
    for (int i = len(ans1); i < 16; i++) cout << 0;
  }
  cout << ans1 << endl;
}