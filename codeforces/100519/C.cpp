#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int a, b, c;
  cin >> a >> b >> c;
  int x = (c + a - 1) / a;
  int y = (c + b - 1) / b;
  
  if (a > b)
  {
    cout << y << ' ' << y << endl;
    return 0;
  }
  
  if (b % a == 0)
  {
    cout << x << ' ' << (x + b / a - 1) / (b / a) << endl;
    return 0;
  }
  
  int k = b / a, r = b % a, maxY = (x + k - 1) / k;
  
  while (y < maxY)
  {
    int rhs = c - y * k * a;
    if (rhs >= 0) rhs = (rhs + r - 1) / r;
    else rhs = -(abs(rhs) / r);
    if (min(x - y * k,  y) >= rhs)
    {
      
      cout << x << ' ' << y << endl;
      return 0;
    }
    y++;
  }
  
  cout << x << ' ' << y << endl;
}
