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

int n, pref[311][311], ord[311];
int one[311], two[311];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    FOR(i,1,n) FOR(j,1,n) scanf("%d", &pref[i][j]);
    FOR(i,1,n) {
        int u; scanf("%d", &u);
        ord[u] = i;
    }
    ord[0] = n + 100;
    
    one[1] = 1; two[1] = 0;
    FOR(i,2,n) {
        if (ord[i] < ord[one[i-1]]) {
            two[i] = one[i-1];
            one[i] = i;
        }
        else if (ord[i] < ord[two[i-1]]) {
            one[i] = one[i-1];
            two[i] = i;
        }
        else {
            one[i] = one[i-1];
            two[i] = two[i-1];
        }
    }
//    FOR(i,1,n) cout << one[i] << ' ' << two[i] << endl;
    FOR(i,1,n) {
        FOR(j,1,n) {
            int need = pref[i][j];
            if (need == i) continue;
            bool ok = false;
            FOR(k,1,n) {
                if (one[k] == need || (one[k] == i && two[k] == need)) {
//                    cout << need << ' ' << k << endl;
                    printf("%d ", k);
                    ok = true;
                    break;
                }
            }
            if (ok) break;
        }
    }
    return 0;
}
