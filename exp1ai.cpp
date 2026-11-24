#include <bits/stdc++.h>
using namespace std;

vector<int> goal = {1,2,3,4,5,6,7,8,0};

vector<vector<int>> generateStates(vector<int> state) {
    vector<vector<int>> states;

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
            states.push_back(next);
        }
    }

    return states;
}

void display(vector<int> state) {
    for (int i = 0; i < 9; i++) {
        cout << state[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
}

void solve(vector<int> start) {
    queue<pair<vector<int>, vector<vector<int>>>> q;
    set<vector<int>> visited;

    q.push({start, {start}});
    visited.insert(start);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        vector<int> state = current.first;
        vector<vector<int>> path = current.second;

        if (state == goal) {
            cout << "Solution Found!\n";
            cout << "Number of moves: "
                 << path.size() - 1 << endl;

            for (int i = 0; i < path.size(); i++) {
                cout << "Step " << i << ":\n";
                display(path[i]);
            }
            return;
        }

        for (auto next : generateStates(state)) {
            if (!visited.count(next)) {
                visited.insert(next);

                vector<vector<int>> newPath = path;
                newPath.push_back(next);

                q.push({next, newPath});
            }
        }
    }

    cout << "No solution found!\n";
}

int main() {
    vector<int> start = {
        1, 2, 3,
        4, 0, 6,
        7, 5, 8
    };

    cout << "Initial State:\n";
    display(start);

    solve(start);

    return 0;
}
