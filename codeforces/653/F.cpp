#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int Z = 500100;

struct SuffixArray
{
	string s;
	int n;
	vector <int> sa, rank, tempSa, tempRank, c, lcp, prev;
	
	SuffixArray(string _s) : s(_s) { initialize(); }
	SuffixArray(char _s[], int len) : s(_s, len) { initialize(); }
	
	void initialize()
	{
		n = s.size();
		rank = sa = tempSa = tempRank = lcp = prev = vector <int>(n);
		c = vector <int>(max(266, n));
	}
	
	void countingSort(int shift)
	{
		int C = max(266, n);
		for (int i = 0; i < C; i++) c[i] = 0;
		for (int i = 0; i < n; i++) c[rank[i]]++;
		for (int i = 0, sum = 0 ; i < C; i++) sum += c[i], c[i] = sum - c[i];
		for (int i = 0; i < n; i++) 
			if (sa[i] + shift < n) tempSa[c[rank[sa[i] + shift]]++] = sa[i];
			else tempSa[c[rank[sa[i] + shift - n]]++] = sa[i];
		for (int i = 0; i < n; i++) sa[i] = tempSa[i];
	}
	
	void construct()
	{
		for (int i = 0; i < n; i++) rank[i] = int(s[i]), sa[i] = i;
		for (int shift = 1; shift < n; shift <<= 1)
		{
			countingSort(shift);
			countingSort(0);
			int R = tempRank[sa[0]] = 0;
			for (int i = 1; i < n; i++)
			{
				if (rank[sa[i]] != rank[sa[i - 1]] || rank[(sa[i] + shift) % n] != rank[(sa[i - 1] + shift) % n]) R++;
				tempRank[sa[i]] = R;
			}
			for (int i = 0; i < n; i++) rank[i] = tempRank[i];
		}
	}
	
	void calcLCP()
	{
		for (int i = 0; i < n; i++) prev[sa[i]] = i ? sa[i - 1] : -1;
		for (int i = 0, match = 0; i < n; i++)
			if (prev[i] < 0) lcp[i] = 0;
			else 
			{
				while (s[(i + match) % n] == s[(prev[i] + match) % n]) match++;
				lcp[i] = match;
				if (!match--) match = 0;
			}
	}
};

char s[Z];
int st[Z], last;
vector <int> a[Z + Z];

int calc(const vector <int>&a, int val)
{
	int low = 0, high = a.size() - 1, where = -1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (a[mid] > val) where = mid, low = mid + 1;
		else high = mid - 1;
	}
	return where + 1;
}

int main()
{
    int n;
    scanf("%d\n", &n);
    scanf("%s", s);
    s[n++] = '$';
    SuffixArray SA(s, n);
    SA.construct();
    SA.calcLCP();
    
    for (int i = 0; i <= n + Z; i++) a[i].clear();
    a[Z].push_back(n - 1);
    st[last = 1] = 0;
    
    long long ans = 0;
    for (int i = n - 2, x = 0; i >= 0; i--)
        if (s[i] == ')') st[++last] = ++x, a[x + Z].push_back(i);
        else
        {
            x--;
            while (last && st[last] > x) a[st[last--] + Z].pop_back();
            st[++last] = x; 
            
            ans += calc(a[x + Z], i + SA.lcp[i]);
            a[x + Z].push_back(i);
        }
        
    cout << ans << endl;
}
