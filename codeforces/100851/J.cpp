#include <bits/stdc++.h>
using namespace std;

int a[1010], dif[1010], n;

int guess()
{
  int x;
  for (int i = 0; i < n; i++)
    cout << a[i];
  cout << endl;
  cin >> x;
  return x;
}

int main()
{
  ios::sync_with_stdio(0);
  srand(time(NULL));
  cin >> n;
  while (1)
  {
    for (int i = 0; i < n; i++)
      a[i] = rand() % 2;
    int x = guess();
    if (x == n)
      return 0;
    if (x == n / 2)
      break;
  }  

  for (int i = 1; i < n; i++)
  {
    a[i] ^= 1;
    a[0] ^= 1;
    int x = guess();
    dif[i] = (x == n / 2) ^ (a[i] ^ a[0]);
    a[i] ^= 1;
    a[0] ^= 1;
  }

  a[0] = 0;
  for (int i = 1; i < n; i++)
    a[i] = dif[i];
  if (guess() == n) 
    return 0;

  for (int i = 0; i < n; i++)
    a[i] ^= 1;
  if (guess() == n)
    return 0;

  assert(0);
}
