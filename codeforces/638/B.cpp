
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
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int ke[333][333];
int vao[333], appear[333];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        memset(ke, 0, sizeof ke);
        memset(vao, 0, sizeof vao);
        memset(appear, 0, sizeof appear);

        FOR(i,1,n) {
            string s; cin >> s;
            for(char c : s) appear[c] = 1;
            REP(u,SZ(s)) FOR(v,u+1,SZ(s)-1) {
                if (ke[s[u]][s[v]]) continue;
                ke[s[u]][s[v]] = 1;
                vao[s[v]]++;
            }
        }
        stack<int> st;
        string res = "";
        FOR(c,'a','z') {
            if (appear[c] && vao[c] == 0) {
                st.push(c);
            }
        }
        while (!st.empty()) {
            int c = st.top(); st.pop();
            res += c;
            FOR(x,'a','z') if (ke[c][x]) {
                --vao[x];
                if (!vao[x]) st.push(x);
            }
        }
        cout << res << endl;
    }
}
