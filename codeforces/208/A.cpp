#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i >= _b; --i)
#define REP(i,a) for(int i = 0, _a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

char tmp[100111];

int main() {
    while (gets(tmp)) {
        string s(tmp);
        while (s.find("WUB") < s.length()) {
            s.replace(s.find("WUB"), 3, " ");
        }
        while (s[0] == ' ') s.erase(0, 1);
        while (s[s.length()-1] == ' ') s.erase(s.length()-1, 1);

        while (s.find("  ") < s.length()) {
            s.replace(s.find("  "), 2, " ");
        }
        cout << s << endl;
    }
    return 0;
}
