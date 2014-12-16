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
struct Query {
    int id, P_init, P_final, x, y;
} queries[MN];
int q, sx, cx[MN], sy, cy[MN];

void RR() {
    FOR(i,1,q) cx[i] = queries[i].x;
    sx = q;
    sort(cx+1, cx+sx+1);
    sx = unique(cx+1, cx+sx+1) - cx - 1;
    FOR(i,1,q) queries[i].x = lower_bound(cx+1, cx+sx+1, queries[i].x) - cx;

    FOR(i,1,q) cy[i] = queries[i].y;
    sy = q;
    sort(cy+1, cy+sy+1);
    sy = unique(cy+1, cy+sy+1) - cy - 1;
    FOR(i,1,q) queries[i].y = lower_bound(cy+1, cy+sy+1, queries[i].y) - cy;

//    PR(cx, sx);
//    PR(cy, sy);

    FOR(i,1,q) {
        queries[i].x = sx - queries[i].x + 1;
        queries[i].y = sy - queries[i].y + 1;
    }
}

int bit[1011][1011];
#define _(X) ((X) & (-(X)))

void update(int startu, int startv) {
    for(int u = startu; u <= sx; u += _(u))
        for(int v = startv; v <= sy; v += _(v))
            bit[u][v] += 1;
}

int get(int startu, int startv) {
    int res = 0;
    for(int u = startu; u > 0; u -= _(u))
        for(int v = startv; v > 0; v -= _(v))
            res += bit[u][v];
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case #" << test << ":\n";
        cin >> q;
        memset(bit, 0, sizeof bit);
        FOR(i,1,q) {
            cin >> queries[i].id >> queries[i].P_init >> queries[i].x >> queries[i].y;
        }
        RR();
        FOR(i,1,q) {
            queries[i].P_final = queries[i].P_init + get(queries[i].x-1, queries[i].y-1);

            update(queries[i].x, queries[i].y);
        }

//        FOR(i,1,q) cout << queries[i].P_final << endl;
        
        set< pair<pair<int,int>,int> > segs;
        map<int,int> id_to_len;
        set< pair<int,int> > all;
        FOR(i,1,q) {
            int from = 1, to = queries[i].P_final;
            while (!segs.empty() && segs.begin()->first.first < to) {
                int id = segs.begin()->second;
                int left = segs.begin()->first.first, right = segs.begin()->first.second;
                segs.erase(segs.begin());

                all.erase(make_pair(-id_to_len[id], id));
                if (right < to) {
                    id_to_len[id] = 0;
                }
                else {
                    left = to;
                    segs.insert(make_pair(make_pair(left, right), id));
                    id_to_len[id] = right - left;
                }
                all.insert(make_pair(-id_to_len[id], id));
            }
            segs.insert(make_pair(make_pair(from, to), queries[i].id));
            id_to_len[queries[i].id] = to - from;
            all.insert(make_pair(from - to, queries[i].id));
//            for(auto seg : segs) cout << seg.first.first << ' ' << seg.first.second << "   "; cout << endl;
            cout << all.begin()->second << ' ' << -all.begin()->first << "\n";
        }
    }
    return 0;
}
