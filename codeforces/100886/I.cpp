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
    if (low == high) return;
    l = new SegmentTree(low , mid);
    r = new SegmentTree(mid + 1, high);
  }

  void update(int x, int v)
  {
    if (low == high) value = v;
    else
    {
      if (x <= mid) l -> update(x, v);
      else r -> update(x, v);
      value = min(l -> value, r -> value);
    }
  }

  int get(int x)
  {
    if (low == high) return low;
    if (l -> value < x) return l -> get(x);
    return r -> get(x);
  }
};

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, id[300300], num;
  cin >> n;
  SegmentTree *tree = new SegmentTree(1, n);
  vector <int> a(n + 1, 1), prev(n + 1, 0);

  for (int i = 1; i <= n; i++)
  {
    if (prev[i])
      a[i] = tree -> get(prev[i]);
    tree -> update(a[i], i);

    cin >> num;
    for (int j = 0; j < num; j++)
      cin >> id[j];
    sort(id, id + num);

    for (int j = 0; j < num; j++)
      if (!prev[id[j]] && i + 1 < id[j]) 
        prev[id[j]] = i + 1;

    cout << a[i] << ' ';
  }
}