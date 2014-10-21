#include <iomanip>
#include <sstream>
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

char s[1000111];
vector<string> v;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d\n", &n);
    while (n--) {
        gets(s);
        if (s[0] == 'p') {
            putchar('/');
            REP(i,v.size()) printf("%s/", v[i].c_str());
            puts("");
        }
        else {
            if (s[3] == '/') v.clear();
            REP(i,strlen(s)) if (s[i] == '/') s[i] = ' ';
            istringstream sin(s);
            string cur;
            sin >> cur;
            while (sin >> cur) {
                if (cur == "..") {
                    if (!v.empty()) v.pop_back();
                }
                else {
                    v.push_back(cur);
                }
            }
        }
    }
    return 0;
}