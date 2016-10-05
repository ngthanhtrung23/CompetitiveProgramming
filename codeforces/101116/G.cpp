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

int INP, AM, REACHEOF;
#define BUFSIZE (1 << 12)
char BUF[BUFSIZE + 1], *inp = BUF;
#define GETCHAR(INP)                              \
  {                                               \
    if (!*inp && !REACHEOF) {                     \
      memset(BUF, 0, sizeof BUF);                 \
      int inpzzz = fread(BUF, 1, BUFSIZE, stdin); \
      if (inpzzz != BUFSIZE) REACHEOF = true;     \
      inp = BUF;                                  \
    }                                             \
    INP = *inp++;                                 \
  }
#define DIG(a) (((a) >= '0') && ((a) <= '9'))
#define GN(j)                                     \
  {                                               \
    AM = 0;                                       \
    GETCHAR(INP);                                 \
    while (!DIG(INP) && INP != '-') GETCHAR(INP); \
    if (INP == '-') {                             \
      AM = 1;                                     \
      GETCHAR(INP);                               \
    }                                             \
    j = INP - '0';                                \
    GETCHAR(INP);                                 \
    while (DIG(INP)) {                            \
      j = 10 * j + (INP - '0');                   \
      GETCHAR(INP);                               \
    }                                             \
    if (AM) j = -j;                               \
  }

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 500111;

struct Node {
  int start, inc;

  void add(int l, int r, int u, int v, int s, int i) {
    assert(u <= l && r <= v);

    start += s + (l - u) * i;
    inc += i;
  }
} it[MN * 4];

void down(int i, int l, int r, int mid) {
  if (!it[i].start && !it[i].inc) return;

  it[i << 1].add(l, mid, l, r, it[i].start, it[i].inc);
  it[i << 1 | 1].add(mid + 1, r, l, r, it[i].start, it[i].inc);

  it[i].start = it[i].inc = 0;
}

int q, n;

int query(int i, int l, int r, int u) {
  assert(l <= u && u <= r);
  if (l == r) return it[i].start;

  int mid = (l + r) >> 1;
  down(i, l, r, mid);

  if (u <= mid)
    return query(i << 1, l, mid, u);
  else
    return query(i << 1 | 1, mid + 1, r, u);
}

void update(int i, int l, int r, int u, int v, int start, int inc) {
  if (v < l || r < u) return;
  if (u <= l && r <= v) {
    it[i].add(l, r, u, v, start, inc);
    return;
  }
  int mid = (l + r) >> 1;
  down(i, l, r, mid);

  update(i << 1, l, mid, u, v, start, inc);
  update(i << 1 | 1, mid + 1, r, u, v, start, inc);
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int ntest;
  GN(ntest);
  while (ntest--) {
    GN(q);
    GN(n);
    memset(it, 0, sizeof it);
    while (q--) {
      char typ = '#';
      while (typ < 'A' || typ > 'Z') GETCHAR(typ);

      if (typ == 'Q') {
        int u;
        GN(u);
        printf("%lld\n", query(1LL, 1LL, n, u));
      } else {
        char dir = '#';
        while (dir < 'A' || dir > 'Z') GETCHAR(dir);
        int u;
        GN(u);
        int start;
        GN(start);
        int inc;
        GN(inc);
        int len;
        GN(len);

        int v;
        if (dir == 'E') {
          v = u + len - 1;
        } else {
          v = u - len + 1;
          start = start + (len - 1) * inc;
          inc = -inc;
          swap(u, v);
        }

        update(1, 1, n, u, v, start, inc);
      }
    }
  }
}
