#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define left left_
#define right right_
using namespace std;

const int MN = 1000111;
const long long MOD = 1000000007;

int n, a[MN], pos[MN], left[MN], right[MN];
long long gt[MN];

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x * x % MOD, k >> 1) % MOD;
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long inverse(long long x) {
    return power(x, MOD - 2);
}

long long C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return gt[n] * inverse(gt[k]) % MOD * inverse(gt[n-k]) % MOD;
}

void init() {
    memset(pos, 0, sizeof pos);
    memset(left, 0, sizeof left);
    memset(right, 0, sizeof right);
}

// last >= 1
// we already placed the numbers [1, last]
// these numbers occupy positions [from, to]
// Now we need to place numbers (last, cur]
// Side effect:
// - this method update values of last, from, to

long long place(int& last, int cur, int& from, int& to) {
    if (pos[cur] < from) { // we extend to the left
        // if we extend to the left, we have to stop at the first position
        // which is positive. So left[from] must == pos[cur]

        // numbers = # values we need to fill
        int numbers = cur - last - 1;

        // How many positions we need to fill on left side
        int pos_left = (from - 1) - pos[cur];

        // How many positions we need to fill on right side
        int pos_right = numbers - pos_left;

        from = pos[cur];
        to += pos_right;
        last = cur;
        return C(numbers, pos_left);
    }
    else if (pos[cur] > to) { // we extend to the right
        int numbers = cur - last - 1;
        int pos_right = pos[cur] - 1 - to;
        int pos_left = numbers - pos_right;

        from -= pos_left;
        to = pos[cur];
        last = cur;
        return C(numbers, pos_left);
    }
    else return 0;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    gt[0] = 1; FOR(i,1,100100) {
        gt[i] = gt[i-1] * i % MOD;
    }
    while (cin >> n) {
        init();
        vector<int> x;
        x.push_back(0);
        bool ok = false;
        FOR(i,1,n) {
            cin >> a[i];
            if (a[i]) {
                ok = true;
                pos[a[i]] = i;
                x.push_back(i);
            }
        }
        if (!ok) {
            cout << power(2, n-1) << endl;
            continue;
        }
        x.push_back(n+1);
        REP(i,x.size()) {
            left[x[i]] = x[i];
            right[x[i]] = x[i];
        }
        FOR(i,1,n) if (!left[i]) left[i] = left[i-1];
        FORD(i,n,1) if (!right[i]) right[i] = right[i+1];

        REP(i,x.size()) {
            if (i) left[x[i]] = x[i-1];
            if (i < x.size()-1) right[x[i]] = x[i+1];
        }

//        PR(pos, n);
//        PR(left, n);
//        PR(right, n);

        a[0] = n+2; pos[n+2] = 0;
        a[n+1] = n+1; pos[n+1] = n+1;

        int last = 0, from = -1, to = -1;
        long long res = 0;
        FOR(cur,1,n+1) if (pos[cur] && cur > last) {
            // Now we will add number in range (last, cur]
            if (last == 0) {
                // Choose a position for number 1
                if (cur == 1) {
                    res = 1;
                    last = 1;
                    from = to = pos[1];
                }
                else {
                    int x = left[pos[cur]];
                    int y = right[pos[cur]];
                    int next = cur + 1;
                    while (!pos[next]) ++next;

                    FOR(pos1,x+1,y-1) if (pos1 != pos[cur]) {
                        int a = pos1, b = pos1;
                        int num = 1;
                        long long t = place(num, cur, a, b);
                        t = t * place(num, next, a, b) % MOD;
                        res = (res + t) % MOD;

                        if (t) {from = a; to = b;}
                    }
                    last = next;
                }
            }
            else {
                long long t = place(last, cur, from, to);
                res = res * t % MOD;
            }
        }
        cout << res << endl;
    }
    return 0;
}

