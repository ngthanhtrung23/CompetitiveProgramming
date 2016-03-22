#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
#define next next___
using namespace std;

const int MN = 100111;
string s;
int n, next[MN];

struct Node {
    int len, link, cnt;
    int next[33];
};
Node nodes[MN * 2];
set< pair<int,int> > order;
struct Automaton {
    int sz, last;
    Automaton() {
        sz = last = 0;
        nodes[0].len = 0;
        nodes[0].link = -1;
        ++sz;
        // need to reset next if necessary
    }
    void extend(char c) {
        c = c - 'A';
        int cur = sz++, p;
        nodes[cur].len = nodes[last].len + 1;
        nodes[cur].cnt = 1;
        order.insert(make_pair(nodes[cur].len, cur));

        for(p = last; p != -1 && !nodes[p].next[c]; p = nodes[p].link)
            nodes[p].next[c] = cur;
        if (p == -1) nodes[cur].link = 0;
        else {
            int q = nodes[p].next[c];
            if (nodes[p].len + 1 == nodes[q].len) nodes[cur].link = q;
            else {
                int clone = sz++;
                nodes[clone].len = nodes[p].len + 1;
                memcpy(nodes[clone].next, nodes[q].next, sizeof(nodes[q].next));
                nodes[clone].link = nodes[q].link;
                nodes[clone].cnt = 0;
                order.insert(make_pair(nodes[clone].len, clone));

                for(; p != -1 && nodes[p].next[c] == q; p = nodes[p].link)
                    nodes[p].next[c] = clone;
                nodes[q].link = nodes[cur].link = clone;
            }
        }
        last = cur;
    }
};

int good[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        memset(nodes, 0, sizeof nodes);
        n = SZ(s);
        s = " " + s + " ";
        int j = 0;
        FOR(i,2,n) {
            while (j > 0 && s[i] != s[j+1]) j = next[j];
            if (s[i] == s[j+1]) ++j;
            next[i] = j;
        }
//        PR(next, n);

        order.clear();
        Automaton sa;
        FOR(i,1,n) sa.extend(s[i]);
        for(auto it = order.rbegin(); it != order.rend(); ++it) {
            int p = nodes[it->second].link;
            nodes[p].cnt += nodes[it->second].cnt;
        }
//        REP(i,sa.sz) {
//            FOR(c,'A','Z') {
//                if (nodes[i].next[c - 'A']) {
//                    cout << (char) c << ' ' << nodes[i].next[c - 'A'] << "    ";
//                }
//            }
//            cout << endl;
//        }

        memset(good, 0, sizeof good);
        int x = n;
        int cnt = 0;
        while (x > 0) {
            good[x] = true;
            x = next[x];
            cnt++;
        }
        cout << cnt << '\n';
        int p = 0;
        FOR(i,1,n) {
            p = nodes[p].next[s[i] - 'A'];
            if (good[i]) {
                cout << i << ' ' << nodes[p].cnt << '\n';
            }
        }
    }
}
