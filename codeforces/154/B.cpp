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
using namespace std;

const double PI = acos(-1.0);
const int MAXV = 100000;

int sieve[100111], next[100111];

void init() {
    for(int i = 2; i <= 1000; i++) if (!sieve[i]) {
        int j = i*i;
        while (j <= MAXV) {
            sieve[j] = i;
            next[j] = j;
            while (next[j] % i == 0) next[j] /= i;
            j += i;
        }
    }
}

int on[100111], mark[100111];

int conflict(int v) {
    int p;
    while (sieve[v]) {
        p = sieve[v];
        if (mark[p]) return mark[p];
        v = next[v];
    }
    if (v > 1) {
        if (mark[v]) return mark[v];
    }
    return -1;
}

void update(int v, int t) {
    int p;
    while (sieve[v]) {
        p = sieve[v];
        mark[p] = t;
        v = next[v];
    }
    if (v > 1) {
        mark[v] = t;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    init();
    int n, m; scanf("%d%d\n", &n, &m);
    char c;
    int v, x;
    while (m--) {
        scanf("%c%d\n", &c, &v);
        if (c == '+') {
            if (on[v]) puts("Already on");
            else {
                x = conflict(v);
                if (x >= 0) printf("Conflict with %d\n", x);
                else {
                    on[v] = true;
                    update(v, v);
                    puts("Success");
                }
            }
        }
        else {
            if (!on[v]) {
                puts("Already off");
            }
            else {
                puts("Success");
                update(v, 0);
                on[v] = false;
            }
        }
    }
    return 0;
}
