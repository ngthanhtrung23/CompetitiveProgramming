
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
using namespace std;

vector<string> gen(int n) {
    if (n == 2) {
        vector<string> res = {"00", "01", "11", "10"};
        return res;
    } else if (n == 3) {
        vector<string> res = {
            "000", "001", "011", "010",
            "110", "111", "101", "100"
        };
        return res;
    }

    auto cur = gen(n-2);
    vector<string> res;

    vector<string> a[4];
    a[0] = {"00", "01", "11", "10"};
    a[1] = {"11", "10", "00", "01"};
    a[3] = {"01", "00", "10", "11"};
    a[2] = {"10", "11", "01", "00"};

    REP(turn,4) {
        REP(i,cur.size()) {
            res.push_back(cur[i] + a[turn][i % 4]);
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);
    int n;
    while (cin >> n) {
        auto res = gen(n);
        for(string s : res) {
            puts(s.c_str());
        }
    }
}

