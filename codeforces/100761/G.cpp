#include <bits/stdc++.h>
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
    return scanf("%d", &x);
}

const int MV = 1111;
int c, k, a[MV][MV], norma[MV][MV];
int id[MV];

void normalize(int a[]) {
    REP(i,MV) {
        a[i+1] += a[i] / 8;
        a[i] %= 8;
    }
}

void add(int a[], int b[], int c[]) {
    memset(c, 0, sizeof c);
    REP(i,MV) c[i] = a[i] + b[i];
    normalize(c);
}
bool lowerEqual(int a[], int b[]) {
    FORD(i,MV-1,0) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return true;
}
bool lower(int a[], int b[]) {
    FORD(i,MV-1,0) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

int cmp(int a, int b) {
    return lower(norma[b], norma[a]);
}

int sum[MV], temp[MV], need[MV];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(c) == 1 && GI(k) == 1) {
        memset(a, 0, sizeof a);
        memset(norma, 0, sizeof norma);
        FOR(i,1,c) {
            REP(j,k) GI(a[i][j]);
            REP(j,k) norma[i][j] = a[i][j];
            normalize(norma[i]);
        }
        FOR(i,1,c) id[i] = i;
        sort(id+1, id+c+1, cmp);
//        FOR(tmp,1,c) {
//            int i = id[tmp];
//            PR0(norma[i], 10);
//        }

        memset(need, 0, sizeof need);
        need[k] = 1;

        memset(sum, 0, sizeof sum);
        FOR(tmp,1,c) { int i = id[tmp];
            add(norma[i], sum, temp);
            memcpy(sum, temp, sizeof temp);

            if (lowerEqual(need, sum)) {
                vector< pair<int, pair<int,int> > > res;
                int ans = tmp;
                FORD(bit,k,0) {
                    FOR(tmp,1,ans) {
                        int i = id[tmp];

                        int used = min(a[i][bit], need[bit]);
                        if (used) {
                            res.push_back(make_pair(i, make_pair(bit, used)));
                            need[bit] -= used;
                        }
                        if (need[bit] == 0) break;
                    }
                    if (bit == 0) assert(need[bit] == 0);

                    need[bit-1] += 8 * need[bit];
                    need[bit] = 0;
                }
                REP(bit,MV) assert(need[bit] == 0);
                printf("%d\n", SZ(res));
                for(auto p : res) {
                    printf("%d %d %d\n", p.first, p.second.first, p.second.second);
                    assert(a[p.first][p.second.first] >= p.second.second);
                }
                return 0;
            }
        }
    }
    puts("NO SOLUTION");
}
