
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

int a[100111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("irreducible.in", "r", stdin);
    freopen("irreducible.out", "w", stdout);

    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        int black = 0, white = 0;
        FOR(i,1,n) {
            if (i % 2 == 1) {
                black += a[i] / 2 + a[i] % 2;
                white += a[i] / 2;
            }
            else {
                black += a[i] / 2;
                white += a[i] / 2 + a[i] % 2;
            }
        }

        FOR(l,0,100111) {
            int diff = 0;
            if (l % 2 == 1) diff = l / 2 + 1;
            else diff = - (l / 2);

            if (diff == black - white) {
                cout << 1 << endl;
                cout << l;
                FORD(i,l,1) cout << ' ' << i; cout << endl;
            }
        }
    }
}
