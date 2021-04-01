// Somehow generate hashes for 10^6 random strings worked..

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MOD=1000000009;
int mult(int a, int b) {
    return (a*b) % MOD;
}
int add(int a, int b) {
    return (a+b) % MOD;
}
const int C[] = {115381398, 276147934};
//MOD=1000000009, C=115381398 or 276147934
int hsh(string s, int id)
{
	int ans=0;
	for(int i=0;i<SZ(s);i++)
	{
		ans=mult(ans,C[id]);
		ans=add(ans,s[i]-'a'+1);
	}
	return ans;
}

string rand_str() {
    string res = "";
    REP(i,50) {
        res += (char) ('a' + rand() % 26);
    }
    return res;
}

int32_t bla() {
    REP(turn,1000) {
        string s = rand_str();
        cout << s << ' ' << hsh(s, 0) << ' ' << hsh(s, 1) << endl;
    }
    return 0;
}

int32_t main() {
    set<int> h0, h1;
    srand(0);
    REP(t,1000111) {
        string s = rand_str();
        h0.insert(hsh(s, 0));
        h1.insert(hsh(s, 1));
    }

    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    vector<int> hashes(ntest);
    REP(i,ntest) {
        cin >> hashes[i];
        assert(0 <= hashes[i] && hashes[i] < MOD);
    }

    vector<string> s(ntest);
    REP(i,ntest) cin >> s[i];

    REP(i,ntest) {
        if (h0.count(hashes[i])) {
            cout << 1 << endl;
            continue;
        } else if (h1.count(hashes[i])) {
            cout << 0 << endl;
            continue;
        }
        cout << 0 << endl;

        /*
        int t = s[i][0] - '0';
        assert(0 <= t && t <= 1);
        assert(SZ(s[i]) == 1);

        cout << t << endl;
        */
    }

    return 0;
}
