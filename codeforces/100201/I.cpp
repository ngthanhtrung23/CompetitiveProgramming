
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

void sort(int turn, vector<int> &a) {
    if (turn < 0) return;
    vector<int> left, right;

    int bound = 1<<turn;
    REP(i,a.size()) {
        int u = a[i];

        if (u & bound) {
            right.push_back(u);
            printf("%d ", u+1);
        }
        else {
            left.push_back(u);
            printf("%d %d ", u+1, u+1);
        }
    }
    sort(turn-1, left);
    
    FORD(i,right.size()-1,0) printf("%d ", right[i]+1);
    reverse(right.begin(), right.end());
    sort(turn-1, right);
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("railsort.in", "r", stdin);
    freopen("railsort.out", "w", stdout);
    int n;
    while (cin >> n) {
        vector<int> a;
        FOR(i,1,1<<n) {
            int x; cin >> x;
            --x;
            a.push_back(x);
        }

        sort(n-1, a);
        puts("");
    }
}

