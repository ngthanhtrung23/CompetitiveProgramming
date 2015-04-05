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

const int MN = 300111;
const int MAXN = MN;
const int MAXLOG = 22;
int n, a[MN], lg[MN], idOf[MN];

int maxTable[MAXLOG][MAXN], minTable[MAXLOG][MAXN];
int numlog[MAXN];

void buildmaxTable() {
    numlog[1] = 0;
    for (int i = 2; i <= n; i++)
        numlog[i] = numlog[i / 2] + 1;

    for (int i = 0; i <= numlog[n]; i++) {
        int curlen = 1 << i;
        for (int j = 1; j <= n; j++) {
            if (i == 0) {
                maxTable[i][j] = a[j];
                minTable[i][j] = a[j];
                continue;
            }
            maxTable[i][j] = max(maxTable[i - 1][j], maxTable[i - 1][j + curlen / 2]);
            minTable[i][j] = min(minTable[i - 1][j], minTable[i - 1][j + curlen / 2]);
        }
    }
}

int getMax(int l, int r) {
    int curlog = numlog[r - l + 1];
    return max(maxTable[curlog][l], maxTable[curlog][r - (1 << curlog) + 1]); 
}
int getMin(int l, int r) {
    int curlog = numlog[r - l + 1];
    return min(minTable[curlog][l], minTable[curlog][r - (1 << curlog) + 1]);
}

long long res = 0;
int cnt[MN * 2];

void update1(int from, int right, int val) {
    cnt[getMax(from, right) - right + MN] += val;
}

void update2(int from, int right, int val) {
    cnt[getMin(from, right) + right] += val;
}

void solve(int l, int r) {
    if (r - l <= 5) {
        FOR(i,l,r) FOR(j,i,r) {
            if (j - i == getMax(i, j) - getMin(i, j)) {
                ++res;
//                cout << "0: " << i << ' ' << j << endl;
            }
        }
        return ;
    }

    int mid = (l + r) >> 1;
    solve(l, mid-1);
    solve(mid+1, r);

//    DEBUG(mid);
    // both min, max is on left side
    FORD(left,mid,l) {
        int nn = getMin(left, mid);
        int ln = getMax(left, mid);
        int len = ln - nn + 1;

        int right = left + len - 1;
        int realMax = getMax(left, right), realMin = getMin(left, right);
        if (right >= mid && right <= r && realMax == ln && realMin == nn) {
            ++res;
//            cout << "1: " << left << ' ' << right << endl;
        }
    }

    // both min, max is on right side
    FOR(right,mid+1,r) {
        int nn = getMin(mid+1, right);
        int ln = getMax(mid+1, right);
        int len = ln - nn + 1;

        int left = right - len + 1;
        int realMax = getMax(left, right), realMin = getMin(left, right);
        if (left <= mid && left >= l && realMax == ln && realMin == nn) {
            ++res;
//            cout << "2: " << left << ' ' << right << endl;
        }
    }
    
    // min on left, max on right
    int minRight = mid+1, maxRight = mid;
    FORD(left,mid,l) {
        int nn = getMin(left, mid);
        int badLn = getMax(left, mid);
        while (maxRight < r && getMin(mid+1, maxRight+1) > nn) {
            ++maxRight;
            update1(mid+1, maxRight, +1);
        }
        while (minRight <= maxRight && badLn > getMax(mid+1, minRight)) {
            update1(mid+1, minRight, -1);
            ++minRight;
        }
        res += cnt[nn - left + MN];
//        if (cnt[nn - left + MN]) cout << "3: " << left << ' ' << nn << ' ' << cnt[nn - left + MN] << endl;
    }
    while (minRight <= maxRight) {
        update1(mid+1, minRight, -1);
        ++minRight;
    }

    // max on left, min on right
    minRight = mid+1, maxRight = mid;
    FORD(left,mid,l) {
        int ln = getMax(left, mid);
        int badNn = getMin(left, mid);

        while (maxRight < r && getMax(mid+1, maxRight+1) < ln) {
            ++maxRight;
            update2(mid+1, maxRight, +1);
        }
        while (minRight <= maxRight && badNn < getMin(mid+1, minRight)) {
            update2(mid+1, minRight, -1);
            ++minRight;
        }
        res += cnt[left + ln];
//        if (cnt[left + ln]) cout << "4: " << left << ' ' << ln << ' ' << cnt[left + ln] << endl;
    }
    while (minRight <= maxRight) {
        update2(mid+1, minRight, -1);
        ++minRight;
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            scanf("%d", &a[x]);
            idOf[a[x]] = x;
        }
//        PR(a, n);

        buildmaxTable();
        res = 0;
        solve(1, n);
        cout << res << endl;
    }
    return 0;
}

