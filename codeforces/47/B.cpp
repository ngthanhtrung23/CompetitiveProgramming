
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

int id[333];
vector<string> all;

bool check(string s) {
    REP(i,SZ(s)) id[s[i]] = i;

    REP(i,SZ(all)) {
        string req = all[i];
        if (req[1] == '<' && id[req[0]] > id[req[2]]) return false;
        if (req[1] == '>' && id[req[0]] < id[req[2]]) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    string tmp;
    while (cin >> tmp) {
        all.push_back(tmp);
    }
    string s = "ABC";
    do {
        if (check(s)) {
            cout << s << endl;
            return 0;
        }
    } while (next_permutation(s.begin(), s.end()));
    cout << "Impossible" << endl;
}
