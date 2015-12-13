
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

#define double long double
const double PI = acos((double) -1.0);
const double EPS = 1e-9;

int cmp(double x, double y) {
	if (fabs(x - y) < EPS) return 0;
	if (x < y) return -1;
	return 1;
}

double refine(double x) {
	while (cmp(x, 0) < 0) x += 2*PI;
	while (cmp(x, 2*PI) > 0) x -= 2*PI;
	return x;
}

bool cmpPair(const pair<double,int>& a, const pair<double,int>& b) {
	int t = cmp(a.first, b.first);
	
	if (t < 0) return true;
	if (t > 0) return false;

	return a.second < b.second;
}

double get(vector<pair<double,double> >& a) {
	vector< pair<double,int> > x;
	for(auto p : a) {
		x.push_back(make_pair(p.first, 0));
		x.push_back(make_pair(p.second, 1));
	}
	sort(x.begin(), x.end(), cmpPair);

	double from = -1.0, res = 0.0;
	int sum = 0;
	for(auto p : x) {
		if (p.second == 0) {
			++sum;
			if (sum == 1) from = p.first;
		}
		else {
			--sum;
			if (sum == 0) res += p.first - from;
		}
	}
	return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	double xc, yc, h, r;
	while (cin >> xc >> yc >> h >> r) {
		double bottom = min((double) 0.0, h);
		double top = max((double) 0.0, h);

		bool seeBottom = 0, seeTop = 0;

		int n; cin >> n;
		vector< pair<double,double> > all;
		FOR(i,1,n) {
			double x, y, z;
			cin >> x >> y >> z;

			if (cmp(z, bottom) < 0) seeBottom = 1;
			if (cmp(z, top) > 0) seeTop = 1;

			double d = sqrt(sqr(x - xc) + sqr(y - yc));
			if (cmp(d, r) > 0) {
				double alpha = refine(atan2(x-xc, y-yc));
				double eye = acos(r / d);

				double from = alpha - eye;
				double to = alpha + eye;

				if (cmp(from, 0) < 0) {
					all.push_back(make_pair(2*PI + from, 2*PI));
					from = 0.0;
				}
				if (cmp(to, 2*PI) > 0) {
					all.push_back(make_pair(0, to - 2*PI));
					to = 2*PI;
				}
				all.push_back(make_pair(from, to));
			}
		}

		double covered = get(all);
		double res = covered * r * h;
		if (seeBottom) res += PI * r * r;
		if (seeTop) res += PI * r * r;

		cout << (fixed) << setprecision(9) << res << endl;
	}
}
