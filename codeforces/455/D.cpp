#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
const int MV = 511;
int n, a[MN], lastans, segId[MN], segPos[MN];

struct Segment {
    deque<int> values;
    int cnt[MN];

    Segment() {
        values.clear();
        memset(cnt, 0, sizeof cnt);
    }

    void insert(int val, int pos, bool end = false) {
        if (end) values.push_back(val);
        else values.insert(values.begin()+(pos-1), val);
        cnt[val] += 1;
    }
    int remove(int pos, bool end = false) {
        int res;
        if (end) res = values.back();
        else res = values[pos-1];
        if (end) values.pop_back();
        else values.erase(values.begin() + (pos-1));
        cnt[res] -= 1;
        return res;
    }
    int count(int l, int r, int k) {
        int res = 0;
        for(int i = max(l-1, 0); i < min(r, (int) values.size()); ++i) {
            if (values[i] == k) ++res;
        }
        return res;
    }
} segs[MN / MV + 111];

void init() {
    int curId = 1, curSize = 1; segId[1] = 1; segPos[1] = 1;
    FOR(i,2,n) {
        if (curSize == MV) {
            curSize = 0;
            curId += 1;
        }
        segId[i] = curId;
        curSize += 1;
        segPos[i] = curSize;
    }
//    PR(segId, n);
//    PR(segPos, n);

    FOR(i,1,segId[n]) segs[i] = Segment();
    FOR(i,1,n) {
        segs[segId[i]].insert(a[i], segPos[i], true);
    }
//    FOR(i,1,segId[n]) cout << segs[i];
}

int translate(int x) {
    return (x + lastans - 1) % n + 1;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        init();
        int q; cin >> q;
        lastans = 0;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int l, r; cin >> l >> r;
                l = translate(l);
                r = translate(r);
                if (l > r) swap(l, r);

                if (segId[l] == segId[r]) {
                    int rem = segs[segId[r]].remove(segPos[r]);
                    segs[segId[l]].insert(rem, segPos[l]);
                }
                else {
                    int rem = segs[segId[r]].remove(segPos[r]);
                    segs[segId[l]].insert(rem, segPos[l]);
                    FOR(id,segId[l],segId[r]-1) {
                        int rem = segs[id].remove(-1, true);
                        segs[id+1].insert(rem, 1);
                    }
                }
            }
            else {
                int l, r, k; cin >> l >> r >> k;
                l = translate(l);
                r = translate(r);
                k = translate(k);
                if (l > r) swap(l, r);

//                cout << "Count: " << l << ' ' << r << ' ' << k << endl;

                int res = 0;
                if (segId[l] == segId[r]) {
                    res = segs[segId[l]].count(segPos[l], segPos[r], k);
                }
                else {
                    res = segs[segId[l]].count(segPos[l], MV, k);
                    res += segs[segId[r]].count(0, segPos[r], k);
                    FOR(id,segId[l]+1,segId[r]-1)
                        res += segs[id].cnt[k];
                }
                cout << res << "\n";
                lastans = res;
//                DEBUG(res);
            }
        }
    }
    return 0;
}
