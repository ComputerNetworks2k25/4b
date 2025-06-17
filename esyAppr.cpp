#include <iostream>
using namespace std;

#define INF 999
#define N 3  

struct RoutingTable {
    int dist[N];
    int nextHop[N];
};

int main() {
    int costMatrix[N][N] = {
        {0, 1, 3},
        {1, 0, 1},
        {3, 1, 0}
    };

    RoutingTable table[N];


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            table[i].dist[j] = costMatrix[i][j];
            table[i].nextHop[j] = j;
        }
    }

    bool updated;

    do {
        updated = false;

        for (int i = 0; i < N; i++) {          
            for (int j = 0; j < N; j++) {      
                for (int k = 0; k < N; k++) { 
                    if (table[i].dist[j] > costMatrix[i][k] + table[k].dist[j]) {
                        table[i].dist[j] = costMatrix[i][k] + table[k].dist[j];
                        table[i].nextHop[j] = k;
                        updated = true;
                    }
                }
            }
        }

    } while (updated);


    for (int i = 0; i < N; i++) {
        cout << "Router " << i << " routing table:\n";
        cout << "Destination\tCost\tNext Hop\n";
        for (int j = 0; j < N; j++) {
            cout << j << "\t\t" << table[i].dist[j] << "\t" << table[i].nextHop[j] << "\n";
        }
        cout << "-------------------------\n";
    }

    return 0;
}
