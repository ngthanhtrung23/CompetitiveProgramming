#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 311;
int n;
vector<int> a[MN], b[MN];

int f(const vector<int>& a) {
    int sum = 0;
    REP(j,SZ(a)) FOR(k,j+1,SZ(a) - 1)
        if (a[j] < a[k]) ++sum;
    return sum;
}

bool check(const vector<int>& p) {
    FOR(i,1,n) {
        int val = p[i - 1];
        // remove p[i]

        vector<int> cur;
        for(int x : p) {
            if (x == val) continue;
            if (x > val) cur.push_back(x - 1);
            else cur.push_back(x);
        }

        b[i] = cur;
    }
    sort(b+1, b+n+1);
    FOR(i,1,n) if (a[i] != b[i]) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    while (cin >> n) {
        int sum = 0;
        // read a[i] & calculate f --> N^3
        FOR(i,1,n) {
            a[i].resize(n-1);
            REP(j,n-1) cin >> a[i][j];

            sum += f(a[i]);
        }
        
        sort(a+1, a+n+1);

        sum /= n - 2;

        // for each vector
        FOR(i,1,n) {
            int need = sum - f(a[i]);
            int pos = n - 1 - need;

            vector<int> cur;
            for(int x : a[i]) cur.push_back(x + 1);
            cur.insert(cur.begin() + pos, 1);

            if (f(cur) != sum) continue;

            if (check(cur)) {
                for(int x : cur) cout << x << ' ';
                goto done;
            }
        }
done:
        cout << endl;
    }
}
