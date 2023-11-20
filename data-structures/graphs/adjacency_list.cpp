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

  void remove(int data) {
    remove(head, data);
  }

  void remove(node* n, int data) {
    if (n == NULL)
      return;
    else if (n->data == data) {
      node* aux = n;
      n = n->next;
      delete aux;
      return;
    }
    remove(n->next, data);
  }

  void print() {
    for (node *i = head; i != NULL; i = i->next) {
      printf("[%d]%s", i->data, (i->next  != NULL ? "->" : ""));
    }
  }
};

class ALGraph {
private:
  LinkedList *vertices; // array of int linked lists
  int n;                // number of vertices
  int edges;            // number of edges

  bool isConnected(int, int);

public:
  ALGraph(int);
  ~ALGraph();

  void addEdge(int, int); // add an edge to the graph
  void deleteEdge(int, int);
  void prettyPrint();
};

ALGraph::ALGraph(int size) : n(size), edges(0) {
  vertices = new LinkedList[n];

  // for (int i = 0; i < n; i++)
  // vertices[i] = new LinkedList;
}

ALGraph::~ALGraph() { cout << "\nThe graph was destroyed\n"; }

bool ALGraph::isConnected(int x, int y) { return vertices[x].search(y); }

// inserts add x-y supposing x and y are int, not equal,
// between 0 and n-1. if edge already exists, does nothing
void ALGraph::addEdge(int x, int y) {
  if (!isConnected(x, y)) {
    vertices[x].push(y);
  }

  edges++;
}

void ALGraph::deleteEdge(int x, int y) {
  if (isConnected(x, y))
    vertices[x].remove(y);

  edges--;
}

//
// displaying
//
void ALGraph::prettyPrint() {
  cout << endl;

  for (int i = 0; i < n; i++) {
    cout << i << " ";
    vertices[i].print();
    cout << endl;
  }
}

int main() {

  cout << "\n===========\n Graph (Adjacency List)\n===========\n" << endl;
  // cout << "time complexity: O(log n)\n" << endl;

  ALGraph graph(5);

  graph.addEdge(1, 3);
  graph.addEdge(1, 3);
  graph.addEdge(4, 2);
  graph.addEdge(2, 2);
  graph.addEdge(4, 3);
  graph.addEdge(1, 2);
  graph.addEdge(4, 3);
  graph.addEdge(4, 4);
  graph.addEdge(4, 5);

  graph.deleteEdge(4, 5);
  // graph.deleteEdge(1, 2);

  graph.prettyPrint();

  return 0;
}
