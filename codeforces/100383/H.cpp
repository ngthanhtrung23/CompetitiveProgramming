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

const int MN = 100111;
string q;
int n;
int a[MN];
ll h[MN], p[MN];

struct Id {
    int x;
    Id(int x) : x(x) {}
};

bool equal(int l, int r, int u, int v) {
    if (r - l != v - u) return 0;

    return (h[r] - h[l-1]) * p[u]
        == (h[v] - h[u-1]) * p[l];
}

int lcp(int u, int v) {
    int l = 0, r = min(u, v);
    int res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (equal(u - mid + 1, u, v - mid + 1, v)) {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return res;
}

int getChar(int id) {
    if (id < 1) return 0;
    if (id > n) return 0;
    return a[id];
}

bool operator < (const Id& a, const Id& b) {
    int l = lcp(a.x, b.x);
    return getChar(a.x-l) < getChar(b.x-l);
}

set<Id> suffix_array;
ll res[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    p[0] = 1; FOR(i,1,MN-1) p[i] = p[i-1] * 31;

    while (cin >> q) {
        n = 0;
        suffix_array.clear();

        res[0] = 0;

        for(char c : q) {
            if (c == '-') {
                suffix_array.erase(Id(n));
                --n;
            }
            else {
                int add = c - 'a' + 1;

                ++n;
                a[n] = add;
                h[n] = h[n-1] + a[n] * p[n];

                auto it = suffix_array.insert(Id(n)).first;
                int l = 0;
                if (it != suffix_array.begin()) {
                    auto prev = it;
                    --prev;
                    
                    l = max(l, lcp(it->x, prev->x));
                }
                auto next = it;
                ++next;
                if (next != suffix_array.end()) {
                    l = max(l, lcp(it->x, next->x));
                }

                res[n] = res[n-1] + n - l;
            }
            printf("%lld\n", res[n]);
            continue;

            cout << "s = "; FOR(j,1,n) cout << (char) (a[j] + 'a' - 1);
            cout << endl;
            for(auto id : suffix_array) {
                cout << id.x << ": ";
                FORD(j,id.x,1) {
                    cout << (char) (a[j] + 'a' - 1);
                }
                cout << endl;
            }
        }
    }
}
