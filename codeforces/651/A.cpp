#include <iostream>
using namespace std;
 
int main() {
	int a, b;
	while (cin >> a >> b) {
		int res = 0;
		while (a > 0 && b > 0 && a + b > 2) {
			++res;
			if (a < b) a += 1, b -= 2;
			else b += 1, a -= 2;
		}
		cout << res << endl;
	}
	return 0;
}
