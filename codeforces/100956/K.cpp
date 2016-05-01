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

const int MN = 2000111;
string s, t;
class DC3Algorithm {
private: 
    int AN;
    int A[3 * MN + 100];
    int cnt[MN + 1]; 
    int SA[MN + 1];

    void radix_pass(int* A, int AN, int* R, int RN, int* D) {
        memset(cnt, 0, sizeof(int) * (AN + 1));
        int* C = cnt + 1;
        for (int i = 0; i < RN; i++) ++C[A[R[i]]];
        for (int i = -1, v = 0; i <= AN && v < RN; v += C[i++]) swap(v, C[i]);
        for (int i = 0; i < RN; i++) D[C[A[R[i]]]++] = R[i];
    }

    void suffix_array(int* A, int AN) {
        if (!AN) 
            SA[0] = 0;
        else if (AN == 1) {
            SA[0] = 1;
            SA[1] = 0;
            return;
        }
        
        int RN = 0;
        int* SUBA = A + AN + 2;
        int* R = SUBA + AN + 2;
        for (int i = 1; i < AN; i += 3) SUBA[RN++] = i;
        for (int i = 2; i < AN; i += 3) SUBA[RN++] = i;
        A[AN + 1] = A[AN] = -1;
        radix_pass(A + 2, AN - 2, SUBA, RN, R);
        radix_pass(A + 1, AN - 1, R, RN, SUBA);
        radix_pass(A + 0, AN - 0, SUBA, RN, R);

        int resfix, resmul, v;
        if (AN % 3 == 1) {
            resfix = 1;
            resmul = RN >> 1;
        }
        else {
            resfix = 2;
            resmul = RN + 1 >> 1;
        }
        for (int i = v = 0; i < RN; i++) {
            v += i && (A[R[i - 1] + 0] != A[R[i] + 0] || A[R[i - 1] + 1] != A[R[i] + 1] || A[R[i - 1] + 2] != A[R[i] + 2]);
            SUBA[R[i] / 3 + (R[i] % 3 == resfix) * resmul] = v;
        }

        if (v + 1 != RN) {
            suffix_array(SUBA, RN);
            SA[0] = AN;
            for (int i = 1; i <= RN; i++) 
                SA[i] = SA[i] < resmul ? 3 * SA[i] + (resfix==1?2:1) : 3 * (SA[i] - resmul) + resfix;
        }
        else {
            SA[0] = AN;
            memcpy(SA + 1, R, sizeof(int) * RN);
        }

        int NMN = RN; 
        for (int i = RN = 0; i <= NMN; i++) 
            if (SA[i] % 3 == 1) 
                SUBA[RN++] = SA[i] - 1;
        
        radix_pass(A, AN, SUBA, RN, R);

        for (int i = 0; i <= NMN; i++) 
            SUBA[SA[i]] = i;

        int ii = RN - 1;
        int jj = NMN;
        int pos;
        for (pos = AN; ii >= 0; pos--) {
            int i = R[ii];
            int j = SA[jj];
            int v = A[i] - A[j];
            if (!v) 
                if (j % 3 == 1) 
                    v = SUBA[i + 1] - SUBA[j + 1];
                else {
                    v = A[i + 1] - A[j + 1];
                    if (!v) v = SUBA[i + 2] - SUBA[j + 2];
                }            
            SA[pos] = v < 0 ? SA[jj--] : R[ii--];
        }
    }

    void prep_string(string s) {
        int v = 0;
        AN = s.length();
        memset(cnt, 0, 256 * sizeof(int));
        for (int i = 0; i < AN; i++) cnt[s[i]]++;
        for (int i = 0; i < 256; i++) cnt[i] = cnt[i] ? v++ : -1;
        for (int i = 0; i < AN; i++) A[i] = cnt[s[i]];
    }

    int REVSA[MN + 1];
    void compute_reverse_sa() {
        for (int i = 0; i <= AN; i++) REVSA[SA[i]] = i;
    }

    int LCP[MN + 1];
    void compute_lcp() {
        int len = 0;
        for (int i = 0; i < AN; i++, len = max(0, len - 1)) {
            int s = REVSA[i];
            int j = SA[s - 1];
            for (; i + len < AN && j + len < AN && A[i + len] == A[j + len]; len++);
            LCP[s] = len;
        }
    }
    
public:
    
    void Construct(string s) {
        prep_string(s.c_str());
        suffix_array(A, AN);
        compute_reverse_sa();
        compute_lcp();
    }
    
    vector<int> GetSA() {
        vector<int> ret; ret.clear();
        for (int i = 1; i <= AN; i++)
            ret.push_back(SA[i]);
        return ret;
    }
    
    vector<int> GetLCP() {
        vector<int> ret; ret.clear();
        for (int i = 1; i <= AN; i++)
            ret.push_back(LCP[i]);
        return ret;
    }
} dc3;

const int MAXLOG = 22;
int table[MAXLOG][MN];
int numlog[MN];
int N;
int a[MN];

void buildTable() {
    numlog[1] = 0;
    for (int i = 2; i <= N; i++)
        numlog[i] = numlog[i / 2] + 1;

    for (int i = 0; i <= numlog[N]; i++) {
        int curlen = 1 << i;
        for (int j = 1; j <= N; j++) {
            if (i == 0) {
                table[i][j] = a[j];
                continue;
            }
            table[i][j] = min(table[i - 1][j], table[i - 1][j + curlen / 2]);
        }
    }
}

int getmin(int l, int r) {
    int curlog = numlog[r - l + 1];
    return min(table[curlog][l], table[curlog][r - (1 << curlog) + 1]); 
}

int from[MN], l[MN], r[MN];

int getLCP(int i, int j) {
    if (i > j) swap(i, j);
    return getmin(i+1, j);
}

int ls, lt;
int f(int l, int r) {
    return r - l - max(l, ls - r - 1) + 1;
}

int savei, savej;

void update(int i, int j) {
    if (savei < 0 || f(i, j) > f(savei, savej)
            || (f(i, j) == f(savei, savej) && make_pair(i, j) < make_pair(savei, savej))) {
        savei = i;
        savej = j;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> s >> t) {
        ls = SZ(s);
        lt = SZ(t);
        string all = s + "#" + t;
        dc3.Construct(all);

        int sep = all.find('#');
        vector<int> SA = dc3.GetSA();
        vector<int> LCP = dc3.GetLCP();

        REP(id,SZ(SA)) {
//            DEBUG(all.substr(SA.SA[id]));

            a[id] = LCP[id];

            int i = SA[id];
            if (i == sep) from[id] = -1;
            else if (i < sep) from[id] = 0;
            else from[id] = 1;
        }

        N = SZ(SA);
        a[N] = 0;
        buildTable();

        l[0] = 0;
        FOR(i,1,N) {
            if (from[i] == 1) l[i] = i;
            else l[i] = l[i-1];
        }
        r[N] = N;
        FORD(i,N-1,0) {
            if (from[i] == 1) r[i] = i;
            else r[i] = r[i+1];
        }

        savei = -1, savej = -1;
        REP(id,N) if (from[id] == 0) {
            int i = SA[id];

            int u = l[id];
            if (u > 0) {
                int len = getLCP(u, id);

                if (len > 0) {
                    int j = i + len - 1;
                    update(i, j);
                }
            }

            int v = r[id];
            if (v < N) {
                int len = getLCP(id, v);

                if (len > 0) {
                    int j = i + len - 1;
                    update(i, j);
                }
            }
        }
        cout << savei << ' ' << savej << endl;
    }
}
