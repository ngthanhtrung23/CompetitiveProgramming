#include <bits/stdc++.h>
using namespace std;

int n, d[100100], c[100100], found;
vector <int> a[100100];

int get(int x)
{
  return x == d[x] ? x : d[x] = get(d[x]);
}

void visit(int x, int lim)
{
  for (int y : a[x])
    if (y <= lim)
    {
      if (c[y] < 0)
      {
        c[y] = c[x] ^ 1;
        visit(y, lim);
      }
      else found |= c[x] == c[y];
    }
}

int hasOddCycle(int lim)
{
  found = 0;
  for (int i = 1; i <= lim; i++)
    c[i] = -1;
  for (int i = 1; i <= lim; i++)
    if (c[i] < 0)
    {
      c[i] = 0;
      visit(i, lim);
    }
  return found;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("jackpot.in", "r", stdin);
  freopen("jackpot.out", "w", stdout);
  int m, x, y;
  while (cin >> n >> m)
  {
    for (int i = 1; i <= n; i++)
      a[i].clear();

    while (m--)
    {
      cin >> x >> y;
      a[x].push_back(y);
      a[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
      d[i] = i;

    int low = 3, high = n, oddCycle = 0;
    while (low <= high)
    {
      int mid = (low + high) / 2;
      if (hasOddCycle(mid)) 
      {
        oddCycle = mid;
        high = mid - 1;
      }
      else low = mid + 1;
    }

    int ans = 0;
    for (int i = 2; i <= n; i++)
    {
      set <int> neighbor;
      int cntOther = 0;
      for (int j : a[i])
        if (j < i)
        {
          int dj = get(j);
          if (neighbor.count(dj)) continue;
          cntOther += i % 2 != dj % 2;
          neighbor.insert(dj);
        }

      if (neighbor.empty()) continue;
      int oldest = *neighbor.begin();
      if (cntOther > 1 || (cntOther && oldest % 2 == i % 2))
      {
        ans = i;
        break;
      }
      d[i] = oldest;
      for (int x : neighbor)
        if (x != oldest)
          d[x] = oldest;
    }

    if (!ans && !oddCycle) cout << "Tie" << endl;
    else 
    {
      if (!ans || (oddCycle && ans > oddCycle))
        ans = oddCycle;
      cout << (ans % 2 ? "Bob" : "Alice") << ' ' << ans << endl;
    }
  }
}