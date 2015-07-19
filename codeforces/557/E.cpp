
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
using namespace std;

const int MN = 5011;
string s;
int k;
bool f[MN][MN];

struct Node {
    int cnt, good;
    Node *child[2];
} *root;

Node* createNode() {
    Node* res = new Node;
    res->child[0] = res->child[1] = NULL;
    res->cnt = res->good = 0;
    return res;
}

void dfs(Node* root) {
    if (!root) return ;

    root->cnt = root->good;
    REP(t,2) 
        if (root->child[t]) {
            dfs(root->child[t]);
            root->cnt += root->child[t]->cnt;
        }
}

void dfs2(Node* root, int k, string res) {
    if (root->good) {
        if (k <= root->good) {
            cout << res << endl;
            return;
        }
        k -= root->good;
    }
    if (root->child[0] && root->child[0]->cnt >= k) {
        dfs2(root->child[0], k, res + 'a');
    }
    else {
        if (root->child[0]) k -= root->child[0]->cnt;
        dfs2(root->child[1], k, res + 'b');
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s >> k) {
        int n = s.length();
        FOR(len,1,n) {
            REP(i,n-len+1) {
                int j = i + len - 1;
                if (len <= 4) f[i][j] = s[i] == s[j];
                else f[i][j] = s[i] == s[j] && f[i+2][j-2];
            }
        }
        root = createNode();

        REP(i,n) {
            Node* p = root;
            FOR(j,i,n-1) {
                int t = s[j] - 'a';
                if (!p->child[t]) p->child[t] = createNode();

                p = p->child[t];
                if (f[i][j]) p->good += 1;
            }
        }
        dfs(root);

        dfs2(root, k, "");
    }
}
