#include <bits/stdc++.h>
using namespace std;

#define DEFAULT 0
#define ACTIVE 1
#define INACTIVE 2

struct SegmentTree
{
  int state;
  long long low, high, mid, sum, minValue, maxValue;
  SegmentTree *left, *right;

  SegmentTree(long long low, long long high): low(low), high(high)
  {
    mid = (low + high) / 2;
    state = DEFAULT;
    sum = (low + high - 2) * (high - low + 1) / 2;
    minValue = low - 1;
    maxValue = high - 1;
    left = NULL;
    right = NULL;
  }

  void updateChildren()
  {
    left -> state = right -> state = ACTIVE;
    left -> minValue = left -> maxValue = minValue;
    left -> sum = (mid - low + 1) * minValue;
    right -> minValue = right -> maxValue = minValue;
    right -> sum = (high - mid) * minValue;
    state = INACTIVE;
  }

  long long update(long long x, long long y, long long v)
  {
    if (minValue >= v) return 0;
    long long res = 0;
    if (low == x && high == y && maxValue <= v)
    {
      state = ACTIVE;
      res = (high - low + 1) * v - sum;
      minValue = maxValue = v;
      sum = (high - low + 1) * v;
      return res;
    }

    if (left == NULL)
      left = new SegmentTree(low, mid);
    if (right == NULL)
      right = new SegmentTree(mid + 1, high);

    if (state == ACTIVE)
      updateChildren();

    if (x <= mid)
      res += left -> update(x, min(y, mid), v);
    if (mid < y)
      res += right -> update(max(x, mid + 1), y, v);
    sum = left -> sum + right -> sum;
    state = INACTIVE;
    maxValue = max(left -> maxValue, right -> maxValue);
    minValue = min(left -> minValue, right -> minValue);

    return res;
  }
};

int main()
{
  int n, x, y;
  SegmentTree *tree = new SegmentTree(0, 2000000000);
  scanf("%d", &n);
  while (n--)
  {
    scanf("%d%d", &x, &y);
    printf("%I64d\n", tree -> update(x, x + y, x + y));
  }  
}