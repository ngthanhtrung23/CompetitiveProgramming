
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

const int MOD = 1e9 + 7;
int GI(int& x) {
    return scanf("%d", &x);
}

int k, n;
int cache[1<<16], cache2[1<<16];

int reverseSlow(int k, int x) {
    int res = 0;
    REP(bit,k) {
        res = res * 2 + ((x >> bit) & 1);
    }
    return res;
}

int reverse(int k, int x) {
    if (k <= 16) return cache[x];
    else {
        int x1 = x >> 16;
        int x2 = x & ((1<<16) - 1);

        x1 = cache2[x1];
        x2 = cache[x2];

        return (x2 << (k - 16)) + x1;
    }
}

int f(int k, int l) {
    if (k == 0) return 0;

    int lastBit = l & 1;

    int x = l >> 1;
    x = reverse(k-1, x);

    if (lastBit == 1) {
        x ^= (1<<(k-1)) - 1;
    }
    return (x<<1) + lastBit;
}

ll get(int l, int r, int k) {
    if (l % 2 == 0) {
        int t = r - l + 1;

        switch (t % 4) {
            case 0: return 0;
            case 1: return f(k, r);
            case 2: return n - 1;
            case 3: return n - 1 - f(k, r);
        }
    }
    else {
        int t = r - l + 1;
        if (t % 2 == 0) {
            return f(k, l) + f(k, r) + (t / 2 - 1) * (n - 1LL);
        }
        else {
            return f(k, l) + (t / 2) * (n - 1LL);
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
//    REP(k,5) {
//        REP(l,1<<k) cout << f(k, l) << ' '; cout << endl;
//    }
//    return 0;

    while (cin >> k) {
        --k;
        if (k <= 16) {
            REP(i,1<<k) cache[i] = reverseSlow(k, i);
        }
        else {
            REP(i,1<<16) cache[i] = reverseSlow(16, i);

            int k2 = k - 16;
            REP(i,1<<k2) cache2[i] = reverseSlow(k2, i);
        }
        ++k;

        int m, l0, r0;
        cin >> m >> l0 >> r0;
        ll a, b, c; cin >> a >> b >> c;

        ll l, r;
        ll h;
        h = 0;

        n = 1<<k;
        ll res = 0;
        REP(i, m+1) {
            if (i == 0) {
                l = l0;
                r = r0;
            }
            else {
                h = ((l ^ r ^ h ^ res) + c) % MOD;
                l = ((l ^ a ^ h) % (n+1)) % n;
                r = ((r ^ b ^ h) % (n - l)) + l;
            }
//            cout << l << ' ' << r << endl;
            res = get(l, r, k);
//            DEBUG(res);
        }
        cout << h << endl;
    }
}
