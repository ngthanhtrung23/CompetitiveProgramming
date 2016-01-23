#include <bits/stdc++.h>
using namespace std;

long long calc(long long n)
{
  long long k = int(sqrt(n));
  if (k * k == n)
    return k;
  return calc(n - k - 1);
}

int main()
{
  freopen("nim.in", "r", stdin);
  freopen("nim.out", "w", stdout);
  long long n;
  cin >> n;
  cout << (calc(n) ? "WIN" : "LOSE") << endl;
}