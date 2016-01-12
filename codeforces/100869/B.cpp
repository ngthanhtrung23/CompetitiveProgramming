
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

int n;
string s[3];

bool done() {
    FOR(i,1,2) FOR(j,1,n) if (s[i][j] == '.') return false;
    return true;
}

bool fill(int i, int j) {
//    DEBUG(s[1]);
//    DEBUG(s[2]);
//    cout << i << ' ' << j << endl;
    if (s[3-i][j] == '.') s[3-i][j] = 'X';
    s[i][j] = 'X';

    int t = j-1;
    while (s[i][t] == '.') {
        s[i][t] = 'X';
        --t;
    }

    t = j + 1;
    while (s[i][t] == '.') {
        s[i][t] = 'X';
        ++t;
    }
//    DEBUG(s[1]);
//    DEBUG(s[2]);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        FOR(t,1,2) {
            cin >> s[t];
            s[t] = "X" + s[t] + "X";
        }
        int res = 0;
        while (!done()) {
            bool good = false;
            FOR(i,1,2) FOR(j,1,n)
                if (s[i][j] == '.' && s[i][j-1] == 'X' && s[i][j+1] == 'X'
                        && s[3-i][j] == '.') {
                    fill(3-i, j);
                    ++res;
                    good = true;
                    break;
                }
            if (good) continue;

            FOR(i,1,2) FOR(j,1,n) {
                if (s[i][j] == '.' && s[3-i][j] == '.') {
                    fill(i, j);
                    fill(3-i, j);
                    res += 2;
                    good = true;
                    break;
                }
            }
            if (good) continue;
            FOR(i,1,2) FOR(j,1,n)
                if (s[i][j] == '.') {
                    fill(i, j);
                    ++res;
                    break;
                }
        }
        cout << "Case #" << test << ": " << res << endl;
    }
}