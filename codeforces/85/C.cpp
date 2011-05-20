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
const int MN = 100111;
const int oo = 1000111000;

vector<int> ke[MN];
int first[MN], last[MN], key[MN], root, cnt, id[MN];
long double res[MN];
ll sum = 0;

void init(int root, int u, int v) {
    if (!ke[root].size()) {
        cnt++;
        first[cnt] = u;
        last[cnt] = v;
        id[cnt] = root;
        sum += key[root];
    }
    else {
        init(ke[root][0], u, key[root] - 1);
        init(ke[root][1], key[root] + 1, v);
    }
}

int minRight[MN], maxLeft[MN], maxRight[MN], minLeft[MN];

void init3(int root) {
    if (!ke[root].size()) {
        minRight[root] = maxLeft[root] = key[root];
        maxRight[root] = minLeft[root] = key[root];
        return ;
    }
    init3(ke[root][0]);
    init3(ke[root][1]);
    
    minLeft[root] = minLeft[ke[root][0]];
    maxLeft[root] = maxRight[ke[root][0]];
    
    minRight[root] = minLeft[ke[root][1]];
    maxRight[root] = maxRight[ke[root][1]];
}

void init2(int root, ll sum, int cnt) {
//    cout << root << ' ' << sum << ' ' << cnt << endl;
    if (!ke[root].size()) {
        res[root] = sum / (long double) cnt;
        return ;
    }
    init2(ke[root][0], sum + minRight[root], cnt+1);
    init2(ke[root][1], sum + maxLeft[root], cnt+1);
}

void refine(int root) {
    if (!ke[root].size()) return ;
    if (key[ke[root][0]] > key[ke[root][1]]) swap(ke[root][0], ke[root][1]);
    refine(ke[root][0]);
    refine(ke[root][1]);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, u;
    scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d %d", &u, &key[i]);
        if (u == -1) root = i;
        else ke[u].PB(i);
    }
    refine(root);
    init(root, -1, oo);
    init3(root);
    init2(root, 0, 0);
    
//    cout << endl;
//    FOR(i,1,cnt) cout << first[i] << ' ' << last[i] << endl;
//    cout << endl;
//    FOR(i,1,n) cout << maxLeft[i] << ' ' << minRight[i] << endl;
//    cout << endl;
//    
//    FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    
    int q;
    scanf("%d", &q);
    
    int it;
    long double now;
    FOR(qq,1,q) {
        scanf("%d", &u);
        if (u <= last[1]) now = res[id[1]];
        else if (u >= first[cnt]) now = res[id[cnt]];
        else {
            it = lower_bound(last + 1, last + cnt + 1, u) - last;
            now = res[id[it]];
        }
        cout << (fixed) << setprecision(10) << now;
        puts("");
    }
    return 0;
}
