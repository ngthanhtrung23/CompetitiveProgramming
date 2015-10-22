#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int test;
  cin >> test;
  while (test--)
  {
    long long l, r;
    cin >> l >> r;
    cout << fixed << setprecision(12) << 1.0 / l - 1.0 / (r + 1) << '\n';
  }  
}