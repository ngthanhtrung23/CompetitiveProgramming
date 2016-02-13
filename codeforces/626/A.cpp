
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    string s;
    int n;
    while (cin >> n) {
        cin >> s;
        int res = 0;
        REP(i,n) FOR(j,i,n-1) {
            string cur = s.substr(i, j - i + 1);

            int x = 0, y = 0;
            for(char c : cur) {
                if (c == 'R') ++x;
                else if (c == 'L') --x;
                else if (c == 'U') ++y;
                else if (c == 'D') --y;
            }
            if (x == 0 && y == 0) ++res;
        }
        cout << res << endl;
    }
}
