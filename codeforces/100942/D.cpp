#include<bits/stdc++.h>

#define ll long long 
using namespace std;

const long long mil = 1000000;


void cal1(long long L, long long N, long long K) {
	long long ntr;
	
	while(L>0) {
		if (N <= K) break;
		
		if (N % K != 1) {
			ntr = (N + K - 1) / K;
			N -= (2 * ntr - 1);
		} else {
			ntr = N / K;
			N = ntr * (K - 2) + 1; 		
		}
		
		L--;
	}
	
	if (L > 0) N = N - L;
	
	cout << max(N, 0ll) << endl;
}

void cal2(long long L, long long N, long long K) {
	long long ntr;

	while(L > 0) {
		if (N <= K) break;
		
		if (N % K== 1) {
			ntr = N / K;
			N = ntr * (K - 2) + 1;
			L--;
		} else {
			ntr = (N + K - 1) / K;
			if (N <= 2 * ntr + (ntr - 1) * K) {
				L--;
				N -= (2 * ntr - 1);
			} else {
				long long nextN = (ntr - 1) * K + 2;
				long long dif = (N - nextN) / (2 * ntr - 1);
				
				dif = min(dif, L);
				L -= dif;
				N -= (2 * ntr - 1) * dif;
			}			
		}
	}
	
	if (L > 0) {
		N = N - L;
	}
	
	cout << max(0ll, N) << endl;
	return;
}

void cal(long long L, long long N, long long K) {
	if (K == 1) {
		cout << 0 << endl;
		return;
	}
	
	if (K == 2) {
		if (L == 1) cout << 1 << endl;
		else cout << 0 << endl; 
		return; 
	}
	
	if (L <= mil) {
		cal1(L, N, K);
		return;
	}
	
	if (100 * K <= L) {
		cout << 0 << endl;
		return;
	}
	
	cal2(L, N, K);
	return;
}

int main() {
	long long L, N, K;
	cin >> L >> N >> K;
	
	cal(L, N, K);
}