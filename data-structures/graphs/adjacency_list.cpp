#include <cstdio>
#include <iostream>

using namespace std;

class LinkedList {
  struct node {
    int data;
    node *next;
  };
  node *head;

public:
  LinkedList() : head(nullptr) {}

  void push(int data) {
    node *aux = new node;
    aux->data = data;

    aux->next = head;
    head = aux;
  }

  bool search(int data) {
    for (node *i = head; i != NULL; i = i->next)
      if (i->data == data)
        return true;

    return false;
  }

  void print() {
    for (node *i = head; i != NULL; i = i->next) {
      printf("[%d]%s", i->data, (i->next != NULL ? "->" : ""));
    }
  }
};

class Graph {
private:
  LinkedList *vertices; // array of int linked lists
  int n;                // number of vertices
  int edges;            // number of edges

  bool isConnected(int, int);

public:
  Graph(int);
  ~Graph();

  void addEdge(int, int); // add an edge to the graph
  void deleteEdge(int, int);
  void prettyPrint();
};

Graph::Graph(int size) : n(size), edges(0) { vertices = new LinkedList[n]; }

Graph::~Graph() { cout << "\nThe graph was destroyed\n"; }

bool Graph::isConnected(int x, int y) { return vertices[x].search(y); }

// inserts add x-y supposing x and y are int, not equal,
// between 0 and n-1. if edge already exists, does nothing
void Graph::addEdge(int x, int y) {
  if (!isConnected(x, y)) {
    vertices[x].push(y);
    vertices[y].push(x);
  }

  edges++;
}

//
// displaying
//
void Graph::prettyPrint() {
  cout << endl;

  for (int i = 0; i < n; i++) {
    cout << i << " ";
    vertices[i].print();
    cout << endl;
  }
}

int main() {

  cout << "\n===========\n Graph (Adjacency List)\n===========\n";
  cout << "time complexity: O(n)\n";
  cout << "space complexity: O(n+edges)\n";
  // cout << "time complexity: O(log n)\n" << endl;

  Graph graph(5);

  graph.addEdge(1, 3);
  graph.addEdge(1, 3);
  graph.addEdge(4, 2);
  graph.addEdge(2, 2);
  graph.addEdge(4, 3);
  graph.addEdge(1, 2);
  graph.addEdge(4, 3);
  graph.addEdge(4, 4);
  graph.addEdge(4, 5);

  graph.prettyPrint();

  return 0;
}
