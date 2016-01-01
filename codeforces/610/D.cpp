
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

const int MN = 300111;

struct Rect {
    int x1, y1, x2, y2;

    void read() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    }
} a[MN];

int n;
int cx[MN], cy[MN], sx, sy;

void RR() {
    sx = sy = 0;
    FOR(i,1,n) {
        cx[++sx] = a[i].x1;
        cx[++sx] = a[i].x2;

        cy[++sy] = a[i].y1;
        cy[++sy] = a[i].y2;
    }
    sort(cx+1, cx+sx+1);
    sort(cy+1, cy+sy+1);

    sx = unique(cx+1, cx+sx+1) - cx - 1;
    sy = unique(cy+1, cy+sy+1) - cy - 1;

    FOR(i,1,n) {
        a[i].x1 = lower_bound(cx+1, cx+sx+1, a[i].x1) - cx;
        a[i].x2 = lower_bound(cx+1, cx+sx+1, a[i].x2) - cx;

        a[i].y1 = lower_bound(cy+1, cy+sy+1, a[i].y1) - cy;
        a[i].y2 = lower_bound(cy+1, cy+sy+1, a[i].y2) - cy;
    }
}

vector< pair<int,int> > hor[MN], ver[MN];
vector<int> add[MN], sub[MN];

vector< pair<int,int> > normalize(vector< pair<int,int> > a) {
    vector< pair<int,int> > events;
    for(auto p : a) {
        events.push_back(make_pair(p.first, -1));
        events.push_back(make_pair(p.second, +1));
    }
    sort(events.begin(), events.end());

    vector< pair<int,int> > res;
    int sum = 0;
    int start = -1;
    for(auto p : events) {
        sum += p.second;
        if (p.second == -1 && sum == -1) {
            start = p.first;
        }
        if (sum == 0) {
            res.push_back(make_pair(start, p.first));
        }
    }
    return res;
}

int bit[MN];

void update(int u, int val) {
    for(int x = u; x < MN; x += x & -x)
        bit[x] += val;
}

int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res += bit[x];
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) a[i].read();
        RR();

        FOR(x,1,sx) ver[x].clear();
        FOR(y,1,sy) hor[y].clear();

        FOR(i,1,n) {
            if (a[i].y1 == a[i].y2) {
                hor[a[i].y1].push_back(make_pair(a[i].x1, a[i].x2));
            }
            else {
                ver[a[i].x1].push_back(make_pair(a[i].y1, a[i].y2));
            }
        }
        FOR(x,1,sx) ver[x] = normalize(ver[x]);
        FOR(y,1,sy) hor[y] = normalize(hor[y]);

//        cout << "Ver" << endl;
//        FOR(x,1,sx) {
//            DEBUG(cx[x]);
//            for(auto p : ver[x]) cout << cy[p.first] << ' ' << cy[p.second] << "   ";
//            cout << endl;
//        }
//        cout << "Hor" << endl;
//        FOR(y,1,sy) {
//            DEBUG(cy[y]);
//            for(auto p : hor[y]) cout << cx[p.first] << ' ' << cx[p.second] << "   ";
//            cout << endl;
//        }

        FOR(y,1,sy) {
            add[y].clear();
            sub[y].clear();
        }

        ll res = 0;
        FOR(x,1,sx) {
            for(auto p : ver[x]) {
                res += cy[p.second] - cy[p.first] + 1;
                sub[p.first].push_back(x);
                add[p.second].push_back(x);
            }
        }
        FOR(y,1,sy) {
            for(auto p : hor[y]) {
                res += cx[p.second] - cx[p.first] + 1;
            }
        }
        FOR(y,1,sy) {
            for(auto x : sub[y]) {
                res += get(x);
            }
            for(auto p : hor[y]) {
                update(p.first, +1);
                update(p.second + 1, -1);
            }
            for(auto x : add[y]) {
                res -= get(x);
            }
        }
        cout << res << endl;
    }
}
