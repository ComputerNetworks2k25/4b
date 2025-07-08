#include <iostream>
#include <vector>
using namespace std;

#define INF 999

struct RoutingTable {
    vector<int> dist;
    vector<int> nextHop;
};

int main() {
    int N;
    cout << "Enter the number of routers: ";
    cin >> N;

    vector<vector<int>> costMatrix(N, vector<int>(N));

    cout << "Enter the cost matrix (use " << INF << " for no direct connection):\n";
    for (int i = 0; i < N; i++) {
        cout << "From router " << i << " to others:\n";
        for (int j = 0; j < N; j++) {
            cin >> costMatrix[i][j];
        }
    }

    vector<RoutingTable> table(N);

    // Initialize routing tables
    for (int i = 0; i < N; i++) {
        table[i].dist.resize(N);
        table[i].nextHop.resize(N);
        for (int j = 0; j < N; j++) {
            table[i].dist[j] = costMatrix[i][j];
            table[i].nextHop[j] = (costMatrix[i][j] == INF || i == j) ? -1 : j;
        }
    }

    bool updated;

    // Distance Vector Algorithm (Bellman-Ford like)
    do {
        updated = false;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (costMatrix[i][k] != INF && table[k].dist[j] != INF) {
                        int newDist = costMatrix[i][k] + table[k].dist[j];
                        if (newDist < table[i].dist[j]) {
                            table[i].dist[j] = newDist;
                            table[i].nextHop[j] = k;
                            updated = true;
                        }
                    }
                }
            }
        }
    } while (updated);

    // Display final routing tables
    for (int i = 0; i < N; i++) {
        cout << "\nRouter " << i << " routing table:\n";
        cout << "Destination\tCost\tNext Hop\n";
        for (int j = 0; j < N; j++) {
            cout << j << "\t\t";
            if (table[i].dist[j] == INF)
                cout << "INF\t";
            else
                cout << table[i].dist[j] << "\t";
            if (table[i].nextHop[j] == -1)
                cout << "-\n";
            else
                cout << table[i].nextHop[j] << "\n";
        }
        cout << "----------------------------\n";
    }

    return 0;
}
