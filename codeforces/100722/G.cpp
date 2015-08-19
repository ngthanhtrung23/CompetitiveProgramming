#include <bits/stdc++.h>
using namespace std;

int isPrime[10100], d[10100];
vector <int> a[10100], primes;

int isValid(int x, int y)
{
  int a[4], b[4], diff = 0;
  for (int i = 0; i < 4; i++) 
  {
    diff += x % 10 != y % 10;
    x /= 10;
    y /= 10;
  }
  return diff == 1;
}

int main()
{
  ios::sync_with_stdio(0);
  
  for (int i = 1000; i < 10000; i++)
  {
    isPrime[i] = 1;
    for (int j = 2; j * j <= i; j++)
      if (i % j == 0)
      {
        isPrime[i] = 0;
        break;
      }
    if (isPrime[i]) primes.push_back(i);
  }

  for (auto x : primes)
    for (auto y : primes)
      if (isValid(x, y))
        a[x].push_back(y);

  int test;
  cin >> test;
  while (test--)
  {
    int from, to;
    cin >> from >> to;
    memset(d, -1, sizeof d);
    queue <int> q;
    d[from] = 0;
    q.push(from);
    while (!q.empty() && d[to] < 0)
    {
      int x = q.front();
      q.pop();
      for (auto y : a[x])
        if (d[y] < 0)
        {
          d[y] = d[x] + 1;
          q.push(y);
        }
    }

    if (d[to] < 0) cout << "Impossible\n";
    else cout << d[to] << endl;
  }
}