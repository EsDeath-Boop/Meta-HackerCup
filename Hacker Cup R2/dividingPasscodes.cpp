#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

using ll = long long;
const ll MOD = 998244353;
const ll PRIMITIVE_ROOT = 3;

static unordered_map<int, vector<ll>> precomputed_totals_cache;
static unordered_map<int, unordered_map<uint64_t, ll>> extension_memo_cache;

string subtract_one(const string &s) {
    if (s == "0" || s == "1") return "0";
    string t = s;
    int i = (int)t.size() - 1;
    while (i >= 0 && t[i] == '0') {
        t[i] = '9';
        --i;
    }
    if (i >= 0) --t[i];
    if (t[0] == '0' && t.length() > 1) {
        return t.substr(1);
    }
    return t;
}

ll str_mod(const string &s) {
    ll r = 0;
    for (char c : s) r = (r * 10 + (c - '0')) % MOD;
    return r;
}

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

ll modInverse(ll n) {
    return power(n, MOD - 2);
}

void ntt(vector<ll> &a, bool invert) {
    int n = a.size();
    if (n == 1) return;
    
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = power(PRIMITIVE_ROOT, (MOD - 1) / len);
        if (invert) wlen = modInverse(wlen);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i+j], v = (a[i+j+len/2] * w) % MOD;
                a[i+j] = (u + v) % MOD;
                a[i+j+len/2] = (u - v + MOD) % MOD;
                w = (w * wlen) % MOD;
            }
        }
    }
    if (invert) {
        ll n_inv = modInverse(n);
        for (ll &x : a) x = (x * n_inv) % MOD;
    }
}

void precompute_for_k(int K) {
    if (precomputed_totals_cache.count(K)) return;

    int n = 1;
    while (n < 2 * K) n <<= 1;

    vector<vector<ll>> dp(1 << K, vector<ll>(K, 0));
    dp[1][0] = 1;

    vector<ll> T(n, 0);
    for (int digit = 1; digit <= 9; ++digit) {
        T[digit % K]++;
    }
    ntt(T, false);

    vector<ll> total_by_len(K, 0);

    for (int depth = 1; depth < K; ++depth) {
        vector<vector<ll>> next_dp(1 << K, vector<ll>(K, 0));
        
        for (int mask = 1; mask < (1 << K); ++mask) {
            if (__builtin_popcount(mask) != depth) continue;

            vector<ll> p(n, 0);
            bool has_data = false;
            for (int sum = 0; sum < K; ++sum) {
                if (dp[mask][sum] > 0) {
                    p[sum] = dp[mask][sum];
                    has_data = true;
                }
            }
            if (!has_data) continue;

            ntt(p, false);
            for (int i = 0; i < n; ++i) {
                p[i] = (p[i] * T[i]) % MOD;
            }
            ntt(p, true);

            for (int i = K; i < n; ++i) {
                p[i % K] = (p[i % K] + p[i]) % MOD;
            }

            for (int next_sum = 0; next_sum < K; ++next_sum) {
                if (!((mask >> next_sum) & 1) && p[next_sum] > 0) {
                    int new_mask = mask | (1 << next_sum);
                    next_dp[new_mask][next_sum] = (next_dp[new_mask][next_sum] + p[next_sum]) % MOD;
                    total_by_len[depth] = (total_by_len[depth] + p[next_sum]) % MOD;
                }
            }
        }
        
        for (int mask = 0; mask < (1 << K); ++mask) {
            for (int sum = 0; sum < K; ++sum) {
                dp[mask][sum] = (dp[mask][sum] + next_dp[mask][sum]) % MOD;
            }
        }
    }
    
    vector<ll> cumulative(K, 0);
    for (int i = 1; i < K; ++i) {
        cumulative[i] = (cumulative[i-1] + total_by_len[i]) % MOD;
    }
    precomputed_totals_cache[K] = move(cumulative);
}

ll count_extensions(int rem_len, int current_sum, uint32_t mask, int K) {
    if (rem_len == 0) return 1;
    
    uint64_t key = ((uint64_t)rem_len << 32) | ((uint64_t)current_sum << 25) | mask;
    
    auto &cache = extension_memo_cache[K];
    if (cache.count(key)) return cache[key];
    
    ll count = 0;
    for (int d = 1; d <= 9; ++d) {
        int next_sum = (current_sum + d) % K;
        if (!((mask >> next_sum) & 1u)) {
            count = (count + count_extensions(rem_len - 1, next_sum, mask | (1u << next_sum), K)) % MOD;
        }
    }
    return cache[key] = count;
}

ll count_nonweak_le(const string &N_str, int k) {
    if (N_str == "0") return 0;
    
    const auto &cum = precomputed_totals_cache.at(k);
    int len = (int)N_str.size();
    if (len >= k) return cum[k-1];
    
    ll ans = cum[len-1];
    uint32_t mask = 1u;
    int current_sum = 0;
    
    for (int pos = 0; pos < len; ++pos) {
        int limit = N_str[pos] - '0';
        
        for (int d = 1; d < limit; ++d) {
            int next_sum = (current_sum + d) % k;
            if (!((mask >> next_sum) & 1u)) {
                int rem = len - pos - 1;
                ans = (ans + count_extensions(rem, next_sum, mask | (1u << next_sum), k)) % MOD;
            }
        }
        
        int d = limit;
        if (d == 0) break;
        
        current_sum = (current_sum + d) % k;
        if ((mask >> current_sum) & 1u) break;
        
        mask |= (1u << current_sum);
        
        if (pos == len - 1) {
            ans = (ans + 1) % MOD;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int tc = 1; tc <= T; ++tc) {
        string L, R;
        int K;
        cin >> L >> R >> K;
        
        precompute_for_k(K);
        
        string Lm1 = subtract_one(L);
        
        extension_memo_cache[K].clear();
        ll nonweakR = count_nonweak_le(R, K);
        
        extension_memo_cache[K].clear();
        ll nonweakL1 = count_nonweak_le(Lm1, K);

        ll total_in_range = (str_mod(R) - str_mod(Lm1) + MOD) % MOD;
        ll nonweak_in_range = (nonweakR - nonweakL1 + MOD) % MOD;
        ll weak = (total_in_range - nonweak_in_range + MOD) % MOD;
        
        cout << "Case #" << tc << ": " << weak << '\n';
    }
    
    return 0;
}
