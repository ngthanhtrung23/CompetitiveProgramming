#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
#define TWO(x) (1<<(x))

void refine(int &l1, int &r1, int &l2, int &r2, const int root) {
    while (l1 > root) {
        l1 -= root;
        r1 -= root;
    }
    while (l2 > root) {
        l2 -= root;
        r2 -= root;
    }
    if (l2 <= root && root <= r2) {
        swap(l1, l2);
        swap(r1, r2);
    }
}

int get(int l1, int r1, int l2, int r2, int root) {
    if (l1 > r1) return 0;
    if (l2 > r2) return 0;
    if (root == 1) return 1;
    if (l1 <= l2 && r2 <= r1) return r2 - l2 + 1;
    if (l2 <= l1 && r1 <= r2) return r1 - l1 + 1;
    refine(l1, r1, l2, r2, root);
    int best = max(r2 - l2 + 1, r1 - l1 + 1);
    int res = 0;
    if (l1 <= root && root <= r1) {
        if (l2 <= root && root <= r2) {
            res = max(res, min(r1, r2) - max(l1, l2) + 1);
            if (res == best) return res;
            int u, v, x, y;
            if (r1 - root > root - l1) u = root + 1, v = r1;
            else u = l1, v = root - 1;
            
            if (r2 - root > root - l2) x = root + 1, y = r2;
            else x = l2, y = root - 1;
            
            res = max(res, get(u, v, x, y, root / 2));
        }
        else {
            res = max(res, min(r1, r2) - max(l1, l2) + 1);
            if (res == best) return res;
            res = max(res, get(root+1, r1, l2, r2, root / 2));
            res = max(res, get(l1, root-1, l2, r2, root / 2));
        }
    }
    else {
        res = get(l1, r1, l2, r2, root >> 1);
    }
//    cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << ' ' << root << ' ' << res << endl;
    return max(res, 0);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    cout << get(l1, r1, l2, r2, TWO(29)) << endl;
    return 0;
}
