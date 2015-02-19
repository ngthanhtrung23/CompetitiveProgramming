
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

char s[1000111];

int main() {
    while (gets(s)) {
        int first = -1, last = -1;
        REP(i,strlen(s)) if (s[i] == '1') {
            if (first < 0) first = i;
            last = i;
        }
        int cnt0 = 0;
        FOR(i,first,last) if (s[i] == '0') ++cnt0;
        
        int l = strlen(s);
        int res = cnt0; if (first != last) ++res, ++l;

        res += l - 1;
        cout << res << endl;
    }
    return 0;
}
