#include <bits/stdc++.h>
using namespace std;
const long long MAX = (long long)1e18 + 5;

int n, a, b, q, p[11], cnt[60000];
long long f[111][60000];
vector <int> goodMask, allMask;
vector < pair<int,int> > tr[111][60000];

bool cmp(int u, int v)
{
  int res = 0;
  for (int i = 0; i < n; i++)
  { 
    int x = u % 3, y = v % 3;
    if (x != 1 && y == 1) res = 1;
    if (x == 1 && y != 1) res = 0;
    u /= 3;
    v /= 3;
  }
  return res;
}

void update(long long &x, long long y)
{
  x = min(MAX, x + y);
}

void solve(long long t)
{
  int mask = -1;
  for (auto u : goodMask)
    if (t <= f[0][u])
    {
      mask = u;
      break;
    }
    else t -= f[0][u];

  assert(mask >= 0);
  for (int i = 0; i < n * n; i++)
  {
    for (auto u : tr[i][mask])
      if (t <= f[i + 1][u.first])
      {
        mask = u.first;
        cout << u.second;
        break;
      }
      else t -= f[i + 1][u.first];
    if (i % n == n - 1)
      cout << endl;
  }
}

int main()
{
  int Q;
  long long t;

  for (int i = 0; i <= 10; i++)
    p[i] = i ? p[i - 1] * 3 : 1;

  cin >> n >> a >> b;

  for (int i = 0; i < p[n]; i++)
  {
    int x = i, nonZero = 1;
    for (int j = 0; j < n; j++)
    {
      cnt[i] += x % 3 == 1;
      nonZero &= x % 3 > 0;
      x /= 3;
    }
    if (nonZero && cnt[i] >= a && cnt[i] <= b)
      goodMask.push_back(i);
    allMask.push_back(i);
  }

  sort(goodMask.begin(), goodMask.end(), cmp);
  sort(allMask.begin(), allMask.end(), cmp);

  f[n * n][0] = 1;
  for (int i = n * n - 1; i >= 0; i--)
    for (int mask : allMask)
      if (f[i + 1][mask])
      { 
        int x = i / n, y = i % n, last = mask % 3;
        if (y == n - 1 && x < n - 1 && (cnt[mask] < a || cnt[mask] > b))
          continue;
        // 0
        if (last == 1) 
        {
          update(f[i][mask / 3 + p[n - 1] * 2], f[i + 1][mask]);
          tr[i][mask / 3 + p[n - 1] * 2].push_back({mask, 0});
        }
        else 
        {
          update(f[i][mask / 3 + p[n - 1] * last], f[i + 1][mask]);
          tr[i][mask / 3 + p[n - 1] * last].push_back({mask, 0});
        }
        // 1
        if (last < 2) 
        {
          update(f[i][mask / 3 + p[n - 1]], f[i + 1][mask]);
          tr[i][mask / 3 + p[n - 1]].push_back({mask, 1});
        }
      }

  long long ans = 0;
  for (auto mask : goodMask)
    update(ans, f[0][mask]);

  cin >> Q;
  while (Q--)
  {
    cin >> t;
    if (t > ans) cout << "No such matrix.\n";
    else solve(t);
    cout << endl;
  }
}