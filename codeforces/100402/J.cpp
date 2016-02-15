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

const int MN = 100111;
const char QUOTE = '\'';

string s;
bool visited[MN][5];
int tru[MN][5], trx[MN][5];
int trc[MN][5];

void trace(int n, int x) {
    if (n == 0) return ;
    trace(tru[n][x], trx[n][x]);
    if (trc[n][x] == 0) cout << s[n];
    else if (trc[n][x] == 1) {
        if (x == 1 || x == 4) cout << ("<i>");
        else cout << ("</i>");
    }
    else {
        if (x == 2 || x == 3) cout << ("<b>");
        else cout << ("</b>");
    }
}

int main() {
    ios :: sync_with_stdio(0);
    freopen("wikipidia.in", "r", stdin);
    freopen("wikipidia.out", "w", stdout);
    while (getline(cin, s)) {
        int n = SZ(s);
        s = " " + s + "       ";

        memset(visited, 0, sizeof visited);
        queue<int> qu, qx;
        qu.push(0);
        qx.push(0);
        visited[0][0] = true;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            int x = qx.front(); qx.pop();
            if (u == n) continue;

            if (s[u+1] != QUOTE) {
                if (!visited[u+1][x]) {
                    visited[u+1][x] = true;
                    qu.push(u+1);
                    qx.push(x);

                    tru[u+1][x] = u;
                    trx[u+1][x] = x;
                    trc[u+1][x] = 0;
                }
            }
            else {
                if (s[u+2] == QUOTE) {
                    int x2 = -1;
                    if (x == 0) x2 = 1;
                    if (x == 1) x2 = 0;
                    if (x == 2) x2 = 4;
                    if (x == 4) x2 = 2;

                    if (x2 >= 0) {
                        if (!visited[u+2][x2]) {
                            visited[u+2][x2] = true;
                            qu.push(u+2);
                            qx.push(x2);

                            tru[u+2][x2] = u;
                            trx[u+2][x2] = x;
                            trc[u+2][x2] = 1;
                        }
                    }
                }
                if (s[u+2] == QUOTE && s[u+3] == QUOTE) {
                    int x2 = -1;
                    if (x == 0) x2 = 2;
                    if (x == 2) x2 = 0;
                    if (x == 1) x2 = 3;
                    if (x == 3) x2 = 1;

                    if (x2 >= 0) {
                        if (!visited[u+3][x2]) {
                            visited[u+3][x2] = true;
                            qu.push(u+3);
                            qx.push(x2);

                            tru[u+3][x2] = u;
                            trx[u+3][x2] = x;
                            trc[u+3][x2] = 2;
                        }
                    }
                }
            }
        }
        if (!visited[n][0]) cout << ("!@#$%");
        else {
            trace(n, 0);
        }
        cout << endl;
    }
    return 0;
}
