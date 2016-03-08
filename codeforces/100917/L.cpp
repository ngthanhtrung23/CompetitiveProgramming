#include <bits/stdc++.h>
using namespace std;

map <long long,long long> f;

long long calc(long long n)
{
  if (n == 1) return 0;
  if (f.count(n))
    return f[n];
  f[n] = -1;
  if (n % 2 == 0) 
  {
    long long u = calc(n / 2);
    return f[n] = u < 0 ? -1 : n + u;
  }

  long long u = calc(n + (n + 1) / 2);
  return f[n] = u < 0 ? -1 : n + 1 + u;
}

int main()
{
  long long n;
  cin >> n;
  cout << calc(n) << endl;
}