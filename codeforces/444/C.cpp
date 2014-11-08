#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;

struct Segment {
    int u, v;
    long long col;
    Segment(int u, int v, long long col) : u(u), v(v), col(col) {}
};

bool operator < (const Segment &a, const Segment &b) {
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

struct Node {
    long long cover, sum;
} it[MN * 8];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void refine(int i, int l, int r, int mid) {
    if (it[i].cover) {
        it[CT(i)].sum += (mid - l + 1) * it[i].cover;
        it[CT(i)].cover += it[i].cover;

        it[CP(i)].sum += (r - mid) * it[i].cover;
        it[CP(i)].cover += it[i].cover;

        it[i].cover = 0;
    }
}

long long get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;
    int mid = (l + r) >> 1;
    refine(i, l, r, mid);
    return get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);
}

void update(int i, int l, int r, int u, int v, long long add) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].cover += add;
        it[i].sum += (r - l + 1) * add;
        return ;
    }
    int mid = (l + r) >> 1;
    refine(i, l, r, mid);

    update(CT(i), l, mid, u, v, add);
    update(CP(i), mid+1, r, u, v, add);
    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, q;
    while (cin >> n >> q) {
        memset(it, 0, sizeof it);
        set< Segment > segs;
        FOR(i,1,n) segs.insert(Segment(i, i, i));
        // cout << "Init" << endl;
        // for(Segment seg : segs) {
            // cout << seg.u << ' ' << seg.v << ' ' << seg.col << endl;
        // }
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u, v, col; cin >> u >> v >> col;
                auto it_left = segs.upper_bound(Segment(u, n+1, u)); --it_left;
                auto it_right = segs.upper_bound(Segment(v, n+1, v));

                vector<Segment> cur;
                while (it_left != it_right) {
                    cur.push_back(*it_left);
                    ++it_left;
                }
                REP(i,cur.size()) {
                    segs.erase(cur[i]);
                    if (cur[i].u <= u && v <= cur[i].v) {
                        segs.insert(Segment(cur[i].u, u-1, cur[i].col));
                        segs.insert(Segment(v+1, cur[i].v, cur[i].col));
                        update(1, 1, n, u, v, abs(cur[i].col - col));
                    }
                    else if (cur[i].u < u) {
                        segs.insert(Segment(cur[i].u, u-1, cur[i].col));
                        update(1, 1, n, u, cur[i].v, llabs(cur[i].col - (long long) col));
                    }
                    else if (cur[i].v > v) {
                        segs.insert(Segment(v+1, cur[i].v, cur[i].col));
                        update(1, 1, n, cur[i].u, v, llabs(cur[i].col - (long long) col));
                    }
                    else {
                        update(1, 1, n, cur[i].u, cur[i].v, llabs(cur[i].col - (long long) col));
                    }
                }
                segs.insert(Segment(u, v, col));
                // cout << "Insert " << u << ' ' << v << ' ' << col << endl;
                // for(Segment seg : segs) {
                    // cout << seg.u << ' ' << seg.v << ' ' << seg.col << endl;
                // }
            }
            else {
                int u, v; cin >> u >> v;
                cout << get(1, 1, n, u, v) << "\n";
            }
        }
    }
    return 0;
}
