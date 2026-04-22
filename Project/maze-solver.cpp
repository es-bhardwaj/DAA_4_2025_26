#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e8;

vector<vector<int>> solveMaze(int R, int C, vector<vector<int>>& maze, pair<int,int> src, vector<vector<pair<int,int>>>& parent) {
    vector<vector<int>> dist(R, vector<int>(C, INF));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    dist[src.first][src.second] = 0;
    pq.push({0, {src.first, src.second}});

    int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};

    while (!pq.empty()) {
        int d = pq.top().first;
        int r = pq.top().second.first;
        int c = pq.top().second.second;
        pq.pop();

        if (d > dist[r][c]) continue;

        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && maze[nr][nc] == 0) {
                if (dist[r][c] + 1 < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[nr][nc] = {r, c};
                    pq.push({dist[nr][nc], {nr, nc}});
                }
            }
        }
    }
    return dist;
}

int main() {
    int R, C;
    cout << "Enter rows and columns: ";
    cin >> R >> C;

    vector<vector<int>> maze(R, vector<int>(C));
    cout << "Enter maze (0=path, 1=wall):\n";
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) cin >> maze[i][j];

    int startR, startC, endR, endC;
    cout << "\nEnter Start Point (row col): ";
    cin >> startR >> startC;
    cout << "Enter End Point (row col): ";
    cin >> endR >> endC;

    if(startR < 0 || startR >= R || startC < 0 || startC >= C || 
       endR < 0 || endR >= R || endC < 0 || endC >= C || 
       maze[startR][startC] == 1 || maze[endR][endC] == 1) {
        cout << "Invalid Start or End point. Points must be within boundaries and NOT walls (1)." << endl;
        return 0;
    }

    pair<int, int> src = {startR, startC};
    pair<int, int> dest = {endR, endC};

    vector<vector<pair<int, int>>> parent(R, vector<pair<int, int>>(C, {-1, -1}));
    vector<vector<int>> dists = solveMaze(R, C, maze, src, parent);

    if (dists[dest.first][dest.second] == INF) {
        cout << "\nNo path found between the selected points." << endl;
        return 0;
    }

    vector<vector<char>> display(R, vector<char>(C));
    for(int i=0; i<R; i++) 
        for(int j=0; j<C; j++) display[i][j] = (maze[i][j] == 1) ? '#' : '.';

    pair<int, int> curr = dest;
    while (curr.first != -1) {
        display[curr.first][curr.second] = '*';
        curr = parent[curr.first][curr.second];
    }
    display[src.first][src.second] = 'S';
    display[dest.first][dest.second] = 'E';

    cout << "\nMaze Solution (S=Start, E=End, *=Path, #=Wall):\n";
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) cout << display[i][j] << " ";
        cout << endl;
    }

    return 0;
}