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

#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

long long cnt, p[30], lt[10];

int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
    long long q; cin >> q;
    if (q == 1) {
        puts("1");
        puts("0");
        return 0;
    }
    for(long long i = 2; i*i <= q; i++) if (q % i == 0) {
        cnt++;
        p[cnt] = i;
        while (q % i == 0) {
            q /= i;
            lt[cnt]++;
        }
        if (cnt > 2) break;
    }
    if (q > 1) {
        cnt++;
        p[cnt] = q;
        lt[cnt] = 1;
    }
//    FOR(i,1,cnt) cout << p[i] << ' ' << lt[i] << endl;
    
    if (cnt == 1) {
        if (lt[1] == 1) {
            puts("1");
            puts("0");
        }
        else if (lt[1] == 2) {
            puts("2");
        }
        else {
            puts("1");
            cout << p[1] * p[1] << endl;
        }
        return 0;
    }
    if (cnt == 2) {
        if (lt[1] == 1 && lt[2] == 1) {
            puts("2");
        }
        else {
            puts("1");
            cout << p[1] * p[2] << endl;
        }
        return 0;
    }
    puts("1");
    cout << p[1] * p[2] << endl;
    return 0;
}
