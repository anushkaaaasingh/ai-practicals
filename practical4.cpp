#include <bits/stdc++.h>
using namespace std;
int n, m;
int evaluate(vector<int>& assignment, vector<vector<int>>& clauses) {
int count = 0;
for (auto &clause : clauses) {
bool satisfied = false;
for (int x : clause) {
int var = abs(x);
if (x > 0 && assignment[var])
satisfied = true;
if (x < 0 && !assignment[var])
satisfied = true;
}
if (satisfied)
count++;
}
return count;
}
int main() {
srand(time(0));
cout << "Enter number of variables: ";
cin >> n;
cout << "Enter number of clauses: ";
cin >> m;
vector<vector<int>> clauses(m, vector<int>(3));
cout << "Enter each clause using 3 integers:\n";
cout << "Example: 1 -2 3 means (x1 OR !x2 OR x3)\n";
for (int i = 0; i < m; i++) {
cin >> clauses[i][0]
>> clauses[i][1]
>> clauses[i][2];
}
vector<int> assignment(n + 1);
for (int i = 1; i <= n; i++)
assignment[i] = rand() % 2;
int current = evaluate(assignment, clauses);
while (current < m) {
vector<int> improving;
for (int i = 1; i <= n; i++) {
assignment[i] = !assignment[i];
int newScore = evaluate(assignment, clauses);
if (newScore > current)
improving.push_back(i);
assignment[i] = !assignment[i];
}
if (improving.empty()) {
cout << "\nStuck at local maximum.\n";
cout << "Satisfied clauses: " << current << "/" << m << endl;
return 0;
}
int chosen = improving[rand() % improving.size()];
assignment[chosen] = !assignment[chosen];
current = evaluate(assignment, clauses);
}
cout << "\nSATISFIABLE\n";
cout << "Assignment:\n";
for (int i = 1; i <= n; i++)
cout << "x" << i << " = " << (assignment[i] ? "True" : "False") << endl;
cout << "Satisfied clauses: " << current << "/" << m << endl;
return 0;
}