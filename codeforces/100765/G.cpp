
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

string s;

char up(char c) {
    if (c >= 'a' && c <= 'z') return c ^ ' ';
    else return c;
}
char down(char c) {
    if (c >= 'A' && c <= 'Z') return c ^ ' ';
    else return c;
}

int main() {
    ios :: sync_with_stdio(false);
    while (getline(cin, s)) {
        int i = 0;
        int n = s.length();
        stack<int> st;
        while (i < n) {
            char cur = s[i];
            if (cur == '<') {
                if (s[i+1] == 'U') {
                    st.push(1);
                }
                else if (s[i+1] == 'D') {
                    st.push(-1);
                }
                else if (s[i+1] == '/') {
                    st.pop();
                }
                while (s[i] != '>') ++i;
                ++i;
            }
            else {
                if (!st.empty()) {
                    if (st.top() == 1) cout << up(cur);
                    else cout << down(cur);
                    ++i;
                }
                else {
                    cout << cur;
                    ++i;
                }
            }
        }
        cout << endl;
    }
}
