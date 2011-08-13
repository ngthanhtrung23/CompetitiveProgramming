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

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))

int n, k, A, B[10], a[10], aa[10];
long double best = 0.0;

void attempt(int i, int k) {
    if (i > n) {
        if (k) return ;
        int cnt = 0;
        FOR(j,1,n) if (aa[j] == 100) cnt++;
        int need = n / 2 + 1;
        if (cnt >= need) {
            best = max(best, (long double) 1.0);
            return ;
        }
        
        long double sum = 0.0;
        REP(mask,TWO(n)) {
            long double f = 1.0;
            int cnt = 0, sumB = 0;
            FOR(j,1,n)
            if (CONTAIN(mask, j-1)) {
                f *= aa[j] / 100.0;
                cnt++;
            }
            else {
                sumB += B[j];
                f *= (100 - aa[j]) / 100.0;
            }
            
            if (cnt >= need) sum += f;
            else sum += f * A * 1.0 / (sumB + A);
        }
        best = max(best, sum);
        return ;
    }
    
    FOR(now,0,k) {
        aa[i] = a[i] + now * 10;
        if (aa[i] > 100) aa[i] = 100;
        attempt(i+1, k - now);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> n >> k >> A;
    FOR(i,1,n) cin >> B[i] >> a[i];
    attempt(1, k);
    cout << setprecision(10) << best;
    return 0;
}
