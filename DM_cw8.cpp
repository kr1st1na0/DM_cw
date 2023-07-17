#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define all(x) (x).begin(), (x).end()

using namespace std;

const int INF = 1e9;

void generateDotFile(const vector<int>& path, int vertNum) {
    ofstream file("path.dot");
    if (!file.is_open()) {
        cout << "Failed to open path.dot file." << endl;
        return;
    }

    file << "digraph {" << endl;
    // Задаем круги для вершин и заполняем цветом
    file << "node [shape = circle,\nstyle = filled,]" << endl;

    // Запись вершин графа
    file << path[0] + 1 << " [fillcolor=brown1];" << endl;
    for (int i = 1; i < vertNum; i++) {
        file << "  " << path[i] + 1 << ";" << endl;
    }

    // Запись ребер графа
    for (int i = 0; i < vertNum; i++) {
        file << "  " << path[i] + 1 << " -> " << path[i + 1] + 1 << ";" << endl;
    }
    file << "}" << endl;

    file.close();
}

// Travelling salesman problem function
int tsp(vector<vector<int>>& graph, int vertNum, int start, vector<int>& path) {
    vector<int> vertex; // Вектор индексов всех вершин без стартовой
    for (int i = 0; i < vertNum; ++i) {
        if (i != start)
            vertex.push_back(i);
    }

    int minPathLength = INF;
    bool flag = true;
    do {
        int currentPathLength = 0;
        int k = start;
        // Вычисляем длину пути текущей перестановки
        for (int i = 0; i < vertex.size(); ++i) {
            if (graph[k][vertex[i]] == 0) {
                flag = false;
                break;
            }
            currentPathLength += graph[k][vertex[i]];
            k = vertex[i];
        }
        if (!flag) {
            break;
        }
        currentPathLength += graph[k][start];
        if (graph[k][start] == 0) {
                flag = false;
                break;
            } 
        // Проверяем минимален ли путь и, если да, то записываем его 
        if (currentPathLength < minPathLength) {
            minPathLength = currentPathLength;
            path.clear();
            path.push_back(start);
            for (int i = 0; i < vertex.size(); ++i)
                path.push_back(vertex[i]);
            path.push_back(start);
        }
    } while (next_permutation(all(vertex)));
    if (flag) {
        return minPathLength;
    }
    else {
        return INF;
    }
}

int main() {
    int vertNum;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertNum;

    vector<vector<int>> graph(vertNum, vector<int>(vertNum));
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < vertNum; ++i) {
        for (int j = 0; j < vertNum; ++j) {
            cin >> graph[i][j];
        }
    }

    int start;
    cout << "Enter the starting vertex: ";
    cin >> start;
    --start;

    vector<int> path;
    int minPathLength = tsp(graph, vertNum, start, path);
    if (minPathLength == INF) {
        cout << "There is no Hamiltonian path" << endl;
    }
    else {
        cout << "Minimum path length: " << minPathLength << endl;
        cout << "Path: ";
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] + 1 << " ";
        cout << endl;

        generateDotFile(path, vertNum);
        system("dot -Tpng path.dot -o path.png");
    }

    return 0;
}