#include <bits/stdc++.h>
using namespace std;
const string COLOR = "RGB";

int n, ans[555];
vector <int> a[555];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("mayors.in", "r", stdin);
  freopen("mayors.out", "w", stdout);
  int m, x, y;
  cin >> n >> m;
  while (m--)
  {
    cin >> x >> y;
    a[x].push_back(y);
    a[y].push_back(x);
  }

  memset(ans, -1, sizeof ans);
  ans[1] = 0;
  while (1)
  {
    int maxCnt = 0, x = -1;
    for (int i = 1; i <= n; i++)
      if (ans[i] < 0)
      {
        int mask = 0;
        for (int y : a[i])
          if (ans[y] >= 0)
            mask |= 1 << ans[y];
        int cnt = __builtin_popcount(mask);
        if (cnt > maxCnt)
        {
          x = i;
          maxCnt = cnt;
        }
      }

    if (x < 0) 
      break;

    int has[3] = {0};
    for (int y : a[x])
      if (ans[y] >= 0)
        has[ans[y]] = 1;
      
    for (int i = 0; i < 3; i++)
      if (!has[i])
      {
        ans[x] = i;
        break;
      }

    if (ans[x] < 0)
    {
      cout << "Plan failed" << endl;
      return 0;
    }
  }

  cout << "Plan OK" << endl;
  for (int i = 1; i <= n; i++)
    cout << COLOR[ans[i]];
  cout << endl;
}