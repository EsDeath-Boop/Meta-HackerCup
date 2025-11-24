#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

void solve() {
    long long N;
    int K, M;
    std::cin >> N >> K >> M;

    std::vector<std::vector<int>> routes(M);
    std::vector<std::vector<std::pair<int, int>>> court_to_routes(N + 1);

    for (int i = 0; i < M; ++i) {
        int l;
        std::cin >> l;
        routes[i].resize(l);
        for (int j = 0; j < l; ++j) {
            std::cin >> routes[i][j];
            court_to_routes[routes[i][j]].push_back({i, j});
        }
    }

    std::vector<long long> D(N + 1, -1);

    if (N > 0) {
        D[1] = 0;
    }

    std::vector<int> q_curr;
    if (N > 0) {
        q_curr.push_back(1);
    }
    
    long long d = 0;

    while (!q_curr.empty()) {
        std::vector<int> q_next;
        
        std::vector<int> active_routes_vec;
        std::vector<bool> is_route_active(M, false);
        for (int u : q_curr) {
            for (auto const& p : court_to_routes[u]) {
                if (!is_route_active[p.first]) {
                    is_route_active[p.first] = true;
                    active_routes_vec.push_back(p.first);
                }
            }
        }

        for (int route_id : active_routes_vec) {
            int furthest_reach = -1;
            int route_len = routes[route_id].size();

            for (int j = 0; j < route_len; ++j) {
                int current_court = routes[route_id][j];
                
                if (D[current_court] == d) {
                    furthest_reach = std::max(furthest_reach, j + K);
                }

                if (j <= furthest_reach) {
                    if (D[current_court] == -1) {
                        D[current_court] = d + 1;
                        q_next.push_back(current_court);
                    }
                }
            }
        }
        
        q_curr = q_next;
        d++;
    }

    long long final_sum = 0;
    for (long long i = 1; i <= N; ++i) {
        final_sum += D[i] * i;
    }
    std::cout << final_sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int T;
    std::cin >> T;
    for (int i = 1; i <= T; ++i) {
        std::cout << "Case #" << i << ": ";
        solve();
        std::cout << "\n";
    }
    return 0;
}
