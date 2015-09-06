
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

pair<int,int> a[5011];
int c[10111];
ll f[2][10111];
int n;

int main() {
    ios :: sync_with_stdio(false);
    int start;
    while (cin >> n >> start) {
        int nc = 0;
        c[++nc] = start;
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
            c[++nc] = a[i].first;
            c[++nc] = a[i].second;
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;

        start = lower_bound(c+1, c+nc+1, start) - c;
        FOR(i,1,n) {
            a[i].first = lower_bound(c+1, c+nc+1, a[i].first) - c;
            a[i].second = lower_bound(c+1, c+nc+1, a[i].second) - c;
        }

        f[0][start] = 0;
        FORD(i,start-1,1) {
            f[0][i] = f[0][i+1] + c[i+1] - c[i];
        }
        FOR(i,start+1,nc) {
            f[0][i] = f[0][i-1] + c[i] - c[i-1];
        }

        FOR(i,1,n) {
            int t = i % 2;
            FOR(j,1,nc) f[t][j] = f[1-t][j];

            FOR(j,2,nc) f[t][j] = min(f[t][j], f[t][j-1] + c[j] - c[j-1]);
            FORD(j,nc-1,1) f[t][j] = min(f[t][j], f[t][j+1] + c[j+1] - c[j]);

            FOR(j,1,nc) {
                if (a[i].first <= j && j <= a[i].second) {}
                else if (j < a[i].first) f[t][j] += c[a[i].first] - c[j];
                else f[t][j] += c[j] - c[a[i].second];
            }
        }
        cout << *min_element(f[n%2]+1, f[n%2]+nc+1) << endl;
    }
}
