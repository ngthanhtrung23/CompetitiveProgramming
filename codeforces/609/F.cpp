
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;

int nFrog, nMos;

int nextInt() {
    int x; scanf("%d", &x);
    return x;
}

struct Frog {
    int eat;
    int id;
    ll pos, tongue;

    void read() {
        pos = nextInt();
        tongue = nextInt();
    }
} frogs[MN];

struct Mos {
    ll pos;
    ll val;

    void read() {
        pos = nextInt();
        val = nextInt();
    }
} mos[MN];

bool cmpPos(const Frog& a, const Frog& b) {
    return a.pos < b.pos;
}
bool cmpId(const Frog& a, const Frog& b) {
    return a.id < b.id;
}

ll it[MN * 4];

void update(int i, int l, int r, int u, ll val) {  // u is frog ID
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = max(it[i], val);
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, val);
    update(i<<1|1, mid+1, r, u, val);

    it[i] = max(it[i<<1], it[i<<1|1]);
}

int get(int i, int l, int r, ll need) {  // return frog ID
    if (it[i] < need) return -1;
    if (l == r) return l;

    int mid = (l + r) >> 1;
    if (it[i<<1] >= need) return get(i<<1, l, mid, need);
    else return get(i<<1|1, mid+1, r, need);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d", &nFrog, &nMos) == 2) {
        FOR(i,1,nFrog) {
            frogs[i].read();
            frogs[i].id = i;
            frogs[i].eat = 0;
        }
        sort(frogs+1, frogs+nFrog+1, cmpPos);

        FOR(i,1,nMos) {
            mos[i].read();
        }
        multiset< pair<int,int> > alive;  // pos, val

        memset(it, -1, sizeof it);
        FOR(i,1,nFrog) update(1, 1, nFrog, i, frogs[i].pos + frogs[i].tongue);

        FOR(i,1,nMos) {
            auto fid = get(1, 1, nFrog, mos[i].pos);
            if (fid == -1 || frogs[fid].pos > mos[i].pos) {
                // can not eat
                alive.insert(make_pair(mos[i].pos, mos[i].val));
            }
            else {
                frogs[fid].eat++;
                frogs[fid].tongue += mos[i].val;

                update(1, 1, nFrog, fid, frogs[fid].pos + frogs[fid].tongue);

                while (true) {
                    auto it = alive.lower_bound(make_pair(frogs[fid].pos, -1));
                    if (it == alive.end()) break;
                    if (it->first > frogs[fid].pos + frogs[fid].tongue) break;

                    frogs[fid].eat++;
                    frogs[fid].tongue += it->second;
                    alive.erase(it);

                    update(1, 1, nFrog, fid, frogs[fid].pos + frogs[fid].tongue);
                }
            }
        }

        sort(frogs+1, frogs+nFrog+1, cmpId);
        FOR(i,1,nFrog) printf("%d %lld\n", frogs[i].eat, frogs[i].tongue);
        puts("");
    }
}
