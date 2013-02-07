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
#include <sstream>
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
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        int n; scanf("%d", &n);
        if (360 % (180 - n) == 0) puts("YES");
        else puts("NO");
    }
    return 0;
}
