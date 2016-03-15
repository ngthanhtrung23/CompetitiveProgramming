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
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1011;

int n;

bool canOdd(int a, int n) {
    int x = a * (a - 1) / 2;
    if (n == x) return true;
    if (n == x + 1) return false;
    if (n > x) return true;
    return false;
}
bool canEven(int a, int n) {
    int x = a * a / 2;
    return n >= x;
}

int res[MN], a[MN][MN];
void pattern(int x, int n) {
    int k = 0;
    FOR(i,1,x) FOR(j,i+1,x) a[i][j] = a[j][i] = 1;
    memset(res, 0, sizeof res);

    if (x % 2 == 0) {
        for(int i = 1; i < x; i += 2) {
            a[i][i+1]++;
            a[i+1][i]++;
        }
    }

    res[k = 1] = 1;
    int bound = (x % 2 == 0) ? x * (x / 2) : x * (x - 1) / 2;

    FOR(turn,2,bound) {
        int last = res[turn-1];
        int cur = x;
        while (a[last][cur] == 0) --cur;
        res[++k] = cur;

        a[last][cur]--;
        a[cur][last]--;
    }

    res[n+1] = res[1];

    while (k < n) {
        ++k;
        res[k] = 1;
        while (res[k] == res[k-1] || res[k] == res[k+1]) {
            res[k] = res[k] % x + 1;
        }
    }
    FOR(i,1,n) cout << res[i] << ' '; cout << endl;
}

int has[1011][1011];
#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("achromatic.in", "r", stdin);
    freopen("achromatic.out", "w", stdout);
    while (cin >> n) {
        int best = 0;
        // a odd
        for(int a = 3; a <= n; a += 2) {
            if (canOdd(a, n)) {
                best = max(best, a);
            }
        }
        // a even
        for(int a = 2; a <= n; a += 2) {
            if (canEven(a, n)) {
                best = max(best, a);
            }
        }
        cout << best << endl;
        pattern(best, n);

        res[n+1] = res[1];
        FOR(i,1,n) {
            if (res[i] < 1 || res[i] > best) {
                cout << "Invalid: " << i << " --> " << res[i] << endl;
                throw 1;
            }
            if (res[i] == res[i+1]) {
                cout << "Cons " << i << endl;
                throw 1;
            }
        }
        memset(has, 0, sizeof has);
        FOR(i,1,n) {
            has[res[i]][res[i+1]] = has[res[i+1]][res[i]] = 1;
        }
        FOR(i,1,best) FOR(j,i+1,best) {
            if (!has[i][j]) {
                cout << "Missing " << i << ' ' << j << endl;
                throw 1;
            }
        }
    }
}
