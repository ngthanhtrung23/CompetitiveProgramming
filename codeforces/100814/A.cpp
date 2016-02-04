
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
string s;
double f[10][1000111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    cout << (fixed) << setprecision(9);

    int gt = 1;
    FOR(n,1,9) {
        gt *= n;
        double sum = 0.0;
        FORD(i,gt,1) {
            if (i == gt) f[n][i] = 0.0;
            else {
                f[n][i] = 1.0 / (double) gt * (sum + 1.0);
            }
            sum += f[n][i];
        }
    }


    while (ntest--) {
        cin >> n;
        stringstream ss; ss << n;
        s = ss.str();

        sort(s.begin(), s.end());
        int cnt = 0;
        do {
            int x = 0;
            for(char c : s) x = x * 10 + c - '0';

            if (x <= n) ++cnt;
            else break;
        } while (next_permutation(s.begin(), s.end()));
        cout << f[SZ(s)][cnt] << endl;
    }
}
