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

string s, tmp;

bool digit(char c) {
    return c >= '0' && c <= '9';
}

char next[300], TMP[300];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(TMP);
    s = string(TMP);
    int n = s.length();
    
    FORD(i,n-2,0) {
        if (s[i+1] == ' ') next[i] = next[i+1];
        else next[i] = s[i+1];
    }
    
    char last = ' ';
    REP(i,n) {
        if (s[i] == ' ') {
            if (digit(last) && digit(next[i])) tmp += 'X';
        }
        else tmp += s[i];
        last = s[i];
    }
    s = tmp;
    n = s.length();
    
    tmp = "";
    
    REP(i,n) {
        if (s[i] == ',') {
            tmp += ",X";
        }
        else tmp += s[i];
    }
    s = tmp;
    tmp = "";
    int i = 0;
    n = s.length();
    while (i < n) {
        if (s[i] == '.') {
            i += 2;
            tmp += "X...";
        }
        else tmp += s[i];
        i++;
    }
    
    s = tmp; n = s.length();
    tmp = "";
    
    bool first = true;
    REP(i,n) {
        if (s[i] == 'X') {
            if (!first) {
                if (s[i-1] != 'X') tmp += 'X';
            }
        }
        else {
            first = false;
            tmp += s[i];
        }
    }
    
    s = tmp;
    int l = s.length()-1;
    while (s[l] == 'X') l--;
    s = s.substr(0,l+1);
    
    REP(i,s.length()) {
        if (s[i] == 'X') cout << ' ';
        else cout << s[i];
    }
    return 0;
}
