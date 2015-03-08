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
bool isLucky(int n) {
    while (n > 0) {
        if (n % 10 != 4 && n % 10 != 7) return false;
        n /= 10;
    }
    return true;
}

const int MN = 100111;
int n, pos[MN], x[MN];
pair<int,int> a[MN];
vector< pair<int,int> > res;

bool increasing() {
    FOR(i,2,n) if (a[i].first < a[i-1].first) return false;
    return true;
}

void move(int i, int j) {
    swap(x[i], x[j]);
    pos[x[i]] = i;
    pos[x[j]] = j;
    res.push_back(make_pair(i, j));
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d", &a[i].first);
            a[i].second = i;
        }
        if (increasing()) cout << 0 << endl;
        else {
            // Find the first lucky number
            int firstLucky = -1;
            FOR(i,1,n) if (isLucky(a[i].first)) {
                firstLucky = i;
                break;
            }
            if (firstLucky < 0) {
                cout << -1 << endl;
            }
            else {
                sort(a+1, a+n+1);
                FOR(i,1,n) x[a[i].second] = i;
                FOR(i,1,n) pos[x[i]] = i;
//                PR(x, n);
//                PR(pos, n);

                res.clear();

                int firstValue = x[firstLucky];
                FOR(i,1,n) if (i != firstValue) {
                    // make number at position i correct
                    if (x[i] == i) continue;

                    if (firstLucky == i) {
                        firstLucky = pos[i];
                        move(i, pos[i]);
                    }
                    else {
                        move(i, firstLucky);
                        firstLucky = pos[i];
                        move(i, pos[i]);
                    }
                }

                printf("%d\n", res.size());
                for(auto x : res) printf("%d %d\n", x.first, x.second);
            }
        }
    }
    return 0;
}

