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

const int MN = 1000111;

int n, a[MN], now[MN], top;

int main() {
    while (cin >> n) {
        REP(i,n) a[i] = i;

        FOR(x,2,n) {
            // (i - (x-2)) % x == 0
            top = 0;
            for(int i = x-2; i < n + x - 2; i += x) {
                now[++top] = i % n;
            }
            for(int i = top; i >= 2; i--) {
                swap(a[now[i]], a[now[i-1]]);
            }
        }

        REP(i,n) printf("%d ", a[(i+n-1) % n] + 1);
        puts("");
    }
    return 0;
}