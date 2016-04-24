#include <bits/stdc++.h>
#define int long long
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 1000111;

struct Arr {
    vector<int> x;
    int start;

    void init(int from, int to, int d) {
        for(int i = from; i <= to; i += d)
            x.push_back(i);
        start = 0;
    }

    void move(int d) {
        start -= d;
        start %= SZ(x);
        if (start < 0) start += SZ(x);
    }

    vector<int> get() {
        vector<int> res;

        int i = start;
        REP(turn,SZ(x)) {
            res.push_back(x[i]);
            i = (i + 1) % SZ(x);
        }
        return res;
    }
};

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, q;
    while (GI(n) == 1 && GI(q) == 1) {
        Arr a[2];
        a[0].init(1, n-1, 2);
        a[1].init(2, n, 2);

        int x = 0, y = 1;

        while (q--) {
            int typ; GI(typ);
            if (typ == 2) swap(x, y);
            else {
                int d; GI(d);
                if (d < 0) d += n;

                if (d % 2 == 0) {
                    a[x].move(d / 2);
                    a[y].move(d / 2);
                }
                else {
                    a[x].move(d / 2);
                    a[y].move(d / 2 + 1);
                    swap(x, y);
                }
            }

        }

        auto t1 = a[x].get();
        auto t2 = a[y].get();

        REP(i,SZ(t1)) printf("%lld %lld ", t1[i], t2[i]);
        puts("");
    }
}
