
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

const ll P = 1e9 + 7;
const int MN = 1000111;
ll cached_power[MN];
ll power(ll k) {
    if (k < MN) return cached_power[k];
    
    ll mid = power(k >> 1);
    mid = mid * mid;
    if (k & 1) return mid * P;
    else return mid;
}

void init() {
    cached_power[0] = 1;
    FOR(i,1,MN-1) cached_power[i] = cached_power[i-1] * P;
}

const int BLACK = 1;
const int WHITE = 0;
const ll MOD = 1e9 + 9;
struct Segment {
    ll x, len;
    int color;

    ll getHash() const {
        return len * power(x % MOD);
    }
} a[MN];

struct LenCompare {
    bool operator () (const Segment& a, const Segment& b) {
        if (a.len != b.len) return a.len > b.len;
        return a.x < b.x;
    }
};

struct PosCompare {
    bool operator () (const Segment& a, const Segment& b) {
        return a.x < b.x;
    }
};

char tmp[1011];
#define hash hash___
ll hash;
set<Segment, LenCompare> allByLen;
set<Segment, PosCompare> allByPos;
set<ll> allHash;

void addSeg(const Segment& t) {
    allByLen.insert(t);
    allByPos.insert(t);
    hash += t.getHash();
}

void remSeg(const Segment& t) {
    allByLen.erase(t);
    allByPos.erase(t);
    hash -= t.getHash();
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("segments.in", "r", stdin);
    freopen("segments.out", "w", stdout);
    init();
    int n, t;
    while (scanf("%d%d", &n, &t) == 2) {
        scanf("%s", &tmp[0]);
        ll sum = 0;
        FOR(i,1,n) {
            int x;
            scanf("%d", &x);
            a[i].len = x;
            a[i].x = sum;
            sum += a[i].len;

            if (i == 1) {
                a[i].color = (tmp[0] == 'w') ? WHITE : BLACK;
            }
            else a[i].color = 1 - a[i-1].color;
        }
//        FOR(i,1,n) cout << a[i].x << ' ' << a[i].len << ' ' << a[i].color << endl;
//        cout << endl;

        hash = 0;
        allByLen.clear();
        allByPos.clear();
        allHash.clear();

        FOR(i,1,n) {
            addSeg(a[i]);
        }
        allHash.insert(hash);

        try {
            FOR(i,1,t) {
                auto t = *allByLen.begin();
                if (t.len == 1) throw i - 1;

                remSeg(t);

                Segment left, right;

                if (t.color == WHITE) {
                    left.x = t.x;
                    left.len = t.len / 2 + t.len % 2;
                    left.color = WHITE;

                    right.x = t.x + left.len;
                    right.len = t.len - left.len;
                    right.color = BLACK;
                    auto it = allByPos.lower_bound(right);
                    if (it != allByPos.end()) {
                        assert(it->color == BLACK);
                        right.len += it->len;
                        remSeg(*it);
                    }
                }
                else {
                    left.x = t.x;
                    left.len = t.len / 2;
                    left.color = WHITE;

                    right.x = t.x + left.len;
                    right.len = t.len - left.len;
                    right.color = BLACK;

                    auto it = allByPos.lower_bound(left);
                    if (it != allByPos.begin()) {
                        --it;
                        assert(it->color == WHITE);
                        left.x = it->x;
                        left.len += it->len;
                        remSeg(*it);
                    }
                }
                addSeg(left);
                addSeg(right);

                if (allHash.count(hash)) throw i;
                allHash.insert(hash);

//                cout << "---------------" << endl;
//                for(auto t : allByPos) cout << t.x << ' ' << t.len << ' ' << t.color << endl;
            }
            cout << t << endl;
        } catch (int e) {
            cout << e << endl;
        }
        break;
    }
}
