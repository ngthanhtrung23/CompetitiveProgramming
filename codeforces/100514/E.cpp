#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

string morse = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.";
map<string,char> m;
char tmp[100111];

int main() {
    istringstream ss(morse);
    FOR(i,'A','Z') {
        string s; ss >> s;
        REP(i,s.size()) if (s[i] == '.') s[i] = 'F'; else s[i] = 'U';
        m[s] = i;
    }
    FOR(i,'0','9') {
        string s; ss >> s;
        REP(i,s.size()) if (s[i] == '.') s[i] = 'F'; else s[i] = 'U';
        m[s] = i;
    }

    while (gets(tmp)) {
        stringstream ss(tmp);
        string s;
        while (ss >> s) {
            cout << m[s];
        }
        cout << endl;
    }
    return 0;
}
