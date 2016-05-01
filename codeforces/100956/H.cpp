
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

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

int n, k;
struct V {
    int x, y, z;

    V() {}
    V(int x, int y, int z) : x(x), y(y), z(z) {}

    V operator + (const V& a) const {
        return V(x+a.x, y+a.y, z+a.z);
    }

    int len() {
        return x*x + y*y + z*z;
    }
} v[44];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> k;
        FOR(i,1,n) cin >> v[i].x >> v[i].y >> v[i].z;

        int bestsum = 0;
        vector<int> res;
        if (k == 1) {
            FOR(a,1,n) {
                V cur = v[a];
                if (cur.len() > bestsum) {
                    bestsum = cur.len();
                    res = vector<int> {a};
                }
            }
        }
        else if (k == 2) {
            FOR(a,1,n) FOR(b,a+1,n) {
                V cur = v[a] + v[b];
                if (cur.len() > bestsum) {
                    bestsum = cur.len();
                    res = vector<int> {a, b};
                }
            }
        }
        else if (k == 3) {
            FOR(a,1,n) FOR(b,a+1,n) FOR(c,b+1,n) {
                V cur = v[a] + v[b] + v[c];
                if (cur.len() > bestsum) {
                    bestsum = cur.len();
                    res = vector<int> {a, b, c};
                }
            }
        }
        else if (k == 4) {
            FOR(a,1,n) FOR(b,a+1,n) FOR(c,b+1,n) FOR(d,c+1,n) {
                V cur = v[a] + v[b] + v[c] + v[d];
                if (cur.len() > bestsum) {
                    bestsum = cur.len();
                    res = vector<int> {a, b, c, d};
                }
            }
        }
        else {
            FOR(a,1,n) FOR(b,a+1,n) FOR(c,b+1,n) FOR(d,c+1,n) {
                vector< pair<int,int> > cur;

                V X = v[a] + v[b] + v[c] + v[d];
                FOR(e,1,n) if (e != a && e != b && e != c && e != d) {
                    V t = X + v[e];
                    cur.emplace_back(t.len(), e);
                }

                sort(cur.begin(), cur.end(), greater< pair<int,int> > ());

                vector<int> t;
                t.push_back(a);
                t.push_back(b);
                t.push_back(c);
                t.push_back(d);

                REP(i,k-4) t.push_back(cur[i].second);

                X = V(0, 0, 0);

                for(auto i : t)
                    X = X + v[i];

                if (X.len() > bestsum) {
                    bestsum = X.len();
                    res = t;
                }
            }
        }
        cout << bestsum << endl;
        sort(res.begin(), res.end());
        for(auto x : res) cout << x << ' ';
        cout << endl;
    }
}
