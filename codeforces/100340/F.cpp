
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

string a, b;
map<char,string> mp;
set<string> all;

void attempt(int i, int j) {
    if (i == SZ(a) && j == SZ(b)) {
        for(auto p : mp) {
            cout << p.first << ' ' << p.second << endl;
        }
        throw 1LL;
    }
    if (i == SZ(a) || j == SZ(b)) {
        return ;
    }

    // we're at position i of string a, position j of string b
    if (mp.count(a[i])) {
        // already mapped to some string --> need to check here

        string t = mp[a[i]];
        if (b.substr(j, SZ(t)) == t) {
            attempt(i+1, j + SZ(t));
        }
    }
    else {
        string cur = "";
        FOR(jj,j+0,j+9) {
            if (jj >= SZ(b)) break;

            cur += b[jj];
            if (all.count(cur)) break;

            bool can = true;
            for(auto p : all) {
                if (p.substr(0, SZ(cur)) == cur) {
                    can = false;
                    break;
                }
            }
            if (!can) continue;

            mp[a[i]] = cur;
            all.insert(cur);

            attempt(i+1, jj+1);

            all.erase(cur);
            mp.erase(a[i]);
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    while (cin >> a >> b) {
        mp.clear();
        all.clear();
        try {
            attempt(0, 0);
        } catch (int e) {
            cout << endl;
        }
    }
}
