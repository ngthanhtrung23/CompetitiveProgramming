
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int INF = 1000111000;
map< pair<int,int>, pair<int, ll> > all;

int n, a[33], b[33], c[33];
ll p3[33];

ll best, save;

void attempt(int turn, int i, int bound, int b_a, int c_a, int sum, ll mask) {
    if (i > bound) {
        if (turn == 0) {
            if (all.count(make_pair(b_a, c_a))) {
                all[make_pair(b_a, c_a)] = max(
                        all[make_pair(b_a, c_a)],
                        make_pair(sum, mask));
            }
            else {
                all[make_pair(b_a, c_a)] = make_pair(sum, mask);
            }
        }
        else {
            if (all.count(make_pair(-b_a, -c_a))) {
                mask += all[make_pair(-b_a, -c_a)].second;
                sum += all[make_pair(-b_a, -c_a)].first;
            
                if (sum > best) {
                    best = sum;
                    save = mask;
                }
            }
        }
        return ;
    }
    // 0 --> a b
    attempt(turn, i+1, bound, b_a + b[i] - a[i], c_a - a[i], sum + a[i], mask);
    // 1 --> a c
    attempt(turn, i+1, bound, b_a - a[i], c_a + c[i] - a[i], sum + a[i], mask + p3[i-1]);
    // 2 --> b c
    attempt(turn, i+1, bound, b_a + b[i], c_a + c[i], sum, mask + 2*p3[i-1]);
}

int main() {
    ios :: sync_with_stdio(false);
    p3[0] = 1; FOR(i,1,30) p3[i] = p3[i-1] * 3LL;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i] >> b[i] >> c[i];
        all.clear();
        int half = n / 2;

        best = -INF;
        save = -1;
        attempt(0, 1, half, 0, 0, 0, 0LL);
        attempt(1, half+1, n, 0, 0, 0, 0LL);

        if (save < 0) puts("Impossible");
        else {
            REP(i,n) {
                int cur = (save % p3[i+1]) / p3[i];
                if (cur == 0) puts("LM");
                else if (cur == 1) puts("LW");
                else if (cur == 2) puts("MW");
            }
        }
    }
}
