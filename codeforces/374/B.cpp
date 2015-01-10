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

long long f[100111];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    string s;
    while (cin >> s) {
        int n = s.length();
        long long res = 1;
        int i = 0;
        while (i < n - 1) {
            if (s[i] + s[i+1] == '9' + '0') {
                int j = i + 1;
                while (j+1 < n && s[j] + s[j+1] == '9' + '0') ++j;
                if ((j - i + 1) % 2) res = res * ((j - i) / 2 + 1);
                i = j + 1;
            }
            else ++i;
        }
        cout << res << endl;
    }
    return 0;
}

