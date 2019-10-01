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
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

int n[2], a[2][100111], save[2][100111], saven[2];

int win(int n[], int a[][100111]) {
    int turn = 1;
    while (n[0] && n[1]) {
        if (a[turn][n[turn]] > a[1-turn][n[1-turn]]) {
            // can kill opponent --> kill him
            --n[1-turn];
        }
        else if (n[turn] >= 2) {
            a[turn][n[turn]-1] += a[turn][n[turn]];
            --n[turn];
        }
        turn = 1 - turn;
    }
    if (n[0]) return 0;
    else return 1;
}

void copyTo(int n[], int a[][100111], int saven[], int save[][100111]) {
    REP(t,2) {
        saven[t] = n[t];
        FOR(i,1,saven[t])
            save[t][i] = a[t][i];
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int test = 0;
    while (GI(n[0]) == 1 && GI(n[1]) == 1) {
        FOR(i,1,n[0]) GI(a[0][i]);
        FOR(i,1,n[1]) GI(a[1][i]);

        sort(a[0]+1, a[0]+n[0]+1);
        sort(a[1]+1, a[1]+n[1]+1);

        copyTo(n, a, saven, save);

        int w = 1;
        if (a[0][n[0]] > a[1][n[1]]) {
            --n[1];
            if (win(n, a) == 0) {
                w = 0;
            }
        }
        if (w) {
            copyTo(saven, save, n, a);
            if (n[0] >= 2) {
                a[0][n[0]-1] += a[0][n[0]];
                --n[0];
                w = win(n, a);
            }
        }

        cout << "Case " << ++test << ": " << (w ==  0 ? "Takeover Incorporated" : "Buyout Limited") << '\n';
    }
}
