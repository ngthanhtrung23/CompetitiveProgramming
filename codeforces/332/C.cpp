#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
using namespace std;

const int MN = 100111;

struct Job {
    int a, b, id;
} a[MN];

int n, p, k;
long long f[MN], g[MN];
set< pair<long long, int> > s;

bool cmpDo(const Job &a, const Job &b) {
    if (a.b != b.b) return a.b > b.b;
    if (a.a != b.a) return a.a < b.a;
    return a.id < b.id;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> p >> k) {
        FOR(i,1,n) {
            cin >> a[i].a >> a[i].b;
            a[i].id = i;
        }
        sort(a+1, a+n+1, cmpDo);

        // FOR(i,1,n) cout << a[i].a << ' ' << a[i].b << endl;

        s.clear();
        long long cur_sum = 0;
        FOR(i,1,n) {
            s.insert(make_pair(a[i].a, a[i].id));
            cur_sum += a[i].a;
            if (s.size() > k) {
                cur_sum -= s.begin()->first;
                s.erase(s.begin());
            }

            f[i] = cur_sum;
        }

        s.clear(); cur_sum = 0;
        FORD(i,n,1) {
            s.insert(make_pair(a[i].b, a[i].id));
            cur_sum += a[i].b;
            if (s.size() > p - k) {
                cur_sum -= s.begin()->first;
                s.erase(s.begin());
            }
            g[i] = cur_sum;
        }

        long long bestf = -1, bestg = 0, save = -1;
        FOR(i,k,n-(p-k)) {
            if (f[i] > bestf || (f[i] == bestf && g[i+1] > bestg)) {
                bestf = f[i];
                bestg = g[i+1];
                save = i;
            }
        }

        s.clear();
        FOR(i,1,save) {
            s.insert(make_pair(a[i].a, a[i].id));
            if (s.size() > k) {
                s.erase(s.begin());
            }
        }
        for(__typeof(s.begin()) it = s.begin(); it != s.end(); ++it)
            printf("%d ", it->second);

        s.clear();
        FORD(i,n,save+1) {
            s.insert(make_pair(a[i].b, a[i].id));
            if (s.size() > p - k) {
                s.erase(s.begin());
            }
        }
        for(__typeof(s.begin()) it = s.begin(); it != s.end(); ++it)
            printf("%d ", it->second);

        puts("");
    }
    return 0;
}

