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

string dirName[4] = {"LEFT", "UP", "RIGHT", "DOWN"};

void print(string s) {
    printf("%s\n", s.c_str());
    fflush(stdout);
}

char res[111];

#undef int
int main() {
#define int long long
    int dir = 2;
    while (true) {
        // try to find a safe dir
        while (true) {
            print("LOOK " + dirName[dir]);
            scanf("%s", res);
            if (strcmp(res, "SAFE") == 0) break;

            dir = (dir + 1) % 4;
        }

        print("GO " + dirName[dir]);
        scanf("%s", res);
        if (strcmp(res, "YES") == 0) break;

        dir = (dir + 3) % 4;
    }
}
