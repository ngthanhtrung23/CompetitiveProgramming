
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

ll toInt(string s) {
    stringstream ss(s);
    ll res; ss >> res;
    return res;
}

bool bad(string s) {
    if (SZ(s) > 1 && s[0] == '0') return true;
    if (SZ(s) > 1 && s[0] == '-' && s[1] == '0') return true;
    return false;
}

bool check(string s) {
    int op = -1, equal = -1;
    FOR(i,1,SZ(s)-1) {
        if (s[i] == '=') equal = i;
        if (s[i] == '+' || s[i] == '-' || s[i] == '*') {
            if (op < 0) op = i;
        }
    }
    string a = s.substr(0, op);
    string b = s.substr(op+1, equal - op - 1);
    string c = s.substr(equal+1);

    if (bad(a) || bad(b) || bad(c)) return false;

    ll A = toInt(a);
    ll B = toInt(b);
    ll C = toInt(c);

    if (s[op] == '+') return A + B == C;
    if (s[op] == '-') return A - B == C;
    if (s[op] == '*') return A * B == C;
    assert(0);
    return false;
}

bool appear[11];
int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest;
    cin >> ntest;
    while (ntest--) {
        string s; cin >> s;
        memset(appear, 0, sizeof appear);
        for(char c : s) {
            appear[c - '0'] = true;
        }
        try {
            REP(ques,10) if (!appear[ques]) {
                string t = "";
                for(char c : s) {
                    if (c == '?') t += (char) ('0' + ques);
                    else t += c;
                }
                if (check(t)) {
                    cout << ques << endl;
                    throw 1;
                }
            }
            cout << -1 << endl;
        } catch(int e) {
        }
    }
}
