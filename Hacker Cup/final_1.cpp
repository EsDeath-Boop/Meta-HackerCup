#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int tc = 1; tc <= T; tc++) {
        int N, A, B;
        cin >> N >> A >> B;
        
        vector<int> result(2 * N, 1);

        int P1 = 1;
        for (int d = 1; d <= A; d++) {
            if (B % d == 0) {
                P1 = d;
            }
        }
        
        int P2 = B / P1;
        
        result[N - 1] = P1;
        result[2 * N - 1] = P2;
        
        cout << "Case #" << tc << ":";
        for (int i = 0; i < 2 * N; i++) {
            cout << " " << result[i];
        }
        cout << endl;
    }
    
    return 0;
}