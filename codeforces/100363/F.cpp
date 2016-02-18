#include <bits/stdc++.h>
using namespace std;
const int oo = 1 << 30;

int go(int x, int y, int turn)
{
  if (!turn)
  {
    if (x < 2) return 0;
    return 1 + go(x - 2, (y ? y - 1 : y + 1), 1);
  }
  else
  {
    if (y < 2) return 0;
    return 1 + go((x ? x - 1 : x + 1), y, 0);
  }
}

int main()
{
  freopen("knights.in", "r", stdin);
  freopen("knights.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, x, y;

  while (cin >> n, n)
  {
    int maxStep = oo;
    while (n--)
    {
      cin >> x >> y;
      int k = min(x / 3, y / 3);
      maxStep = min(maxStep, go(x - k * 3, y - k * 3, 0) + k * 2);
    }

    cout << (maxStep % 2 ? "Andrew" : "Peter") << " wins the game" << '\n';
  }
}