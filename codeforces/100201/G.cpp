#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 211;
const int inf = 1e6;
int n;

#define arg __arg
long long c[MN][MN];
long long fx[MN], fy[MN];
int mx[MN], my[MN];
int trace[MN], qu[MN], arg[MN];
long long d[MN];
int front, rear, start, finish;

void init() {
  FOR(i,1,n) {
    fy[i] = mx[i] = my[i] = 0;
    FOR(j,1,n) c[i][j] = inf;
  }
}
void addEdge(int i, int j, long long cost) {
  c[i][j] = min(c[i][j], cost);
}
inline long long getC(int i, int j) {
  return c[i][j] - fx[i] - fy[j];
}
void initBFS() {
  front = rear = 1;
  qu[1] = start;
  memset(trace, 0, sizeof trace);
  FOR(j,1,n) {
    d[j] = getC(start, j);
    arg[j] = start;
  }
  finish = 0;
}
void findAugPath() {
  while (front <= rear) {
    int i = qu[front++];
    FOR(j,1,n) if (!trace[j]) {
      long long w = getC(i, j);
      if (!w) {
        trace[j] = i;
        if (!my[j]) {
          finish = j;
          return ;
        }
        qu[++rear] = my[j];
      }
      if (d[j] > w) {
        d[j] = w;
        arg[j] = i;
      } } } }
void subx_addy() {
  long long delta = inf;
  FOR(j,1,n)
    if (trace[j] == 0 && d[j] < delta) delta = d[j];
  // xoay
  fx[start] += delta;
  FOR(j,1,n)
    if (trace[j]) {
      int i = my[j];
      fy[j] -= delta;
      fx[i] += delta;
    }
    else d[j] -= delta;

  FOR(j,1,n)
    if (!trace[j] && !d[j]) {
      trace[j] = arg[j];
      if (!my[j]) { finish = j; return ; }
      qu[++rear] = my[j];
    }
}
void enlarge() {
  do {
    int i = trace[finish];
    int next = mx[i];
    mx[i] = finish;
    my[finish] = i;
    finish = next;
  } while (finish);
}
int mincost() {
  FOR(i,1,n) fx[i] = *min_element(c[i]+1, c[i]+n+1);
  FOR(i,1,n) {
    start = i;
    initBFS();
    while (finish == 0) {
      findAugPath();
      if (!finish) subx_addy();
    }
    enlarge();
  }
  int res = 0;
  FOR(i,1,n) res += c[i][mx[i]];
  return res; }

bool has[MN][MN];
int initial[MN];
int main() {
    ios :: sync_with_stdio(false);
    freopen("keeper.in", "r", stdin);
    freopen("keeper.out", "w", stdout);
    int left, right;
    cin >> left >> right;
    n = max(left, right);
    init();
    FOR(i,1,left) {
        int k; cin >> k;
        while (k--) {
            int u; cin >> u;
            has[i][u] = true;
        }
    }
    int existing = 0;
    FOR(i,1,left) {
        cin >> initial[i];
        if (initial[i]) ++existing;
    }

    FOR(i,1,left) FOR(j,1,right)
        if (has[i][j]) {
            if (initial[i] == j) addEdge(i, j, -1);
            else addEdge(i, j, 0);
        }
    int res = -mincost(), cnt = 0;
    FOR(i,1,n) {
        int j = mx[i];
        if (c[i][j] == inf) res += inf;
        else ++cnt;
    }
    cout << cnt << ' ' << existing - res << endl;
    FOR(i,1,left) if (c[i][mx[i]] < inf) cout << mx[i] << ' '; else cout << "0 ";
    cout << endl;
}