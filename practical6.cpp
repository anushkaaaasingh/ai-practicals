#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> graph;
map<string, int> cost;
map<string, int> heuristic;

// AO* Algorithm
int AOStar(string node) {

    // Terminal node
    if (graph[node].empty())
        return heuristic[node];

    int bestCost = INT_MAX;

    // Check each possible alternative
    for (auto group : graph[node]) {

        int total = 0;

        // AND relationship
        for (auto child : group) {
            total += cost[child] + AOStar(child);
        }

        // Select minimum-cost alternative
        bestCost = min(bestCost, total);
    }

    heuristic[node] = bestCost;

    return bestCost;
}

int main() {

    // Define AND-OR graph
    graph["A"] = {{"B", "C"}, {"D"}};
    graph["B"] = {{"E"}, {"F"}};
    graph["C"] = {};
    graph["D"] = {};
    graph["E"] = {};
    graph["F"] = {};

    // Edge costs
    cost["B"] = 1;
    cost["C"] = 1;
    cost["D"] = 1;
    cost["E"] = 1;
    cost["F"] = 1;

    // Initial heuristic values
    heuristic["A"] = 0;
    heuristic["B"] = 2;
    heuristic["C"] = 2;
    heuristic["D"] = 5;
    heuristic["E"] = 2;
    heuristic["F"] = 2;

    int result = AOStar("A");

    cout << "AO* Search Result: " << endl;
    cout << "Minimum Cost: " << result << endl;

    return 0;
}