#include <bits/stdc++.h>
using namespace std;

int n, d[100100];
vector <int> a[100100], order;

int check(int add, vector <int> deg)
{
  priority_queue < pair<int,int> > q;
  for (int i = 1; i <= n; i++)
    if (!deg[i])
      q.push(make_pair(d[i] + add, i));

  order.clear();
  while (!q.empty())
  {
    int x = q.top().second;
    q.pop();
    order.push_back(x);
    for (auto y : a[x])
      if (!--deg[y])
        q.push(make_pair(d[y] + add, y));
  }
  
  for (int i = 0; i < n; i++)
    if (n - i > d[order[i]] + add)
      return 0;
  
  return 1;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("grand.in", "r", stdin);
  freopen("grand.out", "w", stdout);
  
  int m, x, y;
  while (cin >> n, n)
  {
    vector <int> deg(n + 1, 0);
    for (int i = 1; i <= n; i++) 
    {
      cin >> d[i];
      a[i].clear();
    }
      
    cin >> m;
    while (m--)
    {
      cin >> x >> y;
      a[y].push_back(x);
      deg[x]++;
    }
    
    int low = 0, high = n, ans = n;
    while (low <= high)
    {
      int mid = (low + high) / 2;
      if (check(mid, deg))
      {
        ans = mid;
        high = mid - 1;
      }
      else low = mid + 1;
    }
    
    check(ans, deg);
    cout << ans << endl;
    for (int i = n - 1; i >= 0; i--) 
      cout << order[i] << (i ? ' ' : '\n');
  }
}
