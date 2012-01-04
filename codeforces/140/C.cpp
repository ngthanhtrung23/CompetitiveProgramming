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

int a[100111];
pair<int,int> c[100111];
set< pair<int,int> > Set;

int r1[100111], r2[100111], r3[100111];

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d", &a[i]);
    }
    sort(a+1, a+n+1);
    int s = 0, cnt = 0;
    FOR(i,1,n) {
        cnt++;
        if (a[i] != a[i+1]) {
            s++;
            c[s] = MP(-cnt, a[i]);
            cnt = 0;
        }
    }
    
    FOR(i,1,s) {
        Set.insert(c[i]);
//        cout << c[i].F << ' ' << c[i].S << endl;
    }
    
    cnt = 0;
    while (Set.size() >= 3) {
        pair<int,int> x, y, z;
        x = *Set.begin(); Set.erase(Set.begin());
        y = *Set.begin(); Set.erase(Set.begin());
        z = *Set.begin(); Set.erase(Set.begin());
        
        cnt++;
        r1[cnt] = x.S;
        r2[cnt] = y.S;
        r3[cnt] = z.S;
        x.F++; y.F++; z.F++;
        if (x.F) Set.insert(x);
        if (y.F) Set.insert(y);
        if (z.F) Set.insert(z);
        
    }
    printf("%d\n", cnt);
    FOR(i,1,cnt) {
        int ln = max3(r1[i], r2[i], r3[i]);
        int nn = min3(r1[i], r2[i], r3[i]);
        int mid = r1[i] + r2[i] + r3[i] - ln - nn;
        printf("%d %d %d\n", ln, mid, nn);
    }
    return 0;
}
