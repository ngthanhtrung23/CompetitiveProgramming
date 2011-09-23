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

stringstream os;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ll a, b, mod;
    cin >> a >> b >> mod;
    
    for(long long s1 = 0; s1 < mod && s1 <= a; s1++) {
        long long s2 = (mod*mod - (s1 * (1000000000 % mod))) % mod;
        if (s2 > b) {
            os << s1;
            string s; os >> s;
            while (s.length() < 9) s = '0' + s;
            cout << "1 " << s;
            return 0;
        }
    }
    
    puts("2");
    
    return 0;
}
