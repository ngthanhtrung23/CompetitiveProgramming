
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
using namespace std;

#define MAXN 100111 // >= 256

const int MN = MAXN;
class DC3Algorithm {
private: 
    int AN;
    int A[3 * MAXN + 100];
    int cnt[MAXN + 1]; 
    int SA[MAXN + 1];

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

    int REVSA[MAXN + 1];
    void compute_reverse_sa() {
        for (int i = 0; i <= AN; i++) REVSA[SA[i]] = i;
    }

    int LCP[MAXN + 1];
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
};

char tmp[MN];
int idOf[MN], res[MN], query_k[MN];
vector<int> query[MN];

int it[MN * 4];

void update(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    if (l == r) {
        ++it[i];
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u);
    update(i<<1|1, mid+1, r, u);
    it[i] = it[i<<1] + it[i<<1|1];
}

int get(int i, int l, int r, int k) {
    assert(it[i] >= k);

    if (l == r) return l;

    int mid = (l + r) >> 1;
    if (it[i<<1] >= k) return get(i<<1, l, mid, k);
    else return get(i<<1|1, mid+1, r, k - it[i<<1]);
}

int main() {
    ios :: sync_with_stdio(false);
    while (gets(tmp) && strlen(tmp) > 0) {

        string s(tmp);
        DC3Algorithm dc3;
        dc3.Construct(s);
        auto sa = dc3.GetSA();

//        DEBUG(s);
//        PR0(sa, sa.size());

        int n = s.length();
        REP(i,n) {
            idOf[sa[i]] = i + 1;
        }

        FOR(len,0,n) query[len].clear();
        int q; scanf("%d\n", &q);
        FOR(i,1,q) {
            int u; scanf("%d%d\n", &u, &query_k[i]);
            res[i] = -1;
            query[u].push_back(i);
        }

        memset(it, 0, sizeof it);
        FORD(len,n,1) {
            int u = idOf[n - len];
//            DEBUG(u);
            update(1, 1, n, u);

            for(int query_id : query[len]) {
                int k = query_k[query_id];
                res[query_id] = get(1, 1, n, k);
            }
        }
//        PR(res, q);

        FOR(i,1,q) printf("%d\n", sa[res[i] - 1] + 1);
    }
}
