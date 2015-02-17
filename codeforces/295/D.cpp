#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

typedef long long ll;
#define MOD 1000000007ll

int C[6010][6010];
ll up[2010],down[2010];

int main(void){
    int X,Y,d,i,j;
    
    int M = 1000000007;
    
    REP(i,6010) REP(j,i+1){
        if(j == 0 || j == i){
            C[i][j] = 1;
        } else {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
            if(C[i][j] >= M) C[i][j] -= M;
        }
    }
    
    cin >> X >> Y;
    ll ans = 0;
    
    for(d=1;d<=Y-1;d++){
        up[1] = down[1] = 1;
        for(i=2;i<=X;i++){
            ll c = C[d+2*i-3][2*i-2];
            down[i] = (down[i-1] + c) % MOD;
            up[i] = (down[i] - down[i-1] + MOD) % MOD;
        }
        
        ll tmp = 0;
        REP(i,X) tmp = (tmp + up[i+1] * down[X-i]) % MOD;
        ans = (ans + tmp * (Y - d)) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}