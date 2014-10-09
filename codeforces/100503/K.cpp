#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

char tmp[1011];
string a[1011];
int lcp[1011], n;

void go(int l, int r, int inList) {
    int i = l;
    while (i <= r) {
        if (lcp[i] > inList) {
            int j = i+1;
            while (lcp[j] >= inList + 1) ++j;

            if (inList) puts("<li>");

            if (a[i][inList] == '*') puts("<ul>");
            else puts("<ol>");

            go(i, j, inList + 1);

            if (a[i][inList] == '*') puts("</ul>");
            else puts("</ol>");

            if (inList) puts("</li>");

            i = j + 1;
        } else {
            if (inList) puts("<li>");
            FOR(x,inList,a[i].length()-1) putchar(a[i][x]);
            puts("");
            if (inList) puts("</li>");

            ++i;
        }
    }
}

bool good(char c) {
    return c == '*' || c == '#';
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (gets(tmp)) {
        a[++n] = string(tmp);
    }

    FOR(i,1,n) {
        if (i == n) lcp[i] = 0;
        else {
            lcp[i] = 0;
            while (good(a[i][lcp[i]]) && a[i][lcp[i]] == a[i+1][lcp[i]]) ++lcp[i];
        }
    }

    go(1, n, 0);
    return 0;
}
