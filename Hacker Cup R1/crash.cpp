#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int case_num) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    vector<int> a_indices;
    vector<int> b_indices;
    
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') {
            a_indices.push_back(i);
        } else {
            b_indices.push_back(i);
        }
    }
    
    int p = a_indices.size();
    int q = b_indices.size();
    
    if (p == 0) {
        cout << "Case #" << case_num << ": Bob" << endl;
        return;
    }
    if (q == 0) {
        cout << "Case #" << case_num << ": Alice" << endl;
        return;
    }
    
    int k = 0;
    int limit = min(p, q);
    for (int i = 1; i <= limit; ++i) {
        if (a_indices[i - 1] < b_indices[q - i]) {
            k = i;
        } else {
            break;
        }
    }
    
    if (p > k) {
        cout << "Case #" << case_num << ": Alice" << endl;
    } else {
        cout << "Case #" << case_num << ": Bob" << endl;
    }
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