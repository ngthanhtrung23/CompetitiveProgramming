#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

long long gcd(long long a, long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

long long ab(long long x) {
    if (x < 0) return -x; else return x;
}

struct Fraction {
    long long x, y;
    Fraction() { x = 0; y = 1; }
    Fraction(long long X, long long Y) {
        if (Y < 0) {
            Y = -Y;
            X = -X;
        }
        long long g = gcd(ab(X), ab(Y));
        x = X / g;
        y = Y / g;
    }
} c[100111];

bool operator == (Fraction a, Fraction b) {
    return a.x * b.y == a.y * b.x;
}

bool operator < (Fraction a, Fraction b) {
    if (a.x < 0 && b.x > 0) return true;
    if (a.x > 0 && b.x < 0) return false;
    return a.x * b.y < a.y * b.x;
}

Fraction operator * (long long x, Fraction a) {
    return Fraction(x*a.x, a.y);
}

Fraction operator + (Fraction a, Fraction b) {
    long long lcm = a.y * b.y / gcd(a.y, b.y);
    a = (lcm / a.y) * a;
    b = (lcm / b.y) * b;
    return Fraction(a.x + b.x, lcm);
}

pair<long long, long long> a[100111];
vector<int> ls[100111];
int n;

int main() {
    while (scanf("%d", &n) == 1) {
        int s = 0;
        FOR(i,1,n) {
            scanf("%I64d%I64d", &a[i].F, &a[i].S);
            if (a[i].F) c[++s] = Fraction(-a[i].S, a[i].F);
        }
        sort(c+1, c+s+1);
        s = unique(c+1, c+s+1) - c - 1;

        FOR(i,1,s) ls[i].clear();
        FOR(i,1,n) if (a[i].F) {
            int u = lower_bound(c+1, c+s+1, Fraction(-a[i].S, a[i].F)) - c;
            ls[u].PB(i);
        }

        long long k = 0, b = 0, cnt = 0;
        FOR(i,1,n) if (a[i].F <= 0) {
            k += a[i].F;
            b += a[i].S;
        }
        // cout << k << ' ' << b << endl;
        FOR(i,1,s) {
            long long kk = k, bb = b;
            REP(x,ls[i].size()) {
                int u = ls[i][x];
                if (a[u].F > 0) {
                    kk += a[u].F;
                    bb += a[u].S;
                }
                else if (a[u].F < 0) {
                    kk -= a[u].F;
                    bb -= a[u].S;
                }
            }
            if (kk != k || bb != b) {
                if (kk*c[i]+Fraction(bb,1) == k*c[i]+Fraction(b,1)) cnt += 1;
                else cnt += 1;
            }
            k = kk; b = bb;
            // cout << "ls = "; REP(x,ls[i].size()) cout << ls[i][x] << ' '; cout << endl;
            // cout << c[i].x << ' ' << c[i].y << "  -->  ";
            // cout << k << ' ' << b << ' ' << cnt << endl;
        }
        cout << cnt << endl;
    }
    return 0;
}
