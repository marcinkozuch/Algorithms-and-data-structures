#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int u;
    int v;
    int weight;
};
int SIZE;


int* breadthFirstSearchPathMatrix(int **graph, int **f) {
    bool* visited = new bool[SIZE];
    int* path = new int[SIZE];
    queue<int> queue;
    for(int i = 0; i < SIZE; i++) {
        visited[i] = false;
        path[i] = 0;
    }
    path[0] = -1;
    visited[0] = true;

    queue.push(0);
    while(!queue.empty()) {
        int current = queue.front();
        queue.pop();
        for (int next = 0; next < SIZE; next++) {
            if (!visited[next] && graph[current][next] > f[current][next] && graph[current][next] != 0) {
                queue.push(next);
                path[next] = current;
                visited[next] = true;
            }
        }

    }
    cout << visited[SIZE-1] << endl;
    return visited[SIZE-1] != 0 ? path : nullptr;
}

void solveFordFulkersonMatrix(const char* file){
    cout << "Ford-Fulkerson - matrix representation" << endl;
    ifstream input;
    input.open(file);
    int vertices;
    input >> vertices;
    cout << vertices;
    cout << endl;
    SIZE = vertices;
    int** array = new int*[vertices];
    int** f = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        array[i] = new int[vertices];
        f[i] = new int[vertices];
    }
    while(!input.eof()){
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                input >>array[i][j];
                f[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            cout << array[i][j];
            cout << " ";
        }
        cout << endl;
    }
    input.close();

    int flow=10000;
    int maxFlow = 0;
    int* path;
    int u,v;
    path = breadthFirstSearchPathMatrix(array, f);
    while( path != nullptr) {

        for (v = SIZE-1; v != 0; v = path[v]) {
            u = path[v];
            flow = flow < (array[u][v] - f[u][v]) ? flow : (array[u][v] - f[u][v]);
        }

        for (v = SIZE-1; v != 0; v = path[v]) {
            u = path[v];
            f[u][v] += flow;
            f[v][u] -= flow;
        }

        maxFlow += flow;
        path = breadthFirstSearchPathMatrix(array, f);
    }
    cout << "maxflow " << maxFlow << endl;
}


int main( int argc, const char* argv[]){

    solveFordFulkersonMatrix("matrix.txt");

    return 0;
}




