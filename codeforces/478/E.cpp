#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define ll long long
#define left left_
#define right right_
ll n, k;
vector< pair<ll, ll> > left, rightInc, rightDec;
const int MAX = 9999999;

int lastCmp = 0;
bool isWavy(ll n) {
    int lastDigit = n % 10; n /= 10; lastCmp = 0;
    while (n) {
        int curDigit = n % 10; n /= 10;
        if (curDigit == lastDigit) return false;

        int curCmp = (curDigit > lastDigit) ? 1 : -1;

        if (curCmp == lastCmp) return false;
        lastDigit = curDigit;
        lastCmp = curCmp;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        left.clear(); rightInc.clear(); rightDec.clear();
        bool foundSolution = false;
        FOR(i,1,MAX) {
            if (isWavy(i)) {
                if (i % n == 0) {
                    --k;
                    if (k == 0) {
                        cout << i << endl;
                        foundSolution = true;
                        break;
                    }
                    // cout << i << ' ' << i % n << endl;
                }
                if (i >= MAX / 10) {
                    if (lastCmp == 1) rightDec.push_back(make_pair(i % n, i));
                    else rightInc.push_back(make_pair(i % n, i));
                }
                else if (i >= MAX / 100 && lastCmp == 1) rightInc.push_back(make_pair(i % n, i));
                left.push_back(make_pair(i % n, i));
            }
        }
        sort(rightInc.begin(), rightInc.end());
        sort(rightDec.begin(), rightDec.end());
        if (foundSolution) continue;
        // DEBUG(left.size());
        // cout << "left = "; REP(i,20) cout << left[i].second << ' '; cout << " ... "; FOR(i,left.size()-10,left.size()-1) cout << left[i].second << ' '; cout << endl;
        // DEBUG(rightInc.size());
        // cout << "rightInc = "; REP(i,20) cout << rightInc[i].second << ' '; cout << " ... "; FOR(i,rightInc.size()-10,rightInc.size()-1) cout << rightInc[i].second << ' '; cout << endl;
        // DEBUG(rightDec.size());
        // cout << "rightDec = "; REP(i,20) cout << rightDec[i].second << ' '; cout << " ... "; FOR(i,rightDec.size()-10,rightDec.size()-1) cout << rightDec[i].second << ' '; cout << endl;
        
        ll found = 0;
        REP(i,left.size()) {
            ll xmod = (left[i].first * 10000000LL) % n;
            ll ymod = (n - xmod) % n;

            int leftLastDigit = left[i].second % 10;
            int leftPrevDigit = (left[i].second % 100) / 10;

            if (left[i].second < 10 || leftPrevDigit < leftLastDigit) {
                long long lb = 0 * 1000000LL, ub = (leftLastDigit) * 1000000LL - 1;
                auto from = lower_bound(rightInc.begin(), rightInc.end(), make_pair(ymod, lb));
                auto to = lower_bound(rightInc.begin(), rightInc.end(), make_pair(ymod, ub));

                if (from != rightInc.end() && from->first == ymod && lb <= from->second && from->second <= ub) {
                    int cur = to - from;
                    if (cur >= k) {
                        cout << (left[i].second * 10000000LL) + (from + k - 1)->second << endl;
                        foundSolution = true;
                        break;
                    }
                    else k -= cur;
                }
            }
            if (left[i].second < 10 || leftPrevDigit > leftLastDigit) {
                long long lb = (leftLastDigit + 1) * 1000000LL, ub = 10 * 1000000LL;
                auto from = lower_bound(rightDec.begin(), rightDec.end(), make_pair(ymod, lb));
                auto to = lower_bound(rightDec.begin(), rightDec.end(), make_pair(ymod, ub));

                if (from != rightDec.end() && from->first == ymod && lb <= from->second && from->second <= ub) {
                    int cur = to - from;
                    if (cur >= k) {
                        cout << (left[i].second * 10000000LL) + (from + k - 1)->second << endl;
                        foundSolution = true;
                        break;
                    }
                    else k -= cur;
                }
            }
            if (foundSolution) break;
        }
        if (!foundSolution) cout << -1 << endl;
    }
    return 0;
}
