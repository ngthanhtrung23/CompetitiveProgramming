#include <sstream>
#include <iomanip>
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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

int n, m;
pair<char,int> x[MN];
int Plus[MN], Minus[MN], nMinus, nCan;
bool can[MN];

int main() {
    while (scanf("%d%d\n", &n, &m) == 2) {
        nMinus = 0; nCan = 0;
        memset(Plus, 0, sizeof Plus);
        memset(Minus, 0, sizeof Minus);
        memset(can, false, sizeof can);

        FOR(i,1,n) {
            scanf("%c%d\n", &x[i].F, &x[i].S);
            if (x[i].F == '+') Plus[x[i].S]++;
            else {
                Minus[x[i].S]++;
                ++nMinus;
            }
        }

        FOR(i,1,n) {
            if (Plus[i] + nMinus - Minus[i] == m) {
                can[i] = true;
                nCan++;
            }
        }

        FOR(i,1,n) {
            if (x[i].F == '+') {
                if (!can[x[i].S]) puts("Lie");
                else if (nCan == 1) puts("Truth");
                else puts("Not defined");
            }
            else {
                if (!can[x[i].S]) puts("Truth");
                else if (nCan == 1) puts("Lie");
                else puts("Not defined");
            }
        }
    }
    return 0;
}
