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

const int MN = 200111;
multiset<int> crim;
int a, b, c, n, x[MN], my[3];

void eraseOne(int x) {
    if (x > 0) x = -x;
    crim.erase(crim.find(x));
}

void eraseLower(int x) {
    assert(x > 0);
    if (crim.empty()) return ;
    auto it = crim.lower_bound(-x);
    if (it == crim.end()) return ;
    crim.erase(it);
}

bool check(int turn) {
    multiset<int> save = crim;

    REP(i,turn) {
        eraseLower(a); // use a in every turn
    }

    REP(i,turn) {
        int x = -(*crim.begin());

        if (x > b) {
            // must use b + c
            eraseLower(b+c);
        }
        else {
            eraseLower(b);
            eraseLower(c);
        }
    }

    bool res = crim.empty();
    crim = save;

    return res;
}

int solve() {
    int res = 0;
    while (!crim.empty()) {
        int x = -(*crim.begin());
        if (x > a + b + c) return -1;

        if (x > a + b) {
            // must use a + b + c
            ++res;
            eraseOne(x);
        }
        else if (x > a + c) {
            // must use a + b
            ++res;
            eraseOne(x);
            eraseLower(c);
        }
        else if (x > max(a, b+c)) {
            // must use a + c
            ++res;
            eraseOne(x);
            eraseLower(b);
        }
        else break;
    }
    if (crim.empty()) return res;

    int firstPart = res;

    int l = 1, r = SZ(crim);
    res = r;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res + firstPart;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        REP(i,3) scanf("%d", &my[i]);
        sort(my, my+3);
        a = my[2];
        b = my[1];
        c = my[0];

        crim.clear();
        FOR(i,1,n) {
            int u; scanf("%d", &u);
            crim.insert(-u);
        }
        printf("%d\n", solve());
    }
}
