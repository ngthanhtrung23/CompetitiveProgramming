
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 100111;

int na, nb, a[MN], b[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> na >> nb) {
        int xa, xb; cin >> xa >> xb;
        FOR(i,1,na) cin >> a[i];
        FOR(i,1,nb) cin >> b[i];
        sort(a+1, a+na+1);
        sort(b+1, b+nb+1);

        if (a[xa] < b[nb - xb + 1]) puts("YES"); else puts("NO");
    }
}
