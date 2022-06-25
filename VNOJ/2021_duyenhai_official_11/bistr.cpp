//    10, 2, 1, 2, 10
// -> 10, (2, 1, 2), 10
// -> (10, 2, 1, 2, 10)

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

struct Seg {
    int position;
    int sum;

    Seg(int _position, int _sum)
        : position(_position), sum(_sum) {
    }

    int cost() const {
        return sum;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    int n, k;
    while (cin >> n >> k) {
        string s; cin >> s; s = " " + s + " ";
        vector<int> a;

        int cnt = 1;
        FOR(i,2,n+1) {
            if (s[i] != s[i-1]) {
                a.push_back(cnt);
                cnt = 1;
            } else {
                ++cnt;
            }
        }

        n = SZ(a);

        auto cmpPosition = [] (const Seg& u, const Seg& v) {
            return u.position < v.position;
        };
        auto cmpCost = [] (const Seg& u, const Seg& v) {
            if (u.cost() != v.cost()) {
                return u.cost() < v.cost();
            }
            return u.position < v.position;
        };

        int finalRes = n * 2;
        REP(canFlipFirst,2) REP(canFlipLast,2) {
            set<Seg, decltype(cmpPosition)> sByPosition(cmpPosition);
            set<Seg, decltype(cmpCost)> sByCost(cmpCost);

            Seg zeroLeft(0, 0);
            Seg zeroRight(n+1, 0);

            sByPosition.insert(zeroLeft);
            sByPosition.insert(zeroRight);

            int res = 0;
            for (int i = 0; i < n; i++) {
                int cost = a[i];
                if (canFlipFirst) {
                    if (i == 0) {
                        res += a[i];
                        continue;
                    }
                    if (i == 1) {
                        cost = 1e9;
                    }
                } else {
                    if (i == 0) cost = 1e9;
                }

                if (canFlipLast) {
                    if (i == n-1) {
                        res += a[i];
                        continue;
                    }
                    if (i == n-2) {
                        cost = 1e9;
                    }
                } else {
                    if (i == n-1) cost = 1e9;
                }

                Seg cur(i + 1, cost);
                sByPosition.insert(cur);
                sByCost.insert(cur);
            }

            /*
            for (auto seg : sByPosition) {
                cout << '[' << seg.position
                    << ' ' << seg.cost()
                    << "]  ";
            }
            cout << endl;
            */

            while (SZ(sByCost) > k) {
                Seg cur = *sByCost.begin();
                res += cur.cost();

                auto it = sByPosition.find(cur);
                Seg left = *(prev(it));
                Seg right = *(next(it));

                
                Seg newSeg(
                        cur.position,
                        left.sum - cur.sum + right.sum);

                sByPosition.erase(cur);
                sByCost.erase(cur);

                if (left.position != 0) {
                    sByPosition.erase(left);
                    sByCost.erase(left);
                }
                if (right.position != n+1) {
                    sByPosition.erase(right);
                    sByCost.erase(right);
                }

                sByPosition.insert(newSeg);
                sByCost.insert(newSeg);

                /*
                for (auto seg : sByPosition) {
                    cout << '[' << seg.position
                        << ' ' << seg.cost()
                        << "]  ";
                }
                cout << endl;
                */
            }
            finalRes = min(finalRes, res);
        }
        cout << finalRes << endl;
    }
    return 0;
}
