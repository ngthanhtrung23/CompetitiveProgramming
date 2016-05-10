#include <bits/stdc++.h>
using namespace std;

struct Triple
{
  int x, y, z;

  bool operator < (Triple u) const
  {
    if (x != u.x) return x > u.x;
    if (y != u.y) return y > u.y;
    return z > u.z;
  }
};

int num, tree[200200];

void add(int x, int v)
{
  for (int i = x; i <= num; i += i & -i)
    tree[i] = max(tree[i], v);
}

int get(int x)
{
  int res = 0;
  for (int i = x; i; i -= i & -i)
    res = max(res, tree[i]);
  return res;
}

int main()
{
  freopen("pareto.in", "r", stdin);
  freopen("pareto.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int x, y, z, n;
  map <int,int> m;
  cin >> n;

  vector <Triple> a;
  for (int i = 0; i < n; i++)
  {
    cin >> x >> y >> z;
    a.push_back({x, y, z});
    m[y] = 0;
  }

  num = 0;
  for (auto u : m)
    m[u.first] = num++;

  sort(a.begin(), a.end());
  int ans = 0;
  for (auto u : a)
  {
    int y = num - m[u.y];
    ans += get(y - 1) <= u.z;
    add(y, u.z);
  }

  cout << ans << endl;
}