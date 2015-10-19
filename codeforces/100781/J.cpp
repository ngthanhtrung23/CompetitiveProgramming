
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

unordered_map<string,int> id;

int getId(const string& s) {
    if (id.count(s)) return id[s];

    int k = SZ(id) + 1;
    return id[s] = k;
}

struct Node {
    map<int,Node*> c;
    map<int,int> cnt;
    int sz, max_cnt;

    Node() {
        c.clear();
        cnt.clear();
        sz = 0;
        max_cnt = 0;
    }

    void addWord(ll h) {
        cnt[h] += 1;
        ++sz;
        if (cnt[h] > max_cnt) max_cnt = cnt[h];
    }
} *root;

int t, n;
char tmp[1000111];

map< pair<int,Node*>, double > f;

double get(int t, Node*& p) {
    if (t == 0) return 0;
    if (f.count(make_pair(t, p))) return f[make_pair(t, p)];

    // just answer lah
    double res = p->max_cnt / (double) p->sz + get(t-1, root);

    // move to one child
    double sum = 0.0;
    for(__typeof(p->c.begin()) it = p->c.begin(); it != p->c.end(); ++it) {
        double prob = it->second->sz / (double) p->sz;
        sum += prob * get(t-1, it->second);
    }

    return f[make_pair(t, p)] = max(res, sum);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (scanf("%d%d\n", &t, &n) == 2) {
        root = new Node();
        f.clear();
        FOR(i,1,n) {
            gets(tmp);
            string s(tmp);
            int mark = s.find('?');

            string ques = s.substr(0, mark);
            int ans = getId(s.substr(mark + 2));

//            cout << "quest = " << ques << ", ans = " << ans << endl;

            stringstream ss(ques);
            string token;
            Node*p = root;
            p->addWord(ans);

            while (ss >> token) {
                ll cur = getId(token);
                if (!(p->c.count(cur))) {
                    p->c[cur] = new Node();
                }
                p = p->c[cur];
                p->addWord(ans);
            }
        }
        cout << get(t, root) << endl;
    }
}
