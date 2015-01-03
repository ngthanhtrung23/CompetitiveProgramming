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

const int MN = 100111;

struct Str {
    int typ, x;
} a[MN];
int m;
long long n;
long long best, cnt;

bool operator < (const Str& a, const Str& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.typ < b.typ;
}

Str reverse(const Str& a) {
    Str res;
    res.typ = 1 - a.typ;
    res.x = n - a.x;
    return res;
}

void update(long long val, long long c) {
    if (!c) return ;
    if (val > best) {
        best = val;
        cnt = c;
    }
    else if (val == best) {
        cnt += c;
    }
}

int count(int typ) {
    int res = 0;
    FOR(i,1,m)
        if (a[i].typ == typ) ++res;
    return res;
}

long long c3(long long n) {
    return n * (n-1LL) * (n-2LL) / 6;
}

long long c2(long long n) {
    return n * (n-1LL) / 2;
}

void case1() {
    // Case 1: X, Y, Z  (x <= y <= z)
    // Sum = H(X, Y) + H(Y, Z) + H(Z, X)
    //     = 2z - 2x
    // Thus, choose max z and min x
    int nn = -1, ln = -1;
    FOR(i,1,m)
        if (a[i].typ == 0) {
            if (nn < 0) nn = a[i].x; else nn = min(nn, a[i].x);
            if (ln < 0) ln = a[i].x; else ln = max(ln, a[i].x);
        }
    if (nn == ln) {
        update(0LL, c3(count(0)));
    }
    else {
        long long cnt_min = 0, cnt_max = 0, cnt_mid = 0;
        FOR(i,1,m)
            if (a[i].typ == 0) {
                if (a[i].x == nn) cnt_min++;
                else if (a[i].x == ln) cnt_max++;
                else cnt_mid++;
            }
        update(2LL*ln - 2LL*nn,
                cnt_min * cnt_max * cnt_mid
                + c2(cnt_min) * cnt_max
                + cnt_min * c2(cnt_max)
                );
    }
}

void case2() {
    // Case 2: _X, Y, Z
    // Sum = H(_X, Y) + H(Y, Z) + H(_X, Z)
    //     = 2n + 2x - 2y
    long long y = -1, cnt_y = 0, cnt_all = 0;
    FORD(i,m,1) {
        if (a[i].typ == 0) {
            if (a[i].x == y) ++cnt_y;
            else {
                y = a[i].x;
                cnt_y = 1;
            }
            ++cnt_all;
        }
        else {
            update(2LL*n + 2LL*a[i].x - 2LL*y,
                    c2(cnt_y)
                    + cnt_y * (cnt_all - cnt_y)
                  );
        }
    }
}

#define left left_
#define right right_
long long left[MN], right[MN];
void case3() {
    // Case 3: X, _Y, Z
    // Sum = H(X, _Y) + H(_Y, Z) + H(X, Z)
    //     = 2n
    FOR(i,1,m) {
        left[i] = left[i-1];
        if (a[i].typ == 0) ++left[i];
    }
    right[m+1] = 0;
    FORD(i,m,1) {
        right[i] = right[i+1];
        if (a[i].typ == 0) ++right[i];
    }
    FOR(i,2,m-1)
        if (a[i].typ == 1) {
            update(2LL*n, left[i-1] * right[i+1]);
        }
}

void case4() {
    // Case 4: X, Y, _Z
    // Sum = 2n + 2y - 2z
    long long y = -1, cnt_y = 0, cnt_all = 0;
    FOR(i,1,m) {
        if (a[i].typ == 0) {
            if (a[i].x == y) ++cnt_y;
            else {
                y = a[i].x;
                cnt_y = 1;
            }
            cnt_all++;
        }
        else {
            update(2LL*n + 2LL*y - 2LL*a[i].x,
                    c2(cnt_y)
                    + cnt_y * (cnt_all - cnt_y));
        }
    }
}

void solve() {
    sort(a+1, a+m+1);
    if (!count(0)) return ;
    // Let X = 0^x 1^(n-x)
    // Let _X = 1^x 0^(n-x)
    case1();
    if (!count(1)) return ;
    case2();
    case3();
    case4();
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        FOR(i,1,m) cin >> a[i].typ >> a[i].x;
        best = -1, cnt = 0;
        solve();
        FOR(i,1,m) a[i] = reverse(a[i]);
        solve();

//        DEBUG(best);
        cout << cnt << endl;
    }
    return 0;
}
