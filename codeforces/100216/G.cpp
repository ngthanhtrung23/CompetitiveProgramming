
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

typedef vector< vector<int> > Move;

struct State {
    int x[40];

    void init4(int a[4]) {
        REP(face,4) {
            for(int i = face*9; i < face*9+9; ++i)
                x[i] = a[face];
        }
    }

    bool isFinal() {
        REP(face,4) {
            int start = face * 9;
            for(int i = start; i < start + 9; ++i)
                if (x[i] != x[start]) return false;
        }
        return true;
    }

    bool read() {
        REP(i,36) {
            if (!(cin >> x[i])) return false;
        }
        return true;
    }

    pair<ll,int> getHash() {
        pair<ll,int> res = make_pair(0LL, 0LL);
        FORD(i,35,8) {
            res.first = res.first * 4LL + x[i] - 1LL;
        }
        FORD(i,7,0) {
            res.second = res.second * 4LL + x[i] - 1;
        }
        return res;
    }

    void init(pair<ll,int> h) {
        FOR(i,0,7) {
            x[i] = h.second % 4 + 1;
            h.second /= 4;
        }
        FOR(i,8,35) {
            x[i] = h.first % 4 + 1;
            h.first /= 4;
        }
    }

    void print() {
        for(int start = 0; start < 36; start += 9) {
            FOR(i,start,start+8) cout << x[i] << ' ';
            cout << endl;
        }
        cout << endl;
    }

    void rotate(Move pos) {
        vector< vector<int> > values;
        values.resize(pos.size());
        REP(i,SZ(values)) {
            values[i].resize(SZ(pos[i]));
            REP(j,SZ(values[i])) {
                values[i][j] = x[ pos[i][j]-1 ];
            }
        }
        REP(i,SZ(values)) {
            REP(j,SZ(values[i])) {
                x[ pos[i][j]-1 ] = values[ (i-1+3) % 3][j];
            }
        }
    }
} start;

vector< pair<string, Move> > all;

Move reverse(Move x) {
    swap(x[1], x[2]);
    return x;
}

void initMoves() {
    // 4
    all.push_back({"S4C", { {1}, {10}, {19} }});
    all.push_back({"S4W", reverse({ {1}, {10}, {19} }) });

    all.push_back({"B4C", { {1,4,3,2}, {10,13,12,11}, {19,22,21,20} }});
    all.push_back({"B4W", reverse({ {1,4,3,2}, {10,13,12,11}, {19,22,21,20} }) });

    // 1
    all.push_back({"S1C", { {18}, {36}, {23} }});
    all.push_back({"S1W", reverse({ {18}, {36}, {23} }) });

    all.push_back({"B1C", { {18,16,17,13}, {36,34,35,31}, {23,20,24,25} } });
    all.push_back({"B1W", reverse({ {18,16,17,13}, {36,34,35,31}, {23,20,24,25} }) });

    // 2
    all.push_back({"S2C", { {5}, {27}, {32} } });
    all.push_back({"S2W", reverse({ {5}, {27}, {32} }) });

    all.push_back({"B2C", { {5,2,6,7}, {27,25,26,22}, {32,29,33,34} } });
    all.push_back({"B2W", reverse({ {5,2,6,7}, {27,25,26,22}, {32,29,33,34} }) });

    // 3
    all.push_back({"S3W", { {9}, {14}, {28} } });
    all.push_back({"S3C", reverse({ {9}, {14}, {28} } ) });

    all.push_back({"B3W", { {9,4,8,7}, {14,16,15,11}, {28,29,30,31} } });
    all.push_back({"B3C", reverse({ {9,4,8,7}, {14,16,15,11}, {28,29,30,31} } )});
}

map< pair<ll,int>,int> tr[2];
map< pair<ll,int>,int> depth[2];
queue< pair<ll,int>> qu[2];

void trace( pair<ll,int>  u) {
    if (tr[0][u] < 0) return ;

    State cur; cur.init(u);
    cur.rotate(all[tr[0][u] ^ 1].second);

    trace(cur.getHash());
    puts(all[tr[0][u]].first.c_str());

//    cout << "Trace: cur = " << endl;
//    cur.print();
}

void trace2(pair<ll,int> u) {
    if (tr[1][u] < 0) return ;

    string x = all[tr[1][u]].first;
    x[2] = 'W' + 'C' - x[2];
    puts(x.c_str());

    State cur; cur.init(u);
//    cout << "Trace2: cur = " << endl;
//    cur.print();
    cur.rotate(all[tr[1][u] ^ 1].second);
    trace2(cur.getHash());
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("pyraminx.in", "r", stdin);
    freopen("pyraminx.out", "w", stdout);
    initMoves();

    while (start.read()) {
        REP(turn,2) {
            tr[turn].clear();
            depth[turn].clear();
            while (!qu[turn].empty()) qu[turn].pop();
        }
        
        bool found = false;
        REP(turn,2) {
            if (turn == 0) {
                auto hash = start.getHash();
                tr[turn][hash] = -1;
                depth[turn][hash] = 0;

                qu[turn].push(hash);
            }
            else {
                int val[4]; REP(t,4) val[t] = t + 1;
                do {
                    State start;
                    start.init4(val);
//                    start.print();

                    auto hash = start.getHash();
                    tr[turn][hash] = -1;
                    depth[turn][hash] = 0;

                    qu[turn].push(hash);
                } while (next_permutation(val, val+4));
            }
        
            while (!qu[turn].empty()) {
                auto cur = qu[turn].front(); qu[turn].pop();
                State u; u.init(cur);

                if (turn == 0 && u.isFinal()) {
                    found = true;
                    trace(cur);
                    break;
                }
                else if (turn == 1 && tr[0].count(cur)) {
//                    DEBUG(depth[0][cur]);
//                    DEBUG(depth[1][cur]);
                    found = true;
                    trace(cur);
                    trace2(cur);
                    break;
                }
                if (depth[turn][cur] == 6 - turn) continue;

                REP(id, SZ(all)) {
                    auto m = all[id];
                    State v = u;
                    v.rotate(m.second);

                    auto next = v.getHash();
                    if (!tr[turn].count(next)) {
                        tr[turn][next] = id;
                        depth[turn][next] = depth[turn][cur] + 1;

                        qu[turn].push(next);
                    }
                }
            }
//            DEBUG(tr[turn].size());
            if (found) break;
        }
        if (!found) puts("Impossible");
    }
}

