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

string s[] = {
    "qwertyuiop",
    "asdfghjkl;",
    "zxcvbnm,./"
};

pair<int,int> getPos(char c) {
    REP(i,3) REP(j,s[i].length())
        if (s[i][j] == c)
            return make_pair(i, j);
    cout << ":@)" << endl;
    return make_pair(0, 0);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    char dir; string a;
    while (cin >> dir >> a) {
        REP(i,a.length()) {
            pair<int,int> pos = getPos(a[i]);
            if (dir == 'R') --pos.second;
            if (dir == 'L') ++pos.second;

            cout << s[pos.first][pos.second];
        }
        cout << endl;
    }
    return 0;
}
