#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
  int low, mid, high, value;
  SegmentTree *l, *r;

  SegmentTree(int low, int high): low(low), high(high)
  {
    mid = (low + high) / 2;
    value = 0;
    l = r = NULL;
  }

  void add(int x)
  {
    value++;
    if (low == high)
      return;
    if (x <= mid)
    {
      if (!l)
        l = new SegmentTree(low, mid);
      l -> add(x);
    }
    else
    {
      if (!r)
        r = new SegmentTree(mid + 1, high);
      r -> add(x);
    }
  }

  int get(int x, int y)
  {
    if (low == x && high == y)
      return value;
    int u = x <= mid && l ? l -> get(x, min(y, mid)) : 0;
    int v = mid < y && r ? r -> get(max(x, mid + 1), y) : 0;
    return u + v;      
  }
};

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("environment.in", "r", stdin);
  freopen("environment.out", "w", stdout);
  int d = 0, type, x, y, n;
  cin >> n;
  SegmentTree *lTree = new SegmentTree(0, 1000000000);
  SegmentTree *rTree = new SegmentTree(0, 1000000000);
  while (n--)
  {
    cin >> type >> x;
    if (type == 1)
    {
      cin >> y;
      lTree -> add(x + d);
      rTree -> add(y + d);
    }
    else
    {
      d = lTree -> get(0, x);
      if (x)
        d -= rTree -> get(0, x - 1);
      cout << d << '\n';
    }
  }
}