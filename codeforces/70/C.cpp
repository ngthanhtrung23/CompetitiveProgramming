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

int rev(int x) {
    int res = 0;
    while (x) {
        res = res * 10 + x % 10;
        x /= 10;
    }
    return res;
}

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

map< pair<int,int> , int > mx, my;

int X, Y, W;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> X >> Y >> W;
    ll best = 1000111000111000LL;
    int savex = -1, savey;
    
    FOR(y,1,Y) {
        int g = gcd(y, rev(y));
        my[ MP(rev(y)/g, y / g) ]++;
    }
    
    ll now = 0;
    ll y = Y;
    FOR(x,1,X) {
        int g = gcd(x, rev(x));
        mx[ MP(x/g, rev(x)/g) ]++;
        
        now += my[ MP(x/g, rev(x)/g) ];
//        cout << x << ' ' << y << ' ' << now << endl;
        
        while (y > 0 && now >= W) {
            if (x * y <= best) {
                best = x * y;
                savex = x;
                savey = y;
            }
            int g = gcd(y, rev(y));
            now -= mx[ MP(rev(y)/g, y/g) ];
            my[ MP(rev(y)/g, y/g) ]--;
            y--;
//            cout << x << ' ' << y << ' ' << now << endl;
        }
    }
    
    if (savex == -1) {
        puts("-1");
        return 0;
    }
    cout << savex << ' ' << savey;
    return 0;
}
