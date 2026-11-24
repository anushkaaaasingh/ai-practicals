#include <bits/stdc++.h>
using namespace std;
vector<int> goal = {1,2,3,4,5,6,7,8,0};
bool dfs(vector<int> state, int depth, int limit,
vector<vector<int>>& path,
set<vector<int>>& visited) {
if (state == goal)
return true;
if (depth == limit)
return false;
int pos = find(state.begin(), state.end(), 0)
- state.begin();
int row = pos / 3;
int col = pos % 3;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
for (int i = 0; i < 4; i++) {
int r = row + dr[i];
int c = col + dc[i];
if (r >= 0 && r < 3 && c >= 0 && c < 3) {
vector<int> next = state;
swap(next[pos], next[r * 3 + c]);
if (!visited.count(next)) {
visited.insert(next);
path.push_back(next);
if (dfs(next, depth + 1, limit,
path, visited))
return true;
path.pop_back();
visited.erase(next);
}
}
}
return false;
}

bool DFID(vector<int> start) {
for (int limit = 0; limit <= 31; limit++) {
vector<vector<int>> path;
set<vector<int>> visited;
path.push_back(start);
visited.insert(start);
if (dfs(start, 0, limit, path, visited)) {
cout << "Solution Found!\n";
cout << "Number of moves: "
<< path.size() - 1 << endl;
for (int i = 0; i < path.size(); i++) {
cout << "Step " << i << ":\n";
for (int j = 0; j < 9; j++) {
cout << path[i][j] << " ";
if (j % 3 == 2) cout << endl;
}
}
return true;
}
}
cout << "No solution found!\n";
return false;
}
int main() {
vector<int> start = {
1, 2, 3,
4, 0, 6,
7, 5, 8
};
DFID(start);
return 0;
}