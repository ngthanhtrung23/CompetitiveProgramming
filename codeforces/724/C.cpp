#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) \
  { cout << #X << " = " << (X) << endl; }
#define PR(A, n)                      \
  {                                   \
    cout << #A << " = ";              \
    FOR(_, 1, n) cout << A[_] << ' '; \
    cout << endl;                     \
  }
#define PR0(A, n)                  \
  {                                \
    cout << #A << " = ";           \
    REP(_, n) cout << A[_] << ' '; \
    cout << endl;                  \
  }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 400111;
const int INF = 1000111000111000111LL;

int id[4][MN];
int X, Y;
int start[4][MN];

int getId(int x, int y) {
  if (y == 0) return id[0][x];
  if (x == X) return id[1][y];
  if (y == Y) return id[2][x];
  return id[3][y];
}

int dirToId(int dx, int dy) {
  if (dx == 1 && dy == 1) return 1;
  if (dx == 1 && dy == -1) return 2;
  if (dx == -1 && dy == -1) return 3;
  return 0; // dx == -1 && dy == 1
}

void init() {
  // 1. Generate ID for all points
  int nid = 0;
  FOR(x,0,X) id[0][x] = ++nid;
  FOR(y,1,Y) id[1][y] = ++nid;
  FORD(x,X-1,0) id[2][x] = ++nid;
  FORD(y,Y-1,1) id[3][y] = ++nid;

  set< pair<int,int> > corners;
  corners.insert(make_pair(0, 0));
  corners.insert(make_pair(X, 0));
  corners.insert(make_pair(X, Y));
  corners.insert(make_pair(0, Y));

  // 2. Simulate path
  int time = 0;
  int x = 0, y = 0;
  int dx = 1, dy = 1;
  do {
    int u = dirToId(dx, dy);
    int v = getId(x, y);
    if (start[u][v] >= 0) break;
    start[u][v] = time;

    int badx = INF, bady = INF;
    if (dx == 1) badx = X - x; else badx = x;
    if (dy == 1) bady = Y - y; else bady = y;

    int collision = min(badx, bady);

    x += dx * collision;
    y += dy * collision;
    time += collision;

    if (badx <= bady) { dx = -dx; }
    else dy = -dy;

  } while (!corners.count(make_pair(x, y)));
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int q;
  while (GI(X) == 1) {
    GI(Y);
    GI(q);
    memset(start, -1, sizeof start);
    init();
    while (q--) {
      int x, y; GI(x); GI(y);
      int res = INF;
      int savex = x, savey = y;

      for(int dx = -1; dx <= 1; dx += 2)
        for(int dy = -1; dy <= 1; dy += 2) {
          int startx = INF, starty = INF;
          x = savex, y = savey;

          if (dx == -1) startx = X - x; else startx = x;
          if (dy == -1) starty = Y - y; else starty = y;

          int collision = min(startx, starty);

          x -= collision * dx;
          y -= collision * dy;
          int t = start[dirToId(dx, dy)][getId(x, y)];

          if (t >= 0) {
            res = min(res, collision + t);
          }
        }

      if (res == INF) res = -1;
      printf("%lld\n", res);
    }
  }
}
