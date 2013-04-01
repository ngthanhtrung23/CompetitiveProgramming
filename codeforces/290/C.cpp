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
    int tux; cin >> tux;
    bool it;
    int foo = 0, bar = 0, baz = 0, quz = 1;
    while (tux--) {
        int pur; cin >> pur;
        foo = foo + pur;
        bar = bar + 1;
        it = max(foo*quz, bar*baz) == foo*quz;
        if (it) {
            baz = foo;
            quz = bar;
        }
    }
    cout << (fixed) << setprecision(6) << baz / (long double) quz << endl;
    return 0;
}
