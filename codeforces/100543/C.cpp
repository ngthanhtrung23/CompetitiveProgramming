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

void print(long long n, long long a, long long b) {
    cout << n << " =";
    FOR(i,a,b) {
        if (i == a) cout << ' '; else cout << " + ";
        cout << i;
    }
    cout << endl;
}

long long savea = -1, saveb = -1;
void update(long long n, long long a, long long b) {
    if (savea < 0) savea = a, saveb = b;
    else if (saveb - savea > b - a) {
        savea = a, saveb = b;
    }
}

long long N;
bool check(long long sum, long long &a, long long &b) {
    long long diff = N / sum - 1;
    if (diff <= 0) return false;

    if ((sum + diff) % 2) return false;
    a = (sum - diff) / 2;
    b = (sum + diff) / 2;

    return b > a && a > 0;
}

void solve(long long n) {
    if (n == 1) return ;
    if (n % 2 == 1) {
        savea = n / 2;
        saveb = n / 2 + 1;
        return ;
    }
    n *= 2;
    N = n;
    for(long long x = 1; x*x <= n; x++)
        if (n % x == 0) {
            long long a, b;
            if (check(x, a, b)) {
                update(n, a, b);
            }
            if (check(n/x, a, b)) {
                update(n, a, b);
                break;
            }
        }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        long long n; cin >> n;
        savea = saveb = -1;
        solve(n);
        if (savea == -1) cout << "IMPOSSIBLE" << endl;
        else print(n, savea, saveb);
    }
    return 0;
}