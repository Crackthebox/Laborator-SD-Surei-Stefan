#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream fin("alee.in");
    ofstream fout("alee.out");

    int n, m;
    if (!(fin >> n >> m)) return 0;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        dist[x][y] = -1;
    }

    int startX, startY, endX, endY;
    fin >> startX >> startY >> endX >> endY;

    queue<pair<int, int>> q;
    q.push({startX, startY});
    dist[startX][startY] = 1;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto current = q.front();
        int x = current.first;
        int y = current.second;
        q.pop();

        if (x == endX && y == endY) {
            fout << dist[x][y] << "\n";
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && dist[nx][ny] == 0) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return 0;
}