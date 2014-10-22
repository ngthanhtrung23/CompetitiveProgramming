#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7;

int f[200200];

int main()
{
  ios::sync_with_stdio(0);
  int r, g, ans = 0;
  cin >> r >> g;
  
  f[0] = 1;
  for (int h = 1; h <= 1000; h++)
  {
    int canBuild = 0, ways = 0;
    for (int i = r; i >= 0; i--)
    {
      if (i >= h) 
      {
        f[i] += f[i - h];
        if (f[i] >= BASE) f[i] -= BASE;
      }
      
      if (f[i] && i + g >= h * (h + 1) / 2) 
      {
        canBuild = 1;
        ways += f[i];
        if (ways >= BASE) ways -= BASE;
      }      
    }
    
    if (!canBuild) break;
    ans = ways;
  }
  
  cout << ans << endl;
}