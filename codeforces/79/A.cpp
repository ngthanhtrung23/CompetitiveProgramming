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

bool get(int x, int y, int turn) {
    if (turn == 1) {
        if (x >= 2 && y >= 2) {
            return !get(x-2, y-2, 3-turn);
        }
        else if (x >= 1 && y >= 12) {
            return !get(x-1, y-12, 3-turn);
        }
        else if (y >= 22) {
            return !get(x, y-22, 3-turn);
        }
        else return false;
    }
    else {
        if (y >= 22) {
            return !get(x, y-22, 3-turn);
        }
        else if (x >= 1 && y >= 12) {
            return !get(x-1, y-12, 3-turn);
        }
        else if (x >= 2 && y >= 2) {
            return !get(x-2, y-2, 3-turn);
        }
        else return false;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int x, y;
    cin >> x >> y;
    if (get(x, y, 1)) puts("Ciel");
    else puts("Hanako");
    return 0;
}
