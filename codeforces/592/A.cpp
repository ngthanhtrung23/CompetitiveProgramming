
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

string a[11];

bool no(int l, int r, int j, char c) {
    FOR(i,l,r) if (a[i][j] == c) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a[0]) {
        FOR(i,1,7) cin >> a[i];

        int white = 10000, black = 10000;
        REP(i,8) REP(j,8) {
            if (a[i][j] == 'W' && no(0,i-1,j,'B')) white = min(white, i);
            if (a[i][j] == 'B' && no(i+1,7,j,'W')) black = min(black, 7-i);
        }
        
        if (white <= black) cout << 'A' << endl;
        else cout << 'B' << endl;
    }
}
