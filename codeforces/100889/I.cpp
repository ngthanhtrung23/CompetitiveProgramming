#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MOD = 1e9 + 7;
const int MN = 200111;

struct Hash {
    int x, y;
    Hash() { x = y = 0; }
    Hash(int x, int y) : x(x), y(y) {}

    Hash operator + (const Hash& a) const { return Hash(x+a.x, (y+a.y) % MOD); }
    Hash operator - (const Hash& a) const { return Hash(x-a.x, (y-a.y+MOD) % MOD); }
    Hash operator * (const Hash& a) const { return Hash(x*a.x, y*a.y % MOD); }
};
bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
ostream& operator << (ostream& cout, Hash& h) {
    cout << h.x << ' ' << h.y;
    return cout;
}

Hash p[MN], h[MN], h2[MN];

char s[MN], t[MN];
int n;

Hash getHash(int l, int r) {
    Hash res = (l == 0) ? h[r] : h[r] - h[l-1];
    return res * p[n - l];
}
Hash getHash2(int l, int r) {
    Hash res = (l == 0) ? h2[r] : h2[r] - h2[l-1];
    return res * p[n-l];
}


struct node {
	int next[26];
	int len;
	int sufflink;
};

int len;
node tree[MN]; 
int num; 			// node 1 - root with len -1, node 2 - root with len 0
int suff; 			// max suffix palindrome
pair<int,int> found;

bool addLetter(char s[], int pos) {
	int cur = suff, curlen = 0;
	int let = s[pos] - 'a';

	while (true) {
		curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])    	
			break;	
		cur = tree[cur].sufflink;
	}		
	if (tree[cur].next[let]) {	
		suff = tree[cur].next[let];
		return false;
	}

	num++;
	suff = num;
	tree[num].len = tree[cur].len + 2;
	tree[cur].next[let] = num;

    found = make_pair(pos - tree[num].len + 1, pos);

	if (tree[num].len == 1) {
		tree[num].sufflink = 2;
		return true;
	}

	while (true) {
		cur = tree[cur].sufflink;
		curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
			tree[num].sufflink = tree[cur].next[let];
			break;
		}    	
	}           

	return true;
}

void initTree() {
    memset(tree, 0, sizeof tree);
	num = 2; suff = 2;
	tree[1].len = -1; tree[1].sufflink = 1;
	tree[2].len = 0; tree[2].sufflink = 1;
}

void initHash() {
    p[0] = Hash(1, 1);
    FOR(i,1,MN-1) p[i] = p[i-1] * Hash(311, 311);

    REP(i,n) {
        if (i > 0) {
            h[i] = h[i-1];
            h2[i] = h2[i-1];
        }
        h[i] = h[i] + p[i] * Hash(s[i], s[i]);
        h2[i] = h2[i] + p[i] * Hash(t[i], t[i]);
    }
}

int cnt[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; scanf("%lld\n", &ntest);
    while (ntest--) {
        memset(s, 0, sizeof s);
        memset(t, 0, sizeof t);
        memset(cnt, 0, sizeof cnt);
        memset(h, 0, sizeof h);
        memset(h2, 0, sizeof h2);

        gets(s);
        n = strlen(s);

        REP(i,n) t[i] = s[i];
        reverse(t, t+n);

        initHash();
        map<Hash,int> minLeft, maxRight;

        // build palindromic tree from left
        initTree();
//        cout << "LEFT: " << endl;
        REP(i,n) {
            found = make_pair(-1, -1);
            addLetter(s, i);
            if (found.first < 0) continue;

            Hash cur = getHash(found.first, found.second);

            if (minLeft.find(cur) == minLeft.end()) {
                minLeft[cur] = i;
//                cout << found.first << ' ' << found.second << endl;
            }
        }

        // build palindromic tree from right
//        cout << "RIGHT: " << endl;
        initTree();
        REP(i,n) {
            found = make_pair(-1, -1);
            addLetter(t, i);
            if (found.first < 0) continue;

            swap(found.first, found.second);
            found.first = n - found.first - 1;
            found.second = n - found.second - 1;

            Hash cur = getHash(found.first, found.second);

            if (maxRight.find(cur) == maxRight.end()) {
                maxRight[cur] = n - i - 1;
//                cout << found.first << ' ' << found.second << endl;
            }
        }

        // find ranges
        for(auto p : minLeft) {
            int l = p.second + 1;
            int r = maxRight[p.first] - 1;
            if (l <= r) {
                ++cnt[0];
                --cnt[n];
            }
            else {
                ++cnt[l];
                --cnt[n];

                ++cnt[0];
                --cnt[r+1];
            }
        }
        FOR(i,1,n-1) cnt[i] += cnt[i-1];

        REP(i,n) {
            // s[i] --> $
            int l = 0, r = min(i, n-i-1), res = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;

                if (getHash(i-mid, i) == getHash2(n-1-i-mid, n-1-i)) res = mid, l = mid + 1;
                else r = mid - 1;
            }
            cnt[i] += res + 1;
        }

        int ln = 0, ways = 1;
        REP(i,n) {
            if (cnt[i] > ln) {
                ln = cnt[i];
                ways = 1;
            }
            else if (cnt[i] == ln) ++ways;
        }
        cout << ln << ' ' << ways << endl;
    }
}
