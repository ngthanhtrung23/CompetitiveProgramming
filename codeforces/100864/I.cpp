
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

const int MN = 22;
bool visited[1<<22];
int a[(1<<MN) + 111];
int bound, allOne, fail;

void go(int i, int cur) {
    if (i > bound) {
        FOR(t,1,bound) putchar((char) ('0' + a[t]));
        puts("");
        throw 1;
    }

    int t = (cur << 1) & allOne;
    if (!visited[t]) {
        visited[t] = true;
        a[i] = 0;
        go(i+1, t);
        fail++;
        visited[t] = false;
    }
    ++t;
    if (!visited[t]) {
        visited[t] = true;
        a[i] = 1;
        go(i+1, t);
        visited[t] = false;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("infinite.in", "r", stdin);
    freopen("infinite.out", "w", stdout);
    int n;
    while (cin >> n) {
        memset(visited, 0, sizeof visited);
        bound = (1<<n) + n - 1;
        FOR(i,1,n) {
            a[i] = 0;
            visited[0] = 1;
        }
        allOne = (1<<n) - 1;
        fail = 0;
        try {
            go(n+1, 0);
        } catch (int e) {
        }
    }
}
