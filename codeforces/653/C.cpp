#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
using namespace std;

const int MN = 200111;
int n, a[MN];

int check(int pos) {
    if (pos % 2 == 1) {
        return a[pos] < a[pos-1] && a[pos] < a[pos+1];
    }
    else {
        return a[pos] > a[pos-1] && a[pos] > a[pos+1];
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        a[0] = MN;
        if (n % 2 == 0) a[n+1] = 0;
        else a[n+1] = MN;

        vector<int> bad;
        FOR(i,1,n) if (!check(i)) bad.push_back(i);

        if ((int) (bad.size()) > 6) cout << 0 << endl;
        else {
            int res = 0;
            for(int x : bad) {
                FOR(i,1,n) if (i != x && (check(i) || i > x)) {
                    swap(a[i], a[x]);
                    bool good = 1;
                    for(int p : bad) if (!check(p)) good = 0;
                    if (!check(i)) good = 0;
                    if (!check(x)) good = 0;

                    res += good;
                    swap(a[i], a[x]);
                }
            }
            cout << res << endl;
        }
    }
}
