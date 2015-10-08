#include <bits/stdc++.h>
using namespace std;
const int SZ = 170;

int n, a[33333], value[333], active[333];
long long block[333];

int get(int x)
{
  int bx = x / SZ;
  return active[bx] ? value[bx] : a[x];
}

void assign(int b)
{
  for (int i = 0; i < SZ; i++)
    a[b * SZ + i] = value[b];
  active[b] = 0;
}

int getAverage(long long sum, int len, int roundUp)
{
  if (sum >= 0)
    return (sum + roundUp * (len - 1)) / len;
  return (sum - (1 - roundUp) * (len - 1)) / len;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("death.in", "r", stdin);
  freopen("death.out", "w", stdout);

  int m, x, y;
  long long originalSum = 0;

  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    originalSum += a[i];
    block[i / SZ] += a[i];
  }

  int numBlock = (n + SZ - 1) / SZ;
  while (m--)
  {
    cin >> x >> y;
    x--;
    y--;
    if (x > y) swap(x, y);
    int bx = x / SZ, by = y / SZ, len = y - x + 1;
    long long sum = 0, sumAll = 0;

    for (int i = 0; i < numBlock; i++)
      sumAll += block[i];
    if (active[bx])
      assign(bx);
    if (active[by])
      assign(by);

    if (bx == by)
    {
      for (int i = x; i <= y; i++)
        sum += get(i);

      int average = getAverage(sum, len, sumAll <= originalSum);
      for (int i = x; i <= y; i++)
      {
        block[bx] += average - a[i];
        a[i] = average;
      }
    }
    else
    {
      for (int i = x; i < (bx + 1) * SZ; i++)
        sum += get(i);
      for (int i = bx + 1; i < by; i++)
        sum += block[i];
      for (int i = by * SZ; i <= y; i++)
        sum += get(i);

      int average = getAverage(sum, len, sumAll <= originalSum);
      for (int i = x; i < (bx + 1) * SZ; i++)
      {
        block[bx] += average - a[i];
        a[i] = average;
      }
      for (int i = bx + 1; i < by; i++)
      {
        block[i] = 1LL * average * SZ;
        value[i] = average;
        active[i] = 1;
      }
      for (int i = by * SZ; i <= y; i++)
      {
        block[by] += average - a[i];
        a[i] = average;
      }
    }
  }

  for (int i = 0; i < n; i++)
    cout << get(i) << ' ';
}