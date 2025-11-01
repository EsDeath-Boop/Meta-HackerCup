#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void solve(int case_num) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    vector<int> prefix_xor(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_xor[i + 1] = prefix_xor[i] ^ a[i];
    }

    unordered_map<int, long long> counts;
    for (int i = 0; i <= n; ++i) {
        counts[prefix_xor[i]]++;
    }

    long long total_len_sum = (long long)n * (n + 1) * (n + 2) / 6;
    long long num_pairs = 0;
    long long num_triplets = 0;

    for (unordered_map<int, long long>::iterator it = counts.begin(); 
         it != counts.end(); ++it) {
        long long count = it->second;
        
        if (count >= 2) {

            num_pairs += count * (count - 1) / 2;
        }
        if (count >= 3) {

            num_triplets += count * (count - 1) * (count - 2) / 6;
        }
    }

    long long total_cost = total_len_sum - num_pairs - num_triplets;
    cout << "Case #" << case_num << ": " << total_cost << endl;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}