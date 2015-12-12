#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int test, n, x;
  cin >> test;
  for (int iTest = 1; iTest <= test; iTest++)
  {
    cin >> n;
    int ans = 1;
    while (n--)
    {
      cin >> x;
      ans &= x % 3 == 0;
    }
    cout << "Case #" << iTest << ": " << (ans ? "Yes" : "No") << endl;
  }
}