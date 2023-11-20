#include <iostream>

using namespace std;

int matrix[20][20];
int edges = 0;

void displayMatrix(int v, int e) {
  int i, j;
  for (i = 0; i < v; i++) {
    for (j = 0; j < e; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void addEdge(int u, int v) {
  matrix[u][edges] = 1;
  matrix[v][edges] = 1;
  edges++;
}

int main(int argc, char *argv[]) {
  int vertices = 6;
  int edges = 9;

  addEdge(0, 4);
  addEdge(0, 3);
  addEdge(1, 2);
  addEdge(1, 4);
  addEdge(1, 5);
  addEdge(2, 3);
  addEdge(2, 5);
  addEdge(5, 3);
  addEdge(5, 4);
  displayMatrix(vertices, 9);
}
