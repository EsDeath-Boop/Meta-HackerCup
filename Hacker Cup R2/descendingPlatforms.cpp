#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;
void solve() {
    int N;
    long long M;
    cin >> N >> M;
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<long long> S(N);
    S[0] = A[0];
    for (int i = 1; i < N; ++i) {
        S[i] = S[i - 1] + A[i];
    }

    int k_best = 0;
    for (int k = 1; k < N; ++k) {
        if (__int128(S[k]) * (k_best + 1) > __int128(S[k_best]) * (k + 1)) {
            k_best = k;
        }
    }

    int dp_limit = 40000;
    if (N > 0) { 
      dp_limit = min(dp_limit, N * (N + 2)); 
    }


    vector<long long> dp(dp_limit + 1, -1);
    vector<int> parent(dp_limit + 1, 0);
    dp[0] = 0;

    for (int c = 1; c <= dp_limit; ++c) {
        for (int k = 0; k < N; ++k) {
            int cost = k + 1;
            if (c >= cost && dp[c - cost] != -1) {
                long long new_amazingness = dp[c - cost] + S[k];
                if (new_amazingness >= dp[c]) {
                    dp[c] = new_amazingness;
                    parent[c] = k;
                }
            }
        }
    }

    long long min_bricks = -1;
    for (int c = 1; c <= dp_limit; ++c) {
        if (dp[c] >= M) {
            min_bricks = c;
            break;
        }
    }
    int window_start = max(1, dp_limit - (N + 1));
    for (int c = window_start; c <= dp_limit; ++c) {
        if (dp[c] == -1) continue;
        long long remaining_M = M - dp[c];
        if (remaining_M > 0) {
            if (S[k_best] <= 0) continue; 
            long long num_best_items = (remaining_M + S[k_best] - 1) / S[k_best];
            long long current_total_bricks = c + num_best_items * (k_best + 1);
            if (min_bricks == -1 || current_total_bricks < min_bricks) {
                min_bricks = current_total_bricks;
            }
        }
    }

    cout << min_bricks << endl;
    vector<long long> d(N, 0);
    if (min_bricks <= dp_limit) {
        int current_c = min_bricks;
        while (current_c > 0) {
            int k = parent[current_c];
            d[k]++;
            current_c -= (k + 1);
        }
    } else {
        long long best_c_start = -1;
        int window_start_recon = max(1, dp_limit - (N+1));
        for (int c = window_start_recon; c <= dp_limit; ++c) {
            if (dp[c] == -1) continue;
            long long remaining_M = M - dp[c];
            if (remaining_M <= 0) continue;
            if (S[k_best] <= 0) continue;
            long long num_best_items = (remaining_M + S[k_best] - 1) / S[k_best];
            if (c + num_best_items * (k_best + 1) == min_bricks) {
                best_c_start = c;
                break;
            }
        }
        
        long long num_best_to_add = (min_bricks - best_c_start) / (k_best + 1);
        d[k_best] += num_best_to_add;
        int current_c = best_c_start;
        while (current_c > 0) {
            int k = parent[current_c];
            d[k]++;
            current_c -= (k + 1);
        }
    }
    vector<long long> x(N);
    if (N > 0) {
        x[N - 1] = d[N - 1];
        for (int i = N - 2; i >= 0; --i) {
            x[i] = x[i + 1] + d[i];
        }
    }
    
    for (int i = 0; i < N; ++i) {
        cout << x[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}