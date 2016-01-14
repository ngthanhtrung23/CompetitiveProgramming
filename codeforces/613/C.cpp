
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

const int MN = 100111;
int n, a[MN], res[MN], all, best;

void print() {
    printf("%d\n", best);
    FOR(i,1,all) putchar((char) ('a' + res[i] - 1));
    puts("");
}

void solve2() {
    int cur = 0;
    FOR(i,1,n) {
        while (a[i]--) res[++cur] = i;
    }
}

void solve1() {
    FOR(i,1,n) if (a[i] % 2 == 1) {
        int g = a[i];
        FOR(j,1,n) if (j != i) g = __gcd(g, a[j] / 2);

        int cur = 0;
        FOR(group,1,g) {
            FOR(j,1,n) if (j != i) {
                REP(turn, a[j] / 2 / g) res[++cur] = j;
            }
            FORD(j,n,1) if (j != i) {
                REP(turn, a[j] / 2 / g) res[++cur] = j;
            }
            REP(turn,a[i] / g) res[++cur] = i;
        }
        best = g;
    }
}

void solve0() {
    int bestg = 0, besti = 0;
    FOR(i,1,n) {
        int g = a[i] / 2;
        FOR(j,1,n) if (j != i) g = __gcd(g, a[j] / 2);

        if (g > bestg) {
            bestg = g;
            besti = i;
        }
    }
    int i = besti;
    int g = bestg;
    int cur = 0;
    best = g * 2;

    FOR(group,1,g) {
        FOR(j,1,n) if (j != i) {
            REP(turn,a[j]/2/g) res[++cur] = j;
        }
        FORD(j,n,1) if (j != i) {
            REP(turn,a[j]/2/g) res[++cur] = j;
        }
        REP(turn,a[i]/g) res[++cur] = i;
    }
}

int main() {
    while (cin >> n) {
        int sum = 0;
        all = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i] % 2;
            all += a[i];
        }
        memset(res, 0, sizeof res);
        best = 0;
        if (sum > 1) solve2();
        else if (sum == 1) solve1();
        else solve0();
        print();
    }
}
