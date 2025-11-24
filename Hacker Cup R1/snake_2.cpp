#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool canVisitAll(vector<long long>& A, long long h) {
    int n = A.size();
    vector<bool> visited(n, false);
    
    for (int start = 0; start < n; start++) {
        if (visited[start]) continue;
        if (A[start] > h) continue;
        
        visited[start] = true;
        
        for (int i = start; i < n - 1; i++) {
            if (abs(A[i] - A[i+1]) <= h) {
                visited[i+1] = true;
            } else {
                break;
            }
        }
        for (int i = start; i > 0; i--) {
            if (abs(A[i] - A[i-1]) <= h) {
                visited[i-1] = true;
            } else {
                break;
            }
        }
    }
    
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        
        vector<long long> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        
        long long left = 0, right = 1e9;
        long long answer = right;
        while (left <= right) {
            long long mid = (left + right) / 2;
            
            if (canVisitAll(A, mid)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        cout << "Case #" << tc << ": " << answer << endl;
    }
    
    return 0;
}