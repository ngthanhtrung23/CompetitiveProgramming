
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 200111;

int it[MN * 3];

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i] += val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(i*2, l, mid, u, v, val);
    update(i*2+1, mid+1, r, u, v, val);
}

int get(int i, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) return it[i];
    int mid = (l + r) >> 1;
    return it[i] + get(i*2, l, mid, u) + get(i*2+1, mid+1, r, u);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        memset(it, 0, sizeof it);
        int cnt = 1;
        long long sumall = 0;
        FOR(i,1,n) {
            int typ; scanf("%d", &typ);
            if (typ == 1) {
                int a, x; scanf("%d%d", &a, &x);
                update(1, 1, n, 1, a, x);
                sumall += a * (long long) x;
            }
            else if (typ == 2) {
                int k; scanf("%d", &k);
                ++cnt;
                int cur = get(1, 1, n, cnt);
                update(1, 1, n, cnt, cnt, k - cur);

                sumall += k;
            }
            else {
                int cur = get(1, 1, n, cnt);
                --cnt;
                sumall -= cur;
            }
            printf("%.9lf\n", sumall / (double) cnt);
        }
    }
    return 0;
}

