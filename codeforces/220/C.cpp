#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <cmath>
using namespace std;
#define FOR(i, a, b) for(int i=a; i<=b; i++)
#define DOW(i, a, b) for(int i=a; i>=b; i--)
#define FOREACH(it, c) for(typeof(c.begin()) it=c.begin(); it!=c.end(); it++)
#define RESET(c, val) memset(c, val, sizeof(c))
#define maxn 100005

int n, pos[maxn], a[maxn], b[maxn], x;
multiset<int> s;

int main() {
    //freopen("test.inp", "r", stdin);
    //freopen("", "w", stdout);
    cin >> n;
    FOR(i, 1, n) scanf("%d", &x), pos[x]=i;
    FOR(i, 1, n) scanf("%d", &b[i]), a[i]=i-pos[b[i]], s.insert(a[i]);
    //FOR(i, 1, n) cout << a[i] << endl;
    int t=0;
    FOR(i, 1, n) {
        multiset<int>::iterator it=s.lower_bound(t);
        int res=1000000000;
        //cout << i << " " << s.size() << endl;
        //FOREACH(it, s) cout << (*it) << " ";
        //cout << endl;
        if (it!=s.end()) res=min(res, (*it)-t);
        if (it!=s.begin()) it--, res=min(res, t-(*it));
        //if (it!=s.begin()) it--, res=min(res, t-(*it));
        printf("%d\n", res);
        if (i<n) {
            t++;
            s.erase(s.find(a[i]));
            a[i]=n-pos[b[i]];
            s.insert(a[i]+t);
        }
        //if (i==3) cout << a[n]-t << endl;
    }
    return 0;
}