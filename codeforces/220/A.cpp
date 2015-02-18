
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

int n, a[MN];

bool isIncreasing() {
    FOR(i,1,n-1) if (a[i] > a[i+1]) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        if (isIncreasing()) cout << "YES";
        else {
            int x = -1;
            FOR(i,1,n-1) if (a[i] > a[i+1]) {
                x = i;
                break;
            }
            while (x > 1 && a[x-1] == a[x]) --x;
            int y = x + 1;

            FOR(i,x+1,n) if (a[i] < a[x]) y = i;

            swap(a[x], a[y]);

            if (isIncreasing()) cout << "YES";
            else cout << "NO";
        }
        cout << endl;
    }
    return 0;
}

