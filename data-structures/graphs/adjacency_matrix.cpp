#include <iostream>
#include <vector>

using namespace std;

class AMGraph {
private:
  int **matrix; // int matrix
  int n;        // number of vertices
  int edges;    // number of edges

  bool isConnected(int, int);

public:
  AMGraph(int);
  ~AMGraph();

  void addEdge(int, int); // add an edge to the graph
  void deleteEdge(int, int);
  void prettyPrint();
};

AMGraph::AMGraph(int size) : edges(0) {
  n = size >= 2 ? size : 2;

  matrix = new int *[n];

  for (int i = 0; i < n; i++)
    matrix[i] = new int[n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }
}

AMGraph::~AMGraph() {
  for (int i = 0; i < n; i++)
    delete[] matrix[i];

  delete[] matrix;

  cout << "\nThe graph was destroyed\n";
}

bool AMGraph::isConnected(int x, int y) { return matrix[x - 1][y - 1] == 1; }

void AMGraph::addEdge(int x, int y) {
  if (!isConnected(x, y))
    matrix[x - 1][y - 1] = matrix[y - 1][x - 1] = 1;
  else printf("(%d, %d) are connected already.\n", x, y);

  edges++;
}

void AMGraph::deleteEdge(int x, int y) {
  if (isConnected(x, y))
    matrix[x - 1][y - 1] = matrix[y - 1][x - 1] = 0;
  else printf("(%d, %d) are connected already.\n", x, y);

  edges--;
}

//
// displaying
//
void AMGraph::prettyPrint() {
  cout << endl << "   ";

  for (int i = 0; i < n; i++)
    cout << i+1 << " ";

  for (int i = 0; i < n; i++) {
    cout << endl << i+1 << " [";

    for (int j = 0; j < n; ) {
      cout << matrix[j][i] << (++j < n ? "," : "]");
    }
  }
  
  cout << endl;
}

int main() {

  cout << "\n===========\n Graph (Adjacency Matrix)\n===========\n" << endl;
  // cout << "time complexity: O(log n)\n" << endl;

  AMGraph *graph = new AMGraph(5);

  graph->addEdge(1, 5);
  graph->addEdge(4, 2);
  graph->addEdge(2, 2);
  graph->addEdge(5, 3);
  graph->addEdge(1, 2);
  graph->addEdge(1, 2);
  graph->deleteEdge(3, 5);

  graph->prettyPrint();

  delete graph;

  return 0;
}
