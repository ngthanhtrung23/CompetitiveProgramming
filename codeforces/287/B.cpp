#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <fstream>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i >= _b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;

int main() {
    long long n, k;
    while (cin >> n >> k) {
        if (n == 1) {
            puts("0");
            continue;
        }
        --k;
        long long l = 1, r = k + 1, res = k + 1;

        while (l <= r) {
            long long mid = (l + r) / 2;
            if (1 + (2*k-mid+1) * mid / 2 >= n) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        if (res > k) puts("-1");
        else cout << res << endl;
    }
    return 0;
}
