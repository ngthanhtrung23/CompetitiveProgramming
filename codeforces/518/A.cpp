
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

string s, t;
char tmp[100111];

int main() {
    while (gets(tmp)) {
        s = string(tmp);
        gets(tmp); t = string(tmp);

        if (s >= t) cout << "No such string" << endl;
        else {
            bool ok = false;
            FORD(i,s.length()-1,0) {
                if (s[i] == 'z') s[i] = 'a';
                else {
                    ++s[i];
                    ok = true;
                    break;
                }
            }
            if (ok && s < t) puts(s.c_str());
            else cout << "No such string" << endl;
        }
    }
    return 0;
}
