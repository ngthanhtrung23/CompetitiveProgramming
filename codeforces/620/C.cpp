
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

const int MN = 300111;
int f[MN], tr[MN];
#define next next____
int n, a[MN], next[MN];

void trace(int n) {
    if (f[n] == 1) {
        cout << 1 << ' ' << n << endl;
        return ;
    }
    if (n <= 0) return ;
    int x = tr[n];
    trace(x - 1);

    cout << x << ' ' << n << '\n';
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        map<int,int> id;
        FOR(i,1,n) {
            cin >> a[i];
            next[i] = id[a[i]];
            id[a[i]] = i;
        }
        FOR(i,1,n) {
            f[i] = f[i-1];
            tr[i] = tr[i-1];

            int j = next[i];
            if (j > 0 && f[j-1] + 1 > f[i]) {
                f[i] = f[j-1] + 1;
                tr[i] = j;
            }
        }
        if (f[n] == 0) cout << -1 << '\n';
        else {
            cout << f[n] << '\n';
            trace(n);
        }
        cout << endl;
    }
}
