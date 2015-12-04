#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

int n, m, l[1010], f[1010];

int main()
{
  ios::sync_with_stdio(0);
  int x, y;
  cin >> n >> m;

  if (!m)
  {
    cout << n + 1 << endl;
    return 0;
  }

  for (int i = 1; i <= n; i++)
    l[i] = i;

  for (int i = 0; i < m; i++)
  {
    cin >> x >> y;
    l[y] = min(l[y], x);
  }

  vector < pair<int,int> > a, tmp;
  for (int i = 1; i <= n; i++)
  {
    l[i] = l[l[i]];
    if (l[i] != i)
      a.push_back({l[i], i});
  }

  for (int i = 0; i < a.size(); i++)
    for (int j = i + 1; j < a.size(); j++)
      if (make_pair(a[i].first, -a[i].second) > make_pair(a[j].first, -a[j].second))
        swap(a[i], a[j]);

  tmp.push_back(a[0]);
  for (int i = 1; i < a.size(); i++)
    if (a[i].second > tmp.back().second)
      tmp.push_back(a[i]);

  a = tmp;

  int A = a.size();
  for (int i = 1; i <= A; i++)
  {
    int y = a[i - 1].second;
    f[i] = y * 3 - a[0].first * 2;
    for (int j = 1; j < i; j++)
      f[i] = min(f[i], f[j] + y * 3 - a[j].first * 2 - a[j - 1].second);
  }

  cout << f[A] + n + 1 - a[A - 1].second << endl;
}