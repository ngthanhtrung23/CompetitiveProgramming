
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
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
using namespace std;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
int cnt[25];
int NP, k;
ll bound;
vector<int> a;

void attempt(int cur, ll prod) {
    if (cur == NP) {
        a.push_back(prod);
        return ;
    }

    while (prod <= bound) {
        attempt(cur+1, prod);
        prod *= primes[cur];
    }
}

void gen() {
    a.clear();
    bound = 2LL * k * k;
    attempt(0, 1);
}

int main() {
    srand(7777);
    while (cin >> k) {
        ll bound = 2LL * k * k;
        FOR(np,2,10) {
            bool foundSolution = false;
            NP = np;
            gen();

            if (a.size() < k) continue;

            while (true) {
                memset(cnt, 0, sizeof cnt);
                REP(p,np) {
                    REP(i,k) if (a[i] % primes[p] == 0) cnt[p]++;
                }

                bool ok = true;
                REP(i,NP) if (cnt[i] && cnt[i] < (k+1)/2) { ok = false; break; }

                if (ok) {
                    REP(i,k) cout << a[i] << ' ';
                    cout << endl;
                    foundSolution = true;
                    break;
                }
                random_shuffle(a.begin(), a.end());
            }

            if (foundSolution) break;
        }
    }
    return 0;
}
