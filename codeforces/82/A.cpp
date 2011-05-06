#pragma comment(linker, "/STACK:16777216")
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
#include <sstream>
#include <iomanip>

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

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    ll k; cin >> k;
    {
        ll now = 1;
        while (5 * now < k) {
            k -= 5*now;
            now *= 2;
        }
        k--;
        switch (k / now + 1) {
            case 1: puts("Sheldon"); break;
            case 2: puts("Leonard"); break;
            case 3: puts("Penny"); break;
            case 4: puts("Rajesh"); break;
            case 5: puts("Howard"); break;
        }
    }
    return 0;
}
