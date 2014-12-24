#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct Segment {
    int l, r;
    double prob;
    int max_all, max_outside;
} a[5011];

bool operator < (const Segment& a, const Segment& b) {
    if (a.r - a.l != b.r - b.l) return a.r - a.l < b.r - b.l;
    return a.l < b.l;
}

bool isInside(const Segment& a, const Segment& b) {
    return b.l <= a.l && a.r <= b.r;
}

double f[5011][5011], tmp[5011];
int x[100111];
vector<int> child[5011];
int n, q;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        // Read input
        FOR(i,1,n) cin >> x[i];
        FOR(i,1,q) cin >> a[i].l >> a[i].r >> a[i].prob;
        // sort such that: for each segment, the segment containing it is on the right
        // if 2 segments do not contain each other, then they're sorted based on their left ends. This is
        // necessary for calculate max of segments to work.
        sort(a+1, a+q+1);
        ++q;
        a[q].l = 1;
        a[q].r = n;
        a[q].prob = 0.0;

        // For each segment, find its father and add edge
        FOR(i,1,q) child[i].clear();
//        cout << "Segments:" << endl;
        FOR(i,1,q-1) {
//            cout << a[i].l << ' ' << a[i].r << ' ' << a[i].prob << "    --> ";
            FOR(j,i+1,q)
                if (isInside(a[i], a[j])) {
                    child[j].push_back(i);
//                    cout << a[j].l << ' ' << a[j].r << endl;
                    break;
                }
        }

        // Calculate max of segments
//        PR(x, n);
//        cout << "Max values: " << endl;
        FOR(i,1,q) {
            int cur = a[i].l;
            a[i].max_all = -1;
            a[i].max_outside = -1;

            REP(t,child[i].size()) {
                int j = child[i][t];
                while (cur < a[j].l) {
                    a[i].max_outside = max(a[i].max_outside, x[cur]);
                    ++cur;
                }
                a[i].max_all = max(a[i].max_all, a[j].max_all);
                cur = a[j].r + 1;
            }
            while (cur <= a[i].r) {
                a[i].max_outside = max(a[i].max_outside, x[cur]);
                ++cur;
            }
            a[i].max_all = max(a[i].max_all, a[i].max_outside);
//            cout << a[i].max_outside << ' ' << a[i].max_all << endl;
        }

        // Now we're ready, calculate our dp function
        // mx(i) = max of elements in segment i
        // f(i, t) = prob. that at segment i, max value = mx(i) + t
        // tmp(t) = product of f(j, r) where mx(i) + t - 1 = mx(j) + r
        FOR(i,1,q) {
            FOR(t,0,5001) tmp[t] = 1;
            if (a[i].max_outside == a[i].max_all) {
                tmp[0] = 0;
            }
            REP(id,child[i].size()) {
                int j = child[i][id];
                FOR(t,0,5001) {
                    int r = a[i].max_all + t - 1 - a[j].max_all;
                    if (r < 0) tmp[t] = 0;
                    else if (r > 5000) tmp[t] = tmp[t];
                    else tmp[t] = tmp[t] * f[j][r];
                }
            }

            FOR(t,0,5000)
                f[i][t] = a[i].prob * tmp[t] + (1 - a[i].prob) * tmp[t+1];

//            PR0(f[i], 3);
        }
        double res = 0.0;
        FOR(t,0,5000) {
            double cur = f[q][t];
            if (t > 0) cur -= f[q][t-1];
            res += (a[q].max_all + t) * cur;
        }
        cout << res << endl;
    }
    return 0;
}
