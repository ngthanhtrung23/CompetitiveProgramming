
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
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
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
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 200111;
struct Seg {
    int start;
    int can;
    int len;
} x[MN];

int n, a, b, k, nx;
string s;
char tmp[200111];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        GI(a); GI(b); GI(k);
        swap(a, b);
        scanf("%s", &tmp[0]);
        s = " " + string(tmp) + " ";
//        DEBUG(s);

        int i = 1;
        nx = 0;
        while (i <= n) {
            if (s[i] == '1') {
                ++i;
            }
            else {
                int j = i;
                while (s[j+1] == '0') {
                    ++j;
                }
                ++nx;
                x[nx].start = i;
                x[nx].len = j - i + 1;
                x[nx].can = x[nx].len / a;
                i = j + 1;
            }
        }
        vector<int> all;
        int sum = 0;
        FOR(i,1,nx) {
            sum += x[i].can;
            for(int t = a; t <= x[i].len; t += a) {
                all.push_back(x[i].start + t - 1);
            }
        }
        printf("%lld\n", sum - b + 1);
        REP(turn,sum - b + 1) {
            printf("%lld ", all[turn]);
        }
        puts("");
    }
}
