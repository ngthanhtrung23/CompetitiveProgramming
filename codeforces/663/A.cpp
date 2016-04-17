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

int GI(int& x) {
    return scanf("%lld", &x);
}

int can(int add, int sub, int n, int need) {
    int nn = add - sub * n;
    int ln = add * n - sub;
    return nn <= need && need <= ln;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    string s;
    while (getline(cin, s)) {
        s = " + " + s;
        int sub = 0, add = 0;
        vector<int> sign;

        istringstream ss(s);
        char typ;
        int n;
        char tmp;
        while (ss >> typ) {
            if (typ == '+') {
                sign.push_back(1);
                ++add;
                ss >> tmp;
            }
            else if (typ == '-') {
                sign.push_back(-1);
                ++sub;
                ss >> tmp;
            }
            else {
                assert(typ == '=');
                ss >> n;
                break;
            }
        }

        if (!can(add, sub, n, n)) cout << "Impossible" << endl;
        else {
            cout << "Possible" << endl;
            int need = n;
            REP(i,SZ(sign)) {
                int t = sign[i];
                int add2 = add - (t == +1);
                int sub2 = sub - (t == -1);

                FOR(cur,1,n) {
                    if (can(add2, sub2, n, need - t * cur)) {
                        need -= t * cur;
                        add = add2;
                        sub = sub2;

                        if (i || t < 0) {
                            if (t == 1) cout << "+ ";
                            else cout << "- ";
                        }
                        cout << cur << ' ';

                        break;
                    }
                }
            }
            cout << "= " << n << endl;
        }
        break;
    }
}
