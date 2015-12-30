#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2000111;
const ll MOD = 1e9 + 7;

int m, n, l, N;
char s[MN];
int sumdx[MN], sumdy[MN];

int getX(char c) {
    if (c == 'U') return -1;
    if (c == 'D') return 1;
    return 0;
}
int getY(char c) {
    if (c == 'L') return -1;
    if (c == 'R') return 1;
    return 0;
}

const int INF = 1e9;

ll area(int u, int d, int l, int r) {
    return (d - u + 1) * (ll) (r - l + 1LL) % MOD;
}

bool move(int&u, int&d, int&l, int&r, char c) {
    u += getX(c);
    d += getX(c);

    l += getY(c);
    r += getY(c);

    bool res = false;
    if (u < 1) u = 1, res = true;
    if (d > m) d = m, res = true;
    if (l < 1) l = 1, res = true;
    if (r > n) r = n, res = true;
    return res;
}

int main() {
    while (scanf("%d%d%d\n", &l, &m, &n) == 3) {
        scanf("%s\n", &s[1]);
        FOR(i,l+1,l+l) s[i] = s[i-l];
        N = l+l;

//        PR(s, N);

        FOR(i,1,N) {
            sumdx[i] = sumdx[i-1] + getX(s[i]);
            sumdy[i] = sumdy[i-1] + getY(s[i]);
        }

//        PR(sumdx, N);
//        PR(sumdy, N);

        int u = 1, d = m, l = 1, r = n;

        bool ok = false;
        FOR(i,1,N/2) {
            char c = s[i];

            if (move(u, d, l, r, c)) {
            }

            if (u > d || l > r) {
                ok = true;
            }
        }
        if (sumdx[N] == 0 && sumdy[N] == 0 && !ok) {
            cout << -1 << endl;
            continue;
        }
        u = 1, d = m, l = 1, r = n;

        int pos = 1;
        ll res = 0;

        int i = 0;
        int turn = 0;
        vector<int> collisions;
        while (u <= d && l <= r) {
            ++turn;
            int to;
            if (turn <= N) {
                to = turn;
                if (to > N/2) to -= N / 2;
            }
            else {
                to = collisions[i];
                i = (i + 1) % SZ(collisions);
            }
            if (to < pos) to += N / 2;

//            cout << u << ' ' << d << ' ' << l << ' ' << r << endl;
//            DEBUG(pos);
//            DEBUG(to);

            // collide at to --> consider 2 steps:
            // [pos, to-1]
            u += sumdx[to-1] - sumdx[pos-1];
            d += sumdx[to-1] - sumdx[pos-1];
            l += sumdy[to-1] - sumdy[pos-1];
            r += sumdy[to-1] - sumdy[pos-1];

            res = (res + area(u, d, l, r) * (to - pos + 1)) % MOD;
//            DEBUG(res);

            // [to, to]
            char c = s[to];
            if (move(u, d, l, r, c) && turn > N/2 && turn <= N) {
                collisions.push_back(to);
            }

            pos = to + 1; while (pos > N/2) pos -= N/2;
        }
        cout << res << endl;
    }
}
