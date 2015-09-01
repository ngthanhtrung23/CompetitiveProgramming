
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
const int inf = 1e9;

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
            }
        }
    }
}

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
    return res;
}

int A[MN], B[MN], Cost[11][11], K, f[300][300];

int get(int A, int B) {
    if ((A | B) >= K) return 0;

    int res = inf;
    REP(i,256) if ((i | B) >= K) res = min(res, f[A][i]);
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> A[i];
        FOR(i,1,n) cin >> B[i];
        cin >> K;

        REP(i,8) REP(j,8) cin >> Cost[i][j];
        REP(i,8) Cost[i][i] = 0;

        REP(u,256) REP(v,256) f[u][v] = inf;
        REP(u,256) f[u][u] = 0;
        REP(u,256) {
            REP(i,8) REP(j,8) {
                int biti = (u >> i) & 1;
                int bitj = (u >> j) & 1;

                int v = u - (biti<<i) - (bitj<<j) + (biti<<j) + (bitj<<i);
                f[u][v] = min(f[u][v], Cost[i][j]);
            }
        }
        REP(k,256) REP(i,256) REP(j,256) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);

        init();
        FOR(i,1,n) FOR(j,1,n) {
            c[i][j] = get(A[i], B[j]);
        }
//        FOR(i,1,n) PR(c[i], n);

        cout << mincost() << endl;
    }
}

