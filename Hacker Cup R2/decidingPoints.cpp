#include <iostream>

void solve() {
    long long N;
    int M;
    std::cin >> N >> M;
    if (N < M) {
        std::cout << "NO" << std::endl;
        return;
    }
    if (N <= (2LL * M - 2)) {
        std::cout << "YES" << std::endl;
        return;
    }

    if (N % 2 == 0) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;
    for (int i = 1; i <= T; ++i) {
        std::cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}