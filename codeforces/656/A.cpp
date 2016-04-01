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

int a[] = {
1,
2,
4,
8,
16,
32,
64,
128,
256,
512,
1024,
2048,
4096,
8092,
16184,
32368,
64736,
129472,
258944,
517888,
1035776,
2071552,
4143104,
8286208,
16572416,
33144832,
66289664,
132579328,
265158656,
530317312,
1060634624,
2121269248,
4242538496,
8485076992,
16970153984,
33940307968
};

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        cout << a[n] << endl;
    }
}
