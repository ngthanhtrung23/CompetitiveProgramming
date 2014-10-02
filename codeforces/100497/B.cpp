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

string s;
vector<string> res;

bool isPalin(const string &s) {
    for(int i = 0, j = s.length() - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        res.clear();
        if (isPalin(s)) res.push_back(s);

        vector< pair<int,int> > pos;
        for(int i = 0, j = s.length() - 1; i < j; ++i, --j) {
            if (s[i] != s[j]) {
                pos.push_back(make_pair(i, j));
            }
        }
        // REP(i,pos.size()) {
        //     cout << pos[i].first << ' ' << pos[i].second << endl;
        // }

        if (pos.size() == 1 && s.length() % 2 == 1) {
            string t = s;
            swap(t[pos[0].first], t[s.length()/2]);
            if (isPalin(t)) res.push_back(t);

            t = s;
            swap(t[pos[0].second], t[s.length()/2]);
            if (isPalin(t)) res.push_back(t);
        }

        if (pos.size() == 2) {
            int u[4];
            u[0] = pos[0].first;
            u[1] = pos[1].first;
            u[2] = pos[1].second;
            u[3] = pos[0].second;

            REP(x,4) FOR(y,x+1,3) {
                string t = s;
                swap(t[u[x]], t[u[y]]);
                if (isPalin(t)) res.push_back(t);
            }
        }

        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << endl;
    }
    return 0;
}
