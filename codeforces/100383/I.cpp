#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}

const ll MN = 1000011;
const ll MN2 = MN * (ll) MN;
int n;
long long f[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d", &n) == 1) {
        memset(f, 0, sizeof f);
        FOR(i,1,n) {
            int l, r;
            scanf("%d%d", &l, &r);
            f[i] += l;
            f[i] += r * MN;

            if (l) {
                f[l] += i * MN2;
                f[r] += i * MN2;
            }
        }
        int cur = 1, up = 0;
        long long h = 0, sumh = 0;
        int l, r, father;
        puts("DFS");
        while (cur) {
            if (!up) {
                printf("%d\n", cur);
                sumh += h;
            }

            l = f[cur] % MN;
            if (l) {
                ++h;
                up = 0;
                f[cur] -= l;
                cur = l;
                continue;
            }

            r = (f[cur] % MN2) / MN;
            if (r) {
                ++h;
                up = 0;
                f[cur] -= r * MN;
                cur = r;
                continue;
            }
            
            father = f[cur] / MN2;
            f[cur] -= father * MN2;
            up = 1;
            --h;

            cur = father;
        }
        printf("%lld\n", sumh);
        break;
    }
}
