
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <sstream>

#define FOR(i, a, b) for(int i=(a), _b=(b); i<=_b; i++)
#define DOW(i, a, b) for(int i=(a), _b=(b); i>=_b; i--)
#define REP(i, b) for(int i=0; i<b; i++)
#define PB push_back

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

#define MAXN 50111

using namespace std;

int main() {
  ios::sync_with_stdio(0);

  long long l, r;
  while (cin >> l >> r) {
      while (true) {
        long long p2 = 1;
        while (p2*2 <= r) p2 *= 2;

        if (l <= p2-1 && p2 <= r) {
            cout << p2 * 2 - 1 << endl;
            break;
        }
        else {
            l -= p2;
            r -= p2;

            if (r == 0) {
                cout << 0 << endl;
                break;
            }
        }
      }
  }
  
  return 0;
}
