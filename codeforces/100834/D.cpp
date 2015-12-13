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

map<string,int> colIndex;
string a[111][22];
string tmp;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	int rowId = 0;
	while (cin >> tmp) {
		REP(i,tmp.length()) if (tmp[i] == ';') tmp[i] = ' ';
		stringstream ss(tmp.c_str());

		if (rowId == 0) {
			int j = 0;
			string t;
			while (ss >> t) {
				colIndex[t] = j;
				++j;
			}
		}
		else {
			int j = 0;
			while (ss >> a[rowId][j]) {
				++j;
			}
		}
		++rowId;
	}
	--rowId;
	cout << "Team;Login;Email;Participants\n";
	FOR(i,1,rowId) {
		cout << a[i][colIndex["Team"]] << ";";
		cout << "team" << setw(3) << setfill('0') << i << " ("
			 << a[i][colIndex["Organization"]] << ", "
			 << a[i][colIndex["City"]] << ");";
		cout << a[i][colIndex["Email"]] << ";";
		cout << a[i][colIndex["Participant1"]] << ','
			 << a[i][colIndex["Participant2"]] << ','
			 << a[i][colIndex["Participant3"]] << endl;
	}
}
