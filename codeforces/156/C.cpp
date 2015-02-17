#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

typedef long long ll;
#define MOD 1000000007ll

ll dp[110][2510];
char buf[110];
string s;

int main(void){
    int i,j,k;
    
    dp[0][0] = 1;
    REP(i,100) REP(j,2510) if(dp[i][j] > 0) REP(k,26) dp[i+1][j+k] = (dp[i+1][j+k] + dp[i][j]) % MOD;
    
    int T,t;
    scanf("%d",&T);
    
    REP(t,T){
        scanf("%s",buf);
        s = buf;
        
        int len = s.length();
        int sum = 0;
        REP(i,len) sum += (s[i] - 'a');
        
        cout << (dp[len][sum] + MOD - 1) % MOD << endl;
    }
    
    return 0;
}