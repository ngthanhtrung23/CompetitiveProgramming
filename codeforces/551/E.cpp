
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 500111;
int n, q;
int a[MN];

const int BUCKET = 700;

struct Bucket {
    int from, to;
    vector< pair<long long,int> > x;
    long long val;
} buckets[MN / BUCKET + 11];

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);

        int nBucket = 0;
        for(int id = 1, start = 1, last = BUCKET; start <= n; start += BUCKET, last += BUCKET, ++id) {
            buckets[id].from = start;
            buckets[id].to = min(last, n);
            buckets[id].x.clear();
            buckets[id].val = 0;

            FOR(i,buckets[id].from, buckets[id].to) {
                buckets[id].x.push_back(make_pair(a[i], i));
            }
            sort(buckets[id].x.begin(), buckets[id].x.end());
            nBucket = id;
        }
        while (q--) {
            int typ; scanf("%d", &typ);
            if (typ == 1) {
                int l, r, val; scanf("%d%d%d", &l, &r, &val);

                FOR(id,1,nBucket) {
                    if (l <= buckets[id].from && buckets[id].to <= r) buckets[id].val += val;
                    else if (r < buckets[id].from || buckets[id].to < l) {
                    }
                    else {
                        REP(i,buckets[id].x.size())
                            if (l <= buckets[id].x[i].second && buckets[id].x[i].second <= r)
                                buckets[id].x[i].first += val;
                        sort(buckets[id].x.begin(), buckets[id].x.end());
                        while (!buckets[id].x.empty() && buckets[id].x.back().first > 1000000000) buckets[id].x.pop_back();
                    }
                }
//                FOR(id,1,nBucket) {
//                    cout << buckets[id].from << " --> " << buckets[id].to << endl;
//                    for(auto p : buckets[id].x)
//                        cout << '(' << p.first << ' ' << p.second << ")    ";
//                    cout << endl;
//                    DEBUG(buckets[id].val);
//                }
            }
            else {
                int first = -1;
                int last = -1;
                int y; scanf("%d", &y);

                FOR(id,1,nBucket) {
                    long long need = y - buckets[id].val;
                    if (need < 0) continue;
                    auto t = lower_bound(buckets[id].x.begin(), buckets[id].x.end(), make_pair(need, 0));
                    if (t == buckets[id].x.end() || t->first != need) continue;

                    first = t->second;
                    break;
                }
                FORD(id,nBucket,1) {
                    long long need = y - buckets[id].val;
                    if (need < 0) continue;
                    auto t = lower_bound(buckets[id].x.begin(), buckets[id].x.end(), make_pair(need+1, 0));
                    if (t == buckets[id].x.begin()) continue;
                    --t;
                    if (t->first != need) continue;

                    last = t->second;
                    break;
                }
//                DEBUG(first);
//                DEBUG(last);
                if (first < 0) printf("-1\n");
                else printf("%d\n", last - first);
            }
        }
    }
    return 0;
}
