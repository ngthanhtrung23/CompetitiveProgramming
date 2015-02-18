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

ll gcd(ll x, ll y){
    return x ? gcd(y%x,x) : y;
}

ll lcm(ll x, ll y){
    return x / gcd(x,y) * y;
}

pair <ll, int> t[2000010]; // time, people

int main(void){
    ll a,b;
    cin >> a >> b;
    
    ll d = lcm(a,b);
    
    int sz=0,i;
    for(i=0;a*i<=d;i++){
        if((a*i == 0 || a*i == d) && a < b) continue;
        t[sz] = make_pair(a*i,0); sz++;
    }
    for(i=0;b*i<=d;i++){
        if((b*i == 0 || b*i == d) && b < a) continue;
        t[sz] = make_pair(b*i,1); sz++;
    }
    sort(t,t+sz);
    
    ll dasha = 0, masha = 0;
    REP(i,sz-1){
        ll tmp = t[i+1].first - t[i].first;
        if(t[i].second == 0) dasha += tmp; else masha += tmp;
    }
    
//  cout << dasha << ' ' << masha << endl;
    
    if(dasha > masha) cout << "Dasha" << endl;
    if(dasha < masha) cout << "Masha" << endl;
    if(dasha == masha) cout << "Equal" << endl;
    
    return 0;
}