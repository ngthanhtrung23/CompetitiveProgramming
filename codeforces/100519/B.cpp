#include <bits/stdc++.h>
using namespace std;
const int oo = 1000111000;

struct Rect
{
  int x, y, xx, yy;
  
  Rect(int x = 0, int y = 0, int xx = 0, int yy = 0)
  {
    this -> x = x;
    this -> y = y;
    this -> xx = xx;
    this -> yy = yy;
  }
};

map <int,int> X, Y;
int m, n, xBomb[100100], yBomb[100100], pHor[100100], pVer[100100];
long double fx[200100], fy[200100];
Rect a[200100];

int main()
{
  ios::sync_with_stdio(0);
  int x, y, xx, yy;
  cin >> m >> n;
  for (int i = 0; i < m; i++)
  {
    cin >> x >> y >> xx >> yy;
    a[i] = Rect(x, y, xx, yy);
  }
  
  for (int i = 0; i < n; i++)
  {
    cin >> xBomb[i] >> yBomb[i] >> pHor[i] >> pVer[i];
    X[xBomb[i]] = 0;
    Y[yBomb[i]] = 0;
  }
  X[-oo] = X[oo] = Y[-oo] = Y[oo] = 0;
  
  int h = 0;
  for (auto x : X) X[x.first] = ++h;
  int v = 0;
  for (auto y : Y) Y[y.first] = ++v;
  
  for (int i = 0; i < n; i++)
  {
    xBomb[i] = X[xBomb[i]];
    yBomb[i] = Y[yBomb[i]];
    fy[yBomb[i]] = fy[yBomb[i]] + (1 - fy[yBomb[i]]) * pHor[i] * 0.01;
    fx[xBomb[i]] = fx[xBomb[i]] + (1 - fx[xBomb[i]]) * pVer[i] * 0.01;
  }
  
  for (int i = 1; i <= h; i++) fx[i] += fx[i - 1];
  for (int i = 1; i <= v; i++) fy[i] += fy[i - 1];
  
  long double ans = 0;
  for (int i = 0; i < m; i++)
  {
    int lx = X.lower_bound(a[i].x) -> second;
    int rx = (X.upper_bound(a[i].xx) -> second) - 1;
    int ly = Y.lower_bound(a[i].y) -> second;
    int ry = (Y.upper_bound(a[i].yy) -> second) - 1;
    ans += (fx[rx] - fx[lx - 1]) * (a[i].yy - a[i].y + 1);
    ans += (fy[ry] - fy[ly - 1]) * (a[i].xx - a[i].x + 1);
    ans -= (fx[rx] - fx[lx - 1]) * (fy[ry] - fy[ly - 1]);
  }
  
  cout << fixed << setprecision(12) << ans << endl;
}