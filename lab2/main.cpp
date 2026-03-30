#include <iostream>
#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();

struct return_type {
    std::vector<std::pair<int, int>> A;
    int suma;
};

return_type DPA(std::vector<std::vector<std::pair<int,int>>> &G, int s) {
    std::vector<std::pair<int, int>> A;
    int suma = 0;
    int n = G.size();
    std::vector<int> alfa(n, -1);
    std::vector<int> beta(n, INF);
    std::vector<bool> visited(n, false);
    beta[s] = 0;
    int u_star = s;

    for (int i = 0; i < n; i++){
        int u = -1;
        int min_val = INF;

        for (int j = 0; j < n; j++){
            if(!visited[j] && beta[j] < min_val){
                min_val = beta[j];
                u = j;
            }
        }
        u_star = u;
        if (u_star == -1) break;

        visited[u_star] = true;

        if (alfa[u_star] != -1) {
            A.push_back({alfa[u_star], u_star});
            suma += beta[u_star];
        }

        for (auto [v, w] : G[u_star]) {
            if (!visited[v] && w < beta[v]) {
                beta[v] = w;
                alfa[v] = u_star;
            }
        }
    }
    return {A, suma};
}

int main() {
    std::vector<std::vector<std::pair<int,int>>> G(4);

    G[0].push_back({1, 2});
    G[1].push_back({0, 2});

    G[0].push_back({2, 3});
    G[2].push_back({0, 3});

    G[1].push_back({2, 1});
    G[2].push_back({1, 1});

    G[1].push_back({3, 4});
    G[3].push_back({1, 4});

    auto [A, suma] = DPA(G, 0);

    std::cout << "Krawedzie MST:\n";
    for (auto [u, v] : A) {
        std::cout << u << " - " << v << "\n";
    }

    std::cout << "Suma: " << suma << std::endl;

    return 0;
}