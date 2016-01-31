
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
int n, st[MN], top;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        top = 0;
        FOR(i,1,n) {
            st[++top] = 1;
            while (top >= 2 && st[top] == st[top-1]) {
                --top;
                ++st[top];
            }
        }
        FOR(i,1,top) printf("%d ", st[i]); puts("");
    }
}
