#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        
        int maxDiff = 0;
        for (int i = 0; i < N - 1; i++) {
            maxDiff = max(maxDiff, abs(A[i] - A[i + 1]));
        }
        
        cout << "Case #" << tc << ": " << maxDiff << endl;
    }
    
    return 0;
}