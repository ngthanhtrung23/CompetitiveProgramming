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

string s;
vector<string> vars;
vector< pair<string,string> > conds;
map< string, int > values;

void solve() {
    int oo = 10111;
    REP(turn,oo) {
        bool ok = true;
        REP(i,conds.size()) {
            string l = conds[i].first, r = conds[i].second;
            if (values[l] <= values[r]) {
                ok = false;
                ++values[l];
                if (values[l] == 10) {
                    cout << "false" << endl;
                    return ;
                }
            }
        }
        if (ok) {
            for(string s : vars) {
                cout << values[s];
            }
            cout << endl;
            return ;
        }

        if (turn == oo-1) {
            cout << "false" << endl;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        vars.clear();
        conds.clear();
        values.clear();
        int id = s.find(":-");
        string left = s.substr(0, id);
        string right = s.substr(id+2);

        REP(i,left.size()) if (left[i] != '_') left[i] = ' ';
        stringstream ss1(left);
        string tmp;
        while (ss1 >> tmp) {
            vars.push_back(tmp);
            values[tmp] = 0;
        }
        // PR0(vars, vars.size());

        REP(i,right.size()) if (right[i] == ',' || right[i] == '.') right[i] = ' ';
        istringstream ss2(right);
        while (ss2 >> tmp) {
            REP(i,tmp.length()) {
                if (tmp[i] == '>') {
                    conds.push_back(make_pair(tmp.substr(0, i), tmp.substr(i+1)));
                }
                else if (tmp[i] == '<') {
                    conds.push_back(make_pair(tmp.substr(i+1), tmp.substr(0, i)));
                }
            }
        }
        // REP(i,conds.size()) cout << conds[i].first << ' ' << conds[i].second << endl;

        solve();
    }
    return 0;
}
