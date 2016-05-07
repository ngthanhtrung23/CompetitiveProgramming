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

string s;
int n;
char a[22][22], key[22][22], tmp[22][22], visited[22][22];
char res[10111];
int l;
int good;

void go() {
    FOR(i,1,n) FOR(j,1,n) {
        if (key[i][j] == '+') {
            visited[i][j]++;
            res[++l] = a[i][j];
        }
    }
}

void rotate() {
    FOR(i,1,n) FOR(j,1,n) tmp[i][j] = key[i][j];

    FOR(i,1,n) FOR(j,1,n) key[i][j] = tmp[n+1-j][i];
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("sieve.in", "r", stdin);
    freopen("sieve.out", "w", stdout);

    while (cin >> s >> n) {
        memset(a, '*', sizeof a);
        int cur = 0;
        FOR(i,1,n) FOR(j,1,n) {
            if (cur < SZ(s)) a[i][j] = s[cur++];
            else break;
        }

        FOR(i,1,n) FOR(j,1,n) {
            cin >> key[i][j];
        }

        l = 0;
        memset(visited, 0, sizeof visited);
        good = 1;

        REP(turn,4) {
            go();
            rotate();
        }

        FOR(i,1,n) FOR(j,1,n) if (visited[i][j] != 1) good = 0;

        if (!good) cout << "No solution." << endl;
        else {
            FOR(i,1,l) cout << res[i];
            cout << endl;
        }
    }
}
