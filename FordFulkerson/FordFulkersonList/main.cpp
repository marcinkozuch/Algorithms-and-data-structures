#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 30000;

int nodes;
int edges;
int start;
int sink;
int MaxFlow;
int* trace;
int** c;
int** fc;

void BFS(){
    int i, j;
    queue<int> q;
    for(int i=0;i<nodes;i++)
    {
        trace[i] = 0;
    }
    q.push(start);
    trace[start] = -1;
    while (!q.empty()){
        i = q.front();
        q.pop();
        for (j = 1; j <= nodes; j++)
            if ((trace[j] == 0) && (c[i][j] > fc[i][j])){
                q.push(j);
                trace[j] = i;
                if (j == sink) return;
            }
    }
}

void IncrementFlow(){
    int u, v, delta;
    delta = MAX;
    v = sink;
    while (v != start){
        u = trace[v];
        delta = min(delta, c[u][v] - fc[u][v]);
        v = u;
    }
    v = sink;
    while (v != start){
        u = trace[v];
        fc[u][v] += delta;
        fc[v][u] -= delta;
        v = u;
    }
    MaxFlow += delta;
}

void solveFordFulkersonList(const char *file)
{
    cout << "Ford-Fulkerson - list representation" << endl;

    ifstream input;
    input.open(file);

    input >> nodes >> edges >> start >> sink;

    c = new int*[nodes];
    for(int i=0;i<nodes;i++)
    {
        c[i] = new int[nodes];
        for(int j=0;j<nodes;j++)
        {
            c[i][j]=0;
        }
    }

    for(int i=0;i<nodes;i++)
    {
        int u, v, w;
        input >> u >> v >> w;
        c[u][v] = w;
        c[v][u] = w;
    }
    input.close();

    cout << "nodes: " << nodes;
    cout << endl;

    fc = new int*[nodes];
    for(int i=0;i<nodes;i++)
    {
        fc[i] = new int[nodes];
        for(int j=0;j<nodes;j++)
        {
            fc[i][j] = 0;
        }
    }
    MaxFlow = 0;

    trace  = new int[nodes];
    while (true){
        BFS();
        if (trace[sink] == 0) break;
        IncrementFlow();
    }
    cout << "maxflow: " << MaxFlow << endl;
}

int main(int argc, const char *argv[])
{
    solveFordFulkersonList("table.txt");
}
