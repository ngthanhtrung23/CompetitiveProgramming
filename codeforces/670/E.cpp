
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

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 500111;
int l[MN], r[MN];
string s;
char tmp[MN];
int mat[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, q, pos;
    while (GI(n) == 1 && GI(q) == 1 && GI(pos) == 1) {
        scanf("%s\n", &tmp[0]);
        s = " " + string(tmp) + " ";

        stack<int> st;
        FOR(i,1,n) {
            if (s[i] == '(') st.push(i);
            else if (s[i] == ')') {
                int j = st.top(); st.pop();
                mat[i] = j;
                mat[j] = i;
            }
        }

        FOR(i,0,n) r[i] = i + 1;
        FORD(i,n+1,1) l[i] = i - 1;

        while (q--) {
            char c = ' ';
            while (c < 'A' || c > 'Z') scanf("%c", &c);

            if (c == 'L') pos = l[pos];
            else if (c == 'R') pos = r[pos];
            else {
                int u = mat[pos];
                if (u > pos) {
                    int prev = l[pos], next = r[u];
                    r[prev] = next;
                    l[next] = prev;

                    pos = next;
                }
                else {
                    int prev = l[u], next = r[pos];
                    r[prev] = next;
                    l[next] = prev;

                    pos = next;
                }
                if (pos > n) pos = l[pos];
            }
        }
        int i = 0;
        while (true) {
            i = r[i]; if (i > n) break;
            putchar(s[i]);
        }
        puts("");
    }
}
