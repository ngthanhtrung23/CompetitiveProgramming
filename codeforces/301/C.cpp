#include <iostream>
#include <cstdio>
#define FOR(i,a,b) for(int i=(a); i <= (b); ++i)
using namespace std;

int main() {
	FOR(c,'0','8') printf("%c??1??<>%c\n", c, c+1);
	printf("9??1??>>??1??0\n");
	printf("??1??<>1\n");
	FOR(c,'0','9') printf("??0??%c>>%c??0??\n", c, c);
	printf("??0??>>??1??\n");
	FOR(c,'0','9') printf("%c>>%c??0??\n", c, c);
	return 0;
}
