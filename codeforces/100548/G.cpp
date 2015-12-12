#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

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

const int MN = 1000111;
const ll MOD = 1e9 + 7;

struct Hash {
    ll x, y;

    Hash() {}
    Hash(ll x, ll y) : x(x), y(y) {}

    Hash operator - (const Hash& a) {
        return Hash(x - a.x, (y - a.y + MOD) % MOD);
    }
    Hash operator + (const Hash& a) {
        return Hash(x + a.x, (y + a.y) % MOD);
    }
    Hash operator * (const Hash& a) {
        return Hash(x * a.x, y * a.y % MOD);
    }
    Hash operator * (const ll k) {
        return Hash(x * k, y * k % MOD);
    }
};

struct Node {
	int next[26];
	int len;
	int suffixLink;
	Hash hash;

    int lazy;
};
bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
map<Hash,int> cnta, cntb;
Hash h[MN], p[MN];
int num, suff, len;

Node tree[MN];

void clearTree(int num) {
    FOR(i,1,num) {
        memset(tree[i].next, 0, sizeof tree[i].next);
        tree[i].len = 0;
        tree[i].suffixLink = 0;
        tree[i].hash = Hash(0LL, 0LL);

        tree[i].lazy = 0;
    }
}

void init(const char s[]) {
	num = 2;
	suff = 2;
	len = strlen(s);

	tree[1].len = -1; tree[1].suffixLink = 1;
	tree[2].len = 0; tree[2].suffixLink = 1;

    h[0] = p[0] * (ll) s[0];
    FOR(i,1,len-1) {
        h[i] = h[i-1] + p[i] * (ll) s[i];
    }
}

Hash getHash(int from, int to) {
    Hash cur = (from == 0) ? h[to] : h[to] - h[from-1];
    return cur * p[200000 - from];
}

bool addLetter(const char s[], int pos) {
	int cur = suff, curlen = 0;
	int let = s[pos] - 'a';

	while (true) {
		curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;

		cur = tree[cur].suffixLink;
	}
	if (tree[cur].next[let]) {
        int x = tree[cur].next[let];
        suff = x;
        tree[x].lazy += 1;
		suff = tree[cur].next[let];
		return false;
	}
	++num;
	suff = num;
	tree[num].len = tree[cur].len + 2;
    tree[num].lazy = 1;
    tree[num].hash = getHash(pos - tree[num].len + 1, pos);

	tree[cur].next[let] = num;

//    cout << "Node: " << num << ' ' << pos - tree[num].len + 1 << ' ' << pos << endl;
	
	if (tree[num].len == 1) {
		tree[num].suffixLink = 2;
		return false;
	}

	while (true) {
		cur = tree[cur].suffixLink;
		curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
			tree[num].suffixLink = tree[cur].next[let];
			break;
		}
	}
	return true;
}

char a[MN], b[MN];

void build(const char s[], map<Hash,int>& cnt) {
	cnt.clear();
	init(s);
//	DEBUG(num);

    REP(i,len) {
        addLetter(s, i);
    }
//    DEBUG(num);
    FORD(i,num,3) {
//        cout << i << " --> " << tree[i].lazy << endl;
        cnt[tree[i].hash] = tree[i].lazy;

        int x = tree[i].suffixLink;
        tree[x].lazy += tree[i].lazy;
    }

    clearTree(num);

//    DEBUG(num);
}

int main() {
	p[0] = Hash(1LL, 1LL); FOR(i,1,MN-1) p[i] = p[i-1] * 1000003;

	int ntest; scanf("%d\n", &ntest);
	FOR(test,1,ntest) {
		gets(a); gets(b);
		build(a, cnta);
		build(b, cntb);

        ll res = 0;
        for(auto p : cnta) {
            res += p.second * (ll) cntb[p.first];
        }
        printf("Case #%d: %lld\n", test, res);
	}
}

