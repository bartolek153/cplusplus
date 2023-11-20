#include <iostream>

using namespace std;

struct node {
  int data;
  node *next;
};

// node "constructor" definitions
node *initNode(int key) {
  node *result = new node;
  result->data = key;
  result->next = nullptr;

  return result;
}

class LinkedList {
  node *head;
  node *searchRecursive(node *, int);

public:
  LinkedList();
  LinkedList(int);
  ~LinkedList();

  node *push(int);
  node *append(int);
  node *insertAfter(int, node *);

  node *searchIterative(int);
  node *searchRecursive(int);

  void prettyPrint();
};

// Singly Linked List constructor definition
LinkedList::LinkedList() : head(nullptr) {}
LinkedList::LinkedList(int data) { head = initNode(data); }

//
// data manipulation
//
node *LinkedList::push(int newData) {

  node *newNode = initNode(newData);
  newNode->next = this->head;

  // move the head to point to
  // the new node
  this->head = newNode;

  return newNode;
}

node *LinkedList::insertAfter(int newData, node *prev_node) {

  // check if the given prev_node is NULL
  if (prev_node == NULL) {
    cout << "The given previous node cannot be NULL";
    return nullptr;
  }

  node *newNode = initNode(newData);

  // make next of new node as next of prev_node
  newNode->next = prev_node->next;

  // move the next of prev_node as new_node
  prev_node->next = newNode;

  return newNode;
}

node *LinkedList::append(int newData) {
  node *newNode = initNode(newData);
  node *last = this->head;

  if (this->head == NULL) { // if the list is empty,
    this->head = newNode;   // make new node as head
    return nullptr;
  }

  while (last->next != NULL) {
    last = last->next;
  }

  last->next = newNode;

  return newNode;
}

//
// searching
//
node *LinkedList::searchIterative(int data) {
  for (node *i = head; i != NULL; i = i->next)
    if (i->data == data) {
      printf("Found node(%d): [%d|%p]\n", i->data, i->data, i);
      return i;
    }

  printf("Could not find node(%d).\n", data);
  return nullptr;
}

node *LinkedList::searchRecursive(int data) {
  return searchRecursive(head, data);
}

node *LinkedList::searchRecursive(node *current, int data) {
  if (current == NULL) {
    printf("Could not find node(%d) recursively.\n", data);
    return nullptr;
  }

  if (current->data == data) {
    printf("Found node(%d) recursively: [%d|%p]\n", current->data, current->data, current);
    return current;
  }

  return searchRecursive(current->next, data);
}

//
// displaying
//
void LinkedList::prettyPrint() {

  node *temp = head;

  // Check for empty list.
  if (head == NULL) {
    cout << "List is empty." << endl;
    return;
  }

  int indexCount = 1;

  cout << endl << "HEAD\n";
  cout << "[" << temp->data << "]";
  temp = temp->next;

  // Traverse the list.
  while (temp != NULL) {
    cout << "->"
         << "[" << temp->data << "]";
    temp = temp->next;
    indexCount++;
  }

  cout << endl << endl;
  printf("Found %d elements.\n", indexCount);
}

int main() {
  cout << "=======\n Singly Linked List \n=======\n";

  LinkedList *list = new LinkedList(10);

  list->push(5);
  list->push(20);
  list->push(25);

  node *found = list->searchIterative(10);
  node *foundRec = list->searchRecursive(10);

  if (found == foundRec)
    cout << "The algorithms are working nice!";

  list->append(30);
  list->append(40);

  list->prettyPrint();

  return 0;
}
