#include <bits/stdc++.h>
using namespace std;
// Evaluate number of satisfied clauses
int evaluate(vector<int>& assignment,
vector<vector<int>>& clauses) {
int satisfied = 0;
for (auto clause : clauses) {
bool result = false;
for (int literal : clause) {
int var = abs(literal) - 1;
if (literal > 0 && assignment[var] == 1)
result = true;
if (literal < 0 && assignment[var] == 0)
result = true;
}
if (result)
satisfied++;
}
return satisfied;
}
// Generate neighbourhood
vector<vector<int>> getNeighbourhood(
vector<int> assignment, int k) {
vector<vector<int>> neighbours;
int n = assignment.size();
if (k == 1) {
for (int i = 0; i < n; i++) {
vector<int> next = assignment;
next[i] = 1 - next[i];
neighbours.push_back(next);
}
}

else if (k == 2) {
for (int i = 0; i < n; i++) {
for (int j = i + 1; j < n; j++) {
vector<int> next = assignment;
next[i] = 1 - next[i];
next[j] = 1 - next[j];
neighbours.push_back(next);
}
}
}
return neighbours;
}
void VND(vector<int> assignment,
vector<vector<int>>& clauses) {
int k = 1;
int maxK = 2;
while (k <= maxK) {
int currentScore = evaluate(assignment, clauses);
int bestScore = currentScore;
vector<int> bestAssignment = assignment;
vector<vector<int>> neighbours =
getNeighbourhood(assignment, k);
for (auto neighbour : neighbours) {
int score = evaluate(neighbour, clauses);
if (score > bestScore) {
bestScore = score;
bestAssignment = neighbour;
}
}
if (bestScore > currentScore) {
assignment = bestAssignment;
k = 1;
}
else {
k++;
}
}
cout << "\nFinal Assignment:\n";
for (int i = 0; i < assignment.size(); i++)
cout << "x" << i + 1 << " = "
<< assignment[i] << endl;
int satisfied = evaluate(assignment, clauses);
cout << "\nSatisfied Clauses: "
<< satisfied << "/" << clauses.size();
if (satisfied == clauses.size())
cout << "\n3-SAT Solution Found!";
else
cout << "\nLocal Optimum Reached.";
cout << endl;
}
int main() {
int n, m;
cout << "Enter number of variables: ";
cin >> n;
cout << "Enter number of clauses: ";
cin >> m;
vector<vector<int>> clauses(m, vector<int>(3));
cout << "Enter clauses (negative numbers for NOT):\n";
for (int i = 0; i < m; i++) {
for (int j = 0; j < 3; j++)
cin >> clauses[i][j];
}
vector<int> assignment(n, 0);
cout << "\nInitial Assignment:\n";
for (int i = 0; i < n; i++)
cout << "x" << i + 1 << " = 0\n";
VND(assignment, clauses);
return 0;
}