
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

int main() {
    ios :: sync_with_stdio(false);
    int n;
    string s;
    while (cin >> n >> s) {
        int firstR = -1, lastR = -1;
        int firstL = -1, lastL = -1;
        REP(i,n) {
            if (s[i] == 'R') {
                if (firstR < 0) firstR = i;
                lastR = i;
            }
            if (s[i] == 'L') {
                if (firstL < 0) firstL = i;
                lastL = i;
            }
        }
        int s, t;
        if (firstR < 0) {
            // all L
            s = lastL;
            t = firstL - 1;
        }
        else if (firstL < 0) {
            // all R
            s = firstR;
            t = lastR + 1;
        }
        else {
            s = firstR;
            t = lastR;
        }
        cout << s+1 << ' ' << t+1 << endl;
    }
}
