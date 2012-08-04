#include <sstream>
#include <iomanip>
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

multiset<int> s, other;
int n, len, a[100111], k;
long long res;
long long negsum, sum;

void remove(int x) {
    if (s.find(x) != s.end()) {
        negsum -= x;
        s.erase(s.find(x));
    }
    else if (other.find(x) != other.end()) {
        other.erase(other.find(x));
    }

    if (s.size() < k && other.size()) {
        multiset<int> :: iterator it = other.begin();
        negsum += *it;
        s.insert(*it);
        other.erase(it);
    }
}

void add(int x) {
    s.insert(x);
    negsum += x;
    if (s.size() > k) {
        multiset<int> :: iterator it = s.end();
        it--;
        negsum -= *it;
        other.insert(*it);

        s.erase(it);
    }
}

void update() {
    if (res < sum - negsum - negsum) {
        res = sum - negsum - negsum;
    }
}

void solve() {
    negsum = 0;
    sum = 0;
    FOR(i,1,len) {
        sum += a[i];
        if (a[i] < 0) {
            add(a[i]);
        }
    }
    update();

    FOR(i,len+1,n) {
        sum += a[i];
        sum -= a[i-len];

        if (a[i-len] < 0) remove(a[i-len]);
        if (a[i] < 0) add(a[i]);
        update();
    }
}

int main() {
    while (scanf("%d%d", &n, &len) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        scanf("%d", &k);

        res = -1000111000111000111LL;
        s.clear();
        solve();

        FOR(i,1,n) a[i] = -a[i];
        s.clear(); other.clear();
        solve();
        cout << res << endl;
    }
    return 0;
}
