#include <bits/stdc++.h>
using namespace std;
struct Node {
string state;
int g, h;
string path;
int f() const {
return g + h;
}
};
struct Compare {
bool operator()(const Node& a, const Node& b) {
return a.f() > b.f();
}
};
int heuristic(string state, string goal) {
int h = 0;
for (int i = 0; i < 9; i++) {
if (state[i] != '0' && state[i] != goal[i])
h++;
}
return h;
}
int main() {
string start, goal = "123456780";
cout << "Enter initial state (use 0 for blank):\n";
for (int i = 0; i < 9; i++) {
char x;
cin >> x;
start += x;
}
priority_queue<Node, vector<Node>, Compare> pq;
unordered_set<string> visited;

pq.push({
start,
0,
heuristic(start, goal),
""
});
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
char moves[] = {'U', 'D', 'L', 'R'};
while (!pq.empty()) {
Node current = pq.top();
pq.pop();
if (visited.count(current.state))
continue;
visited.insert(current.state);
if (current.state == goal) {
cout << "\nSolution found!\n";
cout << "Number of moves: " << current.g << endl;
cout << "Moves: " << current.path << endl;
return 0;
}
int zero = current.state.find('0');
int r = zero / 3;
int c = zero % 3;
for (int i = 0; i < 4; i++) {
int nr = r + dr[i];
int nc = c + dc[i];
if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
string next = current.state;
int newZero = nr * 3 + nc;
swap(next[zero], next[newZero]);
if (!visited.count(next)) {
int g = current.g + 1;
int h = heuristic(next, goal);
pq.push({
next,
g,
h,
current.path + moves[i]
});
}
}
}
}
cout << "\nNo solution exists.\n";
return 0;
}