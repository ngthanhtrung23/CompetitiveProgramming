
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

char match[333];
bool isOpen[333], isClose[333];

void setMatch(char a, char b) {
    match[a] = b;
    match[b] = a;

    isOpen[a] = true;
    isClose[b] = true;
}

void solve(const string &s) {
    stack<char> st;
    int res = 0;
    for(char c : s) {
        if (isOpen[c]) {
            st.push(c);
        }
        else {
            if (st.empty()) {
                cout << "Impossible" << endl;
                return ;
            }
            else {
                char d = st.top(); st.pop();
                if (match[c] != d) ++res;
            }
        }
    }
    if (!st.empty()) {
        cout << "Impossible" << endl;
        return ;
    }
    cout << res << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    setMatch('<', '>');
    setMatch('{', '}');
    setMatch('[', ']');
    setMatch('(', ')');

    string s;
    while (cin >> s) {
        solve(s);
    }
}
