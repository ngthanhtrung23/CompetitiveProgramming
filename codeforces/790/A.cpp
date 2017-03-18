
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

string names[1011], a[55];
bool good[55];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int t = 0;
    FOR(c1,'A','Z') FOR(c2,'a','z') {
        string s = "";
        s += c1;
        s += c2;
        names[++t] = s;
    }
    int n, k;
    while (cin >> n >> k) {
        bool allBad = true;
        FOR(i,1,n-k+1) {
            string s; cin >> s;
            good[i] = (s == "YES");

            if (good[i]) allBad = false;
        }
        FOR(i,1,n) a[i] = "";

        if (allBad) {
            FOR(i,1,n) a[i] = names[1];
        } else {
            int first = 1;
            while (!good[first]) ++first;

            FOR(x,1,first-1) a[x] = names[1];
            int t = 0;
            FOR(x,first,first+k-1) a[x] = names[++t];

            FOR(x,first+k,n) {
                if (good[x-k+1]) a[x] = names[++t];
                else a[x] = a[x-k+1];
            }
        }

        FOR(i,1,n) cout << a[i] << ' '; cout << endl;
    }
    return 0;
}
