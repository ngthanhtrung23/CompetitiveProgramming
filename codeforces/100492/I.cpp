#include <bits/stdc++.h>
using namespace std;

vector <int> posts[200200];
map <int,int> friends[200200];
long long ans[200200];

void query(int x, int y)
{
  int t = friends[y][x];
  ans[x] += posts[y].end() - lower_bound(posts[y].begin(), posts[y].end(), t);
}

int main()
{
  freopen("intouch.in", "r", stdin);
  freopen("intouch.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, x, y;
  char c;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    cin >> c >> x;
    if (c == '!') posts[x].push_back(i);
    else 
    {
      cin >> y;
      if (c == '+') friends[x][y] = friends[y][x] = i;
      else
      {
        query(x, y);
        query(y, x);
        friends[x].erase(y);
        friends[y].erase(x);
      }
    }
  }

  for (int x = 1; x <= n; x++)
  {
    for (auto u : friends[x])
      query(x, u.first);
    cout << ans[x] << ' ';
  }
}