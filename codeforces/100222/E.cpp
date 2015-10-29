#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
  int low, mid, high, value;
  SegmentTree *l, *r;

  SegmentTree(int low, int high): low(low), high(high) 
  {
    mid = (low + high) / 2;
    value = high - low + 1;
    if (low == high) return;
    l = new SegmentTree(low, mid);
    r = new SegmentTree(mid + 1, high);
  }

  int get(int x, int y)
  {
    if (low == x && high == y) 
      return value;
    int res = 0;
    if (x <= mid) 
      res += l -> get(x, min(y, mid));
    if (mid < y)
      res += r -> get(max(x, mid + 1), y);
    return res;
  }

  int find(int k)
  {
    if (low == high) 
      return low;
    if (k <= l -> value)
      return l -> find(k);
    return r -> find(k - l -> value);
  }

  void pick(int x)
  {
    value--;
    if (low == high) 
      return;
    if (x <= mid) l -> pick(x);
    else r -> pick(x);
  }
};

int main()
{
  ios::sync_with_stdio(0);
  freopen("infinity.in", "r", stdin);
  freopen("infinity.out", "w", stdout);

  int n, m, k;
  cin >> m >> n >> k;
  SegmentTree *tree = new SegmentTree(0, m + n + 1);

  int x = m + n + 1;
  while (tree -> value)
  {
    int newK = k;
    x = (x + 1) % (m + n + 2);
    if (x) 
      newK += tree -> get(0, x - 1);
    newK = (newK - 1) % tree -> value + 1;
    x = tree -> find(newK);
    tree -> pick(x);
    if (!x) tree -> pick(m + 1);
    if (x == m + 1) tree -> pick(0);
  }

  if (x <= m) cout << x << endl;
  else cout << m + 1 - x << endl;
}