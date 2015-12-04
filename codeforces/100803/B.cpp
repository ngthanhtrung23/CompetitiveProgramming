
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

string s;

ll leftRight() {
    ll res = s[0] - '0';
    for(int i = 2; i < SZ(s); i += 2) {
        int cur = s[i] - '0';
        if (s[i-1] == '+') {
            res = res + cur;
        }
        else {
            res = res * cur;
        }
    }
    return res;
}

ll get(int l, int r) {
    if (l == r) return s[l] - '0';

    // add
    for(int i = r-1; i > l; --i)
        if (s[i] == '+') {
            ll left = get(l, i-1);
            ll right = get(i+1, r);
            return left + right;
        }

    // mult
    for(int i = r-1; i > l; --i)
        if (s[i] == '*') {
            ll left = get(l, i-1);
            ll right = get(i+1, r);
            return left * right;
        }
}

int main() {
    ll res;
    while (cin >> s >> res) {
        ll lr = leftRight();
        ll m1 = get(0, SZ(s) - 1);

        if (lr == res && m1 == res) cout << 'U';
        else if (lr == res) cout << 'L';
        else if (m1 == res) cout << 'M';
        else cout << 'I';
        cout << endl;
    }
}
