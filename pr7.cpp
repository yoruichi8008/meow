#include <iostream>
#include <vector>
using namespace std;
class FlightGraph {
int V;
vector<vector<int>> adjMatrix;
vector<string> cities;
public:
FlightGraph(int v) {
V = v;
adjMatrix.resize(V, vector<int>(V, 0));
cities = {"Mumbai", "Delhi", "Chennai", "Kolkata"};
}
void addFlight(int src, int dest, int cost) {
adjMatrix[src][dest] = cost;
adjMatrix[dest][src] = cost;
}
void displayGraph() {
cout << "\nFlight Graph (Adjacency Matrix):\n ";
for (int i = 0; i < V; i++) {
cout << cities[i] << "\t";
}
cout << endl;
for (int i = 0; i < V; i++) {
cout << cities[i] << "\t";
for (int j = 0; j < V; j++) {
cout << adjMatrix[i][j] << "\t";
}
cout << endl;
}
}
void DFS(int v, vector<bool>& visited) {
visited[v] = true;
for (int i = 0; i < V; i++) {
if (adjMatrix[v][i] != 0 && !visited[i]) {
DFS(i, visited);
}
}
}
bool isConnected() {
vector<bool> visited(V, false);
DFS(0, visited);
for (bool v : visited) {
if (!v)
return false;
}
return true;
}
};
int main() {
FlightGraph fg(4);
fg.addFlight(0, 1, 120);
fg.addFlight(0, 2, 150);
fg.addFlight(1, 3, 180);
fg.addFlight(2, 3, 200);
fg.displayGraph();
if (fg.isConnected()) {
cout << "\nThe flight network is connected.\n";
} else {
cout << "\nThe flight network is NOT connected.\n";
}
return 0;
}