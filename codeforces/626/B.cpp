
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

const int MN = 211;
bool visited[MN][MN][MN];
queue<int> qb, qg, qr;

void go(int b, int g, int r) {
    if (!visited[b][g][r]) {
        visited[b][g][r] = true;
        qb.push(b);
        qg.push(g);
        qr.push(r);
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n; 
    string s;
    while (cin >> n >> s) {
        int b = 0, g = 0, r = 0;
        for(char c : s) {
            if (c == 'B') ++b;
            if (c == 'G') ++g;
            if (c == 'R') ++r;
        }
        memset(visited, 0, sizeof visited);
        qb.push(b);
        qg.push(g);
        qr.push(r);
        visited[b][g][r] = 1;

        while (!qb.empty()) {
            int b = qb.front(); qb.pop();
            int g = qg.front(); qg.pop();
            int r = qr.front(); qr.pop();

            if (b >= 2) go(b - 1, g, r);
            if (g >= 2) go(b, g - 1, r);
            if (r >= 2) go(b, g, r - 1);

            if (b && g) go(b - 1, g - 1, r + 1);
            if (g && r) go(b + 1, g - 1, r - 1);
            if (r && b) go(b - 1, g + 1, r - 1);
        }

        if (visited[1][0][0]) cout << 'B';
        if (visited[0][1][0]) cout << 'G';
        if (visited[0][0][1]) cout << 'R';
        cout << endl;
    }
}
