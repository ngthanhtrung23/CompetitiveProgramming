#include <bits/stdc++.h>
#include <chrono>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {
    return uniform_int_distribution<long long> (l, r)(rng);
}

using NumT = int;
void std_sort(std::vector<NumT>& arr) {
    std::sort(arr.begin(), arr.end());
}

void counting_sort(std::vector<NumT>& arr) {
    const int FULL_MASK = (1<<16) - 1;
    auto get_low = [] (NumT x) { return x & FULL_MASK; };
    auto get_high = [] (NumT x) { return x >> 16; };

    std::vector<int> cnt_low(1<<16, 0);  // frequencies of low bits
    std::vector<int> cnt_high(1<<16, 0); // frequencies of high bits
    for (auto x : arr) {
        cnt_low[get_low(x)]++;
        cnt_high[get_high(x)]++;
    }
    std::partial_sum(cnt_low.begin(), cnt_low.end(), cnt_low.begin());
    std::partial_sum(cnt_high.begin(), cnt_high.end(), cnt_high.begin());

    int n = arr.size();
    std::vector<NumT> tmp(n);            // stores temporary sort result

    // 1st pass: sort all numbers according to low bits
    // e.g. if we sort using last 2 bits (instead of 16 bits)
    // [8, 7, 10, 2, 4]
    //
    // -> in binary:
    // [1000, 0111, 1010, 0010, 0100]
    //
    // -> sort low bits:
    // [1000, 0100, 1010, 0010, 0111]
    //
    // -> in base 10:
    // [8, 4, 10, 2, 7]
    for (int i = n-1; i >= 0; --i) {
        tmp[--cnt_low[get_low(arr[i])]] = arr[i];
    }

    // 2nd pass: sort high bits
    for (int i = n-1; i >= 0; --i) {
        arr[--cnt_high[get_high(tmp[i])]] = tmp[i];
    }
}

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

template<typename F>
void benchmark(F func, std::vector<NumT> &arr, const string& name) {
    auto t1 = high_resolution_clock::now();
    func(arr);
    auto t2 = high_resolution_clock::now();

    assert(std::is_sorted(arr.begin(), arr.end()));
    duration<double, std::milli> ms_double = t2 - t1;
    cout << name << "\t\t: " << ms_double << endl;
}

int main(int _, char* argv[]) {
    const int N = atoi(argv[1]);
    std::vector<NumT> tmp(N);
    for (int i = 0; i < N; ++i) tmp[i] = get_rand(0, INT_MAX);

    std::vector<NumT> arr1 = tmp;
    benchmark(std_sort, arr1, "std::sort");

    std::vector<NumT> arr2 = tmp;
    benchmark(counting_sort, arr2, "count_rr");
}
