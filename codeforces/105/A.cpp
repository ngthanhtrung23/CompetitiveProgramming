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

map<string,int> m;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int a, b, k;
    double tmp;
    cin >> a >> b >> tmp;
    k = (int) round(tmp * 100);
    FOR(i,1,a) {
        string s; int x;
        cin >> s >> x;
        m[s] = x;
    }
    for(map<string,int> :: iterator it = m.begin(); it != m.end(); it++) {
        string s = it->first;
        int x = it->second;
        it->second = x * k / 100;
        if (it->second < 100) it->second = -1;
    }
    
    FOR(i,1,b) {
        string s;
        cin >> s;
        if (m.find(s) == m.end() || m[s] == -1) {
            m[s] = 0;
        }
    }
    int cnt = 0;
    for(map<string,int> :: iterator it = m.begin(); it != m.end(); it++)
        if (it->second >= 0) cnt++;
        
    cout << cnt << endl;
    
    for(map<string,int> :: iterator it = m.begin(); it != m.end(); it++)
        if (it->second > -1) {
            cout << it->first << ' ' << it->second << endl;
        }
    
    return 0;
}
