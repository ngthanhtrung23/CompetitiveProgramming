#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <vector>
#include <queue>

using namespace std;

#define PI acos(-1)
#define MP make_pair
#define PB push_back
#define VI vector <int>
#define PII pair <int, int>
#define LL long long
#define SET(v,i) memset(v, i, sizeof(v))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORD(i,a,b) for (int i = (a); i >= (b); i--)
#define FORN(i,a,b) for (int i = (a); i < (b); i++)
#define DOWN(i,a,b) for (int i = (a); i > (b); i--)
#define FIT(it,v) for (typeof(v.begin()) it = v.begin(); it != v.end(); it++)
#define FITD(it,v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)
#define maxn 100111

int n, a[maxn], res;

stack <int> S;

void solve() {
    while (!S.empty()) S.pop();

    S.push(a[1]);

    FOR (i, 2, n) {
        while (!S.empty() && S.top() < a[i]) {
            res = max(res, a[i] ^ S.top());
            S.pop();
        }
        S.push(a[i]);
    }
}

int main() {
    scanf("%d", &n);
    FOR (i, 1, n)
        scanf("%d", &a[i]);

    res = 0;
    solve();

    FOR (i, 1, n / 2)
        swap(a[i], a[n + 1 - i]);

    solve();

    cout << res << endl;
    return 0;
}