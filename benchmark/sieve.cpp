#include <bits/stdc++.h>
#include <chrono>
using namespace std;

const int MAX = 1'000'000'000;
const long long SUM_PRIMES = 24739512092254535LL;

template<typename F>
void benchmark(F func, const string& name) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto t1 = high_resolution_clock::now();
    func();
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;
    cout << name << "\t\t: " << ms_double << endl;
}

// Naive sieve implementation from cp-algorithms {{{
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
void sieve_cp_algorithms() {
    static vector<bool> is_prime(MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= MAX; i++) {
        if (is_prime[i]) {
            for (int j = i*i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }

    long long sum_primes = 0;
    for (int i = 1; i <= MAX; ++i) {
        if (is_prime[i]) sum_primes += i;
    }
    assert(sum_primes == SUM_PRIMES);
}
// }}}
// Naive sieve with bitset {{{
void sieve_bitset() {
    static bitset<MAX + 1> is_prime;
    is_prime.set();

    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i*i <= MAX; i = is_prime._Find_next(i)) {
        if (is_prime[i]) {
            for (int j = i*i; j <= MAX; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    long long sum_primes = 0;
    for (int p = is_prime._Find_first(); p <= MAX; p = is_prime._Find_next(p)) {
        sum_primes += p;
    }
    assert(sum_primes == SUM_PRIMES);
}
// }}}
// Linear sieve from cp-algorithms {{{
// https://cp-algorithms.com/algebra/prime-sieve-linear.html
void linear_sieve_cp_algorithms() {
    const int N = MAX;
    vector<int> lp(N+1);
    vector<int> pr;
    long long sum_primes = 0;

    for (int i=2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
            sum_primes += i;
        }
        for (int j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    assert(sum_primes == SUM_PRIMES);
}
// }}}
// odd sieve with bitset {{{
namespace odd_sieve_bitset {
const int N = 1e9;

uint64_t sieve_mask[N / 64 + 11];

uint64_t ONES[64];  // ONES[i] = 1<<i

inline void mark(uint64_t* s, int bit) { s[bit / 64] |= ONES[bit & 63]; }
inline int test(uint64_t* s, int bit) { return (s[bit / 64] & ONES[bit & 63]) == 0; }

void sieve() {
    for (int i = 0; i < 64; ++i) ONES[i] = 1ULL << i;

    for (unsigned i = 3; i*i <= MAX; i += 2)
        if (test(sieve_mask, i)) {
            unsigned i2 = i + i;
            for (unsigned j = i * i; j < N; j += i2) {
                mark(sieve_mask, j);
            }
        }

    long long sum_primes = 2;
    for (unsigned i = 3; i < N; i += 2)
        if (test(sieve_mask, i)) {
            sum_primes += i;
        }
    assert(sum_primes == SUM_PRIMES);
}
}
// }}}
// Block sieve from cp-algorithms {{{
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html#segmented-sieve
void block_sieve_cp_algorithms() {
    const int n = MAX;
    const int S = 32'000;  // sqrt(N)

    vector<int> primes;
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 2, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    long long sum_primes = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i])
                sum_primes += start + i;
        }
    }
    assert(sum_primes == SUM_PRIMES);
}
// }}}
// Kim Walisch {{{
namespace kim_walisch {
typedef unsigned char byte;

int count = 0; 
void sieve()
{
    const int lim = MAX;
    long long sum_primes = 0;

    int sqrt = std::sqrt(lim);
    int sieve_size = max(sqrt, (1 << 15));
    int segment_size = sieve_size * 16;

    vector<byte> mark(sieve_size);
    vector<byte> is_prime(sqrt + 1, true);
    vector<int> seg_prime;
    vector<int> seg_multi;

    for (int i = 3; i <= sqrt; i += 2)
        if (is_prime[i])
            for (int j = i * i; j <= sqrt; j += i)
                is_prime[j] = false;

    int reset[16];
    for (int i = 0; i < 8; ++i)
        reset[2 * i] = reset[2 * i + 1] = ~(1 << i);

    int s = 3;
    for (int low = 0; low <= lim; low += segment_size)
    {
        fill(mark.begin(), mark.end(), 0xff);
        int high = min(low + segment_size - 1, lim);
        sieve_size = (high - low) / 16 + 1;

        for (; s * s <= high; s += 2)
        {
            if (is_prime[s])
            {
                seg_prime.push_back(s);
                seg_multi.push_back(s * s - low);
            }
        }

        for (size_t i = 0; i < seg_prime.size(); ++i)
        {
            int j = seg_multi[i];
            for (int k = seg_prime[i] * 2; j < segment_size; j += k)
                mark[j >> 4] &= reset[j % 16];

            seg_multi[i] = j - segment_size;
        }

        if (high == lim)
        {
            int bits = 0xff << ((lim % 16) + 1) / 2;
            mark[sieve_size - 1] &= ~bits;
        }
        
        for (int n = 0; n < sieve_size; n++)
        {
            for (int i = 0; i < 8; i++)
                if (mark[n] & (1 << i)) {
                    auto p = low + n * 16 + i * 2 + 1;
                    sum_primes += (p > 1) ? p : 2;
                }
        }
    }
    assert(sum_primes == SUM_PRIMES);
}
}
// }}}
// Block sieve, only odd elements {{{
void block_sieve_odd() {
    long long sum_primes = 2;

    const int S = round(sqrt(MAX));
    vector<char> sieve(S + 1, true);
    vector<array<int, 2>> cp;
    for (int i = 3; i < S; i += 2) {
        if (!sieve[i])
            continue;
        cp.push_back({i, (i * i - 1) / 2});
        for (int j = i * i; j <= S; j += 2 * i)
            sieve[j] = false;
    }
    vector<char> block(S);
    int high = (MAX - 1) / 2;
    for (int low = 0; low <= high; low += S) {
        fill(block.begin(), block.end(), true);
        for (auto &i : cp) {
            int p = i[0], idx = i[1];
            for (; idx < S; idx += p)
                block[idx] = false;
            i[1] = idx - S;
        }
        if (low == 0)
            block[0] = false;
        for (int i = 0; i < S && low + i <= high; i++)
            if (block[i])
                sum_primes += (low + i) * 2 + 1;
    };
    assert(sum_primes == SUM_PRIMES);
}
// }}}

// Segmented sieve with wheel factorization {{{
namespace segmented_sieve_wheel {
const int MAX = 1000000000LL;
const int WHEEL = 3 * 5 * 7 * 11 * 13;
const int N_SMALL_PRIMES = 6536;             // cnt primes less than 2^16
const int SIEVE_SPAN = WHEEL * 64;           // one iteration of segmented sieve
const int SIEVE_SIZE = SIEVE_SPAN / 128 + 1;
 
uint64_t ONES[64];                           // ONES[i] = 1<<i
int small_primes[N_SMALL_PRIMES];            // primes less than 2^16
 
// each element of sieve is a 64-bit bitmask.
// Each bit (0/1) stores whether the corresponding element is a prime number.
// We only need to store odd numbers
// -> 1st bitmask stores 3, 5, 7, 9, ...
uint64_t si[SIEVE_SIZE];
// for each 'wheel', we store the sieve pattern (i.e. what numbers cannot
// be primes)
uint64_t pattern[WHEEL];
 
inline void mark(uint64_t* s, int o) { s[o >> 6] |= ONES[o & 63]; }
inline int test(uint64_t* s, int o) { return (s[o >> 6] & ONES[o & 63]) == 0; }
 
// update_sieve {{{
void update_sieve(int offset) {
    // copy each wheel pattern to sieve
    for (int i = 0, k; i < SIEVE_SIZE; i += k) {
        k = std::min(WHEEL, SIEVE_SIZE - i);
        memcpy(si + i, pattern, sizeof(*pattern) * k);
    }
 
    // Correctly mark 1, 3, 5, 7, 11, 13 as not prime / primes
    if (offset == 0) {
        si[0] |= ONES[0];
        si[0] &= ~(ONES[1] | ONES[2] | ONES[3] | ONES[5] | ONES[6]);
    }
 
    // sieve for primes >= 17 (stored in `small_primes`)
    for (int i = 0; i < N_SMALL_PRIMES; ++i) {
        int j = small_primes[i] * small_primes[i];
        if (j > offset + SIEVE_SPAN - 1) break;
        if (j > offset) j = (j - offset) >> 1;
        else {
            j = small_primes[i] - offset % small_primes[i];
            if ((j & 1) == 0) j += small_primes[i];
            j >>= 1;
        }
        while (j < SIEVE_SPAN / 2) {
            mark(si, j);
            j += small_primes[i];
        }
    }
}
// }}}
 
void sieve() {
    // init small primes {{{
    for (int i = 0; i < 64; ++i) ONES[i] = 1ULL << i;
 
    // sieve to find small primes
    for (int i = 3; i < 256; i += 2) {
        if (test(si, i >> 1)) {
            for (int j = i*i / 2; j < 32768; j += i) mark(si, j);
        }
    }
    // store primes >= 17 in `small_primes` (we will sieve differently
    // for primes 2, 3, 5, 7, 11, 13)
    {
        int m = 0;
        for (int i = 8; i < 32768; ++i) {
            if (test(si, i)) small_primes[m++] = i*2 + 1;
        }
        assert(m == N_SMALL_PRIMES);
    }
    // }}}
 
    // For primes 3, 5, 7, 11, 13: we initialize wheel pattern..
    for (int i = 1; i < WHEEL * 64; i += 3) mark(pattern, i);
    for (int i = 2; i < WHEEL * 64; i += 5) mark(pattern, i);
    for (int i = 3; i < WHEEL * 64; i += 7) mark(pattern, i);
    for (int i = 5; i < WHEEL * 64; i += 11) mark(pattern, i);
    for (int i = 6; i < WHEEL * 64; i += 13) mark(pattern, i);
 
    // Segmented sieve
    long long sum_primes = 2;
    for (int offset = 0; offset < MAX; offset += SIEVE_SPAN) {
        update_sieve(offset);
 
        for (uint32_t j = 0; j < SIEVE_SIZE; j++){
            uint64_t x = ~si[j];
            while (x){
                uint32_t p = offset + (j << 7) + (__builtin_ctzll(x) << 1) + 1;
                if (p > offset + SIEVE_SPAN - 1) break;
                if (p <= MAX) {
                    sum_primes += p;
                }
                x ^= (-x & x);
            }
        }
    }
    assert(sum_primes == SUM_PRIMES);
}
}
// }}}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // benchmark(sieve_cp_algorithms, "cp_algorithms_naive");
    // benchmark(sieve_bitset, "sieve_bitset\t");
    // benchmark(linear_sieve_cp_algorithms, "cp_algorithms_linear");
    benchmark(odd_sieve_bitset::sieve, "odd_sieve_bitset");
    // benchmark(block_sieve_cp_algorithms, "cp_algorithms_block");
    // benchmark(kim_walisch::sieve, "kim_walisch_sieve");
    // benchmark(block_sieve_odd, "block_sieve_odd\t");
    benchmark(segmented_sieve_wheel::sieve, "segmented_sieve_wheel");
    return 0;
}
