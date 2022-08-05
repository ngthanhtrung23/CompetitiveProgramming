#include "bits/stdc++.h"
#include "grader.h"
double sqr(double x) { return x * x; }

constexpr int N_LANGS = 56;
constexpr int MOD = 90901;

int hash(int c1, int c2) {
    return ((c1<<16LL) + c2) % MOD;
}
int hash(int c1, int c2, int c3) {
    return ((c1<<32LL) + (c2<<16LL) + c3) % MOD;
}
int hash(int c1, int c2, int c3, int c4) {
    return ((c1<<48LL) + (c2<<32LL) + (c3<<16LL) + c4) % MOD;
}

struct Language {
    int cnt[4][MOD];
    int total_chars;

    Language() : total_chars(1) {  // avoid division by 0
        memset(cnt, 0, sizeof cnt);
    }

    void add(const std::vector<int>& input) {
        total_chars += input.size();
        for (int i = 0; i + 3 < (int) input.size(); ++i) {
            cnt[0][input[i]] += 1;
            cnt[1][hash(input[i], input[i+1])] += 1;
            cnt[2][hash(input[i], input[i+1], input[i+2])] += 1;
            cnt[3][hash(input[i], input[i+1], input[i+2], input[i+3])] += 1;
        }
    }
};
std::array<Language, N_LANGS> languages;

// Compute "difference" between 2 languages, using sum of square distance
double difference(const std::array<std::set<int>, 4>& chars, const Language& a, const Language& b) {
    double sum = 0.0;
    double weight[4] = {1.0, 4.0, 9.0, 16.0};
    for (int t = 0; t < 4; ++t) {
        for (int c : chars[t]) {
            double fa = a.cnt[t][c] / (double) a.total_chars;
            double fb = b.cnt[t][c] / (double) b.total_chars;
            sum += sqr(fa - fb) * weight[t];
        }
    }
    return sum;
}

void solve(const std::vector<int>& input) {
    Language cur; cur.add(input);
    std::array<std::set<int>, 4> chars;

    for (int i = 0; i + 1 < (int) input.size(); ++i) {
        chars[0].insert(input[i]);
        chars[1].insert(hash(input[i], input[i+1]));
        chars[2].insert(hash(input[i], input[i+1], input[i+2]));
        chars[3].insert(hash(input[i], input[i+1], input[i+2], input[i+3]));
    }

    // Find language with smallest "difference"
    std::pair<double, int> best_lang {1e100, -1};
    for (int lang_id = 0; lang_id < N_LANGS; ++lang_id) {
        double diff = difference(chars, cur, languages[lang_id]);
        best_lang = std::min(best_lang, {diff, lang_id});
    }

    // Answer with our best language, and get the correct language from judge
    int res = language(best_lang.second);

    // Update correct language
    languages[res].add(input);
}

void excerpt(int* input) {
    auto v = std::vector<int> (input, input + 100);
    solve(v);
}
