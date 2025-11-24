#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int MAX_EXP_K = 60;

ll fact[MAX_EXP_K + 5];
ll invFact[MAX_EXP_K + 5];

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

ll modInverse(ll n) {
    return power(n, MOD - 2);
}

void precompute_factorials() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= MAX_EXP_K; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

ll combinations(ll n, int k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    if (k > MAX_EXP_K) return 0;

    ll numerator = 1;
    for (int i = 0; i < k; i++) {

        numerator = (numerator * ((n - i) % MOD)) % MOD;
    }
    return (numerator * invFact[k]) % MOD;
}

ll N_val;
vector<pair<ll, int>> b_factors;
ll sum_result;
ll limit_for_divisors;

void sum_ways_over_divisors(int factor_idx, ll current_D, ll current_ways_prod) {
    if (factor_idx == b_factors.size()) {
        sum_result = (sum_result + current_ways_prod) % MOD;
        return;
    }

    ll p = b_factors[factor_idx].first;
    int e = b_factors[factor_idx].second;

    ll p_power_f = 1;
    for (int f = 0; f <= e; f++) {

        if (current_D > limit_for_divisors / p_power_f) {
            break;
        }

        ll next_D = current_D * p_power_f;
        if (next_D > limit_for_divisors) break;

        ll ways_D = combinations(N_val + f - 1, f);

        ll ways_BD = combinations(N_val + (e - f) - 1, e - f);
        ll ways_prime = (ways_D * ways_BD) % MOD;

        sum_ways_over_divisors(factor_idx + 1, next_D, (current_ways_prod * ways_prime) % MOD);
        
        if (f < e && p_power_f <= limit_for_divisors / p) {
            p_power_f *= p;
        } else {
            break;
        }
    }
}

void solve(int case_num) {
    ll A_val, B_val;
    cin >> N_val >> A_val >> B_val;

    b_factors.clear();
    ll temp_B = B_val;
    for (ll i = 2; i * i <= temp_B; i++) {
        if (temp_B % i == 0) {
            int count = 0;
            while (temp_B % i == 0) {
                temp_B /= i;
                count++;
            }
            b_factors.push_back({i, count});
        }
    }
    if (temp_B > 1) {
        b_factors.push_back({temp_B, 1});
    }

    ll total_ways = 1;
    for (const auto& factor : b_factors) {
        int e = factor.second;
        
        total_ways = (total_ways * combinations(2 * N_val + e - 1, e)) % MOD;
    }

    ll bad_ways = 0;
    if (A_val < B_val) {
        limit_for_divisors = (B_val - 1) / A_val;
        sum_result = 0;
        if (limit_for_divisors > 0) {
            sum_ways_over_divisors(0, 1, 1);
        }
        bad_ways = sum_result;
    }

    ll ans = (total_ways - bad_ways + MOD) % MOD;
    cout << "Case #" << case_num << ": " << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_factorials();

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}