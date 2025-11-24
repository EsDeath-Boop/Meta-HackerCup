#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

void solve() {
    long long n;
    int m;
    std::cin >> n >> m;

    std::map<int, int> score_counts;
    for (int i = 0; i < n; ++i) {
        int score;
        std::cin >> score;
        score_counts[score]++;
    }

    long long total_merch_units = 0;
    for (int i = 0; i < m; ++i) {
        long long b_val;
        std::cin >> b_val;
        total_merch_units += b_val;
    }

    std::vector<std::pair<int, int>> sorted_scores;
    for (auto const& [score, count] : score_counts) {
        sorted_scores.push_back({score, count});
    }

    long long max_winners = 0;
    long long current_winners_k = 0;
    long long prize_sum_p = 0;
    int prize_levels = 0;

    for (int i = sorted_scores.size() - 1; i >= 0; --i) {
        long long count_c = sorted_scores[i].second;

        prize_levels++;
        prize_sum_p = prize_sum_p + current_winners_k + count_c;
        current_winners_k += count_c;

        if (prize_sum_p <= total_merch_units && prize_levels <= m) {
            max_winners = current_winners_k;
        }
    }
    
    std::cout << max_winners << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
        std::cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
