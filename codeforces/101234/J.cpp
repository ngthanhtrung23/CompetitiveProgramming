
#include <sstream>
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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%d", &x); }

const int MN = 1000111;

char tmp[MN];
int a[MN];
int zeros;

int get(int i) {
    return i - 2*a[i];
}

int first, last, st[MN];


int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    gets(tmp);
    int n = strlen(tmp);
    zeros = 0;

    FOR(i,1,n) {
        a[i] = a[i-1] + (tmp[i-1] - '0');

        if (tmp[i-1] == '0') ++zeros;
    }
    
    int q; scanf("%d\n", &q);
    FOR(qq,1,q) {
        int can; scanf("%d\n", &can);

        int res = 0;

        first = 1; last = 0;
        FOR(i,1,n) {
            // add i-1
            while (first <= last
                    && get(st[last]) >= get(i-1)) --last;
            st[++last] = i-1;
            
            // remove first that are too far away
            while (first <= last && a[i] - a[st[first]] > can) ++first;

            int j = st[first];

            res = max(res, can + get(i) - get(j));
        }

        res = min(res, zeros);
        printf("%d\n", res);
    }
}
