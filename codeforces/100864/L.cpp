
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

map<string,int> id;

int getId(string s) {
    if (id.count(s)) return id[s];
    int t = SZ(id) + 1;
    id[s] = t;
    return t;
}

pair< pair<int,int>, int> toPair(int a, int b, int c) {
    return make_pair(make_pair(a, b), c);
}

void min_rotate(int x[]) {
    auto a = toPair(x[0], x[1], x[2]);
    auto b = toPair(x[1], x[2], x[0]);
    auto c = toPair(x[2], x[0], x[1]);

    auto t = min(min(a, b), c);
    x[0] = t.first.first;
    x[1] = t.first.second;
    x[2] = t.second;
}

void get(string a, string b, string c, int x[]) {
    x[0] = getId(a);
    x[1] = getId(b);
    x[2] = getId(c);

    min_rotate(x);
}

int x[1011][3];

map< pair<pair<int,int>, int>, int > cnt;
int col[7];

pair< pair<int,int>, int> init(int t[], int x, int y, int z) {
    t[0] = col[x];
    t[1] = col[y];
    t[2] = col[z];
    min_rotate(t);
    return toPair(t[0], t[1], t[2]);
}

int t[3];
bool check(int x, int y, int z) {
    auto p = init(t, x, y, z);
    return cnt.count(p) && cnt[p] > 0;
}
void update(int x, int y, int z, int val) {
    auto p = init(t, x, y, z);
    cnt[p] += val;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("laboratory.in", "r", stdin);
    freopen("laboratory.out", "w", stdout);
    int n;
    while (cin >> n) {
        id.clear();
        cnt.clear();
        FOR(i,1,n) {
            string a, b, c; cin >> a >> b >> c;
            get(a, b, c, x[i]);
//            PR0(x[i], 3);
            auto p = toPair(x[i][0], x[i][1], x[i][2]);

            cnt[p] += 1;
        }
        try {
            FOR(a,1,n) FOR(b,a+1,n) REP(rota,1) REP(rotb,3) {
                col[1] = x[a][rota];
                col[2] = x[a][(rota + 1) % 3];
                col[3] = x[a][(rota + 2) % 3];

                col[4] = x[b][rotb];
                col[5] = x[b][(rotb + 1) % 3];
                col[6] = x[b][(rotb + 2) % 3];

                bool diff = true;
                FOR(i,1,6) FOR(j,i+1,6) if (col[i] == col[j]) diff = false;
                if (!diff) continue;

                auto aa = toPair(x[a][0], x[a][1], x[a][2]);
                auto bb = toPair(x[b][0], x[b][1], x[b][2]);
                cnt[aa] -= 1;
                cnt[bb] -= 1;

                bool can = true;
                int t[3];
                pair< pair<int,int>, int> p;
                // 142
                if (check(1,4,2)) {
                    update(1,4,2,-1);
                    if (check(1,5,4)) {
                        update(1,5,4,-1);
                        if (check(1,3,5)) {
                            update(1,3,5,-1);
                            if (check(2,4,6)) {
                                update(2,4,6,-1);
                                if (check(3,2,6)) {
                                    update(3,2,6,-1);
                                    if (check(5,3,6)) {
                                        throw 1;
                                    }
                                    update(3,2,6,+1);
                                }
                                update(2,4,6,+1);
                            }
                            update(1,3,5,+1);
                        }
                        update(1,5,4,+1);
                    }
                    update(1,4,2,+1);
                }

                cnt[aa] += 1;
                cnt[bb] += 1;
            }
            cout << "NO" << endl;
        } catch (int e) {
            cout << "YES" << endl;
        }
    }
}
