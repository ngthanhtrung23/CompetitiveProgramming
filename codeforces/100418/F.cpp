
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

const int MN = 100111;
int n;
ll a[MN];

ll read() {
	ll x; assert(scanf("%lld", &x));
	return x;
}

vector<int> p2[111];

int len(ll x) {
	int res = 0;
	while (x > 0) {
		++res;
		x /= 2;
	}
	return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (scanf("%d", &n) == 1) {
		FOR(i,1,n) a[i] = read();

		set< pair<ll,int> > all;
		vector< int > zero;
		FOR(i,1,n) {
			if (a[i] == 0) zero.push_back(i);
			else all.insert(make_pair(a[i], i));
		}

		FOR(i,0,100) p2[i].clear();

		vector<pair<int,int> > res;
		while (!all.empty()) {
			ll cur = all.begin()->first;
			int id = all.begin()->second;
			all.erase(all.begin());

			FORD(bit,62,0) {
				ll need = (1LL << bit) - cur;

				if (need == cur) {
					p2[len(need)].push_back(id);
					break;
				}
				auto it = all.lower_bound(make_pair(need, 0));
				if (it != all.end() && it->first == need) {
					res.push_back(make_pair(id, it->second));
					all.erase(it);
					break;
				}
			}
		}

		FOR(i,0,100) {
			if (SZ(p2[i]) % 2 == 1 && !zero.empty()) {
				res.push_back(make_pair(p2[i].back(), zero.back()));
				zero.pop_back();
				p2[i].pop_back();
			}
		}
		FOR(i,0,100) {
			while (SZ(p2[i]) >= 2 && zero.size() >= 2) {
				REP(turn,2) {
					res.emplace_back(p2[i].back(), zero.back());
					zero.pop_back();
					p2[i].pop_back();
				}
			}
			while (SZ(p2[i]) >= 2) {
				int u = p2[i].back(); p2[i].pop_back();
				int v = p2[i].back(); p2[i].pop_back();
				res.emplace_back(u, v);
			}
		}

		cout << SZ(res) << '\n';
		for(auto p : res) cout << p.first << ' ' << p.second << '\n';
	}
}
