#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 2000000000;

int main() {
    ifstream fin("dijkstra.in");
    ofstream fout("dijkstra.out");

    int n, m;
    if (!(fin >> n >> m)) return 0;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (dist[i] == INF) {
            fout << 0 << " ";
        } else {
            fout << dist[i] << " ";
        }
    }
    fout << "\n";

    return 0;
}