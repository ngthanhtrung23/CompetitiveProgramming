#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <fstream>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i >= _b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;

bool isUpper(char c) {
    return (c >= 'A' && c <= 'Z');
}

int main() {
    string s;
    cin >> s;
    int k; cin >> k;
    REP(i,s.length())
        if (isUpper(s[i])) s[i] ^= ' ';

    string res = "";
    REP(i,s.length()) {
        char c = s[i];
        if (c - 'a' < k) {
            res = res + (char)(c ^ ' ');
        }
        else res = res + c;
    }
    cout << res << endl;
    return 0;
}
