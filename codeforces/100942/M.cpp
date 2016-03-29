#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  long long x, y, g = 0, l = 1;
  while (n--)
  {
    cin >> x >> y;
    l = x / __gcd(x, l) * l;
    g = __gcd(g, y);
  }
  cout << l << ' ' << g << endl;
}