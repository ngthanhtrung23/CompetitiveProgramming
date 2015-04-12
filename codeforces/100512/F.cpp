#include <bits/stdc++.h>
using namespace std;

int minPrimeFactor[10100100];

int solve(int turn, int m, int n)
{
  if (m * n == 1) return 0;
  if (!turn) return m == 1 ? 0 : !solve(1, m / minPrimeFactor[m], n);
  return n == 1 ? 0 : !solve(0, m, n / minPrimeFactor[n]);
}

int main()
{
  for (int i = 1; i <= 10000000; i++) 
    minPrimeFactor[i] = i;
  
  for (int i = 2; i * i <= 10000000; i++)
    if (minPrimeFactor[i] == i)
      for (int j = i * i; j <= 10000000; j += i)
        minPrimeFactor[j] = min(minPrimeFactor[j], i);
  
  ios::sync_with_stdio(0);
  freopen("funny.in", "r", stdin);
  freopen("funny.out", "w", stdout);
  int m, n;
  while (cin >> m >> n, m)
    cout << m << ' ' << n << " - " << (solve(0, m, n) ? "Vera" : "Harry") << '\n';
}
