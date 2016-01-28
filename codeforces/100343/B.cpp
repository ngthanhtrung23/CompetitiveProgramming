#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
  int low, mid, high;
  pair<int,int> val;
  SegmentTree *l, *r;

  SegmentTree(int low, int high): low(low), high(high)
  {
    mid = (low + high) / 2;
    val = {0, 0};
    if (low == high) 
      return;
    l = new SegmentTree(low, mid);
    r = new SegmentTree(mid + 1, high);
  }

  void update(int x, pair<int,int> v)
  {
    val = max(val, v);
    if (low == high)
      return;
    if (x <= mid) l -> update(x, v);
    else r -> update(x, v);
  }

  pair<int,int> get(int x, int y)
  {
    if (low == x && high == y)
      return val;
    pair<int,int> u(0, 0), v(0, 0);
    if (x <= mid) u = l -> get(x, min(y, mid));
    if (mid < y) v = r -> get(max(x, mid + 1), y);
    return max(u, v);
  }
};

int n, k, a[100100];
pair <int,int> f[100100];
map <int,int> m;

int main()
{
  freopen("financial.in", "r", stdin);
  freopen("financial.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    m[a[i]] = 0;
  }

  int cur = 0;
  for (auto u : m)
    m[u.first] = cur++;

  SegmentTree *tree = new SegmentTree(0, cur - 1);
  int ans = 0, x = 0;
  for (int i = 1; i <= n; i++)
  {
    auto high = m.lower_bound(a[i] + k);
    if (high != m.end())
      f[i] = max(f[i], tree -> get(high -> second, cur - 1));
    auto low = m.upper_bound(a[i] - k);
    if (low != m.begin())
    {
      low--;
      f[i] = max(f[i], tree -> get(0, low -> second));
    }

    f[i].first++;
    if (f[i].first > ans)
    {
      ans = f[i].first;
      x = i;
    }

    tree -> update(m[a[i]], {f[i].first, i});
  }

  cout << ans << endl;
  vector <int> choose;
  while (x)
  {
    choose.push_back(x);
    x = f[x].second;
  }

  for (int i = choose.size() - 1; i >= 0; i--)
    cout << a[choose[i]] << ' ';
}