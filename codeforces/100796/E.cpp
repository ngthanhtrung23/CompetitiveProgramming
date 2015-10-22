#include <bits/stdc++.h>
using namespace std;

int tree[100100], n;

void add(int x)
{
  for (int i = x; i <= n; i += i & -i)
    tree[i]++;
}

int get(int x)
{
  int res = 0;
  for (int i = x; i; i -= i & -i)
    res += tree[i];
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  int x;
  cin >> n;
  long long ans = 0;
  vector < pair<int,int> > a;
  for (int i = 1; i <= n; i++)
  {
    cin >> x;
    if (x < i) a.push_back({x, -i});
    else a.push_back({i, -x});
  }
  sort(a.begin(), a.end());
  for (auto u : a)
  {
    ans += get(-u.second - 1) - get(u.first);
    add(-u.second);
  }
  cout << ans << endl;
}