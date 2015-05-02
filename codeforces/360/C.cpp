
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 2011;
const long long MOD = 1e9 + 7;
int n, k;
string s;

// a chunk is a substring t[i..j], such that
//     t[x] = s[x] for i <= x < j
// and t[j] > s[j]
struct Chunk {
    int end, sum, count;
};
vector< Chunk > chunks[MN];
long long f[2][MN][MN];

bool operator < (const Chunk& a, const Chunk& b) {
    return a.sum < b.sum;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        cin >> s;
        s = " " + s;

        memset(f, 0, sizeof f);
        f[0][n+1][0] = 1;

        FOR(i,1,n) chunks[i].clear();
        FOR(i,1,n) FOR(j,i,n) {
            Chunk cur;
            cur.end = j;
            cur.count = 'z' - s[j];
            cur.sum = (j - i + 1) * (n - j + 1);

            if (cur.sum <= k) {
                chunks[i].push_back(cur);
            }
        }
        FOR(i,1,n) sort(chunks[i].begin(), chunks[i].end());

        FOR(sum,0,k) FORD(i,n,1) {
            // use a smaller or equal character
            f[0][i][sum] = (
                    f[0][i+1][sum] * (1 + s[i] - 'a')
                    + f[1][i+1][sum] * (s[i] - 'a')
                    ) % MOD;

            // use a chunk
            for(auto chunk : chunks[i]) {
                if (chunk.sum > sum) break;
                f[1][i][sum] = (f[1][i][sum]
                        + chunk.count * (
                            f[0][chunk.end + 1][sum - chunk.sum] + 
                            f[1][chunk.end + 1][sum - chunk.sum])) % MOD;
            }
        }
//        FORD(i,n,1) {
//            FOR(sum,0,k) cout << f[0][i][sum] + f[1][i][sum] << ' ';
//            cout << endl;
//        }
        cout << (f[0][1][k] + f[1][1][k]) % MOD << endl;
    }
    return 0;
}
