
#include <bits/stdc++.h>
#define int long long
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

const int MN = 10111;
struct Node {
    int child[26];
    int id;
} nodes[1000111];
int root, nNodes;

string words[100111];
int f[MN], tr[MN];
int ls;
string s;
int n;

int createNode() {
    int res = ++nNodes;
    memset(nodes[res].child, 0, sizeof nodes[res].child);
    nodes[res].id = 0;
    return res;
}
bool isUpper(char c) {
    return c >= 'A' && c <= 'Z';
}

void trace(int i) {
    if (!i) return ;

    trace(tr[i]);
    cout << words[f[i]] << ' ';
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> ls >> s) {
        s = " " + s + " ";
        cin >> n; FOR(i,1,n) cin >> words[i];
        nNodes = 0;
        root = createNode();
        // build trie
        FOR(i,1,n) {
            int p = root;
            REP(x,SZ(words[i])) {
                char c = words[i][x];
                if (isUpper(c)) c ^= ' ';

                if (!nodes[p].child[c - 'a']) {
                    nodes[p].child[c - 'a'] = createNode();
                }
                p = nodes[p].child[c - 'a'];
            }
            nodes[p].id = i;
        }
        // DP
        memset(f, -1, sizeof f);
        f[0] = 0;
        FOR(i,1,ls) {
            int p = root;
            FORD(j,i,1) {
                p = nodes[p].child[s[j] - 'a'];
                if (p == 0) break;

                if (nodes[p].id && f[j-1] >= 0) {
                    f[i] = nodes[p].id;
                    tr[i] = j - 1;
                    break;
                }
            }
        }
        trace(ls);
        cout << endl;
    }
}
