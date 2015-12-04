#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
  int low, mid, high, value, reserved;
  SegmentTree *l, *r;

  SegmentTree(int low, int high, int s[]): low(low), high(high)
  {
    mid = (low + high) / 2;
    reserved = 0;
    if (low == high) value = s[low];
    else
    {
      l = new SegmentTree(low, mid, s);
      r = new SegmentTree(mid + 1, high, s);
      value = min(l -> value, r -> value);
    }
  }

  void updateChildren()
  {
    l -> value += reserved;
    l -> reserved += reserved;
    r -> value += reserved;
    r -> reserved += reserved;
    reserved = 0;
  }

  void update(int x, int y, int add)
  {
    if (low == x && high == y) 
    {
      value += add;
      reserved += add;
    }
    else
    {
      if (reserved) updateChildren();
      if (x <= mid) l -> update(x, min(y, mid), add);
      if (mid < y) r -> update(max(x, mid + 1), y, add);
      value = min(l -> value, r -> value);
    }
  }

  int find()
  {
    if (low == high) return low;
    if (reserved) updateChildren();
    if (r -> value >= 2) return l -> find();
    return r -> find();
  }
};

int n, s[300300];
string a;
SegmentTree *tree;
set <int> open, close;

void flip(int x)
{
  if (a[x] == '(')
  {
    open.erase(x);
    close.insert(x);
    tree -> update(x, n, -2);
    a[x] = ')';
  }
  else
  {
    close.erase(x);
    open.insert(x);
    tree -> update(x, n, 2);
    a[x] = '(';
  }
}

int main()
{
  ios::sync_with_stdio(0);
  int q, x;

  cin >> n >> q >> a;
  a = " " + a;
  s[0] = 0;

  for (int i = 1; i <= n; i++)
    if (a[i] == '(')
    {
      open.insert(i);
      s[i] = s[i - 1] + 1;
    }
    else
    {
      close.insert(i);
      s[i] = s[i - 1] - 1;
    }

  tree = new SegmentTree(1, n, s);
  while (q--)
  {
    cin >> x;
    flip(x);

    int y = -1;
    if (a[x] == ')') 
      y = *close.begin();
    else
      y = tree -> find() + 1;

    cout << y << '\n';
    assert(y > 0);
    flip(y);
  }
}