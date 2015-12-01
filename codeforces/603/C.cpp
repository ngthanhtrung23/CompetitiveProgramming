
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int get0(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    if (x == 2) return 2;
    if (x % 2 == 1) return 0;
    return 1;
}

int get1(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    if (x == 3) return 1;
    if (x % 2) return 0;

    int res = 0;
    set<int> s;
    s.insert(get1(x-1));
    s.insert(get1(x/2));
    while (s.count(res))++res;

    return res;
}

int n, k;

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        k %= 2;
        int sum = 0;
        FOR(i,1,n) {
            int a; scanf("%d", &a);
            if (k == 0) sum ^= get0(a);
            else sum ^= get1(a);
        }
        if (sum) puts("Kevin");
        else puts("Nicky");
    }
}
