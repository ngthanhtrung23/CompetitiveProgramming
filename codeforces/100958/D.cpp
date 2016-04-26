
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

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
vector<int> bad[MN];
int h, w, n;

deque<int> odd, even;

void print() {
    REP(i,SZ(odd)) {
        printf("%lld %lld ", odd[i], even[i]);
    }
    puts("");
}

int res[MN];

#undef int
int main() {
#define int long long
    while (GI(h) == 1 && GI(w) == 1 && GI(n) == 1) {
        FOR(i,1,h) bad[i].clear();
        while (n--) {
            int a, b; GI(a); GI(b);
            bad[a].push_back(b);
        }
        while (!odd.empty()) odd.pop_back();
        while (!even.empty()) even.pop_back();

        FOR(i,1,w) {
            if (i % 2 == 1) odd.push_back(i);
            else even.push_back(i);
        }
//        print();

        FOR(i,1,h) {
            if (i % 2 == 1) {
                swap(odd, even);
            }
            else {
                int first = odd.front(); odd.pop_front();
                int last = even.back(); even.pop_back();

                swap(even, odd);
                odd.push_front(first);
                even.push_back(last);
            }

            for(auto x : bad[i]) {
                if (x % 2 == 0) {
                    int u = even[x/2 - 1];
                    int v = odd[x / 2];

                    even[x/2 - 1] = v;
                    odd[x / 2] = u;
                }
                else {
                    int u = odd[x/2];
                    int v = even[x/2];

                    odd[x/2] = v;
                    even[x/2] = u;
                }
            }

//            DEBUG(i);
//            print();
        }

        int pos = 0;
        REP(i,SZ(odd)) {
            res[odd[i]] = ++pos;
            res[even[i]] = ++pos;
        }
        FOR(i,1,w) printf("%lld ", res[i]); puts("");
    }
}
