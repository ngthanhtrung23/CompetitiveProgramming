#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;
const int MN = 1000111;

struct Node {
    int ln, sub;
} it[MN * 4];

string s;
int n, a[MN], skipped[MN];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void up(int i) {
    it[i].ln = max(it[CT(i)].ln, it[CP(i)].ln);
    it[i].sub = 0;
}
void down(int i) {
    if (it[i].sub) {
        int k = it[i].sub;
        it[CT(i)].sub += k;
        it[CT(i)].ln -= k;

        it[CP(i)].sub += k;
        it[CP(i)].ln -= k;

        it[i].sub = 0;
    }
}
void build(int i, int l, int r) {
    if (l == r) {
        it[i].ln = a[l];
        it[i].sub = 0;
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    up(i);
}

void subtract(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].sub++;
        it[i].ln--;
        return ;
    }
    int mid = (l + r) >> 1;
    down(i);
    subtract(CT(i), l, mid, u, v);
    subtract(CP(i), mid+1, r, u, v);
    up(i);
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return -1000111000;
    if (u <= l && r <= v) return it[i].ln;
    down(i);
    int mid = (l + r) >> 1;
    int res = max(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
    up(i);
    return res;
}

bool check0() {
    map<int,int> visited;
    visited[0] = 1;
    int pos = 0;
    REP(i,s.size()) {
        if (s[i] == 'L') {
            --pos;
            visited[pos] += 1;
        }
        else if (s[i] == 'R') {
            ++pos;
            visited[pos] += 1;
        }
    }
    if (visited[pos] == 1) {
        cout << 1 << endl;
        return true;
    }
    else return false;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        if (s.back() == 'L') {
            REP(i,s.size()) s[i] = 'L' + 'R' - s[i];
        }
//        DEBUG(s);

        if (check0()) continue;

        // Init the sequences
        n = 0;
        int cur_skip = 0, pos = 0;
        map<int,int> visited;
        visited[0] = 1;

        REP(i,s.length()) {
            if (s[i] == 'R') {
                ++pos;
                if (i+1 == s.length() || s[i+1] == 'L') {
                    ++n;
                    a[n] = pos;
                    skipped[n] = cur_skip;
                    cur_skip = 0;
                }
            }
            else {
                --pos;
                if (pos < 0) ++cur_skip, pos = 0;
            }
            visited[pos] += 1;
        }
//        PR(a, n);
//        PR(skipped, n);

        build(1, 1, n);
        int res = 0;
        if (visited[pos] == 1) ++res;
        FOR(i,1,n) {
            while (skipped[i]) {
                subtract(1, 1, n, i, n);
                int at_n = get(1, 1, n, n, n);
                int best = get(1, 1, n, 1, n-1);

                if (at_n > best && at_n > 0) ++res;
                --skipped[i];
            }
        }
        cout << res << endl;
    }
    return 0;
}

