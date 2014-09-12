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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1011;
string fullname[MN], name[MN], ext[MN];
bool bad[MN];
int n, m;
map<string,int> cntName, cntExt;

int main() {
    ios :: sync_with_stdio(false);
    cin >> n >> m;
    FOR(i,1,n) {
        cin >> fullname[i];
        size_t found = fullname[i].find('.');
        if (found == string::npos) {
            ext[i] = "";
            name[i] = fullname[i];
        } else {
            ext[i] = fullname[i].substr(found + 1);
            name[i] = fullname[i].substr(0, found);
        }
    }

    FOR(turn,1,m) {
        cntName.clear();
        cntExt.clear();

        FOR(i,1,n) if (!bad[i]) {
            cntName[name[i]]++;
            cntExt[ext[i]]++;
        }

        // EACH(it,cntName) cout << it->first << ' ' << it->second << "   "; cout << endl;
        // EACH(it,cntExt) cout << it->first << ' ' << it->second << "   "; cout << endl;

        FOR(i,1,n) if (!bad[i]) {
            if (turn % 2 == 1) {
                if (cntExt[ext[i]] <= 1)
                    bad[i] = true;
            } else {
                if (cntName[name[i]] <= 1)
                    bad[i] = true;
            }
        }
    }

    int res = 0;
    FOR(i,1,n) if (!bad[i]) ++res;
    cout << res << endl;
    FOR(i,1,n) if (!bad[i]) cout << fullname[i] << endl;
    return 0;
}
