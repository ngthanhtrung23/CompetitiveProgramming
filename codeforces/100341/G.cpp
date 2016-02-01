
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

int a, b, c;
int di[1011], dj[1011], dk[1011], ndir;
int ke[11][11][11];

bool outside(int i, int j, int k) {
    return i < 1 || i > a
        || j < 1 || j > b
        || k < 1 || k > c;
}

void init() {
    ndir = 0;
    FOR(i,-2,2) FOR(j,-2,2) FOR(k,-2,2)
        if (i*i + j*j + k*k == 5) {
            di[ndir] = i;
            dj[ndir] = j;
            dk[ndir] = k;
            ndir++;
        }

    FOR(i,1,a) FOR(j,1,b) FOR(k,1,c) {
        REP(dir,ndir) {
            int ii = i + di[dir];
            int jj = j + dj[dir];
            int kk = k + dk[dir];

            if (!outside(ii, jj, kk)) ++ke[i][j][k];
        }
    }
}

void update(int i, int j, int k, int val) {
    REP(dir,ndir) {
        int ii = i + di[dir];
        int jj = j + dj[dir];
        int kk = k + dk[dir];
        if (outside(ii, jj, kk)) continue;

        ke[ii][jj][kk] += val;
    }
}

int savei[1011], savej[1011], savek[1011];
bool visited[11][11][11];

void dfs(int turn, int i, int j, int k) {
    if (turn > a*b*c) {
        throw 1;
    }

    vector< pair< pair<int,int>, pair<int,int> > > next;
    REP(dir,ndir) {
        int ii = i + di[dir];
        int jj = j + dj[dir];
        int kk = k + dk[dir];
        if (outside(ii, jj, kk)) continue;
        if (visited[ii][jj][kk]) continue;

        next.push_back(make_pair(make_pair(ke[ii][jj][kk], ii), make_pair(jj, kk)));
    }
    sort(next.begin(), next.end());

    for(auto p : next) {
        int ii = p.first.second;
        int jj = p.second.first;
        int kk = p.second.second;

        savei[turn] = ii;
        savej[turn] = jj;
        savek[turn] = kk;

        visited[ii][jj][kk] = 1;
        update(ii, jj, kk, -1);

        dfs(turn + 1, ii, jj, kk);

        visited[ii][jj][kk] = 0;
        update(ii, jj, kk, +1);
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("knight.in", "r", stdin);
    freopen("knight.out", "w", stdout);
    while (cin >> a >> b >> c) {
        if (a == 3 && b == 3 && c == 3) {
            cout << "NO" << endl;
            continue;
        }
        clock_t begin = clock();
        init();
        bool found = true;
        try {
            memset(visited, 0, sizeof visited);
            visited[1][1][1] = true;
            update(1, 1, 1, -1);
            savei[1] = 1;
            savej[1] = 1;
            savek[1] = 1;
            dfs(2, 1, 1, 1);
            cout << "NO" << endl;
            found = false;
        }
        catch (int e) {
            cout << "YES" << endl;
            FOR(t,1,a*b*c) cout << savei[t] << ' ' << savej[t] << ' ' << savek[t] << endl;
        }
        continue;
        clock_t end = clock();
        auto elapsed = (double) (end - begin) / CLOCKS_PER_SEC;
        cerr << a << ' ' << b << ' ' << c << ' ' << found << endl;
        if (elapsed > 0.25) {
            cerr << "-----------------------" << a << ' ' << b << ' ' << c << ' ' << found << endl;
            if (found) {
                cout << a << ' ' << b << ' ' << c << endl;
                FOR(i,1,a*b*c) cout << savei[i] << ' ' << savej[i] << ' ' << savek[i] << endl;
            }
            cout << endl;
        }
    }
}
