#include <bits/stdc++.h>
using namespace std;

int check(vector<pair<int, int>> b)
{
  vector<pair<int, int>> e;
  for (auto [l, r] : b)
  {
    e.push_back({l, r});
    e.push_back({r, l});
  }
  sort(begin(e), end(e));
  set<int> alive;
  for (auto [x, y] : e)
    if (x < y) alive.insert(x);
    else
    {
      auto u = alive.upper_bound(y);
      if (u != end(alive))
        return 0;
      alive.erase(y);
    }

  return 1;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int test;
  cin >> test;
  while (test--)
  {
    int n;
    cin >> n;
    vector<int> a(n * 2);
    for (int i = 0; i < n * 2; i++)
    {
      cin >> a[i];
      a[i]--;
    }

    vector<vector<int>> id(n);
    for (int i = 0; i < n * 2; i++)
      id[a[i]].push_back(i);

    vector<tuple<int, int, int>> e;
    for (int i = 0; i < n; i++)
    {
      e.push_back({id[i][0], id[i][1], i});
      e.push_back({id[i][1], id[i][0], i});
    }

    sort(begin(e), end(e));
    set<pair<int, int>> alive;
    vector<int> color(n, -1);
    for (auto [x, y, id] : e)
      if (x < y)
      {
        alive.insert({x, id});
      }
      else
      {
        if (color[id] < 0)
          color[id] = 0;
        alive.erase({y, id});
        auto u = alive.lower_bound(make_pair(y, id));
        while (u != end(alive))
        {
          auto [yy, idd] = *u++;
          alive.erase({yy, idd});
          color[idd] = color[id] ^ 1;
        }
      }

    vector<vector<pair<int, int>>> b(2);
    for (int i = 0; i < n; i++)
      b[color[i]].push_back({id[i][0], id[i][1]});

    int ans = check(b[0]);
    ans &= check(b[1]);

    cout << (ans ? "yes" : "no") << '\n';
  }
}
