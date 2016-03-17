#include <bits/stdc++.h>
using namespace std;

int n, k;
vector < pair<int,int> > a[100100];
vector <int> ans;

int visit(int x)
{
  int node = 1;
  for (auto u : a[x])
  {
    int y = u.first, edge = u.second;
    int nodeChild = visit(y);
    if (nodeChild > k)
    {
      cout << -1 << endl;
      exit(0);
    }
    if (nodeChild * 2 >= k) ans.push_back(edge);
    else node += nodeChild;
  }
  return node;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  int x, y;
  cin >> n >> k;
  for (int i = 1; i < n; i++)
  {
    cin >> x >> y;
    a[x].push_back({y, i});
  }

  if (visit(1) > k)
  {
    cout << -1 << endl;
    return 0;
  }

  cout << ans.size() << endl;
  for (int x : ans)
    cout << x << ' ';
}