#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 9;

int sz, m, c[11];

void addMod(long long &x, long long y)
{
  x = (x + y) % BASE;
}

struct Matrix
{
  long long a[88][88];
  Matrix()
  {
    memset(a, 0, sizeof a);
  }

  Matrix operator * (const Matrix &u)
  {
    Matrix res;
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        for (int k = 0; k < sz; k++)
          addMod(res.a[i][j], a[i][k] * u.a[k][j]);
    return res;
  }
} matrix[66];

void addCoef(int dif, int cur, int prev, long long val)
{
  addMod(matrix[0].a[(dif - 1) * m + prev][cur], val);
}

int main()
{
  long long n;
  cin >> n >> m;
  for (int i = 1; i <= m; i++)
    cin >> c[i];

  sz = m * m;
  // add 2 x 1
  addCoef(1, 0, 0, c[2]);

  // add 1 x i and 1 x j to (u, 0)
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= m; j++)
      addCoef(min(i, j), abs(i - j), 0, 1LL * c[i] * c[j] % BASE);
  
  // add 1 x j to (u, i)
  for (int i = 1; i < m; i++)
    for (int j = 1; j <= m; j++)
      addCoef(min(i, j), abs(i - j), i, c[j]);

  for (int i = m; i < sz; i++)
    addMod(matrix[0].a[i - m][i], 1);

  for (int i = 1; i <= 60; i++)
    matrix[i] = matrix[i - 1] * matrix[i - 1];

  Matrix ans;
  ans.a[0][0] = 1;
  for (int i = 60; i >= 0; i--)
    if (n >> i & 1)
    {
      ans = ans * matrix[i];
      n ^= 1LL << i;
    }

  cout << ans.a[0][0] << endl;
}