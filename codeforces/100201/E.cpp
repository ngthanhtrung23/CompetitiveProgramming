
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

ll f[20][200][2], g[20][200];
vector<int> bound;

vector<int> getDigits(ll n) {
    vector<int> res;
    while (n > 0) {
        res.push_back(n % 10);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int digitSum(ll n) {
    int res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int getSum(vector<int>& pref) {
    int res = 0;
    for(int x : pref) res += x;
    return res;
}

void getF(vector<int>& pref) { // 20 * 100 * 10 = 20,000
    memset(f, 0, sizeof f);

    int cur = SZ(pref);
    int sum = getSum(pref), lower = 0;
    REP(i,SZ(pref)) {
        int x = pref[i];

        if (!lower) {
            if (x > bound[i]) return ; // bad prefix!
            if (x < bound[i]) lower = 1;
        }
    }

    f[cur][sum][lower] = 1;

    FOR(i,cur,SZ(bound)-1)
        FOR(sum,0,i*9)
        REP(lower,2) {
            int t = f[i][sum][lower];

            if (t) {
                REP(add,10)
                if (i || add)
                if (lower || add <= bound[i]) {
                    int sum2 = sum + add;
                    int lower2 = lower || add < bound[i];

                    f[i+1][sum2][lower2] += f[i][sum][lower];
                }
            }
        }
}

void getG(vector<int>& pref) {
    memset(g, 0, sizeof g);
    int cur = SZ(pref);
    g[cur][getSum(pref)] = 1;
    FOR(i,cur,SZ(bound)-2)
        FOR(sum,0,i*9)
        if (g[i][sum]) {
            REP(add,10) if (i || add)
                g[i+1][sum + add] += g[i][sum];
        }
}

ll h[222];
void countNumbers(vector<int>& pref) {
    getF(pref);
    getG(pref);

    FOR(sum,0,200) {
        h[sum] = f[SZ(bound)][sum][1];
        FOR(len,SZ(pref),SZ(bound)-1)
            h[sum] += g[len][sum];
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("grlex.in", "r", stdin);
    freopen("grlex.out", "w", stdout);

    ll n, k;
    while (cin >> n >> k) {
        ++n; // so now we consider only numbers less than n

        bound = getDigits(n);
//        PR0(bound, SZ(bound));
        vector<int> pref;

        countNumbers(pref);

//        PR0(h,12);

        // Part 1: Find position of K
        auto t = getDigits(k);
        ll res = 0;
        // the numbers with digitSum < digitSum(K):
        FOR(sum,0,digitSum(k)-1)
            res += h[sum];
//        cout << "digitSum < digitSum(k) --> " << res << endl;
        // the numbers with digitSum = digitSum(K)
        // numbers which are prefix of K:
        int trailingZero = 0;
        while (t[SZ(t)-1-trailingZero] == 0) ++trailingZero;
        res += trailingZero;
//        cout << "prefix(k) --> " << res << endl;
        // numbers with 1 digit different from K
        int digitSum_k = digitSum(k);
        FOR(equal,0,SZ(t)-1) {
            FOR(bad,0,t[equal]-1) if (equal || bad) {
                pref.clear();
                REP(i,equal) pref.push_back(t[i]);
                pref.push_back(bad);

                countNumbers(pref);
                res += h[digitSum_k];
            }
        }
        cout << res << endl;

        // Part 2: Find k-th number
        ++k; // allow number 0
        pref.clear();
        countNumbers(pref);

        int requiredSum = -1;
        FOR(sum,0,200) {
            if (h[sum] >= k) {
                requiredSum = sum;
                break;
            }
            else k -= h[sum];
        }
//        DEBUG(requiredSum);
//        DEBUG(k);

        int curSum = 0;
        REP(i,SZ(bound)) {
            FOR(cur,0,9) if (i || cur) {
                pref.push_back(cur);

                countNumbers(pref);
                if (h[requiredSum] >= k) {
                    curSum += cur;
                    break;
                }
                else {
                    k -= h[requiredSum];
                    pref.pop_back();
                }
            }
            if (k == 1 && curSum == requiredSum) {
                for(int x : pref) cout << x;
                cout << endl;
                break;
            }
            else if (curSum == requiredSum) --k;
        }
    }
}

