// Author: dolphinigle

#include <vector>
#include <list>
#include <map>
#include <set>

#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <assert.h>

#define FORN(X,Y) for (int (X) = 0;(X) < (Y);++(X))
#define REP(X,Y,Z) for (int (X) = (Y);(X) < (Z);++(X))

#define SZ(Z) ((int)(Z).size())
#define ALL(W) (W).begin(), (W).end()
#define PB push_back

#define MP make_pair
#define A first
#define B second

#define INF 1023123123
#define EPS 1e-11

#define MX(Z,Y) Z = max((Z),(Y))
#define MN(X,Y) X = min((X),(Y))

#define FORIT(X,Y) for(typeof((Y).begin()) X = (Y).begin();X!=(Y).end();X++)

using namespace std;

typedef long long ll;
typedef double db;
typedef vector<int> vint;

vector<int> Sieve(int abc) {
	vector<int> sieveans;
	abc++;
	sieveans.reserve(abc);
	FORN(i,abc) sieveans.push_back(1);
	for (int i = 2;i * i < abc;i = (i == 2)?3:(i + 2)) {
		for (int j = i + i;j < abc;j += i) {
			sieveans[j] = 0;
			}
		}
	sieveans[0] = sieveans[1] = 0;
	return sieveans;
	}

//generate all prime number lower than or equal to abc;
vector<int> GeneratePrime(int abc) {
	vector<int> stable = Sieve(abc);
	vector<int> returnvalue;
	for (int i = 0;i < (int)stable.size();i++) {
		if (stable[i]) returnvalue.push_back(i);
		}
	return returnvalue;
	}

int dp[105000];
int factors[105000];
int primes[105000];

int main() {

  int n;
  cin >> n;
  vector<int> rawprimes = GeneratePrime(102000);
  int np = SZ(rawprimes);
  FORN(i, np) primes[i] = rawprimes[i];
  FORN(i, n) {
    int x;
    scanf("%d", &x);
    int nf = 0;
    int mx = x;
    int j = 0;
    while (primes[j] * primes[j] <= mx) {
      if (x % primes[j]) ++j;
      else {
        factors[nf] = primes[j];
        ++nf;
        x /= primes[j];
      }
    }
    if (x > 1) {
      factors[nf] = x;
      ++nf;
    }
    int best = 0;
    FORN(i, nf) {
      MX(best, dp[factors[i]]);
    }
    FORN(i, nf) {
      MX(dp[factors[i]], best+1);
    }
  }
  int best = 1;
  FORN(i, 105000) {
    MX(best, dp[i]);
  }
  cout << best << endl;
}